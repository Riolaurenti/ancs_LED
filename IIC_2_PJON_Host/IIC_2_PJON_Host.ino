#include "global.h"
#include "macros.h"
#include "pJon.h"

void parseIIC(){
  int comma = received.indexOf(',');
  String typeN = received.substring(0,comma);
  int t = typeN.toInt();
  switch(t) { // if a channel pulse, send a byte value
    case 10: bus.send_packet(PJON_BROADCAST, "10" , 3);break;
    case 11: bus.send_packet(PJON_BROADCAST, "11" , 3);break;
    case 12: bus.send_packet(PJON_BROADCAST, "12" , 3);break;
    case 13: bus.send_packet(PJON_BROADCAST, "13" , 3);break;
    case 14: bus.send_packet(PJON_BROADCAST, "14" , 3);break;
    case 15: bus.send_packet(PJON_BROADCAST, "15" , 3);break;
    case 16: bus.send_packet(PJON_BROADCAST, "16" , 3);break;
    case 17: bus.send_packet(PJON_BROADCAST, "17" , 3);break;
    case 18: bus.send_packet(PJON_BROADCAST, "18" , 3);break;
    default:  sendPjon(received); break; // // or send everything
  }
}

void eHandler(int howMany) {
  while (Wire.available()) {    
     char c = Wire.read();             // receive a byte as character
     received.concat(c);          //Add the character to the received string
     } 
  DPRINTLN(received);
  parseIIC();
  received = "";
}
void sendPjon(String str){ 
  const char pkt[str.length()+1]; // Create array
  str.toCharArray(pkt,str.length()+1); // Convert string to Char[]
  bus.send(PJON_BROADCAST,pkt,str.length()+1); // Send the packet to everyone 
  DPRINTLN(pkt);
};

void setup() {
  DBEGIN(9600);
  DPRINTLN("Setup"); 
  Wire.begin(I2CADDR);              // join i2c bus with address #8
  Wire.onReceive(eHandler);
  bus.set_receiver(receiver_handler); // link PJON to receiver
  bus.strategy.set_pin(12); // Set PJON pin
  bus.begin(); //
  delay(160); // possibly not needed if master is online
}

void loop() {
  bus.update(); // update the PJON
  bus.receive(5000); // receive for a while
}
