void autoShapes(){
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

void corner() {
  runCheck(120);
  leds.DrawFilledRectangle(0 , 0,  MATRIX_WIDTH, MATRIX_HEIGHT, CHSV(h, 255, 255));
  h += steper;
  for (uint16_t y = 0; y <= MATRIX_WIDTH / 2 - 1 ; y++)  {
    leds.DrawFilledCircle(MIDLX, MIDLY, (MATRIX_WIDTH / 2 + 1 - y) / 3, CHSV(h  + y * steper, 255, 255));
    leds.DrawFilledCircle(0, 0, MATRIX_WIDTH / 2 - y, CHSV(64 + h + y * steper, 255, 255));
    leds.DrawFilledCircle(0, MATRIX_HEIGHT - 1, MATRIX_WIDTH / 2 - y, CHSV(h - 64 + y * steper, 255, 255));
    leds.DrawFilledCircle(MATRIX_WIDTH  - 1, 0, MATRIX_WIDTH / 2 - y, CHSV(h - 64 + y * steper, 255, 255));
    leds.DrawFilledCircle(MATRIX_WIDTH  - 1, MATRIX_HEIGHT - 1, MATRIX_WIDTH / 2 - y, CHSV(h + 64 + y * steper, 255, 255));
  }
}
