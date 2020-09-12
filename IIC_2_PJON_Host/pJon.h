#include <PJON.h>  
uint8_t bus_id[] = {0, 0, 1, 53}; // Ancs unique ID
PJON<SoftwareBitBang> bus(bus_id,100); // Master = 100

// PJON RECEIVER CODE
void receiver_handler(uint8_t *payload, uint16_t length, const PJON_Packet_Info &packet_info) {
   const char * arr = payload; // Not a pointer now.... !
  string.concat(arr); // addd it to our string
    string = ""; // thats all it says!
  for(uint16_t i = 0; i < length; i++) {
    DPRINT((char)payload[i]);
    DPRINT(" ");
  }
  DPRINTLN();
  DFLUSH(); 
};
