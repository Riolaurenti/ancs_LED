void theLights() {
  runCheck(10);
  fadeToBlackBy(&(leds[0]), NUM_LEDS, 10);
  int pos = random16(0, NUM_LEDS);
  leds[pos] = ColorFromPalette( cPal, cycHue, brightness, currentBlending);
}

void rainbow() {
  runCheck(1);
  static int pHue = 0;
  static int hueStore;
    for (int i = 0; i < NUM_LEDS; i++) {
      pHue = i + cycHue;
      if (pHue > 255) {
         hueStore = pHue - 255;
         pHue = hueStore;
      }
    leds[i] = ColorFromPalette(cPal, pHue, brightness, currentBlending);
  }
}
void sinelon() {
   runCheck(10);
  fadeToBlackBy(&(leds[0]), NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS - 1 ) ;
  leds[pos] = ColorFromPalette( cPal, cycHue, brightness, currentBlending);
}

void bpm() {
  runCheck(10);
  uint8_t beat = beatsin8( 62, 64, 255);
  for (int i = 0; i < NUM_LEDS; i++) { 
    leds[i] = ColorFromPalette(cPal, cycHue + (i * 2), beat - 0 + (i * 10));
    }
}

void threeSine() {
  static byte sineOffset = 0; // counter for current position of sine waves
  runCheck(20);
  for (byte x = 0; x < kMatrixWidth; x++) {
    for (int y = 0; y < kMatrixHeight; y++) {
      byte sinDistanceR = qmul8(abs(y * (255 / kMatrixHeight) - sin8(sineOffset * 9 + x * 16)), 2);
      byte sinDistanceG = qmul8(abs(y * (255 / kMatrixHeight) - sin8(sineOffset * 10 + x * 16)), 2);
      byte sinDistanceB = qmul8(abs(y * (255 / kMatrixHeight) - sin8(sineOffset * 11 + x * 16)), 2);
      leds[XY(x, y)] = CRGB(255 - sinDistanceR, 255 - sinDistanceG, 255 - sinDistanceB);
    }
  }
  sineOffset++; // byte will wrap from 255 to 0, matching sin8 0-255 cycle
}

void plasma() {
  static byte offset  = 0; // counter for radial color wave motion
  static int plasVector = 0; // counter for orbiting plasma center
  runCheck(10);
  int xOffset = cos8(plasVector / 256);
  int yOffset = sin8(plasVector / 256);
  for (int x = 0; x < kMatrixWidth; x++) {
    for (int y = 0; y < kMatrixHeight; y++) {
      byte color = sin8(sqrt(sq(((float)x - 7.5) * 10 + xOffset - 127) + sq(((float)y - 2) * 10 + yOffset - 127)) + offset);
      leds[XY(x, y)] = CHSV(color, 255, 255);
    }
  }
  offset++; // wraps at 255 for sin8
  plasVector += 16; // using an int for slower orbit (wraps at 65536)
}

void rider() {
  static byte riderPos = 0;
  if (fxInit == false) {
    fxInit = true;
    fxDelay = 5;
    riderPos = 0;
  }
  for (byte x = 0; x < kMatrixWidth; x++) {
    int brightness = abs(x * (256 / kMatrixWidth) - triwave8(riderPos) * 2 + 127) * 3;
    if (brightness > 255) brightness = 255;
    brightness = 255 - brightness;
    CRGB riderColor = CHSV(cycHue, 255, brightness);
    for (byte y = 0; y < kMatrixHeight; y++) {
      leds[XY(x, y)] = riderColor;
    }
  }
  riderPos++; // byte wraps to 0 at 255, triwave8 is also 0-255 periodic
}


void slantBars() {
  static byte slantPos = 0;
  runCheck(5);
  for (byte x = 0; x < kMatrixWidth; x++) {
    for (byte y = 0; y < kMatrixHeight; y++) {
      leds[XY(x, y)] = CHSV(cycHue, 255, quadwave8(x * 32 + y + slantPos));
    }
  }
  slantPos -= 4;
}

void glitter() {
  runCheck(30);
  for (int x = 0; x < kMatrixWidth; x++) {
    for (int y = 0; y < kMatrixHeight; y++) {
      leds[XY(x, y)] = CHSV(cycHue, 255, random8(5) * 63);
    }
  }
}

#define rainDir 0
void sideRain() {
  runCheck(15);
  scrollArray(rainDir);
  byte randPixel = random8(kMatrixHeight);
  for (byte y = 0; y < kMatrixHeight; y++) leds[XY((kMatrixWidth - 1) * rainDir, y)] = CRGB::Black;
   leds[XY((kMatrixWidth - 1)*rainDir, randPixel)] = CHSV(cycHue, 255, 255);  
}

void confetti() {
  runCheck(30);
  //selectRandomPalette();
  // scatter random colored pixels at several random coordinates
  for (byte i = 0; i < 4; i++) {
    leds[XY(random16(kMatrixWidth), random16(kMatrixHeight))] = ColorFromPalette(cPal, random16(255), 255); //CHSV(random16(255), 255, 255);
    }
}

void colourFill() {
   fadeToBlackBy(&(leds[0]), NUM_LEDS, 20); // keep or not?
  static byte currentColor = 0;
  static byte currentRow = 0;
  static byte currentDirection = 0;
  if (fxInit == false) {
    fxInit = true;
    fxDelay = 45;
    currentColor = 0;
    currentRow = 0;
    currentDirection = 0;
    cPal = RainbowColors_p;
  }
  // test a bitmask to fill up or down when currentDirection is 0 or 2 (0b00 or 0b10)
  if (!(currentDirection & 1)) {
    fxDelay = 45; // slower since vertical has fewer pixels
    for (byte x = 0; x < kMatrixWidth; x++) {
      byte y = currentRow;
      if (currentDirection == 2) y = kMatrixHeight - 1 - currentRow;
      leds[XY(x, y)] = cPal[currentColor];
    }
  }
  // test a bitmask to fill left or right when currentDirection is 1 or 3 (0b01 or 0b11)
  if (currentDirection & 1) {
    fxDelay = 20; // faster since horizontal has more pixels
    for (byte y = 0; y < kMatrixHeight; y++) {
      byte x = currentRow;
      if (currentDirection == 3) x = kMatrixWidth - 1 - currentRow;
      leds[XY(x, y)] = cPal[currentColor];
    }
  }
  currentRow++;
  // detect when a fill is complete, change color and direction
  if ((!(currentDirection & 1) && currentRow >= kMatrixHeight) || ((currentDirection & 1) && currentRow >= kMatrixWidth)) {
    currentRow = 0;
    currentColor += random8(3, 6);
    if (currentColor > 15) currentColor -= 16;
    currentDirection++;
    if (currentDirection > 3) currentDirection = 0;
    fxDelay = 300; // wait a little bit longer after completing a fill
  }
}
void bouncingTrails(){ // this is some messy code - will come back to it...
   runCheck(10);
  //sets a "spawn" in the middle half of a strip then sends a trail in either direction which bounces of the ends of the strip.
  static int counter=0;//used to set a start point at 1
  static int lastCount=0;//i use this to be able to tell when the counter has increased. (had problems with if(counter++))
  static int paletteRef=0;//the number of the color, in the palette, to set.
  static int posUp=0;//holds the light that goes up the strip
  static int posDown=0;//holds the light that goes down the strip
  static byte upReversed=0;//if up hits the top of the strip, sets this to 1 and and runs back down the strip
  static byte downReversed=0;//as above, in reverse
  static int pos=0;//holds the initial position from which the two trails emerge
  counter++;
  if (counter==(kMatrixWidth*4)){//used a multiple of 2 so that a new point s formed when the two trails are close to each other (looks better in my opinon)
    counter=0;
  }
  if (lastCount!=counter){//if the counter has progressed
    //Run a fadeAll flag
    paletteRef=(counter*5);//used a multiple here as we want to adress as broad a rang from 0 - 256 as possible, with more LEDs be worth lowering this value.
  }
  if ((counter==1)&&(lastCount!=counter)){   
    pos = random16((kMatrixWidth/4),((kMatrixWidth/4)*3));//if on count 1, set the spawn, and clear the reversed states.
    downReversed=0;    upReversed=0;    posUp=pos;    posDown=pos;
    for (int i = 0; i < kMatrixHeight; i++){
        leds[(pos+(i*kMatrixWidth))]=ColorFromPalette( cPal, paletteRef, brightness, currentBlending);
    }
  }  
    if ((counter!=1)&&(lastCount!=counter)){//this set of if statements increment the trailing dots, and tarcks if they are reversed
    switch (upReversed){
      case  0:
        if(posUp!=kMatrixWidth-1){          posUp++;
          break;
        }
        else{          upReversed=1;          posUp--;
          break;
        }
      case 1:
        if(posUp!=0){          posUp--;
          break;
        }
        else{          upReversed=0;      posUp++;
          break;
        }
    }
    switch (downReversed){
      case 0:
        if (posDown!=0){          posDown--;
          break;
        }
        else{          downReversed=1;          posDown++;
          break;
        }
      case 1:
        if (posDown!=kMatrixWidth-1){          posDown++;
          break;
        }
        else{          downReversed=0;          posDown--;
          break;
        }
    }
    for (int i = 0; i < kMatrixHeight; i++){
        leds[(posUp+(i*kMatrixWidth))]=ColorFromPalette( cPal, paletteRef,  brightness, currentBlending);
        leds[(posDown+(i*kMatrixWidth))]=ColorFromPalette( cPal, paletteRef, brightness, currentBlending);
    }
  }
  lastCount=counter;
}

///also not working!
void BouncingBalls(byte red, byte green, byte blue, int BallCount) {
  runCheck(50);
  float Gravity = -9.81;
  int StartHeight = 1;
  float Height[BallCount];
  float ImpactVelocityStart = sqrt( -2 * Gravity * StartHeight );
  float ImpactVelocity[BallCount];
  float TimeSinceLastBounce[BallCount];
  int   Position[BallCount];
  long  ClockTimeSinceLastBounce[BallCount];
  float Dampening[BallCount];
  
  for (int i = 0 ; i < BallCount ; i++) {  
    ClockTimeSinceLastBounce[i] = millis();
    Height[i] = StartHeight;
    Position[i] = 0;
    ImpactVelocity[i] = ImpactVelocityStart;
    TimeSinceLastBounce[i] = 0;
    Dampening[i] = 0.90 - float(i)/pow(BallCount,2);
  }

  while (true) {
    for (int i = 0 ; i < BallCount ; i++) {
      TimeSinceLastBounce[i] =  millis() - ClockTimeSinceLastBounce[i];
      Height[i] = 0.5 * Gravity * pow( TimeSinceLastBounce[i]/1000 , 2.0 ) + ImpactVelocity[i] * TimeSinceLastBounce[i]/1000;
 
      if ( Height[i] < 0 ) {                      
        Height[i] = 0;
        ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
        ClockTimeSinceLastBounce[i] = millis();
 
        if ( ImpactVelocity[i] < 0.01 ) {
          ImpactVelocity[i] = ImpactVelocityStart;
        }
      }
      Position[i] = round( Height[i] * (NUM_LEDS - 1) / StartHeight);
    }
 
    for (int i = 0 ; i < BallCount ; i++) {
      setPixel(Position[i],red,green,blue);
    } 
    //setAll(0,0,0);
  }
}


/*
 * Frame By Frame +  Other Animations
 */

/*
 * Strobe Code!
 */
 
static void strobeDraw( uint8_t startpos, uint16_t lastpos, uint8_t period, uint8_t width, uint8_t huestart, uint8_t huedelta, uint8_t saturation, uint8_t value) {
  uint8_t hue = huestart;
  for ( uint16_t i = startpos; i <= lastpos; i += period) {
    CRGB color = CHSV( hue, saturation, value);
    //CRGB color = CRGB::Blue; // USE TO COMPLETELY BYPASS HSV Change Scheme
    uint16_t pos = i;
    for ( uint8_t w = 0; w < width; w++) {
      leds[pos] = ColorFromPalette( cPal, cycHue, brightness, currentBlending);
      pos++;
      if ( pos >= NUM_LEDS) {
        break;
      }
    }
    hue += huedelta;
  }
}
void strobeCore(uint8_t dashperiod, uint8_t dashwidth, int8_t  dashmotionspeed, uint8_t stroberepeats, uint8_t huedelta) {
  static uint8_t sRepeatCounter = 0;
  static int8_t sStartPosition = 0;
  static uint8_t sStartHue = 0;
  sStartHue += 1; //Shift the Colour little by little
  sRepeatCounter = sRepeatCounter + 1;
  if ( sRepeatCounter >= stroberepeats) {
    sRepeatCounter = 0;
    sStartPosition = sStartPosition + dashmotionspeed;
    if ( sStartPosition >= dashperiod ) {
      while ( sStartPosition >= dashperiod) {
        sStartPosition -= dashperiod;
      }
      sStartHue  -= huedelta;
    }
    else if ( sStartPosition < 0) {
      while ( sStartPosition < 0) {
        sStartPosition += dashperiod;
      }
      sStartHue  += huedelta;
    }
  }
  const uint8_t kSaturation = 208; // WHITE >> CURRENT COLOUR control (def 208)
  const uint8_t kValue = 200; // Brightness??
  strobeDraw( sStartPosition, NUM_LEDS - 1, dashperiod, dashwidth, sStartHue, huedelta, kSaturation, kValue);
}
void simpleStrobe () {
  runCheck(20);
  fill_solid( leds, NUM_LEDS, CRGB::Black);
  const uint8_t kStrobeCycleLength = 4; // light every Nth frame
  static uint8_t sStrobePhase = 0;
  sStrobePhase = sStrobePhase + 1;
  if ( sStrobePhase >= kStrobeCycleLength ) {
    sStrobePhase = 0;
  }
  if ( sStrobePhase == 0 ) {
    uint8_t dashperiod = beatsin8( 8, 4, 10);
    uint8_t dashwidth = (dashperiod / 4) + 1;
    uint8_t zoomBPM = STROBE_BEATS_PER_MINUTE;
    int8_t  dashmotionspeed = beatsin8( (zoomBPM / 2), 1, dashperiod);
    if ( dashmotionspeed >= (dashperiod / 2)) {
      dashmotionspeed = 0 - (dashperiod - dashmotionspeed );
    }
    uint8_t cycle = beat8(2); // two cycles per minute
    uint8_t easedcycle = ease8InOutCubic( ease8InOutCubic( cycle));
    uint8_t wavecycle = cubicwave8( easedcycle);
    //uint8_t hueShift = 0; // NO SHIFT OF HUE IN COLOUR (we should rebuild in RGB...)
    uint8_t hueShift = scale8( wavecycle, 130); // METHOD HOW HUE VALUE SHIFTS
    uint8_t strobesPerPosition = 2; // try 1..4
    strobeCore( dashperiod, dashwidth, dashmotionspeed, strobesPerPosition, hueShift);
  }
 // FastLED.delay(myDelay/4);
}
