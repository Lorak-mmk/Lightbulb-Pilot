#include <IRremote.h>


IRsend irsend;

void setup()
{
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 3; i++) {
    irsend.sendNEC(0xFF2AD5, 24);
    delay(40);
  }
  delay(5000); //5 second delay between each signal burst
}
