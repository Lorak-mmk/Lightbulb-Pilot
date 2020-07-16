#include "pilot.h"

#include <IRremoteESP8266.h>

String get_command(long num) {
    switch(num) {
        FOREACH_COMMAND(GENERATE_CASE);
        default:
            return "";
    }
}

void Sender::send(uint32_t data) {
    this->irsend.sendNEC(data, 32);
}
