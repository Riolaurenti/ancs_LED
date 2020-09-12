/*
    Simple Momentary Tricks
*/
void flash() { // Single Channel Pulse Example
  runCheck(30);
  if (pFlag[0] == 1) {
    for (int x = 0; x < leds.Width(); x++) {
      for (int y = 0; y < leds.Height(); y++) {
        leds(x, y) = ColorFromPalette( cPal, cycHue, brightness, currentBlending);
      }
    }
  }
  pFlag[0] = 0;
}

void flashArray() { // Multi-Channel Pulse Example single Strip. (BadCode - UPDATE)
  runCheck(30);
  for (int i = 0; i < 8; i++) {
    if (pFlag[i] == 1) {
      for (int x = 0; x < leds.Width() / 8; x++) {
        for (int y = 0; y < leds.Height(); y++) {
          leds(x + (i * (leds.Width() / 8)), y) = ColorFromPalette( cPal, cycHue + (10 * i), brightness, currentBlending);
        }
      }
    }
    pFlag[i] = 0;
  }
}

void mFlash() { // Multi Channel Pulse Example
  runCheck(30);
  for ( int i = 0 ; i < leds.Height(); i++) {
    if (pFlag[i] == 1) {
      for (int x = 0; x < leds.Width(); x++) {
        leds(x, i) = ColorFromPalette( cPal, cycHue, brightness, currentBlending);
      }
    }
    pFlag[i] = 0;
  }
}
void zoneFlash() { // Bad example of hard colour choices - use cpal Hue + val.
  runCheck(30);
  for ( int i = 0 ; i < leds.Height(); i++) {
    if (pFlag[i] == 1) {
      for (int x = 0; x < leds.Width(); x++) {
        if (i == 0)leds(x, 0) = CRGB::White;
        if (i == 1)leds(x, 1) = CRGB::Blue;
        if (i == 2)leds(x, 2) = CRGB::Red;
        if (i == 3)leds(x, 3)= CRGB::Green;
      }
    }
    pFlag[i] = 0;
  }
}

void riderS() { //Single Dash on Pulse
  static byte riderPos = 0;
  if (fxInit == false) {
    fxInit = true;
    fxDelay = 2;
    riderPos = 0;
  }
  for (int k = 0; k < 4; k++) {
    if (pFlag[k] == 1) {
      for (byte x = 0; x < leds.Width(); x++) {
        int brightness = abs(x * (256 / leds.Width()) - triwave8(riderPos) * 4 + 127) * 2;
        if (brightness > 255) brightness = 255;
        brightness = 255 - brightness;
        CRGB riderColor = CHSV(cycHue, 255, brightness);
        for (byte y = 0; y < leds.Height(); y++) {
          leds(x, k) = riderColor;
        }
      }
      riderPos++; // byte wraps to 0 at 255, triwave8 is also 0-255 periodic
      if (riderPos >= 64)riderPos = 0;
    }
    pFlag[k] = 0;
  }
}

void confet() {
  runCheck(30);
  for (int k = 0; k < 4; k++) {
    if (pFlag[k]) {
      for (int x = 0; x < leds.Width(); x++) {
        leds(random16(leds.Width()), k) = ColorFromPalette(cPal, random16(255), 255); //CHSV(random16(255), 255, 255);
      }
    }
    pFlag[k] = 0;
  }
}

void fader() {
  runCheck(1);
  for (int i = 0; i < leds.Size(); i++) {
    leds[i] == ColorFromPalette( cPal, cycHue);
  }
  for (int k = 0; k < 4; k++) {
    if (pFlag[k]) {
      for (int x = 0; x < leds.Width(); x++) {
        if (k)leds(x, k) = CRGB::White;
      }
    }
    pFlag[k] = 0;
  }
}


void iterator() { // realy bad example of on frame actions
  runCheck(30);
  for (int k = 0; k < 4; k++) {
    if (pFlag[k]) {
      itXmem[k]++;
      if(itXmem[k]>=leds.Width()){
        itXmem[k]=0;
      }
      for(int a=0;a<3;a++){
        leds(itXmem[k]+a, k) = ColorFromPalette( cPal, cycHue);  
      }
      if (itXmem[k] == 0)leds(leds.Width(), k) = CRGB::Black;
      else leds(itXmem[k] - 1, k) = CRGB::Black;
    }
    pFlag[k] = 0;
  }
}

void fun(){
  runCheck(30);
  int mov[] = {0,0,0,0};
  int rVal = random8(leds.Width());
  for (int k = 0; k < 4; k++) {
    if (pFlag[k]) {
      mov[k]++;
      if(mov[k]>=leds.Width()/2)mov[k]=0;;
      CRGB col = CRGB(random8(),random8(),random8());
      for (int x = 0; x <rVal ; x++) {
        leds(x, k) = col;
      }
    }
    pFlag[k] = 0;
    
  }
}
/*
 * 
 */
void pShapes(){
  if (pFlag[0]) {
  runCheck(160);
   fadeToBlackBy(mleds, leds.Size(), 20);
  int16_t xA,yA,xB,yB,r;
  xA = random8(0,leds.Width()); xB = random8(xA,leds.Width());
  yA = random8(0,leds.Height()); yB = random8(yA,leds.Height());
  r = random8(0,60);
  switch(shape){
    case 0: { leds.DrawLine(xA,yA,xB,yB, ColorFromPalette( cPal, cycHue)); } break;
    case 1: { leds.DrawRectangle(xA,yA,xB,yB, ColorFromPalette( cPal, cycHue)); } break;
    case 2: { leds.DrawCircle(xA,yA,r, ColorFromPalette( cPal, cycHue)); } break;
    case 3: { leds.DrawFilledRectangle(xA,xB,xB,yB, ColorFromPalette( cPal, cycHue)); } break;
    case 4: { leds.DrawFilledCircle(xA,xB,r, ColorFromPalette( cPal, cycHue)); } break;
  }
  }
  pFlag[0] = 0; 
}
 
 void cpFXsel() {
  switch(cpFX) {
    case 0:    flash();    break;
    case 1:    flashArray();    break;
    case 2:    mFlash();    break;
    case 3:    zoneFlash();    break;
    case 4:    riderS();    break;
    case 5:    confet();    break;
    case 6:    fader();    break;
    case 7:    iterator();    break;
    case 8:    fun();    break;

     case 9:    pShapes();    break;
    
  }
}
