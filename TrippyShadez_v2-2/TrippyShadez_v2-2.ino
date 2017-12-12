#include <Adafruit_NeoPixel.h>

#define NeopixelPin 4//chane to 1?
#define MicPin A0
#define ButtonPin 3 //interrupt is 0 even though GPIO #2
#define PotPin A5 //mic sensitivity pot

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(58, NeopixelPin);
  
uint32_t red = pixels.Color(255,0,0);
uint32_t orange = pixels.Color(255,100,0);
uint32_t yellow = pixels.Color(255,255,0);
uint32_t green = pixels.Color(0,255,0);
uint32_t blue = pixels.Color(0,0,255);
uint32_t purple = pixels.Color(255,0,200);
uint32_t white = pixels.Color(255,255,255);
uint32_t blank = pixels.Color(0,0,0);
int brightness = 0;
long debouncing_time = 15; //Debouncing Time in Milliseconds
volatile unsigned long last_micros;
unsigned int sample;
volatile byte mode = 0;

void setup() 
{
  Serial.begin(9600);
  pixels.begin();
  pinMode(PotPin, INPUT);
  pinMode(MicPin, INPUT);
  pinMode(ButtonPin, INPUT_PULLUP);
  pixels.setBrightness(85); // 1/3 brightness  
  attachInterrupt(1, debounceInterrupt, FALLING); //Trinket
}

void loop()
{
  
  if(mode==0)
  {
    brightness = analogRead(PotPin);
    pixels.setBrightness(map(brightness,0,1023,0,255));
    //calibrate();
    int number = 5;
    unsigned long startMillis= millis();  // Start of sample window
    unsigned int peakToPeak = 0;   // peak-to-peak level
    unsigned int signalMax = 0;
    unsigned int signalMin = 1024;
    uint32_t color = red;
    while (millis() - startMillis < 50) //50 is the same size, 50ms
    {
       sample = analogRead(MicPin); 
       if (sample < 1024)  // toss out spurious readings
       {
          if (sample > signalMax)
          {
             signalMax = sample;  // save just the max levels
          }
          else if (sample < signalMin)
          {
             signalMin = sample;  // save just the min levels
          }
       }
    }
    peakToPeak = signalMax - signalMin;
    //Serial.println(peakToPeak);
    allSet(blank);
    if(peakToPeak <= 227)
    {
      allSet(blank);
    }
      if(peakToPeak > 227)
    {
      number = random(1,8);
      if(number==1)
      {
        Serial.println("red");
        color = red;
      }
      else if(number==2)
      {
        Serial.println("orange");
        color = orange;        
      }
      else if(number==3)
      {
        Serial.println("yellow");
        color = yellow;        
      }
      else if(number==4)
      {
        Serial.println("green");
        color = green;        
      }
      else if(number==5)
      {
        Serial.println("blue");
        color = blue;        
      }
      else if(number==6)
      {
        Serial.println("purple");
        color = purple;        
      }
      else
      {
        Serial.println("white");
        color = white;        
      }
      pixels.setPixelColor(0,color);
      pixels.setPixelColor(57,color);
      pixels.show();
    }
    if(peakToPeak > 255)
    {
      number = random(1,8);
      if(number==1)
      {
        color = red;
      }
      else if(number==2)
      {
        color = orange;        
      }
      else if(number==3)
      {
        color = yellow;        
      }
      else if(number==4)
      {
        color = green;        
      }
      else if(number==5)
      {
        color = blue;        
      }
      else if(number==6)
      {
        color = purple;        
      }
      else
      {
        color = white;        
      }
      pixels.setPixelColor(1,color);
      pixels.setPixelColor(56,color);
      pixels.show();
    }
    if(peakToPeak > 282)
    {
      number = random(1,8);
      if(number==1)
      {
        color = red;
      }
      else if(number==2)
      {
        color = orange;        
      }
      else if(number==3)
      {
        color = yellow;        
      }
      else if(number==4)
      {
        color = green;        
      }
      else if(number==5)
      {
        color = blue;        
      }
      else if(number==6)
      {
        color = purple;        
      }
      else
      {
        color = white;        
      }
      pixels.setPixelColor(2,color);
      pixels.setPixelColor(55,color);
      pixels.show();
    }
    if(peakToPeak > 310)
    {
      number = random(1,8);
      if(number==1)
      {
        color = red;
      }
      else if(number==2)
      {
        color = orange;        
      }
      else if(number==3)
      {
        color = yellow;        
      }
      else if(number==4)
      {
        color = green;        
      }
      else if(number==5)
      {
        color = blue;        
      }
      else if(number==6)
      {
        color = purple;        
      }
      else
      {
        color = white;        
      }
      pixels.setPixelColor(3,color);
      pixels.setPixelColor(54,color);
      pixels.show();
    }
    if(peakToPeak > 337)
    {
      number = random(1,8);
      if(number==1)
      {
        color = red;
      }
      else if(number==2)
      {
        color = orange;        
      }
      else if(number==3)
      {
        color = yellow;        
      }
      else if(number==4)
      {
        color = green;        
      }
      else if(number==5)
      {
        color = blue;        
      }
      else if(number==6)
      {
        color = purple;        
      }
      else
      {
        color = white;        
      }
      pixels.setPixelColor(4,color);
      pixels.setPixelColor(53,color);
      pixels.show();
    }
    if(peakToPeak > 365)
    {
      number = random(1,8);
      if(number==1)
      {
        color = red;
      }
      else if(number==2)
      {
        color = orange;        
      }
      else if(number==3)
      {
        color = yellow;        
      }
      else if(number==4)
      {
        color = green;        
      }
      else if(number==5)
      {
        color = blue;        
      }
      else if(number==6)
      {
        color = purple;        
      }
      else
      {
        color = white;        
      }
      pixels.setPixelColor(5,color);
      pixels.setPixelColor(52,color);
      pixels.show();
    }
    if(peakToPeak > 393)
    {
      number = random(1,8);
      if(number==1)
      {
        color = red;
      }
      else if(number==2)
      {
        color = orange;        
      }
      else if(number==3)
      {
        color = yellow;        
      }
      else if(number==4)
      {
        color = green;        
      }
      else if(number==5)
      {
        color = blue;        
      }
      else if(number==6)
      {
        color = purple;        
      }
      else
      {
        color = white;        
      }
      pixels.setPixelColor(6,color);
      pixels.setPixelColor(51,color);
      pixels.show();
    }
    if(peakToPeak > 420)
    {
      number = random(1,8);
      if(number==1)
      {
        color = red;
      }
      else if(number==2)
      {
        color = orange;        
      }
      else if(number==3)
      {
        color = yellow;        
      }
      else if(number==4)
      {
        color = green;        
      }
      else if(number==5)
      {
        color = blue;        
      }
      else if(number==6)
      {
        color = purple;        
      }
      else
      {
        color = white;        
      }
      pixels.setPixelColor(7,color);
      pixels.setPixelColor(50,color);
      pixels.show();
    }
    if(peakToPeak > 448)
    {
      number = random(1,8);
      if(number==1)
      {
        color = red;
      }
      else if(number==2)
      {
        color = orange;        
      }
      else if(number==3)
      {
        color = yellow;        
      }
      else if(number==4)
      {
        color = green;        
      }
      else if(number==5)
      {
        color = blue;        
      }
      else if(number==6)
      {
        color = purple;        
      }
      else
      {
        color = white;        
      }
      pixels.setPixelColor(8,color);
      pixels.setPixelColor(49,color);
      pixels.show();
    }
    if(peakToPeak > 475)
    {
      number = random(1,8);
      if(number==1)
      {
        color = red;
      }
      else if(number==2)
      {
        color = orange;        
      }
      else if(number==3)
      {
        color = yellow;        
      }
      else if(number==4)
      {
        color = green;        
      }
      else if(number==5)
      {
        color = blue;        
      }
      else if(number==6)
      {
        color = purple;        
      }
      else
      {
        color = white;        
      }
      pixels.setPixelColor(9,color);
      pixels.setPixelColor(48,color);
      pixels.show();
    }
    if(peakToPeak > 503)
    {
      number = random(1,8);
      if(number==1)
      {
        color = red;
      }
      else if(number==2)
      {
        color = orange;        
      }
      else if(number==3)
      {
        color = yellow;        
      }
      else if(number==4)
      {
        color = green;        
      }
      else if(number==5)
      {
        color = blue;        
      }
      else if(number==6)
      {
        color = purple;        
      }
      else
      {
        color = white;        
      }
      pixels.setPixelColor(10,color);
      pixels.setPixelColor(47,color);
      pixels.show();
    }
    if(peakToPeak > 531)
    {
      number = random(1,8);
      if(number==1)
      {
        color = red;
      }
      else if(number==2)
      {
        color = orange;        
      }
      else if(number==3)
      {
        color = yellow;        
      }
      else if(number==4)
      {
        color = green;        
      }
      else if(number==5)
      {
        color = blue;        
      }
      else if(number==6)
      {
        color = purple;        
      }
      else
      {
        color = white;        
      }
      pixels.setPixelColor(11,color);
      pixels.setPixelColor(46,color);
      pixels.show();
    }
    if(peakToPeak > 558)
    {
      number = random(1,8);
      if(number==1)
      {
        color = red;
      }
      else if(number==2)
      {
        color = orange;        
      }
      else if(number==3)
      {
        color = yellow;        
      }
      else if(number==4)
      {
        color = green;        
      }
      else if(number==5)
      {
        color = blue;        
      }
      else if(number==6)
      {
        color = purple;        
      }
      else
      {
        color = white;        
      }
      pixels.setPixelColor(12,color);
      pixels.setPixelColor(45,color);
      pixels.show();
    }
    if(peakToPeak > 586)
    {
      number = random(1,8);
      if(number==1)
      {
        color = red;
      }
      else if(number==2)
      {
        color = orange;        
      }
      else if(number==3)
      {
        color = yellow;        
      }
      else if(number==4)
      {
        color = green;        
      }
      else if(number==5)
      {
        color = blue;        
      }
      else if(number==6)
      {
        color = purple;        
      }
      else
      {
        color = white;        
      }
      pixels.setPixelColor(13,color);
      pixels.setPixelColor(44,color);
      pixels.show();
    }
    if(peakToPeak > 613)
    {
      number = random(1,8);
      if(number==1)
      {
        color = red;
      }
      else if(number==2)
      {
        color = orange;        
      }
      else if(number==3)
      {
        color = yellow;        
      }
      else if(number==4)
      {
        color = green;        
      }
      else if(number==5)
      {
        color = blue;        
      }
      else if(number==6)
      {
        color = purple;        
      }
      else
      {
        color = white;        
      }
      pixels.setPixelColor(14,color);
      pixels.setPixelColor(43,color);
      pixels.show();
    }
    if(peakToPeak > 641)
    {
      number = random(1,8);
      if(number==1)
      {
        color = red;
      }
      else if(number==2)
      {
        color = orange;        
      }
      else if(number==3)
      {
        color = yellow;        
      }
      else if(number==4)
      {
        color = green;        
      }
      else if(number==5)
      {
        color = blue;        
      }
      else if(number==6)
      {
        color = purple;        
      }
      else
      {
        color = white;        
      }
      pixels.setPixelColor(15,color);
      pixels.setPixelColor(42,color);
      pixels.show();
    }
    if(peakToPeak > 668)
    {
      number = random(1,8);
      if(number==1)
      {
        color = red;
      }
      else if(number==2)
      {
        color = orange;        
      }
      else if(number==3)
      {
        color = yellow;        
      }
      else if(number==4)
      {
        color = green;        
      }
      else if(number==5)
      {
        color = blue;        
      }
      else if(number==6)
      {
        color = purple;        
      }
      else
      {
        color = white;        
      }
      pixels.setPixelColor(16,color);
      pixels.setPixelColor(41,color);
      pixels.show();
    }
    if(peakToPeak > 696)
    {
      number = random(1,8);
      if(number==1)
      {
        color = red;
      }
      else if(number==2)
      {
        color = orange;        
      }
      else if(number==3)
      {
        color = yellow;        
      }
      else if(number==4)
      {
        color = green;        
      }
      else if(number==5)
      {
        color = blue;        
      }
      else if(number==6)
      {
        color = purple;        
      }
      else
      {
        color = white;        
      }
      pixels.setPixelColor(17,color);
      pixels.setPixelColor(40,color);
      pixels.show();
    }
    if(peakToPeak > 724)
    {
      number = random(1,8);
      if(number==1)
      {
        color = red;
      }
      else if(number==2)
      {
        color = orange;        
      }
      else if(number==3)
      {
        color = yellow;        
      }
      else if(number==4)
      {
        color = green;        
      }
      else if(number==5)
      {
        color = blue;        
      }
      else if(number==6)
      {
        color = purple;        
      }
      else
      {
        color = white;        
      }
      pixels.setPixelColor(18,color);
      pixels.setPixelColor(39,color);
      pixels.show();
    }
    if(peakToPeak > 751)
    {
      number = random(1,8);
      if(number==1)
      {
        color = red;
      }
      else if(number==2)
      {
        color = orange;        
      }
      else if(number==3)
      {
        color = yellow;        
      }
      else if(number==4)
      {
        color = green;        
      }
      else if(number==5)
      {
        color = blue;        
      }
      else if(number==6)
      {
        color = purple;        
      }
      else
      {
        color = white;        
      }
      pixels.setPixelColor(19,color);
      pixels.setPixelColor(38,color);
      pixels.show();
    }
    if(peakToPeak > 779)
    {
      number = random(1,8);
      if(number==1)
      {
        color = red;
      }
      else if(number==2)
      {
        color = orange;        
      }
      else if(number==3)
      {
        color = yellow;        
      }
      else if(number==4)
      {
        color = green;        
      }
      else if(number==5)
      {
        color = blue;        
      }
      else if(number==6)
      {
        color = purple;        
      }
      else
      {
        color = white;        
      }
      pixels.setPixelColor(20,color);
      pixels.setPixelColor(37,color);
      pixels.show();
    }
    if(peakToPeak > 806)
    {
      number = random(1,8);
      if(number==1)
      {
        color = red;
      }
      else if(number==2)
      {
        color = orange;        
      }
      else if(number==3)
      {
        color = yellow;        
      }
      else if(number==4)
      {
        color = green;        
      }
      else if(number==5)
      {
        color = blue;        
      }
      else if(number==6)
      {
        color = purple;        
      }
      else
      {
        color = white;        
      }
      pixels.setPixelColor(21,color);
      pixels.setPixelColor(36,color);
      pixels.show();
    }
    if(peakToPeak > 834)
    {
      number = random(1,8);
      if(number==1)
      {
        color = red;
      }
      else if(number==2)
      {
        color = orange;        
      }
      else if(number==3)
      {
        color = yellow;        
      }
      else if(number==4)
      {
        color = green;        
      }
      else if(number==5)
      {
        color = blue;        
      }
      else if(number==6)
      {
        color = purple;        
      }
      else
      {
        color = white;        
      }
      pixels.setPixelColor(22,color);
      pixels.setPixelColor(35,color);
      pixels.show();
    }
    if(peakToPeak > 862)
    {
      number = random(1,8);
      if(number==1)
      {
        color = red;
      }
      else if(number==2)
      {
        color = orange;        
      }
      else if(number==3)
      {
        color = yellow;        
      }
      else if(number==4)
      {
        color = green;        
      }
      else if(number==5)
      {
        color = blue;        
      }
      else if(number==6)
      {
        color = purple;        
      }
      else
      {
        color = white;        
      }
      pixels.setPixelColor(23,color);
      pixels.setPixelColor(34,color);
      pixels.show();
    }
    if(peakToPeak > 889)
    {
      number = random(1,8);
      if(number==1)
      {
        color = red;
      }
      else if(number==2)
      {
        color = orange;        
      }
      else if(number==3)
      {
        color = yellow;        
      }
      else if(number==4)
      {
        color = green;        
      }
      else if(number==5)
      {
        color = blue;        
      }
      else if(number==6)
      {
        color = purple;        
      }
      else
      {
        color = white;        
      }
      pixels.setPixelColor(24,color);
      pixels.setPixelColor(33,color);
      pixels.show();
    }
    if(peakToPeak > 917)
    {
      number = random(1,8);
      if(number==1)
      {
        color = red;
      }
      else if(number==2)
      {
        color = orange;        
      }
      else if(number==3)
      {
        color = yellow;        
      }
      else if(number==4)
      {
        color = green;        
      }
      else if(number==5)
      {
        color = blue;        
      }
      else if(number==6)
      {
        color = purple;        
      }
      else
      {
        color = white;        
      }
      pixels.setPixelColor(25,color);
      pixels.setPixelColor(32,color);
      pixels.show();
    }
    if(peakToPeak > 944)
    {
      number = random(1,8);
      if(number==1)
      {
        color = red;
      }
      else if(number==2)
      {
        color = orange;        
      }
      else if(number==3)
      {
        color = yellow;        
      }
      else if(number==4)
      {
        color = green;        
      }
      else if(number==5)
      {
        color = blue;        
      }
      else if(number==6)
      {
        color = purple;        
      }
      else
      {
        color = white;        
      }
      pixels.setPixelColor(26,color);
      pixels.setPixelColor(31,color);
      pixels.show();
    }
    if(peakToPeak > 972)
    {
      number = random(1,8);
      if(number==1)
      {
        color = red;
      }
      else if(number==2)
      {
        color = orange;        
      }
      else if(number==3)
      {
        color = yellow;        
      }
      else if(number==4)
      {
        color = green;        
      }
      else if(number==5)
      {
        color = blue;        
      }
      else if(number==6)
      {
        color = purple;        
      }
      else
      {
        color = white;        
      }
      pixels.setPixelColor(27,color);
      pixels.setPixelColor(30,color);
      pixels.show();
    }
    if(peakToPeak > 1000)
    {
      number = random(1,8);
      if(number==1)
      {
        color = red;
      }
      else if(number==2)
      {
        color = orange;        
      }
      else if(number==3)
      {
        color = yellow;        
      }
      else if(number==4)
      {
        color = green;        
      }
      else if(number==5)
      {
        color = blue;        
      }
      else if(number==6)
      {
        color = purple;        
      }
      else
      {
        color = white;        
      }
      pixels.setPixelColor(28,color);
      pixels.setPixelColor(29,color);
      pixels.show();
    }
    delay(5);
  }
  else if(mode==1)
  {
    brightness = analogRead(PotPin);
    pixels.setBrightness(map(brightness,0,1023,0,255));
    Fire(55,120,15);
  }
  else if(mode==2)
  {
    brightness = analogRead(PotPin);
    pixels.setBrightness(map(brightness,0,1023,0,255));
    rainbow(20);
  }
  else if(mode==3)
  {
    brightness = analogRead(PotPin);
    pixels.setBrightness(map(brightness,0,1023,0,255));
    randomFill(75);
  }
  else if(mode==4)
  {
    brightness = analogRead(PotPin);
    pixels.setBrightness(map(brightness,0,1023,0,255));
    CylonBounce(random(0,256), random(0,256), random(0,256), 4, 30, 50);
  }
  else
  {
    mode = 0; //change this to 0 if microphone works
  }
}

// number, twinkle color, background color, delay
// twinkleRand(5,pixels.Color(255,255,255),pixels.Color(255, 0, 100),90);

// twinkle random number of pixels
void calibrate()
{
  allSet(red);
  delay(500);
  allSet(blue);
  delay(500);
  allSet(green);
  delay(500);
}

void twinkleRand(int num,uint32_t c,uint32_t bg,int wait) {
  // set background
   allSet(blank);
   // for each num
   for (int i=0; i<num; i++) {
     pixels.setPixelColor(random(pixels.numPixels()),c);
   }
  pixels.show();
  delay(wait);
}
void randomFill(uint8_t wait) 
{
  int fillSize = random(1,29);
  int number = 0;
  allSet(blank);
  for(uint16_t i=0; i<=fillSize; i++) 
  {
      number = random(1,8);
      switch (number) 
      {
      case 1:
         pixels.setPixelColor(i,red);
         pixels.setPixelColor(58-i,red);
        break;
      case 2:
         pixels.setPixelColor(i,orange);
         pixels.setPixelColor(58-i,orange);
        break;
      case 3:
         pixels.setPixelColor(i,yellow);
         pixels.setPixelColor(58-i,yellow);
        break;
      case 4:
         pixels.setPixelColor(i,green);
         pixels.setPixelColor(58-i,green);
        break;
      case 5:
         pixels.setPixelColor(i,blue);
         pixels.setPixelColor(58-i,blue);
        break;
      case 6:
         pixels.setPixelColor(i,purple);
         pixels.setPixelColor(58-i,purple);
        break;
      case 7:
         pixels.setPixelColor(i,white);
         pixels.setPixelColor(58-i,white);
        break;
      }
  }
  // move the show outside the loop
  pixels.show();
  delay(wait);
}
void pixelsSet(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, c);
  }
  // move the show outside the loop
  pixels.show();
  delay(wait);
}
void simpleWave(float rate,int cycles, int wait) {
   float pos=0.0;
  // cycle through x times
  for(int x=0; x<(pixels.numPixels()*cycles); x++)
  {
      pos = pos+rate;
      for(int i=0; i<pixels.numPixels(); i++) {
        // sine wave, 3 offset waves make a rainbow!
        float level = sin(i+pos) * 127 + 128;
        // set color level 
        pixels.setPixelColor(i,(int)level*(random(0,11)/10),(int)level*(random(0,11)/10),(int)level*(random(0,11)/10));
      }
         pixels.show();
         delay(wait);
  }
}
void CylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){
int number = 0;
  for(int i = 0; i < pixels.numPixels()-EyeSize-2; i++) {
    allSet(blank);
    number = random(1,8);
    switch (number) {
    case 1:
       pixels.setPixelColor(i,red/10);
      break;
    case 2:
       pixels.setPixelColor(i,orange/10);
      break;
    case 3:
       pixels.setPixelColor(i,yellow/10);
      break;
    case 4:
       pixels.setPixelColor(i,green/10);
      break;
    case 5:
       pixels.setPixelColor(i,blue/10);
      break;
    case 6:
       pixels.setPixelColor(i,purple/10);
      break;
    case 7:
       pixels.setPixelColor(i,white/10);
      break;
    }
    for(int j = 1; j <= EyeSize; j++) {
      number = random(1,8);
      switch (number) {
      case 1:
         pixels.setPixelColor(i+j,red);
        break;
      case 2:
         pixels.setPixelColor(i+j,orange);
        break;
      case 3:
         pixels.setPixelColor(i+j,yellow);
        break;
      case 4:
         pixels.setPixelColor(i+j,green);
        break;
      case 5:
         pixels.setPixelColor(i+j,blue);
        break;
      case 6:
         pixels.setPixelColor(i+j,purple);
        break;
      case 7:
         pixels.setPixelColor(i+j,white);
        break;
      }
    }
    number = random(1,8);
    switch (number) {
    case 1:
       pixels.setPixelColor(i+EyeSize+1,red);
      break;
    case 2:
       pixels.setPixelColor(i+EyeSize+1,orange);
      break;
    case 3:
       pixels.setPixelColor(i+EyeSize+1,yellow);
      break;
    case 4:
       pixels.setPixelColor(i+EyeSize+1,green);
      break;
    case 5:
       pixels.setPixelColor(i+EyeSize+1,blue);
      break;
    case 6:
       pixels.setPixelColor(i+EyeSize+1,purple);
      break;
    case 7:
       pixels.setPixelColor(i+EyeSize+1,white);
      break;
    }
    pixels.show();
    delay(SpeedDelay);
  }

  delay(ReturnDelay);

  for(int i = pixels.numPixels()-EyeSize-2; i > 0; i--) {
    allSet(blank);
    number = random(1,8);
    switch (number) {
    case 1:
       pixels.setPixelColor(i,red/10);
      break;
    case 2:
       pixels.setPixelColor(i,orange/10);
      break;
    case 3:
       pixels.setPixelColor(i,yellow/10);
      break;
    case 4:
       pixels.setPixelColor(i,green/10);
      break;
    case 5:
       pixels.setPixelColor(i,blue/10);
      break;
    case 6:
       pixels.setPixelColor(i,purple/10);
      break;
    case 7:
       pixels.setPixelColor(i,white/10);
      break;
    }
    for(int j = 1; j <= EyeSize; j++) {
      number = random(1,8);
      switch (number) {
      case 1:
         pixels.setPixelColor(i+j,red);
        break;
      case 2:
         pixels.setPixelColor(i+j,orange);
        break;
      case 3:
         pixels.setPixelColor(i+j,yellow);
        break;
      case 4:
         pixels.setPixelColor(i+j,green);
        break;
      case 5:
         pixels.setPixelColor(i+j,blue);
        break;
      case 6:
         pixels.setPixelColor(i+j,purple);
        break;
      case 7:
         pixels.setPixelColor(i+j,white);
        break;
      } 
    }
    number = random(1,8);
    switch (number) {
    case 1:
       pixels.setPixelColor(i+EyeSize+1,red);
      break;
    case 2:
       pixels.setPixelColor(i+EyeSize+1,orange);
      break;
    case 3:
       pixels.setPixelColor(i+EyeSize+1,yellow);
      break;
    case 4:
       pixels.setPixelColor(i+EyeSize+1,green);
      break;
    case 5:
       pixels.setPixelColor(i+EyeSize+1,blue);
      break;
    case 6:
       pixels.setPixelColor(i+EyeSize+1,purple);
      break;
    case 7:
       pixels.setPixelColor(i+EyeSize+1,white);
      break;
    }
    pixels.show();
    delay(SpeedDelay);
  }
  
  delay(ReturnDelay);
}
void allSet(uint32_t c)
{
  for(int i=0;i<pixels.numPixels();i++)
  {
    pixels.setPixelColor(i,c);
  }
  pixels.show();
}
void travellingDot()
{
  int number = 0;
  for(int i=0; i<pixels.numPixels(); i++)
  {
    number = random(1,8);
    switch (number) {
    case 1:
       pixels.setPixelColor(i,red);
      break;
    case 2:
       pixels.setPixelColor(i,orange);
      break;
    case 3:
       pixels.setPixelColor(i,yellow);
      break;
    case 4:
       pixels.setPixelColor(i,green);
      break;
    case 5:
       pixels.setPixelColor(i,blue);
      break;
    case 6:
       pixels.setPixelColor(i,purple);
      break;
    case 7:
       pixels.setPixelColor(i,white);
      break;
    }
    pixels.show();
    delay(30);
    allSet(blank);
  }
  for(int j=pixels.numPixels()-1; j>=0; j--)
  {
    number = random(1,8);
    switch (number) {
    case 1:
       pixels.setPixelColor(j,red);
      break;
    case 2:
       pixels.setPixelColor(j,orange);
      break;
    case 3:
       pixels.setPixelColor(j,yellow);
      break;
    case 4:
       pixels.setPixelColor(j,green);
      break;
    case 5:
       pixels.setPixelColor(j,blue);
      break;
    case 6:
       pixels.setPixelColor(j,purple);
      break;
    case 7:
       pixels.setPixelColor(j,white);
      break;
    }
    pixels.show();
    delay(30);
    allSet(blank);
  }
}
void debounceInterrupt() 
{
  if((long)(micros() - last_micros) >= debouncing_time * 1000) 
  {
    Interrupt();
    last_micros = micros();
  }
}
void Interrupt()
{
  mode++;
}

void Fire(int Cooling, int Sparking, int SpeedDelay) {
  static byte heat[60];
  int cooldown;
  
  // Step 1.  Cool down every cell a little
  for( int i = 0; i < pixels.numPixels(); i++) {
    cooldown = random(0, ((Cooling * 10) / pixels.numPixels()) + 2);
    
    if(cooldown>heat[i]) {
      heat[i]=0;
    } else {
      heat[i]=heat[i]-cooldown;
    }
  }
  
  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for( int k= pixels.numPixels() - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }
    
  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160,255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for( int j = 0; j < pixels.numPixels(); j++) {
    setPixelHeatColor(j, heat[j] );
  }

  pixels.show();
  delay(SpeedDelay);
}

void setPixelHeatColor (int Pixel, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature/255.0)*191);
 
  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252
 
  // figure out which third of the spectrum we're in:
  if( t192 > 0x80) {                     // hottest
    pixels.setPixelColor(Pixel, 255, 255, heatramp);
  } else if( t192 > 0x40 ) {             // middle
    pixels.setPixelColor(Pixel, 255, heatramp, 0);
  } else {                               // coolest
    pixels.setPixelColor(Pixel, heatramp, 0, 0);
  }
}

void Sparkle(byte red, byte green, byte blue, int SpeedDelay) {
  int Pixel = random(pixels.numPixels());
  pixels.setPixelColor(Pixel,red,green,blue);
  pixels.show();
  delay(SpeedDelay);
  pixels.setPixelColor(Pixel,0,0,0);
}

void TwinkleRandom(int Count, int SpeedDelay, boolean OnlyOne) {
  
  allSet(blank);
  
  for (int i=0; i<Count; i++) 
  {
     pixels.setPixelColor(random(pixels.numPixels()),random(0,255),random(0,255),random(0,255));
     pixels.show();
     delay(SpeedDelay);
     if(OnlyOne) { 
       allSet(blank); 
     }
   }
  
  delay(SpeedDelay);
}

void colorWipe(uint32_t c, uint8_t wait) 
{
  for(uint16_t i=0; i<pixels.numPixels(); i++) 
  {
      pixels.setPixelColor(i, c);
      pixels.show();
      delay(wait);
  }
}
void rainbow(uint8_t wait) 
{
  uint16_t i, j;

  for(j=0; j<256; j++) 
  {
    for(i=0; i<pixels.numPixels(); i++) 
    {
      pixels.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}
void theaterChaseRainbow(uint8_t wait) 
{
  for (int j=0; j < 256; j++) 
  {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) 
    {
        for (int i=0; i < pixels.numPixels(); i=i+3) 
        {
          pixels.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        pixels.show();
       
        delay(wait);
       
        for (int i=0; i < pixels.numPixels(); i=i+3) 
        {
          pixels.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}
void randomCycle(int count)
{
  //uint32_t c;
  int pixel = random(0,62);
  byte color = random(1,7);
  allSet(blank);
  pixels.show();
  if(color == 1)
  {
    pixels.setPixelColor(pixel,red);
    //c = red;
  }
  else if(color == 2)
  {
    pixels.setPixelColor(pixel,orange);
    //c = orange;
  }
  else if(color == 3)
  {
    pixels.setPixelColor(pixel,yellow);
    //c = yellow;
  }
  else if(color == 4)
  {
    pixels.setPixelColor(pixel,green);
    //c = green;
  }
  else if(color == 5)
  {
    pixels.setPixelColor(pixel,blue);
    //c = blue;
  }
  else if(color == 6)
  {
    pixels.setPixelColor(pixel,purple);
    //c = purple;
  }
  //pixels.setPixelColor(pixel,c);
  pixels.show();
  delay(20); 
  
}
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
