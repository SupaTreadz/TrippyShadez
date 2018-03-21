#include <Adafruit_NeoPixel.h>

#define NeopixelPin 6
#define AccelPin A3
#define MicPin A4
#define PotPin A5
#define ButtonPin 3

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(58, NeopixelPin);
  
uint32_t red = pixels.Color(255,0,0);
uint32_t orange = pixels.Color(255,50,0);
uint32_t yellow = pixels.Color(255,215,0);
uint32_t green = pixels.Color(0,255,0);
uint32_t blue = pixels.Color(0,0,255);
uint32_t purple = pixels.Color(255,0,200);
uint32_t white = pixels.Color(255,255,255);
uint32_t blank = pixels.Color(0,0,0);
int brightness = 0;
int pastBrightness = 0;
long debouncing_time = 15; //Debouncing Time in Milliseconds
volatile unsigned long last_micros;
unsigned int sample;
volatile byte mode = 8;
volatile boolean trigger = false;
unsigned int lowBound = 100;

// pixel orders
uint32_t lefthalf[] = {28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0};
uint32_t righthalf[] = {47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,48,49,50,51,52,53,54,55,56,57};

// color schemes
uint32_t listColors[] = {red, orange, yellow, green, blue, purple, white};
uint32_t holidayColors[] = {red, green};
uint32_t winterColors[] = {blue, purple, white};
uint32_t warmColors[] = {red, orange, yellow};
uint32_t brandColors[] = {yellow, green, blue, white};

void setup() 
{
  Serial.begin(9600);
  pixels.begin();

  //pinMode(AccelPin, INPUT);
  pinMode(PotPin, INPUT);
  pinMode(MicPin, INPUT);
  pinMode(ButtonPin, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(ButtonPin), debounceInterrupt, LOW); //Trinket
}

void loop()
{
  brightness = analogRead(PotPin);
  if (brightness != pastBrightness) {
    uint16_t level = uint16_t(map(brightness,0,1023,0, 100));
    pixels.setBrightness(level);
  }
  if(mode==0) 
  {
    //SoundReactive(10);
    SoundReactiveSparkle(10);
    //SoundReactiveColor(10);
  }
  else if(mode==1) 
  {
    SoundReactive(10);
    //SoundReactiveBrightness(10);
    //SoundReactiveColor(10);
  } 
  else if(mode==2) 
  {
    FireSparkle(55,120,15);
  } 
  else if(mode==3) 
  {
    rainbow(20);
  } 
  else if(mode==4)
  {
    Snake(15);
  }
  else if(mode==5)
  {
    SimpleWave(5,2,15);
  }
  else if(mode==6)
  {
    StrangerThings(15,100);
  }
  else if(mode==7)
  {
    Accel(10);
  }
  else if(mode==8)
  {
    AccelSlide(10);
  }
  else 
  {
    mode = 0;
  }
  pastBrightness = brightness;
}

void debounceInterrupt() {
  if((long)(micros() - last_micros) >= debouncing_time * 1000) 
  {
    Interrupt();
    last_micros = micros();
  }
}

void Interrupt() 
{
  trigger = true;
  mode++;
}

void AccelSlide(int wait) 
{
  int maxZ = 411;
  int minZ = 275;

  int sample = analogRead(AccelPin);
  //Serial.println(sample);
  int blobPosition = map(sample, minZ, maxZ, 27, 1);

  pixels.setPixelColor(lefthalf[blobPosition],listColors[random(0,8)]);
  pixels.setPixelColor(righthalf[blobPosition],listColors[random(0,8)]);
  pixels.setPixelColor(lefthalf[blobPosition+1],listColors[random(0,8)]);
  pixels.setPixelColor(righthalf[blobPosition+1],listColors[random(0,8)]);
  pixels.setPixelColor(lefthalf[blobPosition-1],listColors[random(0,8)]);
  pixels.setPixelColor(righthalf[blobPosition-1],listColors[random(0,8)]);
  pixels.show();

  for (int i = 0; i <= 28; i++) 
  {
    if(i==blobPosition || i==blobPosition+1 || i==blobPosition-1)
    {
      continue;
    }
    else
    {
      pixels.setPixelColor(lefthalf[i],blank);
      pixels.setPixelColor(righthalf[i],blank);  
    }
    
  }
    
  delay(wait);
  allSet(blank);
} 

void Accel(int wait) 
{
  int peakToPeak = getPeakToPeakAccel();
  //Serial.println(peakToPeak);
  int lightPixels = map(peakToPeak, 0, 100, 0, 28);

  for (int i = 0; i <= lightPixels; i++) 
  {
    pixels.setPixelColor(lefthalf[i],listColors[random(0,8)]);
    pixels.setPixelColor(righthalf[i],listColors[random(0,8)]);
    pixels.show();
    if(trigger)
    {
      trigger = false;
      return;
    }
    delay(wait);
  }
  allSet(blank);
} 

void Snake(int wait) {
  for (int j = 0; j < 6; j++) {
    // forward
    for (int i = 0; i < pixels.numPixels()/2; i++) {
      pixels.setPixelColor(i,listColors[j]);
      pixels.setPixelColor(pixels.numPixels()-1-i,listColors[j]);
      pixels.show();
      delay(wait);
      if(trigger)
      {
        trigger = false;
        return;
      }
    }

    // backward
    for (int i = pixels.numPixels()/2 - 1; i >= 0; i--) {
      pixels.setPixelColor(i,blank);
      pixels.setPixelColor(pixels.numPixels()-1-i,blank);
      pixels.show();
      delay(wait);
      if(trigger)
      {
        trigger = false;
        return;
      }
    }
  }
}

void SnakeReverse(int wait) {
  for (int j = 0; j < 6; j++) {
    // forward
    for (int i = pixels.numPixels()/2 - 1; i >= 0; i--) {
      pixels.setPixelColor(i,listColors[j]);
      pixels.setPixelColor(pixels.numPixels()-1-i,listColors[j]);
      pixels.show();
      delay(wait);
      if(trigger)
      {
        trigger = false;
        return;
      }
    }

    // backward
    for (int i = 0; i < pixels.numPixels()/2; i++) {
      pixels.setPixelColor(i,blank);
      pixels.setPixelColor(pixels.numPixels()-1-i,blank);
      pixels.show();
      delay(wait);
      if(trigger)
      {
        trigger = false;
        return;
      }
    }
  }
}

void pixelsSet(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, c);
      if(trigger)
      {
        trigger = false;
        return;
      }
  }
  // move the show outside the loop
  pixels.show();
  delay(wait);
}

void SimpleWave(float rate,int cycles, int wait) {
   float pos=0.0;
  // cycle through x times
  for(int x=0; x<cycles; x++)
  {
    pos = pos+rate;
    for(int i=0; i<pixels.numPixels(); i++) {
      // sine wave, 3 offset waves make a rainbow!
      float level = sin(i+pos) * 127 + 128;
      // set color level 
      pixels.setPixelColor(i,(int)level*(random(0,11)/10),(int)level*(random(0,11)/10),(int)level*(random(0,11)/10));
      if(trigger)
      {
        trigger = false;
        return;
      }
    }
    pixels.show();
    delay(wait);
  }
}
int getPeakToPeakAccel() 
{
  unsigned long startMillis= millis();  // Start of sample window
  unsigned int peakToPeak;
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  //50 is the same size, 50ms
  while (millis() - startMillis < 50) {
    sample = analogRead(AccelPin); 
    Serial.println(sample);
    if (sample < 1024) { // toss out spurious readings
        if (sample > signalMax) {
          signalMax = sample;  // save just the max levels
        }
        else if (sample < signalMin) {
          signalMin = sample;  // save just the min levels
        }
     }
  }
 
  peakToPeak = signalMax - signalMin;
  
  return peakToPeak;
}
int getPeakToPeak() 
{
  unsigned long startMillis= millis();  // Start of sample window
  unsigned int peakToPeak;
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  //50 is the same size, 50ms
  while (millis() - startMillis < 50) {
    sample = analogRead(MicPin); 
    if (sample < 1024) { // toss out spurious readings
        if (sample > signalMax) {
          signalMax = sample;  // save just the max levels
        }
        else if (sample < signalMin) {
          signalMin = sample;  // save just the min levels
        }
     }
  }
 
  peakToPeak = signalMax - signalMin;
  
  return peakToPeak;
}

void SoundReactive(int wait) 
{
  int peakToPeak = getPeakToPeak();
  int soundLevel = map(peakToPeak,0,900,28,0);
  Serial.println(soundLevel);

  for (int i = 28; i >= soundLevel; i--) 
  {
    pixels.setPixelColor(lefthalf[i],listColors[random(0,8)]);
    pixels.setPixelColor(righthalf[i],listColors[random(0,8)]);
    pixels.show();
    if(trigger)
    {
      trigger = false;
      return;
    }
    delay(wait);
  }
  allSet(blank);
  
} 

void SoundReactiveReverse(int wait) {
  int maxSound = 1024;
  int peakToPeak = getPeakToPeak();

  if (peakToPeak > lowBound) {
    int halfLights = pixels.numPixels() / 2;
    float divisor = float((maxSound - lowBound) / halfLights);
    int numToLight = int((peakToPeak - lowBound) / divisor);
    
    for (int i = halfLights; i >= (halfLights - numToLight); i--) {
      pixels.setPixelColor(i,listColors[random(7)]);
      pixels.setPixelColor(pixels.numPixels()-1-i,listColors[random(7)]);
      if(trigger)
      {
        trigger = false;
        return;
      }
    }

    if ((halfLights - numToLight) > 0) {
      for (int i = 0; i < (halfLights - numToLight); i++) {
        pixels.setPixelColor(i,blank);
        pixels.setPixelColor(pixels.numPixels()-1-i,blank);
        if(trigger)
        {
          trigger = false;
          return;
        }
      }
    }
    
    pixels.show();
  } else {
    allSet(blank);
  }    
  delay(wait);
}

void SoundReactiveBrightness(int wait) {
  int peakToPeak = getPeakToPeak();
  int bound = 30;

  if (peakToPeak > bound) {
    int bright = map(peakToPeak, bound, 1023, 0, 255);
    for (int i = 0; i < pixels.numPixels(); i++) 
    {
      if ((i % 4 == 3) || (i % 4 == 2)) {
        // green
        pixels.setPixelColor(i,pixels.Color(0,bright,0));
      } else {
        // red
        pixels.setPixelColor(i,pixels.Color(bright,0,0));
      }
      if(trigger)
      {
        trigger = false;
        return;
      }
      
    }
    pixels.show();
  } else {
    allSet(blank);
  }
  delay(wait);
}

void SoundReactiveColor(int wait) {
  int maxSound = 1024;
  int peakToPeak = getPeakToPeak();
  int bound = 30;

  if (peakToPeak > bound) {
    // start with red => green
    int colorSum = map(peakToPeak, lowBound, 1023, 0, 255*2);
    uint32_t color;
    if (colorSum < 255) {
      color = pixels.Color(255-colorSum, 0, 0);
    } else {
      color = pixels.Color(255, 255*2-colorSum, 0);
    }
    allSet(color);
  } else {
    allSet(blank);
  }    
  delay(wait);
}

void SoundReactiveSparkle(int wait) {
  int maxSound = 1024;
  int peakToPeak = getPeakToPeak();

  if (peakToPeak > lowBound) {
    float divisor = float((maxSound - lowBound) / (pixels.numPixels()-10));
    int numToLight = int((peakToPeak - lowBound) / divisor);

    int isOn[pixels.numPixels()] = {0};

    // turn on a random selection of lights based on loudness
    for (int i = 0; i < numToLight; i++) 
    {
      bool litLight = false;
      while (litLight == false) 
      {
        int turnOn = random(pixels.numPixels());
        if (isOn[turnOn] == 0) {
          pixels.setPixelColor(turnOn,listColors[random(7)]);
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
    for (int i = 0; i < pixels.numPixels(); i++) {
      if (isOn[i] == 0) {
        pixels.setPixelColor(i, blank);
        if(trigger)
        {
          trigger = false;
          return;
        }
      }
    }
    
    pixels.show();
    delay(wait);
  } else {
    allSet(blank);
  }
}

void CylonBounce(int EyeSize, int SpeedDelay, int ReturnDelay){
  int number = 0;
  // forward
  for(int i = 0; i < pixels.numPixels()-EyeSize+1; i++) {
    for(int j = 0; j < EyeSize; j++) {
      pixels.setPixelColor(i+j,listColors[j]);
    }

    // set all other pixels blank
    if (i > 0) {
      for(int j = 0; j < i; j++) {
        pixels.setPixelColor(j, blank);
        if(trigger)
        {
          trigger = false;
          return;
        }
      }
    }
    if (i+EyeSize < pixels.numPixels()) {
      for(int j = i+EyeSize; j < pixels.numPixels(); j++) {
        pixels.setPixelColor(j, blank);
        if(trigger)
        {
          trigger = false;
          return;
        }
      }
    }
    
    pixels.show();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);

  // backward
  for(int i = pixels.numPixels()-EyeSize-2; i > 0; i--) {
    for(int j = 0; j < EyeSize; j++) {
      pixels.setPixelColor(i+j,listColors[j]);
      if(trigger)
      {
        trigger = false;
        return;
      }
    }

    // set all other pixels blank
    if (i > 0) {
      for(int j = 0; j < i; j++) {
        pixels.setPixelColor(j, blank);
        if(trigger)
        {
          trigger = false;
          return;
        }
      }
    }
    if (i+EyeSize < pixels.numPixels()) {
      for(int j = i+EyeSize; j < pixels.numPixels(); j++) {
        pixels.setPixelColor(j, blank);
        if(trigger)
        {
          trigger = false;
          return;
        }
      }
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
    pixels.setPixelColor(i,listColors[random(7)]);
    pixels.show();
    delay(30);
    allSet(blank);
    if(trigger)
    {
      trigger = false;
      return;
    }
  }
  for(int j=pixels.numPixels()-1; j>=0; j--)
  {
    pixels.setPixelColor(j,listColors[random(7)]);
    pixels.show();
    delay(30);
    allSet(blank);
    if(trigger)
    {
      trigger = false;
      return;
    }
  }
}

void Fire(int Cooling, int Sparking, int SpeedDelay) {
  static byte heat[60];
  int cooldown;
  
  // Step 1.  Cool down every cell a little
  for( int i = 0; i < pixels.numPixels(); i++) {
    cooldown = random(0, ((Cooling * 10) / pixels.numPixels()) + 2);
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
  for( int k= pixels.numPixels() - 1; k >= 2; k--) {
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
  for( int j = 0; j < pixels.numPixels(); j++) {
    setPixelHeatColor(j, heat[j] );
    if(trigger)
    {
      trigger = false;
      return;
    }
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
  for( int k= pixels.numPixels() - 1; k >= 2; k--) {
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
  for( int j = 0; j < pixels.numPixels(); j++) {
    setPixelHeatColor(j, heat[j] );
    if(trigger)
    {
      trigger = false;
      return;
    }
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

void Sparkle(int Count, int wait) {
  //create zero array of lights
  int isOn[pixels.numPixels()] = {0};

  // light random lights, but only if not turned on already
  for (int i=0; i<Count; i++) {
    bool litLight = false;
    while (litLight == false) {
      int turnOn = random(pixels.numPixels());
      if (isOn[turnOn] == 0) {
        pixels.setPixelColor(turnOn,listColors[random(7)]);
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
  for (int i = 0; i < pixels.numPixels(); i++) {
    if (isOn[i] == 0) {
      pixels.setPixelColor(i, blank);
      if(trigger)
      {
        trigger = false;
        return;
      }
    }
  }
  
  pixels.show();
  delay(wait);
}

void StrangerThings(int Count, int wait) {
  // set background
  allSet(blank);

  //create zero array of lights
  int isOn[pixels.numPixels()] = {0};

  // light random lights, but only if not turned on already
  for (int i=0; i<Count; i++) {
    bool litLight = false;
    while (litLight == false) {
      int turnOn = random(pixels.numPixels());
      if (isOn[turnOn] == 0) {
        pixels.setPixelColor(turnOn,listColors[random(7)]);
        isOn[turnOn] = 1;
        litLight = true;
      }
      if(trigger)
      {
        trigger = false;
        return;
      }
    }
    pixels.show();
    delay(wait);
  }
  allSet(blank); 
  delay(wait);
}

void colorWipe(uint32_t c, uint8_t wait) 
{
  for(int i=0; i<pixels.numPixels(); i++) 
  {
      pixels.setPixelColor(i, c);
      pixels.show();
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
    for(i=0; i<pixels.numPixels(); i++) 
    {
      pixels.setPixelColor(i, Wheel((i+j) & 255));
      if(trigger)
      {
        trigger = false;
        return;
      }
    }
    pixels.show();
    delay(wait);
  }
}
void TheaterChaseRainbow(uint8_t wait) 
{
  for (int j=0; j < 256; j++) 
  {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) 
    {
        for (int i=0; i < pixels.numPixels(); i=i+3) 
        {
          pixels.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
          if(trigger)
          {
            trigger = false;
            return;
          }
        }
        pixels.show();
       
        delay(wait);
       
        for (int i=0; i < pixels.numPixels(); i=i+3) 
        {
          pixels.setPixelColor(i+q, 0);        //turn every third pixel off
          if(trigger)
          {
            trigger = false;
            return;
          }
        }
    }
  }
}
void randomCycle(int count)
{
  //uint32_t c;
  int pixel = random(0,62);
  byte color = random(7);
  allSet(blank);
  pixels.show();
  pixels.setPixelColor(pixel,listColors[color]);
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
