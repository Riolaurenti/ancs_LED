int clk = 0; // Get clock int
int clkMem = 0;
int tClk = 0 ; //Counter for bars

int cPal = 0; // global Palette Choice
int cPalVal = 0;
int cFX = 0; // Global current FX Choice
int cpFX = 0; // Global pulse choice
int Zone = 0; // Global Zone place holder
int subZone[4] = {}; // Global Strip Selector
byte randomPalette = 0;
byte randomZone = 0;
byte randomFX = 0;
byte randomPFX = 0;

int howManyBars = 0; // Global holder for HowmanyBars until change...
int i; 
int ratio = 4; // value to devide the counter by
int runT = 32; // runtime / max divisable quantity

int vol = 0; // volume debug holder

int mode = 0; // current Mode selection.
int ioRule[5] = {0,0,0,0,0}; // Is Channel 0)Primary 1)Secondary 2) Tertary
int ioRuleMem[5] = {0,0,0,0,0};
/*
int arrA[64] = {
  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0
  };

int arrB[64] = {
  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0
  };
  
int arrC[64] = {
  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0
  };

int arrD[64] = {
  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0
  };
  */
