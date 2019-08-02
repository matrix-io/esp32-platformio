# MatrixVoice PlatformIO

The current project show how build and upload any firmware for [MatrixVoice ESP32 board](https://www.matrix.one/products/voice) using [PlatformIO](https://platformio.org/) OTA or `Arduino OTA`. 

**note**: The next documentation is based on [Program Over the Air on ESP32 MATRIX Voice](https://www.hackster.io/matrix-labs/program-over-the-air-on-esp32-matrix-voice-5e76bb) documentation but it using PlatformIO instead Arduino IDE. You dont need IDF toolchain or any library, PlatformIO do it for you.

---

## Prerequisites

### PlatformIO software

Please install first [PlatformIO](http://platformio.org/) open source ecosystem for IoT development and its command line tools (Windows, MacOs and Linux). Also, you may need to install [git](http://git-scm.com/) in your system (PC).


### MatrixVoice software

For get OTA updates without RaspberryPi, first you should have a one RaspberryPi with `MatrixVoice` software. Please run into your RaspberryPi shell or ssh:

##### add debian repository key:

```bash
curl https://apt.matrix.one/doc/apt-key.gpg | sudo apt-key add -
echo "deb https://apt.matrix.one/raspbian $(lsb_release -sc) main" | sudo tee /etc/apt/sources.list.d/matrixlabs.list
```

##### update your repository and packages:
```bash
sudo apt-get update
sudo apt-get upgrade
```
#####  install the MATRIX init package:
```bash
sudo apt install matrixio-creator-init
```
#####  reboot your Raspberry Pi:
```bash
sudo reboot
```
##### SSH back into the pi, execute this command:
```bash
voice_esp32_enable
```

### Installing initial firmware for OTA

Return to your PC and clone this repository:

```bash
git clone https://github.com/hpsaturn/matrixvoice_platformio.git
cd matrixvoice_platformio
```
Copy `platformio.ini` sample and change your network parameters:
```bash
cp platformio.ini.sample platformio.ini
```
**NOTE:** plase change `platformio.ini` and set your `SSID` and `PASSW` like this:

```python
'-DWIFI_SSID="MyWifiSsid"'
'-DWIFI_PASS="MyWifiPassw"'
```
##### building
```bash
pio run
```
##### upload

Enter to OTA directory and upload the firmware. Please replace the `ip` parameter with your `RaspberryPi` ip like this:

```bash
cd ota
./install.sh 192.168.178.65
```

The console output should be like this:
```bash
(master) avp:ota$ ./install.sh 192.168.178.65

Loading firmware: ../.pio/build/esp32dev/firmware.bin

-----------------------------------
esptool.py wrapper for MATRIX Voice
-----------------------------------
esptool.py v2.7
Serial port /dev/ttyS0
Connecting....
Chip is ESP32D0WDQ6 (revision 1)
Features: WiFi, BT, Dual Core, Coding Scheme None
Crystal is 40MHz
MAC: 30:ae:a4:07:6f:7c
Uploading stub...
Running stub...
Stub running...
Configuring flash size...
Auto-detected Flash size: 4MB
Wrote 32768 bytes at 0x00001000 in 3.0 seconds (86.2 kbit/s)...
Hash of data verified.
Wrote 966656 bytes at 0x00010000 in 90.4 seconds (85.6 kbit/s)...
Hash of data verified.
Wrote 16384 bytes at 0x00008000 in 1.5 seconds (86.5 kbit/s)...
Hash of data verified.

Leaving...
Hard resetting via RTS pin...
done

[SUCCESS] Please disconnect your MatrixVoice from the RaspberryPi and reconnect it alone for future OTA updates.
```
(end of `Prerequisites`)

---

## Upload via PlatformIO OTA

After that, you can using your MatrixVoice `without` RaspberryPi. For send new OTA updates, you only need:
```bash
pio run --target upload
```

For update `MatrixVoice` libraries in the future, you only need:
```bash
pio lib update
```

---

## Troubleshooting

#### Uploading issues

If `pio run --target upload` not works, please check `MVID` parameter, it should be a short name, or you can passing ESP32 ip in `upload_port` parameter in `platformio.ini` file.

#### Building issues

For a complete `clean` of the project and get the last version of the libraries, please test the next commands:

```javascript
git pull
pio run -t clean && rm -r .pio
pio run
```
