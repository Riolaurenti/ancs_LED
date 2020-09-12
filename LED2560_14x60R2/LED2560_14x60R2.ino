#include <FastLED.h>
#include <Wire.h>
#include <LEDMatrix.h>
#include <LEDText.h>
#include <FontMatrise.h>
#include "global.h"
#include "utils.h"
#include "macros.h"
#include "pulseFX.h"
#include "ledFX.h"
#include "matFX.h"
#include "msg.h"
#include "palettes.h"

void setup() {
  DBEGIN(9600);
  DPRINT("Setup");
  Wire.begin(ADDR);
  Wire.onReceive(eHandler);
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds[0], leds.Size());
  FastLED.setBrightness(48);
  FastLED.clear(true);
  lowTxt.SetFont(MatriseFontData); 
  lowTxt.Init(&leds, leds.Width(), lowTxt.FontHeight() + 1, 0, 4);
  lowTxt.SetText((unsigned char *)TxtAncs, sizeof(TxtAncs) - 1);
  lowTxt.SetTextColrOptions(COLR_RGB | COLR_SINGLE, 0xff, 0xff, 0xff);
  lowTxt.SetScrollDirection(SCROLL_LEFT);
  lowTxt.SetFrameRate(2);

  mstep = byte( 256 / min((leds.Width() - 1), 255)); //mstep is the step size to distribute 256 over an array the width of the matrix
  delay(500);
}

void loop() {
  EVERY_N_SECONDS( 30 ) { randcFX(); }
  cMil = millis();
  //hue Cycle (add more pattern based cycles here)
  if (cMil - hMil > hTime) {
    hMil = cMil;
    hCycle(1 + hueSpeed); // increment the global hue value
  }
  //Choose FX style and pattern
  if (Mode) { // when pulse on, do without runTime
    cpFXsel(); // choose from pulseFX List
  }
  else { // when patternMode on, do with runTime
    if (cMil - fxMil > fxDelay) {
      fxMil = cMil;
      cFXsel(); // choose from FX list
    }
  }
  //Add a Fade of aftertouch FX
  if (Mode) {
    fadeAll(1 + fadeTime); // fade out the leds after pulse
  }
  else {
    switch(mirror){
      case 0: break;
      case 1: leds.HorizontalMirror(); break;
      case 2: leds.VerticalMirror(); break;
      case 3: leds.QuadrantMirror(); break;
      case 4: leds.QuadrantRotateMirror(); break;
      case 5: leds.TriangleTopMirror();   break;
      case 6: leds.TriangleBottomMirror();    break;
      case 7: leds.QuadrantTopTriangleMirror();    break;
      case 8: leds.QuadrantBottomTriangleMirror();    break;
      
    }
    //if (fxList[cFX] == confetti) fadeAll(1+fadeTime);
    //if(cFX == 0) fadeAll(10); //glitter
    //if(fxList[cFX] == sinelon) fadeAll(2);
    //if (fxList[cFX] == bpm) fadeAll(1+fadeTime);
    // if (fxList[cFX] == bouncingTrails) fadeAll(1+fadeTime);
  }
  FastLED.show(); // send the contents of the led memory to the LEDs
}

void parseIIC() {
  int comma = received.indexOf(',');
  String typeN = received.substring(0, comma);
  String valN = received.substring(comma + 1, 5);
  int t = typeN.toInt();
  int v = valN.toInt();
  switch (t) {
    case 1: {
        cur_Step = v;
      }    break;
    case 2: {
        if (v)Mode = 0;
        if (v == 2) Mode = 1;
      }   break;
    case 5: {
        cPalVal = v;
        selPal();
      }   break;
    case 6: {
        cFX = v;
      } break;
    case 7: {
        cpFX = v;
      }    break;
    //case 8: {        byte Go = v; get_bits(8, Go);      } break;
    //case 9: {        byte Go = v; get_bits(9, Go);      } break;
    case 10:      pFlag[0] = 1;      break;
    case 11:      pFlag[1] = 1;      break;
    case 12:      pFlag[2] = 1;      break;
    case 13:      pFlag[3] = 1;      break;
    case 14:      pFlag[4] = 1;      break;
    case 15:      pFlag[5] = 1;      break;
    case 16:      pFlag[6] = 1;      break;
    case 17:      pFlag[7] = 1;      break;
    case 20:      {        hueSpeed = v;        DPRINT("hue = ");        DPRINTLN(v);      }     break;
    case 21:      {        runTime = v;        DPRINT("autoRunTime = ");        DPRINTLN(v);      }     break;
    case 23:      {        fadeTime = v;        DPRINT("fadeTime = ");        DPRINTLN(v);      }     break;
  }
  //DPRINT("t = ");DPRINTLN(t);DPRINT("v = ");DPRINTLN(v);
}

void eHandler(int aa) {
  while (Wire.available()) {
    char c = Wire.read();             // receive a byte as character
    received.concat(c);          //Add the character to the received string
  }
  parseIIC();
  //DPRINTLN(received);
  received = "";
}
void cFXsel() {
  switch(cFX) {
    case 0:    glitter();    break;         
    case 1:    sideRain();    break;
    case 2:    confetti();    break;
    case 3:    theLights();    break;
    case 4:    rainbow();    break;
    case 5:    sinelon();    break;
    case 6:    threeSine();    break;
    case 7:    sinelonXY();    break;
    case 8:    bouncingTrails();    break;
    case 9:    bpm();    break;
    case 10:    rider();    break;
    case 11:    colourFill();    break;
    case 12:    slantBars();    break;
    case 13:    autoShapes();    break;
    case 14:    corner();    break;
    case 15:    scrollText();    break;
  }
} 
