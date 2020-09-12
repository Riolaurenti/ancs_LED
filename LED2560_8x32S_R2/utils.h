void runCheck(int val) {
  if (fxInit == false) {
    fxInit = true;
    fxDelay = val;
  }
}
// Increment the global hue value for functions that use it
void hCycle(byte incr) {
  cycHueCount = 0;
  cycHue += incr;
}
void randVars(){
  dot = random(2, 6); //controls circle size in many patterns
  steper = random8(2, 8);// steper is used to modify h to generate a color step on each move
  driftx = random8(4, leds.Width() - 4);//set an initial location for the animation center
  drifty = random8(4, leds.Height() - 4);// set an initial location for the animation center

}
// Fade every LED in the array by a specified amount
void fadeAll(byte fadeIncr) {
  for (byte i = 0; i < leds.Size(); i++) {
   mleds[i] = mleds[i].fadeToBlackBy(fadeIncr);
  }
}
void setPixel(int Pixel, byte red, byte green, byte blue){ 
   mleds[Pixel].r = red;
   mleds[Pixel].g = green;
   mleds[Pixel].b = blue;
}
void scrollArray(byte scrollDir) {
    byte scrollX = 0;
    for (byte x = 1; x < leds.Width(); x++) {
      if (scrollDir == 0) {
        scrollX = leds.Width() - x;
      } else if (scrollDir == 1) {
        scrollX = x - 1;
      }      
      for (byte y = 0; y < leds.Height(); y++) {
        leds(scrollX,y) = leds(scrollX + scrollDir*2 - 1,y);
      }
    }  
}
