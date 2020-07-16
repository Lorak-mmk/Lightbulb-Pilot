#include <IRremote.h>


IRsend irsend;

int RECV_PIN = 8;


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


void setup() {
    Serial.begin(9600);
    Serial.print("Setup finished\n");
}

void loop() {
    unsigned long msg = readsignal();
    irsend.sendNEC(msg, 32);

    Serial.print("Sent ");
    Serial.print(msg);
    Serial.print("\n");
}
