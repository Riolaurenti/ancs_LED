//LED Defines
#define LED_PIN1        5
#define LED_PIN2        7
#define COLOR_ORDER    GRB
#define CHIPSET        WS2812B
#define MATRIX_TILE_WIDTH   32  // Set this negative if physical led 0 is opposite to where you want logical 0
#define MATRIX_TILE_HEIGHT  8  // Set this negative if physical led 0 is opposite to where you want logical 0
#define MATRIX_TYPE    HORIZONTAL_ZIGZAG_MATRIX  // See top of LEDMatrix.h for matrix wiring types
#define MATRIX_TILE_H       1  // number of matrices arranged horizontally (negative for reverse order)
#define MATRIX_TILE_V       2  // number of matrices arranged vertically (negative for reverse order)
#define MATRIX_SIZE         (MATRIX_WIDTH*MATRIX_HEIGHT)
#define MATRIX_PANEL        (MATRIX_WIDTH*MATRIX_HEIGHT)
#define MATRIX_WIDTH        (MATRIX_TILE_WIDTH*MATRIX_TILE_H)
#define MATRIX_HEIGHT       (MATRIX_TILE_HEIGHT*MATRIX_TILE_V)
#define NUM_LEDS            (MATRIX_WIDTH*MATRIX_HEIGHT)
cLEDMatrix<MATRIX_TILE_WIDTH, MATRIX_TILE_HEIGHT, MATRIX_TYPE, MATRIX_TILE_H, MATRIX_TILE_V> leds;
cLEDText lowTxt;
// cLEDMatrix creates a FastLED array inside its object and we need to retrieve
// a pointer to its first element to act as a regular FastLED array, necessary
// for NeoMatrix and other operations that may work directly on the array like FadeAll.
CRGB *mleds = leds[0];
CRGBPalette16 cPal(RainbowColors_p); // global palette storage
TBlendType currentBlending;
//I2C Defines
#define ADDR           2
int ourAddr = ADDR-2; // Our IIC address holder for logic work.
String received;
//Storage for Foundation Values
int cur_Step = 0;
bool cFlag = 0; //clock Flag
bool pFlag[8] = {0,0,0,0, 0,0,0,0}; //pulse Flag
int Mode = 0; //Menu pulse/auto
boolean fxInit = false; // indicates if a pattern has been recently switched
byte cycHue = 0;
byte cycHueCount = 0;
//Storage for Active Values
uint8_t brightness = 64;
volatile int clkVal;
volatile int mirror = 0 ;
volatile int shape = 2 ;
volatile byte cFX = 15; // index to the currently running effect
volatile byte cpFX = 0; // index to the currently running effect
volatile int cPalVal = 0; // current Paltte Value
volatile int runTime = 0; // Global holder for Runtime value multiplier (0-60)
volatile int fadeTime = 0; // Global holder for Fade increment value ( 0 - 100+)
volatile int hueSpeed = 0; // hueSpeed multiplier (0-10 maybe more)
//Timer Variables
#define hTime 30 //not best defined, use volatile
uint16_t fxDelay = 0; // time between automatic effect changes
unsigned long fxMil = 0; // store the time of last effect function run
unsigned long cMil; // store current loop's millis value
unsigned long hMil; // store time of last hue change
//Pattern Variables
#define STROBE_BEATS_PER_MINUTE 97.5
#define MIDLX               (leds.Width()/2)
#define MIDLY               (leds.Height()/2)
int16_t dot = 3, steper, mstep;
float driftx, drifty;
uint16_t h = 0;
int itXmem[] = {0,0,0,0}; //iterator (cpFX)
