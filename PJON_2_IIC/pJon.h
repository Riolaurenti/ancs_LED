
 /*
  * Parser - Receives PJON and routes to I2C
  */

void receiver_handler(uint8_t *payload, uint16_t length, const PJON_Packet_Info &packet_info) {
  const  char * arr = payload; // Not a pointer now.... !
  string.concat(arr); // addd it to our string
  iic(string);
  string = "";
 };
