/*
 * OSC Host MCU - Takes OSC from Reaktor 6 and Forwards Messages to Router via I2C
 * 
 * Functions controlled here include all OSC receive commands.
 * Current Global Messages : Flags for Pulse/Clock/Zones
 *                           Ints for current Clk, Bar / pallette / autoFX and PulseFX
 */

#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>    
#include <OSCBundle.h>
#include <OSCBoards.h>
#include <Wire.h>


#include"global.h"
#include "macros.h"
#include "utils.h"
#include"cOSC.h"


EthernetUDP Udp;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; 
IPAddress ip(192, 168, 0, 150);
const unsigned int inPort = 8888;

void setup() { 
  DBEGIN(115200);
  DPRINT("Setup");
  Wire.begin();
  //Wire.onReceive(eHandler);
  Ethernet.begin(mac,ip);
  Udp.begin(inPort);
  DPRINTLN(Ethernet.localIP());
}

void loop() {  
  routeOSC(); 
}
/*
 * Route all Incoming OSC Bundles here
 */
void routeOSC() {
  OSCBundle bundleIN;
  int size;
   if((size = Udp.parsePacket())>0) {
     while(size--) bundleIN.fill(Udp.read());
     if(!bundleIN.hasError()) {
      bundleIN.route("/m", MODE);
      bundleIN.route("/s", STRIPMODE);
      bundleIN.route("/CLK", CLK);
      bundleIN.route("/p", onPulse);
      bundleIN.route("/v", VOL);
     
      bundleIN.route("/cFX", CUSTOM);
      bundleIN.route("/cPFX", CUSTOM);
      bundleIN.route("/cPal", CUSTOM);
      bundleIN.route("/hS", CUSTOM); //hueSpeed
      bundleIN.route("/rT", CUSTOM); //runTime
      bundleIN.route("/fT", CUSTOM); //fadeTime

       bundleIN.route("/lZ", CUSTOM);
      bundleIN.route("/sM", CUSTOM);
     }
   }
}
/*
 * Receive I2C Arguements
 */
 /*
void eHandler(int aa) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    DPRINT(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  DPRINTLN(x);         // print the integer
}
*/
