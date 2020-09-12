// Varidaic Debug Macro
 // #define DEBUG   //Comment this line to disable Debug output
#ifdef DEBUG    // Debug is on
#define DBEGIN(...)    Serial.begin(__VA_ARGS__)
#define DPRINT(...)    Serial.print(__VA_ARGS__)     //Sends our arguments to DPRINT()
#define DPRINTLN(...)  Serial.println(__VA_ARGS__)   //Sends our arguments to DPRINTLN()
#define DFLUSH(...)    Serial.flush()

#else // Debug is off
#define DBEGIN(...)
#define DPRINT(...)     //Nothing Happens
#define DPRINTLN(...)   //Nothing Happens
#define DFLUSH(...)

#endif // end macro

#define FL(aa,bb) for (int i = aa; i < bb; i++)
/*
 *  0 = 0000    8 = 1000
 *  1 = 0001    9 = 1001
 *  2 = 0010    10 = 1010
 *  3 = 0011    11 = 1011
 *  4 = 0100    12 = 1100
 *  5 = 0101    13 = 1101
 *  6 = 0110    14 = 1110
 *  7 = 0111    15 = 1111 
 */
