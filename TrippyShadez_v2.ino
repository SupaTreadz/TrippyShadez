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
volatile byte mode = 1;

void setup() 
{
  //Serial.begin(9600);
  pixels.begin();
  
  pinMode(PotPin, INPUT);
  pinMode(MicPin, INPUT);
  pinMode(ButtonPin, INPUT_PULLUP);

  
  pixels.setBrightness(85); // 1/3 brightness  
  
  attachInterrupt(1, debounceInterrupt, FALLING); //Trinket
  //Serial.begin(9600);
}

void loop()
{
  if(mode==0)
  {
    
    unsigned long startMillis= millis();  // Start of sample window
    unsigned int peakToPeak = 0;   // peak-to-peak level
    unsigned int signalMax = 0;
    unsigned int signalMin = 1024;
    unsigned int maxSound = map(analogRead(PotPin),0,1023,0,750);
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
    //peakToPeak = map(peakToPeak2, 0, 750, -5, 29);
    //Serial.println(peakToPeak);

    if(peakToPeak > maxSound*(0/28))
    {
      pixels.setPixelColor(0,purple);
      pixels.setPixelColor(57,purple);
      pixels.show();
    }
    if(peakToPeak > maxSound*(1/28))
    {
      pixels.setPixelColor(1,purple);
      pixels.setPixelColor(56,purple);
      pixels.show();
    }
    if(peakToPeak > maxSound*(2/28))
    {
      pixels.setPixelColor(2,purple);
      pixels.setPixelColor(55,purple);
      pixels.show();
    }
    if(peakToPeak > maxSound*(3/28))
    {
      pixels.setPixelColor(3,purple);
      pixels.setPixelColor(54,purple);
      pixels.show();
    }
    if(peakToPeak > maxSound*(4/28))
    {
      pixels.setPixelColor(4,purple);
      pixels.setPixelColor(53,purple);
      pixels.show();
    }
    if(peakToPeak > maxSound*(5/28))
    {
      pixels.setPixelColor(5,blue);
      pixels.setPixelColor(52,blue);
      pixels.show();
    }
    if(peakToPeak > maxSound*(6/28))
    {
      pixels.setPixelColor(6,blue);
      pixels.setPixelColor(51,blue);
      pixels.show();
    }
    if(peakToPeak > maxSound*(7/28))
    {
      pixels.setPixelColor(7,blue);
      pixels.setPixelColor(50,blue);
      pixels.show();
    }
    if(peakToPeak > maxSound*(8/28))
    {
      pixels.setPixelColor(8,blue);
      pixels.setPixelColor(49,blue);
      pixels.show();
    }
    if(peakToPeak > maxSound*(9/28))
    {
      pixels.setPixelColor(9,blue);
      pixels.setPixelColor(48,blue);
      pixels.show();
    }
    if(peakToPeak > maxSound*(10/28))
    {
      pixels.setPixelColor(10,green);
      pixels.setPixelColor(29,green);
      pixels.show();
    }
    if(peakToPeak > maxSound*(11/28))
    {
      pixels.setPixelColor(11,green);
      pixels.setPixelColor(30,green);
      pixels.show();
    }
    if(peakToPeak > maxSound*(12/28))
    {
      pixels.setPixelColor(12,green);
      pixels.setPixelColor(31,green);
      pixels.show();
    }
    if(peakToPeak > maxSound*(13/28))
    {
      pixels.setPixelColor(13,green);
      pixels.setPixelColor(32,green);
      pixels.show();
    }
    if(peakToPeak > maxSound*(14/28))
    {
      pixels.setPixelColor(14,yellow);
      pixels.setPixelColor(33,yellow);
      pixels.show();
    }
    if(peakToPeak > maxSound*(15/28))
    {
      pixels.setPixelColor(15,yellow);
      pixels.setPixelColor(34,yellow); 
      pixels.show();
    }
    if(peakToPeak > maxSound*(16/28))
    {
      pixels.setPixelColor(16,yellow);
      pixels.setPixelColor(35,yellow);
      pixels.show();
    }
    if(peakToPeak > maxSound*(17/28))
    {
      pixels.setPixelColor(17,yellow);
      pixels.setPixelColor(36,yellow);
      pixels.show();
    }
    if(peakToPeak > maxSound*(18/28))
    {
      pixels.setPixelColor(18,orange);
      pixels.setPixelColor(37,orange);
      pixels.show();
    }
    if(peakToPeak > maxSound*(19/28))
    {
      pixels.setPixelColor(19,orange);
      pixels.setPixelColor(38,orange);
      pixels.show();
    }
    if(peakToPeak > maxSound*(20/28))
    {
      pixels.setPixelColor(20,orange);
      pixels.setPixelColor(39,orange);
      pixels.show();
    }
    if(peakToPeak > maxSound*(21/28))
    {
      pixels.setPixelColor(21,orange);
      pixels.setPixelColor(40,orange);
      pixels.show();
    }
    if(peakToPeak > maxSound*(22/28))
    {
      pixels.setPixelColor(22,red);
      pixels.setPixelColor(41,red);
      pixels.show();
    }
    if(peakToPeak > maxSound*(23/28))
    {
      pixels.setPixelColor(23,red);
      pixels.setPixelColor(42,red);
      pixels.show();
    }
    if(peakToPeak > maxSound*(24/28))
    {
      pixels.setPixelColor(24,red);
      pixels.setPixelColor(43,red);
      pixels.show();
    }
    if(peakToPeak > maxSound*(25/28))
    {
      pixels.setPixelColor(25,red);
      pixels.setPixelColor(44,red);
      pixels.show();
    }
    if(peakToPeak > maxSound*(26/28))
    {
      pixels.setPixelColor(26,white);
      pixels.setPixelColor(45,white);
      pixels.show();
    }
    if(peakToPeak > maxSound*(27/28))
    {
      pixels.setPixelColor(27,white);
      pixels.setPixelColor(46,white);
      pixels.show();
    }
    if(peakToPeak > maxSound*(28/28))
    {
      pixels.setPixelColor(28,white);
      pixels.setPixelColor(47,white);
      pixels.show();
    }
    delay(10);
    allSet(blank);
    pixels.show();
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
    FireSparkle(55,120,15);
  }
  else if(mode==3)
  {
    brightness = analogRead(PotPin);
    pixels.setBrightness(map(brightness,0,1023,0,255));
    rainbow(10);
  }
  else if(mode==4)
  {
    brightness = analogRead(PotPin);
    pixels.setBrightness(map(brightness,0,1023,0,255));
    simpleWave(0.07,5,10);
  }
  else if(mode==5)
  {
    brightness = analogRead(PotPin);
    pixels.setBrightness(map(brightness,0,1023,0,255));
    CylonBounce(random(0,256), random(0,256), random(0,256), 4, 30, 50);
  }
  else if(mode==-1)
  {
    brightness = analogRead(PotPin);
    pixels.setBrightness(map(brightness,0,1023,0,255));
    TwinkleRandom(20, 100, false);
  }
  else
  {
    mode = 1;
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

void FireSparkle(int Cooling, int Sparking, int SpeedDelay) {
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
    pixels.setPixelColor(Pixel, random(0,256), random(0,256), random(0,256));
  } else if( t192 > 0x40 ) {             // middle
    pixels.setPixelColor(Pixel, random(0,256), random(0,256), 0);
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

void setPixelSparkleColor (int Pixel, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature/255.0)*191);
 
  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252
 
  // figure out which third of the spectrum we're in:
  if( t192 > 0x80) {                     // hottest
    pixels.setPixelColor(Pixel, random(0,256), random(0,256), random(0,256));
  } else if( t192 > 0x40 ) {             // middle
    pixels.setPixelColor(Pixel, random(0,256)/2, random(0,256)/2, random(0,256)/2);
  } else {                               // coolest
    pixels.setPixelColor(Pixel, random(0,256)/4, random(0,256)/4, random(0,256)/4);
  }
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
