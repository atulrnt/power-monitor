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
Adafruit_INA219 ina219_A(0x40);
Adafruit_INA219 ina219_B(0x41);
Adafruit_INA219 ina219_C(0x44);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define PAUSE 50
#define LED_RED 9
#define LED_GREEN 10
#define LED_BLUE 11
#define BUTTON A0

int buttonState = 0;         // current state of the button
int lastButtonState = 0;
int buttonDuration = 0;
int rainbowState = true;

int rVal = 254;
int gVal = 1;
int bVal = 80;

int rDir = -5;
int gDir = 5;
int bDir = -5;

float shuntvoltage = 0;
float busvoltage = 0;
float current_mA = 0;
float power_mW = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(BUTTON,INPUT_PULLUP);
  
  // initialize ina219 with default measurement range of 32V, 2A
  ina219_A.begin();
  ina219_B.begin();
  ina219_C.begin();

  // ina219.setCalibration_32V_2A();    // set measurement range to 32V, 2A  (do not exceed 26V!)
  // ina219.setCalibration_32V_1A();    // set measurement range to 32V, 1A  (do not exceed 26V!)
  // ina219.setCalibration_16V_400mA(); // set measurement range to 16V, 400mA

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
  readButtonState();

  delay(PAUSE);
}

void readButtonState() {
  buttonState = digitalRead(BUTTON);
  
  if (rainbowState) {
    rainbow();
  }

  if (buttonState == LOW) {
    buttonDuration = buttonDuration + 1;
  }

  if (buttonState == HIGH && buttonDuration > 0) {
    if (buttonDuration >= 1000/PAUSE) {
      rainbow();
    } else {
      randomRGB();
    }

    buttonDuration = 0;
  }
  
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;
}

void displayLogo(){
  // show data on OLED
  display.clearDisplay();
  
  display.fillScreen(SSD1306_BLACK);
  display.drawLine(34, 5, 34, 57, SSD1306_WHITE);
  display.drawLine(35, 5, 35, 57, SSD1306_WHITE);
  display.drawLine(36, 5, 36, 57, SSD1306_WHITE);
  display.drawLine(37, 5, 37, 57, SSD1306_WHITE);

  display.drawLine(86, 5, 86, 57, SSD1306_WHITE);
  display.drawLine(87, 5, 87, 57, SSD1306_WHITE);
  display.drawLine(88, 5, 88, 57, SSD1306_WHITE);
  display.drawLine(89, 5, 89, 57, SSD1306_WHITE);

  display.drawLine(59, 5, 59, 57, SSD1306_WHITE);
  display.drawLine(60, 5, 60, 57, SSD1306_WHITE);
  display.drawLine(61, 5, 61, 57, SSD1306_WHITE);
  display.drawLine(62, 5, 62, 57, SSD1306_WHITE);

  display.drawLine(38, 30, 85, 30, SSD1306_WHITE);
  display.drawLine(38, 31, 85, 31, SSD1306_WHITE);
  display.drawLine(38, 32, 85, 32, SSD1306_WHITE);
  display.drawLine(38, 33, 85, 33, SSD1306_WHITE);

  display.drawLine(37, 54, 86, 5, SSD1306_WHITE);
  display.drawLine(37, 55, 86, 6, SSD1306_WHITE);
  display.drawLine(37, 56, 86, 7, SSD1306_WHITE);
  display.drawLine(37, 57, 86, 8, SSD1306_WHITE);

  display.display();
}

void displayMonitor(){
  // read data from ina219
  shuntvoltage = ina219_A.getShuntVoltage_mV();
  busvoltage = ina219_A.getBusVoltage_V();
  current_mA = ina219_A.getCurrent_mA();
  power_mW = ina219_A.getPower_mW();
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("+ 12V");
  
  display.setTextSize(1);
  display.setCursor(0, 25);
  display.print("Bus     ");
  display.print(busvoltage);
  display.print(" V");
  
  display.setCursor(0, 35);
  display.print("Current ");
  display.print(current_mA);
  display.print(" mA");

  display.setCursor(0, 45);
  display.print("Power   ");
  display.print(power_mW);
  display.print(" mW");

  display.setCursor(0, 55);
  display.print("Shunt   ");
  display.print(shuntvoltage);
  display.print(" mV");

  display.display();
}

void rainbow() {
  rainbowState = true;
  
  // for each color, change direction if
  // you reached 0 or 255
  if (rVal >= 255 || rVal <= 0) {
    rDir = rDir * -1;
  }

  if (gVal >= 255 || gVal <= 0) {
    gDir = gDir * -1;
  }

  if (bVal >= 255 || bVal <= 0) {
    bDir = bDir * -1;
  }

  // change the values of the LEDs
  rVal = rVal + rDir;
  gVal = gVal + gDir;
  bVal = bVal + bDir;

  analogWrite(LED_RED, rVal);
  analogWrite(LED_GREEN, gVal);
  analogWrite(LED_BLUE, bVal);
}

void randomRGB() {  
  rainbowState = false;
  rVal = random(255);
  gVal = random(255);
  bVal = random(255);

  Serial.println(rVal);
  Serial.println(gVal);
  Serial.println(bVal);

  analogWrite(LED_RED, rVal);
  analogWrite(LED_GREEN, gVal);
  analogWrite(LED_BLUE, bVal);
}
