#!/usr/bin/env bash
#
# Flash-and-monitor loop for bench / small-batch board bring-up.
#
#   ./flash-loop.sh <env> [extra pio run args...]
#
# Plug a board in, it gets flashed and its serial log is shown. Unplug it and
# the script goes back to waiting for the next one. Ctrl-C quits.
#
# Assumes a single board is connected at a time; the port is auto-detected.

set -uo pipefail

cd "$(dirname "${BASH_SOURCE[0]}")"

PIO="$(command -v pio || echo "$HOME/.platformio/penv/bin/pio")"
[ -x "$PIO" ] || { echo "error: pio not found (looked for 'pio' on PATH and in ~/.platformio/penv/bin)" >&2; exit 1; }

# PlatformIO's own interpreter - it ships pyserial, used by the no-TTY fallback.
PIO_PYTHON="$(dirname "$PIO")/python"
[ -x "$PIO_PYTHON" ] || PIO_PYTHON="$(command -v python3 || true)"

list_envs() { sed -n 's/^\[env:\(.*\)\]$/  \1/p' platformio.ini; }

ENV_NAME="${1:-}"
if [ -z "$ENV_NAME" ]; then
    echo "usage: $(basename "$0") <env> [extra pio run args...]" >&2
    echo "" >&2
    echo "available environments:" >&2
    list_envs >&2
    exit 2
fi
shift

if ! list_envs | grep -qx "  $ENV_NAME"; then
    echo "error: no [env:$ENV_NAME] in platformio.ini" >&2
    echo "" >&2
    echo "available environments:" >&2
    list_envs >&2
    exit 2
fi

# monitor_speed from [env:<name>], else from [env], else the usual default.
MONITOR_BAUD="$(
    awk -v e="[env:$ENV_NAME]" '
        /^\[/      { in_sec = ($0 == e); in_base = ($0 == "[env]") }
        /^monitor_speed[ \t]*=/ {
            gsub(/^monitor_speed[ \t]*=[ \t]*|[ \t]*$/, "")
            if (in_sec) { specific = $0 } else if (in_base) { base = $0 }
        }
        END { print (specific != "" ? specific : base) }
    ' platformio.ini
)"
[ -n "$MONITOR_BAUD" ] || MONITOR_BAUD=115200

# USB-serial devices only - skips /dev/cu.Bluetooth-Incoming-Port, paired
# headsets, debug-console and friends.
find_port() {
    ls /dev/cu.usbmodem* /dev/cu.usbserial* /dev/cu.wchusbserial* \
       /dev/cu.SLAB_USBtoUART* /dev/ttyUSB* /dev/ttyACM* 2>/dev/null | head -n 1
}

# Waits until a port shows up, then until it stops changing - a board that has
# just been plugged in can enumerate, drop and come back before it settles.
wait_for_port() {
    local port=""
    while [ -z "$port" ]; do
        port="$(find_port)"
        [ -z "$port" ] && sleep 0.3
    done
    sleep 0.7
    port="$(find_port)"
    [ -z "$port" ] && { wait_for_port; return; }
    PORT="$port"
}

wait_for_disconnect() {
    while [ -n "$(find_port)" ]; do sleep 0.5; done
}

trap 'echo ""; echo "stopped after $COUNT board(s)."; exit 0' INT TERM

COUNT=0
echo "env: $ENV_NAME   (Ctrl-C to quit)"

while true; do
    if [ -z "$(find_port)" ]; then
        echo ""
        echo "--- waiting for a board ..."
    fi
    wait_for_port

    COUNT=$((COUNT + 1))
    echo ""
    echo "=== board #$COUNT on $PORT - flashing $ENV_NAME"

    if ! "$PIO" run -e "$ENV_NAME" -t upload --upload-port "$PORT" "$@"; then
        echo "!!! flash FAILED on board #$COUNT - unplug it and try again" >&2
        wait_for_disconnect
        continue
    fi

    # Native-USB parts re-enumerate after the reset that ends an upload, and may
    # come back under a different name, so resolve the port again.
    sleep 0.5
    if [ -z "$(find_port)" ]; then
        echo "--- board re-enumerating ..."
        wait_for_port
    else
        PORT="$(find_port)"
    fi

    echo ""
    echo "=== board #$COUNT flashed OK - monitoring $PORT (unplug for next board)"

    if [ -t 0 ]; then
        # Interactive: pio monitor picks up monitor_speed / monitor_filters from
        # the env, decodes backtraces, and lets you type CLI commands.
        # --no-reconnect is essential here: without it the monitor sits waiting
        # for the same board to come back when you unplug it, and the loop never
        # advances to the next one.
        "$PIO" device monitor -e "$ENV_NAME" --port "$PORT" --no-reconnect || true
    else
        # Output is being redirected (e.g. piped to tee), and pio device monitor
        # refuses to run without a TTY. Log the port read-only instead.
        echo "--- (no TTY: read-only log, CLI input unavailable)"
        "$PIO_PYTHON" -c '
import serial, sys
port, baud = sys.argv[1], int(sys.argv[2])
try:
    s = serial.Serial(port, baud, timeout=1)
except Exception as e:
    sys.exit("cannot open %s: %s" % (port, e))
while True:
    try:
        data = s.read(4096)
    except Exception:
        break          # unplugged
    if data:
        sys.stdout.write(data.decode("utf-8", "replace"))
        sys.stdout.flush()
' "$PORT" "$MONITOR_BAUD" || true
    fi

    wait_for_disconnect
    echo "--- board #$COUNT disconnected"
done
