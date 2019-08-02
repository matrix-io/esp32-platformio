#include "MATRIXVoiceOTA.h"

#include <Arduino.h>
#include "wishbone_bus.h"
#include "everloop.h"
#include "everloop_image.h"
#include "microphone_array.h"
#include "microphone_core.h"
#include "voice_memory_map.h"

#define RATE 16000

//Matrix Voice
namespace hal = matrix_hal;
static hal::WishboneBus wb;
static hal::Everloop everloop;
static hal::MicrophoneArray mics;
static hal::EverloopImage image1d;

MATRIXVoiceOTA otaObj(WIFI_SSID,WIFI_PASS,MVID,MVPASS); // please see platformio.ini

void setup() {
  Serial.begin(115200);
  Serial.println("[SETUP] MatrixVoice init..");
  wb.Init();
  everloop.Setup(&wb);
  
  // setup mics
  mics.Setup(&wb);
  mics.SetSamplingRate(RATE);
  // mics.SetGain(5);

  // microphone core init
  hal::MicrophoneCore mic_core(mics);
  mic_core.Setup(&wb);

  otaObj.setup();
  Serial.println("[SETUP] MatrixVoice done.");
}

unsigned counter = 0;

void everloopAnimation() {
  for (hal::LedValue &led : image1d.leds) {
    led.red = 0;
    led.green = 0;
    led.blue = 0;
    led.white = 0;
  }
  image1d.leds[(counter / 2) % image1d.leds.size()].red = 20;
  image1d.leds[(counter / 7) % image1d.leds.size()].green = 30;
  image1d.leds[(counter / 11) % image1d.leds.size()].blue = 30;
  image1d.leds[image1d.leds.size() - 1 - (counter % image1d.leds.size())].white = 10;

  ++counter;
  everloop.Write(&image1d);
  usleep(25000);
}

void loop() {
  // put your main code here
  everloopAnimation();
  otaObj.loop();
}
