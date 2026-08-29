## TPA3128 1SPW modulation pop and static noise issue

**Description:**

Amped-ESP32, Amped-Esparagus and Amped Raspberry Hat boards equipped with the TPA3128 amp exhibit audible pops for a few seconds when exiting the MUTE state, followed by a quiet static/hiss noise from the speakers afterward.

**Impact:**

Every time playback resumes from a paused/muted state, the speakers emit a noticeable pops lasting a few seconds. A faint but audible static noise can also be heard from the speakers during playback afterward. This does not damage the hardware but is annoying in a home listening environment.

**Affected Products:**

- Amped-ESP32, revisions equipped with the TPA3128 amp
- Amped-Esparagus, revisions equipped with the TPA3128 amp
- Amped Raspberry Hat, revisions equipped with the TPA3128 amp

##### Detailed Description

**Issue Details:**

The TPA3128 amp ships from the factory with 1SPW (1-Spread Phase Modulation) as the default modulation mode. While 1SPW is more power-efficient than the alternative BD (Band-Distortion) modulation mode, it is more prone to producing audible pops on state transitions (e.g., exiting MUTE) as well as a quiet static noise during normal playback.

**Detection:**

Users may notice a quiet pops lasting a few seconds every time the amp exits the MUTE state (e.g., resuming playback after a pause), and a faint static/hiss noise from the speakers afterward.

### Resolution/Corrective Action

**Status:**

This issue is fixed permanently on all later board designs, which moved to the TPA3118 amp with modulation hardwired to BD mode.

**Permanent Solution:**

On boards equipped with the TPA3128 amp, you can switch the modulation mode from 1SPW to BD by changing the state of a solder bridge on the back side of the PCB, in the amp area. This eliminates the pops and static noise almost completely.

| Step | Description | Image |
|---|---|---|
| 1 | Locate the modulation-select solder bridge on the back side of the PCB, in the amp area. Cut the "1SPW" solder bridge with a sharp knife. Make sure these no electrical connections are left. | _Photo placeholder_ |
| 2 | Change the solder bridge state to select BD modulation mode instead of the default 1SPW. | _Photo placeholder_ |

**Additional Notes:**

Boards using the TPA3118 amp are not affected, as the modulation mode is hardwired to BD from the factory, along with few extra measures to reduce both pops and Wifi interference noise. See [Amped-ESP32 with TPA3118/TPA3128 amp](/README.md#amped-esp32-with-tpa3118tpa3128-amp) for more background on the TPA3110 → TPA3128 → TPA3118 amp evolution.
