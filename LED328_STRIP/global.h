#define LED_PIN        2
#define LED_PIN2       3
#define LED_PIN3       4
#define LED_PIN4       5
//#define NUM_STRIPS     4 
//#define NUM_LEDS_PER_STRIP 42 

#define COLOR_ORDER    GRB
#define CHIPSET        WS2812B
#define MAXBRIGHT 64
#define STARTBRIGHT 60
#define cTime 15000
#define hTime 30
#define STROBE_BEATS_PER_MINUTE 97.5
#define COOLING  55 // fire (20-100)
#define SPARKING 120 //(50-200)
bool gReverseDirection = false;

int ourAddr = ADDR-2; // Our IIC address holder for logic work.

CRGBPalette16 cPal(RainbowColors_p); // global palette storage

int cur_Step = 0;
volatile int clkVal;
bool cFlag = 0; //clock Flag
bool pFlag[8] = {0,0,0,0, 0,0,0,0}; //pulse Flag
int Mode = 0; //Menu pulse/auto
int Solo = 0; // host auto / solo auto
int ioRule[] = {0,0,0,0,0}; // Rule Holder for Primary/Secondary MCU
int Zone = 0; //Change to cur MCU#
byte zVals[4] = {}; // Zone Value (get bits) used for pattern store
int subZone[4] = {}; // Change Strip
int subZoneMem[4] = {}; // Change Strip
int iicTable[8] = {}; // holder for iic array message (reduce to 8)
byte stripMode = 0;
volatile byte cFX = 0; // index to the currently running effect
volatile byte cpFX = 0; // index to the currently running effect
volatile int cPalVal = 0; // current Paltte Value
byte cBright = STARTBRIGHT; // 0-255 will be scaled to 0-MAXBRIGHTNESS

volatile int runTime = 0; // Global holder for Runtime value multiplier (0-60)
volatile int fadeTime = 0; // Global holder for Fade increment value ( 0 - 100+)
volatile int hueSpeed = 0; // hueSpeed multiplier (0-10 maybe more)
uint8_t gHue = 0;
int myDelay = 30;
TBlendType currentBlending;

String received; 
boolean fxInit = false; // indicates if a pattern has been recently switched
uint16_t fxDelay = 0; // time between automatic effect changes
unsigned long fxMil = 0; // store the time of last effect function run
unsigned long cycMil = 0; // store the time of last effect change
unsigned long cMil; // store current loop's millis value
unsigned long hMil; // store time of last hue change
int itXmem[] = {0,0,0,0};


typedef void (*functionList)(); // definition for list of effect function pointers
extern const byte numFX;
