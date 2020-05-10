#define PAUSE 50;
#define LED_RED 9
#define LED_GREEN 10
#define LED_BLUE 11

float brightness = 0.7; 
int buttonState = 0;         // current state of the button
int lastButtonState = 0;
int buttonDuration = 0;
int rainbowState = true;

int counter = 0;

// Number of colors used for animating, higher = smoother and slower animation)
int numColors = 255;

void setup() {
  Serial.begin(9600);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(A0,INPUT_PULLUP);
}

void loop() {
  buttonState = digitalRead(A0);
  
  if (rainbowState) {
    rainbow();
  }

  if (buttonState == LOW) {
    buttonDuration = buttonDuration + 1;
  }

  if (buttonState == HIGH && buttonDuration > 0) {
    if (buttonDuration >= 1000 / 50) {
      rainbow();
    } else {
      randomRGB();
    }

    buttonDuration = 0;
  }
  
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;

  delay(50);
}

void rainbow() {
  Serial.println("[[[ RAINBOW ]]]");

  rainbowState = true;
  

   // This part takes care of displaying the
 // color changing in reverse by counting backwards if counter
 // is above the number of available colors  
 float colorNumber = counter > numColors ? counter - numColors: counter;
 
 // Play with the saturation and brightness values
 // to see what they do
 float saturation = 1; // Between 0 and 1 (0 = gray, 1 = full color)
 float hue = (colorNumber / float(numColors)) * 360; // Number between 0 and 360
 long color = HSBtoRGB(hue, saturation, brightness);
 
 // Get the red, blue and green parts from generated color
 int red = color >> 16 & 255;
 int green = color >> 8 & 255;
 int blue = color & 255;

 setColor(red, green, blue);
 
 // Counter can never be greater then 2 times the number of available colors
 // the colorNumber = line above takes care of counting backwards (nicely looping animation)
 // when counter is larger then the number of available colors
 counter = (counter + 1) % (numColors * 2);
 
 // If you uncomment this line the color changing starts from the
 // beginning when it reaches the end (animation only plays forward)
 // counter = (counter + 1) % (numColors);
}

void randomRGB() {
  Serial.println("[[[ RANDOM ]]]");
  
  rainbowState = false;

  long color = HSBtoRGB(random(360), 1, brightness);
 
 // Get the red, blue and green parts from generated color
 int red = color >> 16 & 255;
 int green = color >> 8 & 255;
 int blue = color & 255;

 setColor(red, green, blue);
 
}

void setColor (unsigned char red, unsigned char green, unsigned char blue)
{       
   analogWrite(LED_RED, red);
   analogWrite(LED_GREEN, green);
   analogWrite(LED_BLUE, blue);
}

long HSBtoRGB(float _hue, float _sat, float _brightness) {
   float red = 0.0;
   float green = 0.0;
   float blue = 0.0;
   
   if (_sat == 0.0) {
       red = _brightness;
       green = _brightness;
       blue = _brightness;
   } else {
       if (_hue == 360.0) {
           _hue = 0;
       }

       int slice = _hue / 60.0;
       float hue_frac = (_hue / 60.0) - slice;

       float aa = _brightness * (1.0 - _sat);
       float bb = _brightness * (1.0 - _sat * hue_frac);
       float cc = _brightness * (1.0 - _sat * (1.0 - hue_frac));
       
       switch(slice) {
           case 0:
               red = _brightness;
               green = cc;
               blue = aa;
               break;
           case 1:
               red = bb;
               green = _brightness;
               blue = aa;
               break;
           case 2:
               red = aa;
               green = _brightness;
               blue = cc;
               break;
           case 3:
               red = aa;
               green = bb;
               blue = _brightness;
               break;
           case 4:
               red = cc;
               green = aa;
               blue = _brightness;
               break;
           case 5:
               red = _brightness;
               green = aa;
               blue = bb;
               break;
           default:
               red = 0.0;
               green = 0.0;
               blue = 0.0;
               break;
       }
   }

   long ired = red * 255.0;
   long igreen = green * 255.0;
   long iblue = blue * 255.0;
   
   return long((ired << 16) | (igreen << 8) | (iblue));
}
