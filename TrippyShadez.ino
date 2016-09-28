#include <Adafruit_NeoPixel.h>
//#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
//#include <avr/power.h>
//#endif

#define NeopixelPin 0//chane to 1?
#define MicPin 3 //GPIO #3 is actually Analog #3 2is1
#define ButtonPin 2 //interrupt is 0 even though GPIO #2

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(62, NeopixelPin);
  
uint32_t red = pixels.Color(255,0,0);
uint32_t orange = pixels.Color(255,100,0);
uint32_t yellow = pixels.Color(255,255,0);
uint32_t green = pixels.Color(0,255,0);
uint32_t blue = pixels.Color(0,0,255);
uint32_t purple = pixels.Color(255,0,200);
uint32_t white = pixels.Color(255,255,255);
uint32_t blank = pixels.Color(0,0,0);

long debouncing_time = 15; //Debouncing Time in Milliseconds
volatile unsigned long last_micros;
unsigned int sample;
volatile byte mode = 1;

void setup() 
{
  pixels.begin();
  pixels.setBrightness(63); // 1/3 brightness
  pinMode(ButtonPin, INPUT_PULLUP);
  attachInterrupt(0, Interrupt, FALLING); //Trinket
}

void loop()
{
  if(mode==1)
  {
    unsigned long startMillis= millis();  // Start of sample window
    int peakToPeak = 0;   // peak-to-peak level
    int signalMax = 0;
    int signalMin = 1024;
    while (millis() - startMillis < 20) //50 is the same size, 50ms
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
    peakToPeak = map(peakToPeak, 0, 700, 0, 10000);

    if(peakToPeak > 600)
    {
      pixels.setPixelColor(0,purple);
      pixels.setPixelColor(61,purple);
      pixels.show();
    }
    if(peakToPeak > 900)
    {
      pixels.setPixelColor(1,purple);
      pixels.setPixelColor(60,purple);
      pixels.show();
    }
    if(peakToPeak > 1200)
    {
      pixels.setPixelColor(2,purple);
      pixels.setPixelColor(59,purple);
      pixels.show();
    }
    if(peakToPeak > 1500)
    {
      pixels.setPixelColor(3,purple);
      pixels.setPixelColor(58,purple);
      pixels.show();
    }
    if(peakToPeak > 1800)
    {
      pixels.setPixelColor(4,purple);
      pixels.setPixelColor(57,purple);
      pixels.show();
    }
    if(peakToPeak > 2100)
    {
      pixels.setPixelColor(5,blue);
      pixels.setPixelColor(56,blue);
      pixels.show();
    }
    if(peakToPeak > 2400)
    {
      pixels.setPixelColor(6,blue);
      pixels.setPixelColor(55,blue);
      pixels.show();
    }
    if(peakToPeak > 2700)
    {
      pixels.setPixelColor(7,blue);
      pixels.setPixelColor(54,blue);
      pixels.show();
    }
    if(peakToPeak > 3000)
    {
      pixels.setPixelColor(8,blue);
      pixels.setPixelColor(53,blue);
      pixels.show();
    }
    if(peakToPeak > 3300)
    {
      pixels.setPixelColor(9,blue);
      pixels.setPixelColor(52,blue);
      pixels.show();
    }
    if(peakToPeak > 3600)
    {
      pixels.setPixelColor(10,green);
      pixels.setPixelColor(51,green);
      pixels.show();
    }
    if(peakToPeak > 3900)
    {
      pixels.setPixelColor(11,green);
      pixels.setPixelColor(50,green);
      pixels.show();
    }
    if(peakToPeak > 4200)
    {
      pixels.setPixelColor(12,green);
      pixels.setPixelColor(49,green);
      pixels.show();
    }
    if(peakToPeak > 4500)
    {
      pixels.setPixelColor(13,green);
      pixels.setPixelColor(31,green);
      pixels.show();
    }
    if(peakToPeak > 4800)
    {
      pixels.setPixelColor(14,yellow);
      pixels.setPixelColor(32,yellow);
      pixels.show();
    }
    if(peakToPeak > 5100)
    {
      pixels.setPixelColor(15,yellow);
      pixels.setPixelColor(33,yellow); 
      pixels.show();
    }
    if(peakToPeak > 5400)
    {
      pixels.setPixelColor(16,yellow);
      pixels.setPixelColor(34,yellow);
      pixels.show();
    }
    if(peakToPeak > 5700)
    {
      pixels.setPixelColor(17,yellow);
      pixels.setPixelColor(35,yellow);
      pixels.show();
    }
    if(peakToPeak > 6000)
    {
      pixels.setPixelColor(18,orange);
      pixels.setPixelColor(36,orange);
      pixels.show();
    }
    if(peakToPeak > 6300)
    {
      pixels.setPixelColor(19,orange);
      pixels.setPixelColor(37,orange);
      pixels.show();
    }
    if(peakToPeak > 6600)
    {
      pixels.setPixelColor(20,orange);
      pixels.setPixelColor(38,orange);
      pixels.show();
    }
    if(peakToPeak > 6900)
    {
      pixels.setPixelColor(21,orange);
      pixels.setPixelColor(39,orange);
      pixels.show();
    }
    if(peakToPeak > 7200)
    {
      pixels.setPixelColor(22,red);
      pixels.setPixelColor(40,red);
      pixels.show();
    }
    if(peakToPeak > 7500)
    {
      pixels.setPixelColor(23,red);
      pixels.setPixelColor(41,red);
      pixels.show();
    }
    if(peakToPeak > 7800)
    {
      pixels.setPixelColor(24,red);
      pixels.setPixelColor(42,red);
      pixels.show();
    }
    if(peakToPeak > 8100)
    {
      pixels.setPixelColor(25,red);
      pixels.setPixelColor(43,red);
      pixels.show();
    }
    if(peakToPeak > 8400)
    {
      pixels.setPixelColor(26,white);
      pixels.setPixelColor(44,white);
      pixels.show();
    }
    if(peakToPeak > 8700)
    {
      pixels.setPixelColor(27,white);
      pixels.setPixelColor(45,white);
      pixels.show();
    }
    if(peakToPeak > 9000)
    {
      pixels.setPixelColor(28,white);
      pixels.setPixelColor(46,white);
      pixels.show();
    }
    if(peakToPeak > 9300)
    {
      pixels.setPixelColor(29,white);
      pixels.setPixelColor(47,white);
      pixels.show();
    }
    if(peakToPeak > 9600)
    {
      pixels.setPixelColor(30,white);
      pixels.setPixelColor(48,white);
      pixels.show();
    }
    allSet(blank);
    pixels.show();
  }
  else if(mode==2)
  {
    rainbow(50);
  }
  else if(mode==3)
  {
    TwinkleRandom(20, 100, false);
  }
  else if(mode==4)
  {
    //randomCycle(500);
  }
  else
  {
    mode = 1;
  }
}
// number, twinkle color, background color, delay
// twinkleRand(5,pixels.Color(255,255,255),pixels.Color(255, 0, 100),90);

// twinkle random number of pixels
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
void CylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){

  for(int i = 0; i < pixels.numPixels()-EyeSize-2; i++) {
    allSet(blank);
    pixels.setPixelColor(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      pixels.setPixelColor(i+j, red, green, blue); 
    }
    pixels.setPixelColor(i+EyeSize+1, red/10, green/10, blue/10);
    pixels.show();
    delay(SpeedDelay);
  }

  delay(ReturnDelay);

  for(int i = pixels.numPixels()-EyeSize-2; i > 0; i--) {
    allSet(blank);
    pixels.setPixelColor(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      pixels.setPixelColor(i+j, red, green, blue); 
    }
    pixels.setPixelColor(i+EyeSize+1, red/10, green/10, blue/10);
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
  for(int i=0; i<pixels.numPixels(); i++)
  {
    pixels.setPixelColor(i,white);
    pixels.show();
    delay(30);
    allSet(blank);
  }
  for(int j=pixels.numPixels()-1; j>=0; j--)
  {
    pixels.setPixelColor(j,white);
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
