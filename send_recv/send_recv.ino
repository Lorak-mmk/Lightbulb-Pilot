#include <IRremote.h>


IRsend irsend;

int RECV_PIN = 8;
// irrecv(RECV_PIN);
//decode_results results;
//bool FIRST = true;

unsigned long readsignal()
{
  char buffer[32];
  uint8_t idx = 0;
  char c;
  do
  {
    while (Serial.available() == 0) ; // wait for a char this causes the blocking
    c = Serial.read();
    buffer[idx++] = c;
  }
  while (c != '\n' && c != '\r');
  buffer[idx - 1] = 0;
  return strtol(buffer, NULL, 16);
}

void setup()
{
  Serial.begin(9600);
  //irrecv.enableIRIn(); // Start the receiver
  Serial.print("Hello\n");
}

void loop() {
    while(true){
      Serial.print("Loop\n");
      unsigned long msg = readsignal();
      Serial.print("Send");
      Serial.print(msg);
      Serial.print("\n");
      irsend.sendNEC(msg, 32);
    }
}
