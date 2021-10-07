#include <FastLED.h>

//Upload instructions
//Set board to "arduino nano" and processor to "atmega328p" (not old bootloader)
//Connect FTDI pins to RTVG pins on glasses, hold reset button the entire time once connected
//Release reset button when "uploading" appears on status
//Wait a couple of seconds after "uploading" to release button
//It probably wont tell you when it's finished, but the code should eventually upload, there will still likely be an error in the IDE. Sometimes it does say done uploading.
//wait until LEDs light up to indicate upload complete? if it doesnt tell you

#define AccelPin A3
#define MicPin A4
#define PotPin A5
#define ButtonPin 3

#define DATA_PIN    6
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define NUM_LEDS    65
#define MIRROR      32

CRGBArray<NUM_LEDS> leds;

#define FRAMES_PER_SECOND  240
#define TWINKLE_SPEED 6
#define TWINKLE_DENSITY 5

// How often to change color palettes.
#define SECONDS_PER_PALETTE  10
CRGB gBackgroundColor = CRGB::Black; 
#define AUTO_SELECT_BACKGROUND_COLOR 0
#define COOL_LIKE_INCANDESCENT 1

CRGBPalette16 gCurrentPalette;
CRGBPalette16 gTargetPalette;

bool gReverseDirection = false; //fire mode direction

int brightness = 0;
int pastBrightness = 0;
long debouncing_time = 15; //Debouncing Time in Milliseconds
volatile unsigned long last_micros;
unsigned int sample;
volatile byte mode = 3;
volatile bool trigger = false;
unsigned int lowBound = 100;
bool forward = true;

// pixel orders (these are for <=v4 only)
uint32_t lefthalf[] = {32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0};
uint32_t righthalf[] = {34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65};

DEFINE_GRADIENT_PALETTE( example_gp ) {

0, 0,0,0, //Black

36, 255,0,0, //Red

72, 255,128,0, //Orange

108, 255,255,0, //Yellow

144, 0,255,0, //Green

180, 0,0,255, //Blue

216, 255,0,255, //Violet

255, 255,255,255 }; //White

CRGBPalette16 gPal = example_gp;

CRGBPalette16 gPal2;

void setup() 
{
  delay(3000);
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 20000);

   // ----------- Fire with pallete code --------------------
  // This first palette is the basic 'black body radiation' colors,
  // which run from black to red to bright yellow to white.
  gPal2 = HeatColors_p;
  
  // These are other ways to set up the color palette for the 'fire'.
  // First, a gradient from black to red to yellow to white -- similar to HeatColors_p
  //gPal2 = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::Yellow, CRGB::White);
  
  // Second, this palette is like the heat colors, but blue/aqua instead of red/yellow
  //gPal = CRGBPalette16( CRGB::Green, CRGB::Red, CRGB::White,  CRGB::Blue);
  //gPal = CRGBPalette16( CRGB::Black, CRGB::Green, CRGB::Aquamarine,  CRGB::White);
  //gPal = CRGBPalette16( CRGB::Black, CRGB::Purple, CRGB::Lavender,  CRGB::White);
  // Third, here's a simpler, three-step gradient, from black to red to white
  //   gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::White);
  
  //pinMode(AccelPin, INPUT);
  pinMode(PotPin, INPUT);
  pinMode(MicPin, INPUT);
  pinMode(ButtonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ButtonPin), debounceInterrupt, LOW); //Trinket
}

uint8_t gHue = 0; // rotating "base color" used by many of the patterns

//converted
void loop()
{
  random16_add_entropy( random());
  
  brightness = analogRead(PotPin);
  if (brightness != pastBrightness) 
  {
    uint16_t level = uint16_t(map(brightness, 0, 1023, 0, 100));
    FastLED.setBrightness(level);
  }
  
  if(mode==0)
  {
    FastLED.delay(1000/FRAMES_PER_SECOND); //add this to make twinle faster?
    EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  
    EVERY_N_SECONDS( SECONDS_PER_PALETTE ) 
    { 
      chooseNextColorPalette( gTargetPalette ); 
    }
    EVERY_N_MILLISECONDS( 10 ) 
    {
      nblendPaletteTowardPalette( gCurrentPalette, gTargetPalette, 12);
    }
    drawTwinkles(leds);
    FastLED.show();
  }
  else if(mode==1)
  {
    SoundReactiveSparkle(0);
  }
  else if(mode==2) 
  {
    SoundReactive(5);
  }
  else if(mode==3) 
  {
    //Fire(55,120,15);
    Fire2012WithPalette(120,120,15,1); //rainbow fire - mirrored
  }
  else if(mode==4) 
  {
    Fire2012WithPalette2(120,120,15,1); //regular fire - mirroed
  } 
  else if(mode==5)
  {
    rainbow(20);
  }
  else if(mode==6)
  {
    SimpleWave(5,2,50); //change to random hue instead of just RGB?
    //StrangerThings(15,100);
  }
  else if(mode==7)
  {
    Accel(0);
  }
  else if(mode==8)
  {
    AccelSlide(0); //very cool
  }
  else 
  {
    mode = 0;
  }
  
  pastBrightness = brightness;
  FastLED.show();
}
//no change for FL
void debounceInterrupt() {
  if((long)(micros() - last_micros) >= debouncing_time * 1000) 
  {
    Interrupt();
    last_micros = micros();
  }
}
//no change for FL
void Interrupt() 
{
  trigger = true;
  mode++;
}

//done?
void SoundReactiveSparkle(int wait) 
{
  int maxSound = 1024;
  int peakToPeak = getPeakToPeak();

  if (peakToPeak > lowBound) 
  {
    float divisor = float((maxSound - lowBound) / (NUM_LEDS-10));
    int numToLight = int((peakToPeak - lowBound) / divisor);

    int isOn[NUM_LEDS] = {0};

    // turn on a random selection of lights based on loudness
    for (int i = 0; i < numToLight; i++) 
    {
      bool litLight = false;
      while (litLight == false) 
      {
        int turnOn = random(NUM_LEDS);
        if (isOn[turnOn] == 0) 
        {
          leds[turnOn] = CHSV(random8(),255,255);
          //pixels.setPixelColor(turnOn,listColors[random(7)]);
          isOn[turnOn] = 1;
          litLight = true;
        }
        if(trigger)
        {
          trigger = false;
          return;
        }
      }
    }

    // turn the rest of the lights off
    
    for (int i = 0; i < NUM_LEDS; i++) 
    {
      if (isOn[i] == 0) 
      {
        leds[i] = CRGB::Black;
        //pixels.setPixelColor(i, CRGB::Black);
        if(trigger)
        {
          trigger = false;
          return;
        }
      }
    }
    
    FastLED.show();
    delay(wait);
  } 
  else 
  {
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
  }
}

void SoundReactive(int wait) 
{
  int peakToPeak = getPeakToPeak();
  int soundLevel = map(peakToPeak,0,900,32,0);
  Serial.println(soundLevel);

  for (int i = 32; i >= soundLevel; i--) //32 is the size of the half LEDs array, don't use sizeof function though, it is too slow
  {
    leds[lefthalf[i]] = CHSV(random8(),255,255);
    leds[righthalf[i]] = CHSV(random8(),255,255);
    FastLED.show();
    if(trigger)
    {
      trigger = false;
      return;
    }
    delay(wait);
  }
  fill_solid(leds, NUM_LEDS, CRGB::Black);
} 

//no change for FL
int getPeakToPeakAccel() 
{
  unsigned long startMillis= millis();  // Start of sample window
  unsigned int peakToPeak;
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  //50 is the same size, 50ms
  while (millis() - startMillis < 50) 
  {
    sample = analogRead(AccelPin); 
    Serial.println(sample);
    if (sample < 1024) 
    { // toss out spurious readings
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
  
  return peakToPeak;
}

//no change for FL
int getPeakToPeak() 
{
  unsigned long startMillis= millis();  // Start of sample window
  unsigned int peakToPeak;
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  //50 is the same size, 50ms
  while (millis() - startMillis < 25) 
  {
    sample = analogRead(MicPin); 
    if (sample < 1024) 
    { // toss out spurious readings
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
  
  return peakToPeak;
}
//done
void Accel(int wait) 
{
  int peakToPeak = getPeakToPeakAccel();
  int lightPixels = map(peakToPeak, 0, NUM_LEDS, 0, 32);

  for (int i = 0; i <= lightPixels; i++) 
  {
    leds[lefthalf[i]] = CHSV(random8(),255,255);
    leds[righthalf[i]] = CHSV(random8(),255,255);
    //pixels.setPixelColor(lefthalf[i],CHSV(random8(),255,255)]);
    //pixels.setPixelColor(righthalf[i],CHSV(random8(),255,255)]);
    FastLED.show();
    if(trigger)
    {
      trigger = false;
      return;
    }
  }
  fill_solid(leds, NUM_LEDS, CRGB::Black);
} 

void AccelWalk(int wait) 
{
  int peakToPeak = getPeakToPeakAccel();
  int lightPixels = map(peakToPeak, 0, NUM_LEDS, 16, 0);
  
  
  for (int i = 16; i <= 32 - lightPixels; i++) 
  {
    leds[lefthalf[i]] = CHSV(random8(),255,255);
    leds[righthalf[i]] = CHSV(random8(),255,255);
    FastLED.show();  
    if(trigger)
    {
      trigger = false;
      return;
    }
  }
  for (int j = 16; j >= lightPixels; j--) 
  {
    leds[lefthalf[j]] = CHSV(random8(),255,255);
    leds[righthalf[j]] = CHSV(random8(),255,255);
    FastLED.show();  
    if(trigger)
    {
      trigger = false;
      return;
    }
  }
  fill_solid(leds, NUM_LEDS, CRGB::Black);
} 

//done?
void Travel(int wait) 
{
  for (int i = 0; i <= 32; i++) 
  {
    if(forward)
    {
      leds[lefthalf[i]] = CHSV(random8(),255,255);
      leds[lefthalf[i-1]] = CRGB::Black;

      if(i==32)
      {
        forward=false;
        i=0;  
      }
    }
    else
    {
      leds[righthalf[i]] = CHSV(random8(),255,255);
      leds[righthalf[i-1]] = CRGB::Black;   
    }
    FastLED.show();
    if(trigger)
    {
      trigger = false;
      return;
    }
    delay(wait);
  }
  forward=true;
} 

void AccelSlide(int wait) 
{
  int maxZ = 400;
  int minZ = 290;

  int sample = analogRead(AccelPin);
  //Serial.println(sample);
  int blobPosition = map(sample, minZ, maxZ, 32, 1);

  leds[lefthalf[blobPosition]] = CHSV(random8(),255,255);
  leds[righthalf[blobPosition]] = CHSV(random8(),255,255);
  leds[lefthalf[blobPosition+1]] = CHSV(random8(),255,255);
  leds[righthalf[blobPosition+1]] = CHSV(random8(),255,255);
  leds[lefthalf[blobPosition-1]] = CHSV(random8(),255,255);
  leds[righthalf[blobPosition-1]] = CHSV(random8(),255,255);
  FastLED.show();

  for (int i = 0; i <= 32; i++) 
  {
    if(i==blobPosition || i==blobPosition+1 || i==blobPosition-1)
    {
      continue;
    }
    else
    {
      leds[lefthalf[i]] = CRGB::Black;
      leds[righthalf[i]] = CRGB::Black;  
    }
    if(trigger)
    {
      trigger = false;
      return;
    }
  }
  fill_solid(leds, NUM_LEDS, CRGB::Black);
} 

void SimpleWave(float rate,int cycles, int wait) 
{
  float pos=0.0;
  // cycle through x times
  for(int x=0; x<cycles; x++)
  {
    pos = pos+rate;
    for(int i=0; i<NUM_LEDS; i++) 
    {
      // sine wave, 3 offset waves make a rainbow!
      //float level = sin(i+pos) * 127 + 128;
      // set color level 
      //leds[i] = CHSV((int)level*(random(0,11)/10),255,255);
      leds[i] = CHSV(random8(),255,255);
      if(trigger)
      {
        trigger = false;
        return;
      }
    }
    FastLED.show();
    delay(wait);
  }
}

void CylonBounce(int EyeSize, int SpeedDelay, int ReturnDelay)
{
  int number = 0;
  // forward
  for(int i = 0; i < NUM_LEDS-EyeSize+1; i++)
  {
    for(int j = 0; j < EyeSize; j++) 
    {
      leds[i+j] = CRGB::Red;
    }

    // set all other pixels CRGB::Black
    if (i > 0) {
      for(int j = 0; j < i; j++) 
      {
        leds[j] = CRGB::Black;
        if(trigger)
        {
          trigger = false;
          return;
        }
      }
    }
    if (i+EyeSize < NUM_LEDS) 
    {
      for(int j = i+EyeSize; j < NUM_LEDS; j++) 
      {
        leds[j] = CRGB::Black;
        if(trigger)
        {
          trigger = false;
          return;
        }
      }
    }
    
    FastLED.show();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);

  // backward
  for(int i = NUM_LEDS-EyeSize-2; i > 0; i--) 
  {
    for(int j = 0; j < EyeSize; j++) 
    {
      leds[i+j] = CRGB::Red;
      if(trigger)
      {
        trigger = false;
        return;
      }
    }

    // set all other pixels CRGB::Black
    if (i > 0) 
    {
      for(int j = 0; j < i; j++) 
      {
        leds[j] = CRGB::Black;
        if(trigger)
        {
          trigger = false;
          return;
        }
      }
    }
    if (i+EyeSize < NUM_LEDS) 
    {
      for(int j = i+EyeSize; j < NUM_LEDS; j++) 
      {
        leds[j] = CRGB::Black;
        if(trigger)
        {
          trigger = false;
          return;
        }
      }
    }
    
    FastLED.show();
    delay(SpeedDelay);
  } 
  delay(ReturnDelay);
}

void travellingDot()
{
  int number = 0;
  for(int i=0; i<NUM_LEDS; i++)
  {
    leds[i] = CHSV(random8(),255,255);
    FastLED.show();
    delay(30);
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    if(trigger)
    {
      trigger = false;
      return;
    }
  }
  for(int j=NUM_LEDS-1; j>=0; j--)
  {
    leds[j] = CHSV(random8(),255,255);
    FastLED.show();
    delay(30);
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    if(trigger)
    {
      trigger = false;
      return;
    }
  }
}

void Fire2012WithPalette(int COOLING, int SPARKING, int SpeedDelay, int Mirror)
{
// Array of temperature readings at each simulation cell
  static uint8_t heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LEDS; i++) 
    {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LEDS - 1; k >= 2; k--) 
    {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) 
    {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_LEDS - MIRROR; j++) 
    {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      uint8_t colorindex = scale8( heat[j], 240);
      CRGB color = ColorFromPalette( gPal, colorindex);
      int pixelnumber;
      if( gReverseDirection ) 
      {
        pixelnumber = (NUM_LEDS-1) - j;
      } 
      else 
      {
        pixelnumber = j;
      }
      leds[pixelnumber+MIRROR] = color;
      leds[MIRROR-pixelnumber] = color;
    }
    delay(SpeedDelay);
}

void Fire2012WithPalette2(int COOLING, int SPARKING, int SpeedDelay, int Mirror)
{
// Array of temperature readings at each simulation cell
  static uint8_t heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LEDS; i++) 
    {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LEDS - 1; k >= 2; k--) 
    {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) 
    {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_LEDS - MIRROR; j++) 
    {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      uint8_t colorindex = scale8( heat[j], 240);
      CRGB color = ColorFromPalette( gPal2, colorindex);
      int pixelnumber;
      if( gReverseDirection ) 
      {
        pixelnumber = (NUM_LEDS-1) - j;
      } 
      else 
      {
        pixelnumber = j;
      }
      leds[pixelnumber+MIRROR] = color;
      leds[MIRROR-pixelnumber] = color;
    }
    delay(SpeedDelay);
}

void Fire(int Cooling, int Sparking, int SpeedDelay) {
  static byte heat[NUM_LEDS];
  int cooldown;
  
  // Step 1.  Cool down every cell a little
  for( int i = 0; i < NUM_LEDS; i++) {
    cooldown = random(0, ((Cooling * 10) / NUM_LEDS) + 2);
    
    if(cooldown>heat[i]) {
      heat[i]=0;
    } else {
      heat[i]=heat[i]-cooldown;
    }
  }
  
  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for( int k= NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }
    
  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160,255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for( int j = 0; j < NUM_LEDS; j++) {
    setPixelHeatColor(j, heat[j] );
  }

  FastLED.show();
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
    leds[Pixel] = CRGB(255, 255, heatramp);
  } else if( t192 > 0x40 ) {             // middle
    leds[Pixel] = CRGB(255, heatramp, 0);
  } else {                               // coolest
    leds[Pixel] = CRGB(heatramp, 0, 0);
  }
}


/*
void Fire(int Cooling, int Sparking, int SpeedDelay) {
  static byte heat[60];
  int cooldown;
  
  // Step 1.  Cool down every cell a little
  for( int i = 0; i < NUM_LEDS; i++) {
    cooldown = random(0, ((Cooling * 10) / NUM_LEDS) + 2);
    if(trigger)
    {
      trigger = false;
      return;
    }
    
    if(cooldown>heat[i]) {
      heat[i]=0;
    } else {
      heat[i]=heat[i]-cooldown;
    }
  }
  
  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for( int k= NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
    if(trigger)
    {
      trigger = false;
      return;
    }
  }
    
  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160,255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for( int j = 0; j < NUM_LEDS; j++) {
    setPixelHeatColor(j, heat[j] );
    if(trigger)
    {
      trigger = false;
      return;
    }
  }

  FastLED.show();
  delay(SpeedDelay);
}


void FireSparkle(int Cooling, int Sparking, int SpeedDelay) {
  static byte heat[60];
  int cooldown;
  
  // Step 1.  Cool down every cell a little
  for( int i = 0; i < NUM_LEDS; i++) {
    cooldown = random(0, ((Cooling * 10) / NUM_LEDS) + 2);
    if(trigger)
    {
      trigger = false;
      return;
    }
    if(cooldown>heat[i]) {
      heat[i]=0;
    } else {
      heat[i]=heat[i]-cooldown;
    }
  }
  
  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for( int k= NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
    if(trigger)
    {
      trigger = false;
      return;
    }
  }
    
  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160,255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for( int j = 0; j < NUM_LEDS; j++) {
    setPixelHeatColor(j, heat[j] );
    if(trigger)
    {
      trigger = false;
      return;
    }
  }

  FastLED.show();
  delay(SpeedDelay);
}

void setPixelHeatColor (int Pixel, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature/255.0)*191);
 
  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252
 
  // figure out which third of the spectrum we're in:
  if( t192 > 0x80) 
  {                     // hottest
    leds[Pixel] = CRGB(random(0,256), random(0,256), random(0,256));
    //pixels.setPixelColor(Pixel, random(0,256), random(0,256), random(0,256));
  } 
  else if( t192 > 0x40 ) 
  {             // middle
    leds[Pixel] = CRGB(random(0,256), random(0,256), 0);
    //pixels.setPixelColor(Pixel, random(0,256), random(0,256), 0);
  } 
  else 
  {                // coolest
    leds[Pixel] = CRGB(random(0,256), 0, 0);
    //pixels.setPixelColor(Pixel, heatramp, 0, 0);
  }
}

void setPixelSparkleColor (int Pixel, byte temperature) 
{
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature/255.0)*191);
 
  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252
 
  // figure out which third of the spectrum we're in:
  if( t192 > 0x80) 
  {                     // hottest
    leds[Pixel] = CRGB(random(0,256), random(0,256), random(0,256));
    //pixels.setPixelColor(Pixel, random(0,256), random(0,256), random(0,256));
  } 
  else if( t192 > 0x40 ) 
  {             // middle
    leds[Pixel] = CRGB(random(0,256)/2, random(0,256)/2, random(0,256)/2);
    //pixels.setPixelColor(Pixel, random(0,256)/2, random(0,256)/2, random(0,256)/2);
  } 
  else 
  {                               // coolest
    leds[Pixel] = CRGB(random(0,256)/4, random(0,256)/4, random(0,256)/4);
    //pixels.setPixelColor(Pixel, random(0,256)/4, random(0,256)/4, random(0,256)/4);
  }
}
*/

void Sparkle(int Count, int wait) 
{
  //create zero array of lights
  int isOn[NUM_LEDS] = {0};

  // light random lights, but only if not turned on already
  for (int i=0; i<Count; i++) {
    bool litLight = false;
    while (litLight == false) {
      int turnOn = random(NUM_LEDS);
      if (isOn[turnOn] == 0) 
      {
        leds[turnOn] = CHSV(random8(),255,255);
        //pixels.setPixelColor(turnOn,listColors[random(7)]);
        isOn[turnOn] = 1;
        litLight = true;
      }
      if(trigger)
      {
        trigger = false;
        return;
      }
    }
  }

  // turn the rest of the lights off
  for (int i = 0; i < NUM_LEDS; i++) {
    if (isOn[i] == 0) {
      leds[i] = CRGB::Black;
      //pixels.setPixelColor(i, CRGB::Black);
      if(trigger)
      {
        trigger = false;
        return;
      }
    }
  }
  
  FastLED.show();
  delay(wait);
}

void StrangerThings(int Count, int wait) {
  // set background
  fill_solid(leds, NUM_LEDS, CRGB::Black);

  //create zero array of lights
  int isOn[NUM_LEDS] = {0};

  // light random lights, but only if not turned on already
  for (int i=0; i<Count; i++) {
    bool litLight = false;
    while (litLight == false) {
      int turnOn = random(NUM_LEDS);
      if (isOn[turnOn] == 0) 
      {
        leds[turnOn] = CHSV(random8(),255,255);
        //pixels.setPixelColor(turnOn,listColors[random(7)]);
        isOn[turnOn] = 1;
        litLight = true;
      }
      if(trigger)
      {
        trigger = false;
        return;
      }
    }
    FastLED.show();
    delay(wait);
  }
  fill_solid(leds, NUM_LEDS, CRGB::Black); 
  delay(wait);
}

void colorWipe(CRGB myColor, uint8_t wait) 
{
  for(int i=0; i<NUM_LEDS; i++) 
  {
      leds[i] = myColor;
      //pixels.setPixelColor(i, c);
      FastLED.show();
      delay(wait);
      if(trigger)
      {
        trigger = false;
        return;
      }
  }
}

void rainbow(uint8_t wait) 
{
  uint16_t i, j;
  for(j=0; j<256; j++) 
  {
    for(i=0; i<NUM_LEDS; i++) 
    {
      leds[i] = Wheel( (i+j) % 255);
      //pixels.setPixelColor(i, Wheel((i+j) & 255));
      if(trigger)
      {
        trigger = false;
        return;
      }
    }
    FastLED.show();
    delay(wait);
  }
}
void TheaterChaseRainbow(uint8_t wait) 
{
  for (int j=0; j < 256; j++) 
  {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) 
    {
        for (int i=0; i < NUM_LEDS; i=i+3) 
        {
          leds[i+q] = Wheel( (i+j) % 255);
          //pixels.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
          if(trigger)
          {
            trigger = false;
            return;
          }
        }
        FastLED.show();
       
        delay(wait);
       
        for (int i=0; i < NUM_LEDS; i=i+3) 
        {
          leds[i+q] = CRGB::Black;
          //pixels.setPixelColor(i+q, 0);        //turn every third pixel off
          if(trigger)
          {
            trigger = false;
            return;
          }
        }
    }
  }
}

//done
void randomCycle(int count)
{
  //uint32_t c;
  int pixel = random(0,62);
  byte color = random(7);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  leds[pixel] = CHSV(random8(),255,255);
  //pixels.setPixelColor(pixel,listColors[color]);
  FastLED.show();
  delay(20); 
}

CRGB Wheel(byte WheelPos) 
{
  if(WheelPos < 85) 
  {
    return CRGB(WheelPos * 3, 255 - WheelPos * 3, 0);
    //return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) 
  {
    WheelPos -= 85;
    return CRGB(255 - WheelPos * 3, 0, WheelPos * 3);
    //return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else 
  {
    WheelPos -= 170;
    return CRGB(0, WheelPos * 3, 255 - WheelPos * 3);
    //return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}


void drawTwinkles( CRGBSet& L)
{
  // "PRNG16" is the pseudorandom number generator
  // It MUST be reset to the same starting value each time
  // this function is called, so that the sequence of 'random'
  // numbers that it generates is (paradoxically) stable.
  uint16_t PRNG16 = 11337;
  
  uint32_t clock32 = millis();

  // Set up the background color, "bg".
  // if AUTO_SELECT_BACKGROUND_COLOR == 1, and the first two colors of
  // the current palette are identical, then a deeply faded version of
  // that color is used for the background color
  CRGB bg;
  if( (AUTO_SELECT_BACKGROUND_COLOR == 1) &&
      (gCurrentPalette[0] == gCurrentPalette[1] )) {
    bg = gCurrentPalette[0];
    uint8_t bglight = bg.getAverageLight();
    if( bglight > 64) {
      bg.nscale8_video( 16); // very bright, so scale to 1/16th
    } else if( bglight > 16) {
      bg.nscale8_video( 64); // not that bright, so scale to 1/4th
    } else {
      bg.nscale8_video( 86); // dim, scale to 1/3rd.
    }
  } else {
    bg = gBackgroundColor; // just use the explicitly defined background color
  }

  uint8_t backgroundBrightness = bg.getAverageLight();
  
  for( CRGB& pixel: L) {
    PRNG16 = (uint16_t)(PRNG16 * 2053) + 1384; // next 'random' number
    uint16_t myclockoffset16= PRNG16; // use that number as clock offset
    PRNG16 = (uint16_t)(PRNG16 * 2053) + 1384; // next 'random' number
    // use that number as clock speed adjustment factor (in 8ths, from 8/8ths to 23/8ths)
    uint8_t myspeedmultiplierQ5_3 =  ((((PRNG16 & 0xFF)>>4) + (PRNG16 & 0x0F)) & 0x0F) + 0x08;
    uint32_t myclock30 = (uint32_t)((clock32 * myspeedmultiplierQ5_3) >> 3) + myclockoffset16;
    uint8_t  myunique8 = PRNG16 >> 8; // get 'salt' value for this pixel

    // We now have the adjusted 'clock' for this pixel, now we call
    // the function that computes what color the pixel should be based
    // on the "brightness = f( time )" idea.
    CRGB c = computeOneTwinkle( myclock30, myunique8);

    uint8_t cbright = c.getAverageLight();
    int16_t deltabright = cbright - backgroundBrightness;
    if( deltabright >= 32 || (!bg)) {
      // If the new pixel is significantly brighter than the background color, 
      // use the new color.
      pixel = c;
    } else if( deltabright > 0 ) {
      // If the new pixel is just slightly brighter than the background color,
      // mix a blend of the new color and the background color
      pixel = blend( bg, c, deltabright * 8);
    } else { 
      // if the new pixel is not at all brighter than the background color,
      // just use the background color.
      pixel = bg;
    }
  }
}


//  This function takes a time in pseudo-milliseconds,
//  figures out brightness = f( time ), and also hue = f( time )
//  The 'low digits' of the millisecond time are used as 
//  input to the brightness wave function.  
//  The 'high digits' are used to select a color, so that the color
//  does not change over the course of the fade-in, fade-out
//  of one cycle of the brightness wave function.
//  The 'high digits' are also used to determine whether this pixel
//  should light at all during this cycle, based on the TWINKLE_DENSITY.
CRGB computeOneTwinkle( uint32_t ms, uint8_t salt)
{
  uint16_t ticks = ms >> (8-TWINKLE_SPEED);
  uint8_t fastcycle8 = ticks;
  uint16_t slowcycle16 = (ticks >> 8) + salt;
  slowcycle16 += sin8( slowcycle16);
  slowcycle16 =  (slowcycle16 * 2053) + 1384;
  uint8_t slowcycle8 = (slowcycle16 & 0xFF) + (slowcycle16 >> 8);
  
  uint8_t bright = 0;
  if( ((slowcycle8 & 0x0E)/2) < TWINKLE_DENSITY) {
    bright = attackDecayWave8( fastcycle8);
  }

  uint8_t hue = slowcycle8 - salt;
  CRGB c;
  if( bright > 0) {
    c = ColorFromPalette( gCurrentPalette, hue, bright, NOBLEND);
    if( COOL_LIKE_INCANDESCENT == 1 ) {
      coolLikeIncandescent( c, fastcycle8);
    }
  } else {
    c = CRGB::Black;
  }
  return c;
}


// This function is like 'triwave8', which produces a 
// symmetrical up-and-down triangle sawtooth waveform, except that this
// function produces a triangle wave with a faster attack and a slower decay:
//
//     / \ 
//    /     \ 
//   /         \ 
//  /             \ 
//

uint8_t attackDecayWave8( uint8_t i)
{
  if( i < 86) {
    return i * 3;
  } else {
    i -= 86;
    return 255 - (i + (i/2));
  }
}

// This function takes a pixel, and if its in the 'fading down'
// part of the cycle, it adjusts the color a little bit like the 
// way that incandescent bulbs fade toward 'red' as they dim.
void coolLikeIncandescent( CRGB& c, uint8_t phase)
{
  if( phase < 128) return;

  uint8_t cooling = (phase - 128) >> 4;
  c.g = qsub8( c.g, cooling);
  c.b = qsub8( c.b, cooling * 2);
}

// A mostly red palette with green accents and white trim.
// "CRGB::Gray" is used as white to keep the brightness more uniform.
const TProgmemRGBPalette16 RedGreenWhite_p FL_PROGMEM =
{  CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, 
   CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, 
   CRGB::Red, CRGB::Red, CRGB::Gray, CRGB::Gray, 
   CRGB::Green, CRGB::Green, CRGB::Green, CRGB::Green };

// A mostly (dark) green palette with red berries.
#define Holly_Green 0x00580c
#define Holly_Red   0xB00402
const TProgmemRGBPalette16 Holly_p FL_PROGMEM =
{  Holly_Green, Holly_Green, Holly_Green, Holly_Green, 
   Holly_Green, Holly_Green, Holly_Green, Holly_Green, 
   Holly_Green, Holly_Green, Holly_Green, Holly_Green, 
   Holly_Green, Holly_Green, Holly_Green, Holly_Red 
};

// A red and white striped palette
// "CRGB::Gray" is used as white to keep the brightness more uniform.
const TProgmemRGBPalette16 RedWhite_p FL_PROGMEM =
{  CRGB::Red,  CRGB::Red,  CRGB::Red,  CRGB::Red, 
   CRGB::Gray, CRGB::Gray, CRGB::Gray, CRGB::Gray,
   CRGB::Red,  CRGB::Red,  CRGB::Red,  CRGB::Red, 
   CRGB::Gray, CRGB::Gray, CRGB::Gray, CRGB::Gray };

// A mostly blue palette with white accents.
// "CRGB::Gray" is used as white to keep the brightness more uniform.
const TProgmemRGBPalette16 BlueWhite_p FL_PROGMEM =
{  CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::Blue, 
   CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::Blue, 
   CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::Blue, 
   CRGB::Blue, CRGB::Gray, CRGB::Gray, CRGB::Gray };

// A pure "fairy light" palette with some brightness variations
#define HALFFAIRY ((CRGB::FairyLight & 0xFEFEFE) / 2)
#define QUARTERFAIRY ((CRGB::FairyLight & 0xFCFCFC) / 4)
const TProgmemRGBPalette16 FairyLight_p FL_PROGMEM =
{  CRGB::FairyLight, CRGB::FairyLight, CRGB::FairyLight, CRGB::FairyLight, 
   HALFFAIRY,        HALFFAIRY,        CRGB::FairyLight, CRGB::FairyLight, 
   QUARTERFAIRY,     QUARTERFAIRY,     CRGB::FairyLight, CRGB::FairyLight, 
   CRGB::FairyLight, CRGB::FairyLight, CRGB::FairyLight, CRGB::FairyLight };

// A palette of soft snowflakes with the occasional bright one
const TProgmemRGBPalette16 Snow_p FL_PROGMEM =
{  0x304048, 0x304048, 0x304048, 0x304048,
   0x304048, 0x304048, 0x304048, 0x304048,
   0x304048, 0x304048, 0x304048, 0x304048,
   0x304048, 0x304048, 0x304048, 0xE0F0FF };

// A palette reminiscent of large 'old-school' C9-size tree lights
// in the five classic colors: red, orange, green, blue, and white.
#define C9_Red    0xB80400
#define C9_Orange 0x902C02
#define C9_Green  0x046002
#define C9_Blue   0x070758
#define C9_White  0x606820
const TProgmemRGBPalette16 RetroC9_p FL_PROGMEM =
{  C9_Red,    C9_Orange, C9_Red,    C9_Orange,
   C9_Orange, C9_Red,    C9_Orange, C9_Red,
   C9_Green,  C9_Green,  C9_Green,  C9_Green,
   C9_Blue,   C9_Blue,   C9_Blue,
   C9_White
};

// A cold, icy pale blue palette
#define Ice_Blue1 0x0C1040
#define Ice_Blue2 0x182080
#define Ice_Blue3 0x5080C0
const TProgmemRGBPalette16 Ice_p FL_PROGMEM =
{
  Ice_Blue1, Ice_Blue1, Ice_Blue1, Ice_Blue1,
  Ice_Blue1, Ice_Blue1, Ice_Blue1, Ice_Blue1,
  Ice_Blue1, Ice_Blue1, Ice_Blue1, Ice_Blue1,
  Ice_Blue2, Ice_Blue2, Ice_Blue2, Ice_Blue3
};


// Add or remove palette names from this list to control which color
// palettes are used, and in what order.
const TProgmemRGBPalette16* ActivePaletteList[] = {
  &RetroC9_p,
  &BlueWhite_p,
  &RainbowColors_p,
  &FairyLight_p,
  &RedGreenWhite_p,
  &PartyColors_p,
  &RedWhite_p,
  &Snow_p,
  &Holly_p,
  &Ice_p  
};


// Advance to the next color palette in the list (above).
void chooseNextColorPalette( CRGBPalette16& pal)
{
  const uint8_t numberOfPalettes = sizeof(ActivePaletteList) / sizeof(ActivePaletteList[0]);
  static uint8_t whichPalette = -1; 
  whichPalette = addmod8( whichPalette, 1, numberOfPalettes);

  pal = *(ActivePaletteList[whichPalette]);
}
