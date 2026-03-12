#!/bin/bash
# Collect squeezelite-esp32 build artifacts into the binaries output folder.
#
# Run manually from inside the ESP-IDF container after a successful build.
# The working directory should be the squeezelite-esp32 source root.
#
# Environment variables (set automatically by VS Code tasks or override manually):
#   IDF_TARGET         - chip target: esp32 or esp32s3  (injected by task)
#   DEPTH              - bit depth: 16 or 32            (default: 16)
#   TARGET_BUILD_NAME  - build name prefix              (default: I2S-4MFlash)

set -euo pipefail

DEPTH="${DEPTH:-16}"
IDF_TARGET="${IDF_TARGET:-esp32}"
TARGET_BUILD_NAME="${TARGET_BUILD_NAME:-I2S-4MFlash}"
COMMIT_ID="${COMMIT_ID:-a71aff68}"

BUILD_DIR="$(pwd)/build"

if [ ! -d "${BUILD_DIR}" ]; then
    echo "ERROR: Build directory not found: ${BUILD_DIR}"
    echo "Run from the squeezelite-esp32 source root after a successful build."
    exit 1
fi

FOLDER_NAME="${TARGET_BUILD_NAME}-sdkconfig.${IDF_TARGET}-${DEPTH}bit"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
OUT_DIR="${SCRIPT_DIR}/${FOLDER_NAME}"

echo "Collecting artifacts"
echo "  Build name : ${FOLDER_NAME}"
echo "  Commit     : ${COMMIT_ID}"
echo "  Source     : ${BUILD_DIR}"
echo "  Output     : ${OUT_DIR}"
echo ""

mkdir -p "${OUT_DIR}"

copy_artifact() {
    local src="$1"
    local name="$2"
    local dest="${OUT_DIR}/${name}-${COMMIT_ID}.bin"
    if [ -f "${src}" ]; then
        cp "${src}" "${dest}"
        echo "  [OK] ${name}-${COMMIT_ID}.bin"
    else
        echo "  [--] ${name} not found, skipping (${src})"
    fi
}

copy_artifact "${BUILD_DIR}/bootloader/bootloader.bin"           "bootloader"
copy_artifact "${BUILD_DIR}/partition_table/partition-table.bin" "partition-table"
copy_artifact "${BUILD_DIR}/ota_data_initial.bin"                "ota_data_initial"
copy_artifact "${BUILD_DIR}/squeezelite.bin"                     "squeezelite"
copy_artifact "${BUILD_DIR}/recovery.bin"                        "recovery"

echo ""
echo "Done. Artifacts written to: ${OUT_DIR}"
