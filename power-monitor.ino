// INA219 Current Sensor with OLED Display for Arduino Uno
//
// This sketch was modified from the Adafruit INA219 library example
//
// Gadget Reboot
//
// Required Libraries
// https://github.com/adafruit/Adafruit_INA219
// https://github.com/adafruit/Adafruit_SSD1306

#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Adafruit_SSD1306.h>

Adafruit_INA219 sensors[3] = {
    Adafruit_INA219 ina219_A(0x40),
    Adafruit_INA219 ina219_B(0x41),
    Adafruit_INA219 ina219_C(0x44),
};

#define SENSOR_POS_12V 0
#define SENSOR_NEG_12V 1
#define SENSOR_POS_5V 2
byte currentSensor = SENSOR_POS_12V;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LED_RED 9
#define LED_GREEN 10
#define LED_BLUE 11
#define BUTTON_SCREEN A0
#define BUTTON_LED A1

Button2 buttonScreen = Button2(BUTTON_SCREEN);
Button2 buttonLed = Button2(BUTTON_LED);

float brightness = 0.7;
int rainbowState = true;
int counter = 0;
int numColors = 255;

float shuntvoltage = 0;
float busvoltage = 0;
float current_mA = 0;
float power_mW = 0;

void setup() {
  delay(50);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  // Initialize buttons
  buttonScreen.setClickHandler(click);
  buttonLed.setClickHandler(click);
  buttonLed.setLongClickHandler(longpress);
  
  // initialize ina219 with default measurement range of 32V, 2A
  sensors[SENSOR_POS_12V].begin();
  sensors[SENSOR_NEG_12V].begin();
  sensors[SENSOR_POS_5V].begin();
  updateSensorData(currentSensor);

  // initialize OLED display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.display();

  displayLogo();
  delay(3000);
}

void loop() {
    displayMonitor();

    buttonScreen.loop();
    buttonLed.loop();
    delay(50);
}

void click(Button2& btn) {
    if (btn == buttonScreen) {
        currentSensor++;

        if (currentSensor > 2) {
            currentSensor = 0;
        }

        updateSensorData(currentSensor);
    } else if (btn == buttonLed) {
        randomRGB();
    }
}

void longpress(Button2& btn) {
    if (btn == buttonLed) {
        if (btn.wasPressedFor() > 1500) {
            rainbow();
        }
    }
}