# esp32-i2s-bare example firmware

Simple example demonstrates how to initialize ESP32 I2S peripheral, external DAC and start sending samples directly into I2S output buffer.

By sending enough positive and negative values we can generate square wave with given frequency and amplitudeAfter applying power audio starts automatically.

```
const int frequency = 512; 
const int amplitude = 256; 
```