// INA219 Current Sensor with OLED Display for Arduino Uno
//
// This sketch was modified from the Adafruit INA219 library example
//
// Gadget Reboot
//
// Required Libraries
// https://github.com/adafruit/Adafruit_INA219
// https://github.com/adafruit/Adafruit_SSD1306

#define PAUSE 50
#define LED_RED 9
#define LED_GREEN 10
#define LED_BLUE 11
#define BUTTON A0

int buttonState = 0;         // current state of the button
int lastButtonState = 0;
int buttonDuration = 0;
int rainbowState = true;

int rVal = 1;
int gVal = 1;
int bVal = 1;

int rDir = -1;
int gDir = 1;
int bDir = -1;

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(BUTTON,INPUT_PULLUP);


}

void loop() {
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
