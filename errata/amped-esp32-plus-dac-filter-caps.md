## Amped-ESP32-Plus muffled sound caused by wrong DAC output filter capacitors

**Description:**

A specific production batch of Amped-ESP32-Plus boards (rev D0 and rev E0, PCM5122 DAC, TPA3118 amp) was assembled with the wrong capacitors in the DAC output filter. Instead of 2.2nF 0805 capacitors, high-value (~22µF) 1206 capacitors were fitted at positions C65 and C73. Together with the 470Ω series resistors, they form a low-pass filter with a cutoff of about 12 Hz, which makes the sound muffled and quiet.

**Impact:**

Sound is noticeably muffled and lacks treble, as if heard through a wall, and overall volume is much lower than expected. At low volume settings (below ~45%), the sound may cut out almost completely. Both the speaker output and the line-out/headphone output are affected, regardless of firmware (ESPHome, Sendspin, Squeezelite) or power source. The issue is in hardware and cannot be fixed with firmware or DSP/EQ settings. It does not damage the board, speakers, or any other components.

**Affected Products:**

- Amped-ESP32-Plus, rev D0 (ESP32), equipped with the TPA3118 amp
- Amped-ESP32-Plus, rev E0 (ESP32-S3), equipped with the TPA3118 amp

Only boards from a specific production batch are affected, not all boards of these revisions. Affected boards were shipped:

| Store | Shipped between |
|---|---|
| Tindie | 24 Oct 2026 – 1 Nov 2026 |
| Lectronz | 24 Oct 2026 – 1 Nov 2026 |
| Elecrow | 15 Oct 2026 – 1 Nov 2026 |

Boards shipped after 1 Nov 2026 have the fix applied before shipping.

##### Detailed Description

**Issue Details:**

The PCM5122 DAC outputs pass through a small RC filter (R34/R35 470Ω with C65/C73 2.2nF, Samsung CL21C222JBFNNNE) that removes out-of-band noise, with a cutoff of about 150 kHz. On the affected batch, a different part was fitted by the assembly house at these positions: a 1206-size capacitor measured at about 22µF. This moves the filter cutoff down to about 12 Hz, so the output falls by ~6 dB per octave across the whole audible band. For example, with a -6 dBFS sine at 100% volume, line-out measures ~0.03 V at 400 Hz instead of the expected ~1 V. The part numbers in the published BOM are correct; the issue was a component mix-up during assembly, and it was confirmed by the manufacturer.

**Detection:**

- Sound is clearly muffled, quiet, and lacking high frequencies on both speaker and line-out/headphone outputs.
- A frequency sweep on line-out shows a steady roll-off of ~6 dB/octave across the whole range.
- Visual check: look at positions C65 and C73. On an affected board, these capacitors are visibly larger (1206 size) than the neighboring 0805 parts and overhang their pads. On a correct board, they are small 0805 parts matching the other capacitors around them.

<img width="591" height="652" alt="image" src="https://github.com/user-attachments/assets/b8fb58a9-f994-4a9a-9367-bfd15fd922b5" />

<img width="566" height="678" alt="image" src="https://github.com/user-attachments/assets/f59fe1cd-7d82-40f2-b1f0-751c916146e0" />

Line-out frequency sweep on an affected board (measured by a community member in [#204](https://github.com/sonocotta/esp32-audio-dock/issues/204)):

<img width="1300" height="715" alt="Line-out frequency sweep on an affected board" src="https://github.com/user-attachments/assets/73c2fd70-9129-47c9-bcf4-96bdda576e6b" />

One of the removed capacitors, measuring ~27µF instead of 2.2nF:

<img width="1230" height="843" alt="Removed capacitor measured at 27uF" src="https://github.com/user-attachments/assets/53c39210-785a-45ae-a7fc-684a607ce603" />

### Resolution/Corrective Action

**Status:**

The root cause is identified and confirmed with the manufacturer. All boards shipped after 1 Nov 2026 are reworked and tested before shipping.

**Permanent Solution:**

Remove capacitors C65 and C73. No replacement part is needed: the TPA3118 amp has its own input filter network, so the board performs as intended without them.

| Step | Description | Image |
|---|---|---|
| 1 | Disconnect power and any connected speakers. Locate C65 and C73 near the PCM5122 DAC (U1). | <img width="915" height="734" alt="image" src="https://github.com/user-attachments/assets/1ca082cf-4ff0-457f-9163-e92f301a7710" /> <img width="773" height="709" alt="image" src="https://github.com/user-attachments/assets/8efb69aa-852d-4f98-aeac-b17fedc049d7" />
| 2 | Remove C65 and C73 with hot tweezers or two soldering irons. Alternatively, heat one side with a soldering iron and gently lift or twist the capacitor off. Take care not to lift the pads or disturb neighboring parts. | <img width="672" height="584" alt="image" src="https://github.com/user-attachments/assets/9365eba6-bed4-4156-9a46-b1595974e57f" />
| 3 | Clean the pads and check under magnification that no solder bridges or leftover pieces remain between the pads. | <img width="454" height="369" alt="image" src="https://github.com/user-attachments/assets/d4b30c21-8806-4201-b483-9cedf4ee83eb" />
| 4 | Power the board and play some music. The sound should now be clear, with full treble. | |

**Additional Notes:**

The original report and investigation are in [issue #204](https://github.com/sonocotta/esp32-audio-dock/issues/204). Thanks to everyone who reported and helped track it down.

If you bought a board from the affected batch, you will be contacted directly with options, including a replacement board if you prefer not to do the rework yourself. If you did not receive a message, or are unsure whether your board is affected, please reach out through the store where you purchased it.

See [Amped-ESP32 with TPA3118/TPA3128 amp](/README.md#amped-esp32-with-tpa3118tpa3128-amp) for more background on the amp and its input filter.
