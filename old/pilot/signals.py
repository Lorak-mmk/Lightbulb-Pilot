from enum import Enum

class PilotSignal(Enum):
    Power = 0xFF2AD5

    LightUp = 0xFF6897
    LightDown = 0xFF10EF
    BrightCycle = 0xFF1AE5

    Temp1 = 0xFF7887
    Temp2 = 0xFF807F
    Temp3 = 0xFF8877
    Temp4 = 0xFFA857

    Mode1 = 0xFF50AF
    Mode2 = 0xFFE817
    Mode3 = 0xFF609F
    Mode4 = 0xFF48B7
    Mode5 = 0xFF38C7
    Mode6 = 0xFF30CF
    Mode7 = 0xFF708F
    Mode8 = 0xFF40BF

    Yellow = 0xFFB04F
    Green = 0xFF9867
    Blue = 0xFFC03F
    Purple = 0xFF32CD
    Red = 0xFF58A7
    Orange = 0xFF8A75



