#include <Arduino.h>
#include <FastLED.h>
#include <LEDMatrix.h>
#include <LEDText.h>
#include <LEDSprites.h>
#include <FontMatrise.h>
//#include <SoftwareSerial.h>
// Change the next 6 defines to match your matrix type and size

#define LED_PIN        3
#define COLOR_ORDER    GRB
#define CHIPSET        WS2812B

#define FULL_MATRIX_WIDTH   60
#define FULL_MATRIX_HEIGHT  14
#define MATRIX_TYPE    HORIZONTAL_ZIGZAG_MATRIX
#define MATRIX_A_WIDTH      46
#define MATRIX_B_WIDTH      46
#define MATRIX_C_WIDTH      14
#define MATRIX_A_HEIGHT     7
#define MATRIX_B_HEIGHT     7
#define MATRIX_C_HEIGHT     14

cLEDMatrix<FULL_MATRIX_WIDTH, FULL_MATRIX_HEIGHT, MATRIX_TYPE> leds;
cLEDMatrix<MATRIX_A_WIDTH, MATRIX_A_HEIGHT, MATRIX_TYPE> matA;
cLEDText scrollMsgA;
cLEDMatrix<MATRIX_B_WIDTH, MATRIX_B_HEIGHT, MATRIX_TYPE> matB;
cLEDText scrollMsgB;
cLEDMatrix<MATRIX_C_WIDTH, MATRIX_C_HEIGHT, MATRIX_TYPE> matC;
cLEDText scrollMsgC;
const uint8_t SpritesdfdgData[] = {
  B8_2BIT(00000001),B8_2BIT(11000000),
  B8_2BIT(10000011),B8_2BIT(11110000),
  B8_2BIT(11200011),B8_2BIT(11110000),
  B8_2BIT(11111111),B8_2BIT(11110000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(01111111),B8_2BIT(11100000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(00011111),B8_2BIT(10000000),
  B8_2BIT(00111111),B8_2BIT(00000000),
  B8_2BIT(01111100),B8_2BIT(00000000) };
const struct CRGB SpritesdfdgCols[3] = { CRGB(79,79,255), CRGB(159,159,255), CRGB(0,0,0) };
cSprite Spritesdfdg(12, 11, SpritesdfdgData, 1, _2BIT, SpritesdfdgCols);
const uint8_t SpritelogoIconData[] = {
  0x01,0x01,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x01,0x09,0x0A,0x0B,
  0x01,0x01,0x0C,0x0D,0x0E,0x0F,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,
  0x01,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,0x21,0x22,0x23,0x24,
  0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,0x30,0x31,0x32,
  0x33,0x34,0x35,0x36,0x37,0x1B,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
  0x40,0x41,0x42,0x43,0x36,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,
  0x4D,0x4E,0x36,0x4F,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,
  0x5A,0x28,0x5B,0x5C,0x5D,0x5E,0x5F,0x60,0x61,0x62,0x4A,0x63,0x64,0x65,
  0x66,0x36,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,0x70,0x71,0x72,
  0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,0x01,
  0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x83,0x84,0x87,0x11,0x88,0x89,0x01,
  0x01,0x01,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,0x87,0x04,0x90,0x91,0x01,0x01,
  0x01,0x01,0x01,0x92,0x93,0x94,0x71,0x95,0x96,0x97,0x98,0x01,0x01,0x01, };
const struct CRGB SpritelogoIconCols[255] = { CRGB(255,255,255), CRGB(135,38,38), CRGB(125,36,32), CRGB(131,38,34), CRGB(143,54,51), CRGB(134,41,37), CRGB(128,36,32), CRGB(132,52,51), CRGB(240,147,95), CRGB(235,137,76), CRGB(187,91,60), CRGB(147,81,79), CRGB(134,40,36), CRGB(136,42,38), CRGB(138,46,41), CRGB(144,51,48),
   CRGB(137,45,41), CRGB(135,40,36), CRGB(135,44,39), CRGB(145,55,45), CRGB(241,136,70), CRGB(224,114,59), CRGB(152,33,36), CRGB(158,70,67), CRGB(132,38,34), CRGB(191,78,49), CRGB(246,136,70), CRGB(214,113,64), CRGB(143,52,48), CRGB(139,45,41), CRGB(155,61,57), CRGB(157,65,61),
   CRGB(202,101,65), CRGB(240,127,61), CRGB(184,64,42), CRGB(164,51,54), CRGB(169,113,109), CRGB(150,57,54), CRGB(143,45,37), CRGB(216,82,45), CRGB(235,118,61), CRGB(245,136,71), CRGB(159,67,48), CRGB(138,44,40), CRGB(151,58,54), CRGB(156,61,53), CRGB(233,122,60), CRGB(219,102,51),
   CRGB(175,30,36), CRGB(177,26,34), CRGB(154,62,59), CRGB(149,54,50), CRGB(186,68,42), CRGB(219,83,45), CRGB(221,89,47), CRGB(212,112,60), CRGB(142,48,44), CRGB(154,58,54), CRGB(196,91,52), CRGB(235,118,55), CRGB(193,57,41), CRGB(175,57,59), CRGB(254,255,255), CRGB(157,67,63),
   CRGB(158,62,55), CRGB(217,82,45), CRGB(210,76,42), CRGB(233,115,58), CRGB(241,130,64), CRGB(165,70,50), CRGB(159,64,56), CRGB(229,112,53), CRGB(216,93,47), CRGB(183,32,39), CRGB(160,57,54), CRGB(154,71,66), CRGB(136,43,42), CRGB(187,68,42), CRGB(171,43,36), CRGB(206,74,41),
   CRGB(211,81,44), CRGB(235,121,57), CRGB(212,103,56), CRGB(195,87,49), CRGB(231,108,51), CRGB(192,53,41), CRGB(174,45,46), CRGB(146,54,49), CRGB(138,44,42), CRGB(147,52,42), CRGB(202,69,41), CRGB(164,39,35), CRGB(213,111,85), CRGB(199,75,45), CRGB(213,95,49), CRGB(232,111,52),
   CRGB(227,104,51), CRGB(213,84,45), CRGB(154,52,49), CRGB(142,49,45), CRGB(142,81,77), CRGB(215,92,66), CRGB(177,43,37), CRGB(199,85,46), CRGB(236,119,55), CRGB(233,114,53), CRGB(231,109,51), CRGB(229,103,49), CRGB(226,98,48), CRGB(191,49,41), CRGB(170,41,42), CRGB(154,60,56),
   CRGB(141,48,44), CRGB(240,241,238), CRGB(222,101,71), CRGB(204,69,42), CRGB(167,30,34), CRGB(178,76,43), CRGB(184,81,45), CRGB(181,76,41), CRGB(184,77,47), CRGB(182,74,46), CRGB(172,62,38), CRGB(160,41,41), CRGB(142,42,39), CRGB(148,56,51), CRGB(133,46,42), CRGB(218,99,70),
   CRGB(186,44,39), CRGB(154,36,36), CRGB(130,37,32), CRGB(128,35,31), CRGB(135,42,37), CRGB(140,47,42), CRGB(133,40,36), CRGB(135,47,43), CRGB(120,41,39), CRGB(129,38,34), CRGB(130,36,32), CRGB(132,40,36), CRGB(133,40,35), CRGB(137,44,40), CRGB(129,35,31), CRGB(138,50,46),
   CRGB(121,32,31), CRGB(126,39,40), CRGB(128,38,33), CRGB(133,46,43), CRGB(132,40,37), CRGB(136,55,54), CRGB(149,81,78), CRGB(249,235,226), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0),
   CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0),
   CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0),
   CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0),
   CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0),
   CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0),
   CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0) };
cSprite SpritelogoIcon(14, 13, SpritelogoIconData, 1, _8BIT, SpritelogoIconCols);
cLEDSprites Sprites(&matC);
uint8_t hue;
int16_t counter;
// Patterns //
int aW = MATRIX_A_WIDTH;
int bW = MATRIX_B_WIDTH;
int cW = MATRIX_C_WIDTH;
int aH = MATRIX_A_HEIGHT;
int bH = MATRIX_B_HEIGHT;
int cH = MATRIX_C_HEIGHT;
int fW = FULL_MATRIX_WIDTH;
int fH = FULL_MATRIX_HEIGHT;
int mAoX = 0;
int mAoY = 0;
int mBoX = 0;
int mBoY = MATRIX_A_HEIGHT;
int mCoX = MATRIX_A_WIDTH;
int mCoY = 0;
String theStr = "";
String theUser = "xxxxxxxx";
String theMessage = "No Message Received";
String defUser = "AutoAV Presents : ";
String defMessage = "AutoNoiseCreationStation - http://AutoAV.gq/";
bool scrollText = false;
String partBuilder = "";
//SoftwareSerial sofSer(10,11); // GREEN , BLUE
uint16_t XY( uint8_t x, uint8_t y, uint8_t w)
{
  uint16_t i;
    if( y & 0x01) {
      // Odd rows run backwards
      uint8_t reverseX = (w - 1) - x;
      i = (y * w) + reverseX;
    } else {
      // Even rows run forwards
      i = (y * w) + x;
    }  
  return i;
}
uint16_t translateXY(char mat, uint8_t mX, uint8_t mY){
  int offSetX;
  int offSetY;
  int w;
  if (mat == 'A'){
    offSetX = mAoX;
    offSetY = mAoY;
    w = aW;
  }
  else if (mat == 'B'){
    offSetX = mBoX;
    offSetY = mBoY;
    w = bW;
  }
  else if (mat == 'C'){
    offSetX = mCoX;
    offSetY = mCoY;   
    w = cW;
  }
  else {
    offSetX = 0;
    offSetY = 0;    
    w = fW;
    
    Serial.print("E");
  }
  int miniMatVal = XY(mX,mY,w);
  int bigMatVal = XY(mX+offSetX,mY+offSetY,fW);
  return bigMatVal;
}
void buildMatrix(){
  for (int x = 0; x<matA.Width();++x){
    for (int y = 0; y<matA.Height(); ++y){
      int full = translateXY('A',x,y);
      int sub = XY(x,y,matA.Width());
     
      leds(full)  = matA(sub);
    }
  }
  for (int x = 0; x<matB.Width();++x){
    for (int y = 0; y<matB.Height(); ++y){
      int full = translateXY('B',x,y);
      int sub = XY(x,y,matB.Width());
      leds(full)  = matB(sub);
    }
  }
    for (int x = 0; x<matC.Width();++x){
    for (int y = 0; y<matC.Height(); ++y){
      int full = translateXY('C',x,y);
      int sub = XY(x,y,matC.Width());
      leds(full)  = matC(sub);
    }
    }
  }
void parseString(){
  Serial.println(theStr);
  if(theStr.startsWith("@")){
    theUser = theStr.substring(0,theStr.indexOf("+&+"));
    theUser.concat(" tweeted:");
    scrollMsgB.SetText((unsigned char *)theUser.c_str(),theUser.length());
    theStr.remove(0,theStr.indexOf("+&+")+3);
    theMessage = theStr;
    scrollMsgA.SetText((unsigned char *)theMessage.c_str(),theMessage.length());
    Serial.print("USER : ");
    Serial.println(theUser);
    Serial.print("MESSAGE");
    Serial.println(theMessage);
  }
}
void setup()
{
 Serial.begin(115200);
 Serial2.begin(9600);
 Serial3.begin(9600);
 FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds[0], leds.Size());
  FastLED.setBrightness(127);
  FastLED.clear(true);
  delay(500);
  FastLED.showColor(CRGB::Red);
  delay(1000);
  FastLED.showColor(CRGB::Lime);
  delay(1000);
  FastLED.showColor(CRGB::Blue);
  delay(1000);
  FastLED.showColor(CRGB::White);
  delay(1000);
  scrollMsgA.SetFont(MatriseFontData);
  scrollMsgA.Init(&matA, matA.Width(), scrollMsgA.FontHeight() + 1, 0, 0);
  scrollMsgA.SetText((unsigned char *)defMessage.c_str(), defMessage.length());
  scrollMsgB.SetFont(MatriseFontData);
  scrollMsgB.Init(&matB, matB.Width(), scrollMsgB.FontHeight() + 1, 0, 0);
  scrollMsgB.SetText((unsigned char *)defUser.c_str(), defUser.length());
  FastLED.clear(true);
  Serial.println("SETUP DONE");
  hue = 0;
  counter = 0;
}
void loop()
{
  int16_t sx, sy, x, y;
  uint8_t h;
  String serStr = "";
  while(Serial2.available()){
	  char c = Serial2.read();
	  serStr.concat(c);
  }
  String espSer = "ESP: ";
    while (Serial3.available()) { // loop through all but the last
      char c = Serial3.read(); // receive byte as a character
      delay(10);
    espSer.concat(c);       
    }
  if (espSer != "ESP: "){
    Serial.println(espSer);
  }
  if(serStr != ""){
    Serial.print("Serial in ");
	  Serial.println(serStr);
    if (serStr.startsWith("$>$") && serStr.endsWith("$<$")){
      Serial.println("Part message");
      Serial.println(serStr);
      serStr.remove(0,3);
      serStr.remove(serStr.length()-3,serStr.length());
      Serial.println(serStr);
      partBuilder.concat(serStr);
      Serial2.write("%");
    }
    else if (serStr == "$!$!$"){
      theStr = partBuilder;
      partBuilder = "";
      parseString();
    }
    else if (serStr.startsWith("@") && serStr.endsWith("$+")){
        Serial.print("Full Message - ");
        Serial.println(serStr);
        Serial2.write("%");
        serStr.remove(0,1);
        serStr.remove(serStr.indexOf("$+"),2);
        Serial.print(serStr);
        theStr = serStr;
        parseString();
    }
    else {
        Serial2.write("$");
    }
  }
  h = hue;
  FastLED.clear();
  if (counter < 1000){
    //Serial.println("show ANCS");
    for (int y=0; y<matC.Height(); ++y)
    {
      matC.DrawLine(0, y, matC.Width() - 1, y, CHSV(h, 0, 0));
      h+=16;
    }
    if (scrollMsgA.UpdateText() == -1)
      scrollMsgA.SetText((unsigned char *)defMessage.c_str(), defMessage.length());
    if (scrollMsgB.UpdateText() == -1)
      scrollMsgB.SetText((unsigned char *)defUser.c_str(), defUser.length());
 
      for (y=0; y<matC.Height(); ++y)
    {
      matC.DrawLine(0, y, leds.Width() - 1, y, CHSV(h, 255, 255));
      h+=16;
    }
  }
  else if (counter < 6000){
    FastLED.clear();
    //Serial.println("showTwitter");
    if (scrollMsgA.UpdateText() == -1)
      scrollMsgA.SetText((unsigned char *)theMessage.c_str(), theMessage.length());
    if (scrollMsgB.UpdateText() == -1)
      scrollMsgB.SetText((unsigned char *)theUser.c_str(), theUser.length());
    Spritesdfdg.SetPositionFrameMotionOptions(0/*X*/, 0/*Y*/, 0/*Frame*/, 0/*FrameRate*/, +1/*XChange*/, 1/*XRate*/, +1/*YChange*/, 1/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_X_KEEPIN | SPRITE_Y_KEEPIN);
    Sprites.AddSprite(&Spritesdfdg);
    Sprites.UpdateSprites();
    Sprites.RenderSprites();
  }
  else if (counter < 8000){
    //Serial.println("PATTERNS");
     for (x=0; x<(matA.Width()+matA.Height()); ++x)
    {
      matA.DrawLine(x - matA.Height(), matA.Height() - 1, x, 0, CHSV(h, 255, 255));
      h+=16;
    }
    for (y=0; y<matB.Height(); ++y)
    {
      matB.DrawLine(0, y, matB.Width() - 1, y, CHSV(h, 255, 255));
      h+=16;
    }
    for (y=0; y<matC.Height(); ++y)
    {
      matC.DrawLine(0, y, leds.Width() - 1, y, CHSV(h, 255, 255));
      h+=16;
    }
  }
  else{
    
    }
  hue+=4;
  buildMatrix();
  counter++;
  if (counter >= 8010)
    counter = 0;
    scrollText = false;
  FastLED.show();
}
