
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <Adafruit_VL53L0X.h>

#define TFT_CS D3
#define TFT_RST D0
#define TFT_DC D4

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup(void) {
  Serial.begin(9600);
  Serial.print("Hello! ST77xx TFT Test");


  // wait until serial port opens for native USB devices
  while (!Serial) {
    delay(1);
  }

  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1)
      ;
  }
  // power
  Serial.println(F("VL53L0X API Simple Ranging example\n\n"));


  tft.init(240, 320);  // initialize a ST7789 chip, 240x240 pixels

  Serial.println("Initialized");

  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  time = millis() - time;
  Serial.println(time, DEC);
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;

  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextSize(5);
  tft.setTextColor(ST77XX_GREEN);
  lox.rangingTest(&measure, false);  // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {
    tft.println("Distance (mm): ");
    tft.println((int)measure.RangeMilliMeter, 6);
  } else {
    tft.println("out of range");
  }
}
