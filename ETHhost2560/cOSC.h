void deBug(OSCMessage &msg, int addrOffset ){ // get float from clock #1 - Receive int/pulse
  int c = msg.getFloat(0);
  DPRINT("c = ");
  DPRINT(c);
  DPRINTLN();
  int d = msg.getFloat(1);
  DPRINT("d = ");
  DPRINT(d);
  DPRINTLN();
}

void CLK(OSCMessage &msg, int addrOffset ){ // get float from clock #1 - Receive int/pulse
  int a = msg.getFloat(0);
  clk = a;
  countBars();
  String strVal = String(a);
  String mOut = "1," + strVal;
  char outClk[mOut.length()+2];
  mOut.toCharArray(outClk, mOut.length()+1);
  iic(outClk);  
  DPRINTLN(outClk);
}
void CUSTOM(OSCMessage &msg, int addrOffset ){ // get float from clock #1 - Receive int/pulse
  int a = msg.getFloat(0);
  String strVal = String(a);
  int b = msg.getFloat(1);
  String strVal2 = String(b);
  String mOut = strVal + "," + strVal2;
  char outClk[mOut.length()+2];
  mOut.toCharArray(outClk, mOut.length()+1);
  iic(outClk);  
  DPRINTLN(outClk);
}

void VOL(OSCMessage &msg, int addrOffset ){ // get float from clock #1 - Receive int/pulse
  int c = msg.getFloat(0);
  vol = c;
}
void MODE(OSCMessage &msg, int addrOffset ){ // get float from clock #1 - Receive int/pulse
  int d = msg.getFloat(0);
  String strVal = String(d);
  mode = d;
  String mOut = "2," + strVal;
  char outMode[mOut.length()+2];
  mOut.toCharArray(outMode, mOut.length()+1);
  iic(outMode);
}
void STRIPMODE(OSCMessage &msg, int addrOffset ){ // get float from clock #1 - Receive int/pulse
  int e = msg.getFloat(0);
  String strVal = String(e);
  // keep a record on master here?
  String mOut = "21," + strVal;
  char outMode[mOut.length()+2];
  mOut.toCharArray(outMode, mOut.length()+1);
  iic(outMode);
}

// there is a much cleaner way to do this... later.
void onPulse(OSCMessage &msg, int addrOffset ){ // get float from clock #1 - Receive int/pulse
  //
   int aA = msg.getFloat(0);
   if (aA==1){ 
    String Aa = String(aA);
    String mOut = "10," + Aa;
    char outA[mOut.length()+2]; 
    mOut.toCharArray(outA, mOut.length()+1);
    iic(outA);
    } 
   int aB = msg.getFloat(1);
   if(aB==1){ 
    String Ba = String(aB);
    String mOut = "11," + Ba;
    char outB[mOut.length()+2]; 
    mOut.toCharArray(outB, mOut.length()+1);
    iic(outB);
    }
   int aC = msg.getFloat(2);
   if(aC==1){  
    String Ca = String(aC);
    String mOut = "12," + Ca;
    char outC[mOut.length()+2]; 
    mOut.toCharArray(outC, mOut.length()+1);
    iic(outC);
   }
   int aD = msg.getFloat(3);
   if(aD==1){
    String Da = String(aD);
    String mOut = "13," + Da;
    char outD[mOut.length()+2]; 
    mOut.toCharArray(outD, mOut.length()+1);
    iic(outD);
    }
   int aE = msg.getFloat(4);
   if (aE==1){
    String Ea = String(aE);
    String mOut = "14," + Ea;
    char outE[mOut.length()+2]; 
    mOut.toCharArray(outE, mOut.length()+1);
    iic(outE);
    }
   int aF = msg.getFloat(5);
   if(aF==1){ 
    String Fa = String(aF);
    String mOut = "15," + Fa;
    char outF[mOut.length()+2]; 
    mOut.toCharArray(outF, mOut.length()+1);
    iic(outF);
    }
   int aG = msg.getFloat(6);
   if(aG==1){
    String Ga = String(aG);
    String mOut = "16," + Ga;
    char outG[mOut.length()+2]; 
    mOut.toCharArray(outG, mOut.length()+1);
    iic(outG); }
   int aH = msg.getFloat(7);
   if(aH==1){
    String Ha = String(aH);
    String mOut = "17," + Ha;
    char outH[mOut.length()+2]; 
    mOut.toCharArray(outH, mOut.length()+1);
    iic(outH);
    }
}
