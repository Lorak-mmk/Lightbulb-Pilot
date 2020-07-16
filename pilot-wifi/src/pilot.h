#ifndef PILOT_H
#define PILOT_H

#include <Arduino.h>
#include <IRsend.h>


#define FOREACH_COMMAND(FUNC) \
    FUNC(Power, 0xFF2AD5) \
    FUNC(LightUp, 0xFF6897) \
    FUNC(LightDown, 0xFF10EF) \
    FUNC(BrightCycle, 0xFF1AE5) \
    FUNC(Temp1, 0xFF7887) \
    FUNC(Temp2, 0xFF807F) \
    FUNC(Temp3, 0xFF8877) \
    FUNC(Temp4, 0xFFA857) \
    FUNC(Mode1, 0xFF50AF) \
    FUNC(Mode2, 0xFFE817) \
    FUNC(Mode3, 0xFF609F) \
    FUNC(Mode4, 0xFF48B7) \
    FUNC(Mode5, 0xFF38C7) \
    FUNC(Mode6, 0xFF30CF) \
    FUNC(Mode7, 0xFF708F) \
    FUNC(Mode8, 0xFF40BF) \
    FUNC(Yellow, 0xFFB04F) \
    FUNC(Green, 0xFF9867) \
    FUNC(Blue, 0xFFC03F) \
    FUNC(Purple, 0xFF32CD) \
    FUNC(Red, 0xFF58A7) \
    FUNC(Orange, 0xFF8A75) \

#define GENERATE_ENUM(NAME, VAL) NAME = VAL,
#define GENERATE_STRINGS(NAME, VAL) {#NAME, VAL},
#define GENERATE_CASE(NAME, VAL) case VAL: return #NAME; break;

enum CommandsEnum {
    FOREACH_COMMAND(GENERATE_ENUM)
};

struct Command {
    String name;
    int value;
};

static Command commands_names[] = {
        FOREACH_COMMAND(GENERATE_STRINGS)
};

String get_command(long num);

class Sender {
public:
    static constexpr uint16_t kIrLedPin = 4;
    explicit Sender(uint16_t pin = Sender::kIrLedPin): irsend(pin) {
        irsend.begin();
    }

    void send(uint32_t data);
private:
    IRsend irsend;
};

#endif
