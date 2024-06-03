# EspTranscriptionPedal

Simple program for the ESP32 (ESP32-C3 in this instance) that allows you to connect to switches that will act  as the previous track and play/pause media buttons over Bluetooth.

I created some simple pedals with aluminium foil on card board and a bit of foam at one end, so that they are normally separated, but pushing at the other end creates contact between the two pieces of foil. The play/pause button is connected on pin 8, the previous track button on pin 6 and the other wires of both switches to ground.

In Windows you should forget the device before unplugging and repairing it every time, otherwise it won't get a stable connection. (At least that's my experience.)

## Playing media

On Windows, I found that [this fork of Media Player Classic - Home Cinema](https://github.com/clsid2/mpc-hc/) works best. The built in media players don't have hotkeys to skip back a few seconds while in the background and VLC has some delays when hitting play/pause quickly and occasionally skips a few seconds. To make the skip back key work, you need to modify the hotkeys under Options > Player > Keys for the command Jump Backward (I chose the medium one). In the App Command column, choose MEDIA_PREVIOUSTRACK, and make sure the Global Media Keys option at the bottom of the window is checked. Remove the MEDIA_PREVIOUSTRACK value from the normal Previous command. (For symmetry, you may also choose to modify the Jump Forward command similarly.)

On Linux, [Parlatype](https://github.com/gkarsay/parlatype) is a very nice player. It can automatically skip back on pause for a configurable number of seconds, which allows for single pedal operation. Unfortunately, I've not found a way to have it listen to a global Skip Backward shortcut from the media keys.

## Running on a NodeMCU ESP-C3-12F-Kit (d) type

I have a couple of [these boards](https://docs.ai-thinker.com/_media/esp32/docs/esp-c3-12f-kit-v1.0_specification.pdf), which are a little special. The ESP32-C3 has a RISC-V processor, rather than the ARM chips found in other ESP32 modules. The ones I have are the (d) type, with only 2M of flash storage, rather than the usual 4M. Since this board is unknown to PlatformIO, I use the c3-devkit board and set the following settings:

```ini
monitor_rts = 0
monitor_dtr = 0
board_upload.flash_size = 2MB
board_build.partitions = esp32c3-2m-partitions.csv
board_build.flash_mode = dio
```

The `rts` and `dtr` flags are required for the serial monitor to work on these boards, and the C3 in general seems to require the `dio` flash mode. For the special size, I set the `flash_size` option and used a custom partition table.
