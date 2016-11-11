#include "CalliopeRobot.h"

#include "MicroBit.h"
#include "CalliopeRGB.h" 
#include "CalliopeSoundMotor.h" 

#ifdef CALLIOPE_ROBOT

MicroBit uBit;

uint8_t speedLeft = 0;
uint8_t speedRight = 0;

void onData(MicroBitEvent event) {
    PacketBuffer packet = uBit.radio.datagram.recv();

    switch(packet.getByte(0)) {
        // brake
        case 'B':
            speedLeft = 0;
            speedRight = 0;
            uBit.display.print("B");
            uBit.soundmotor.motorAOn(speedLeft);
            uBit.soundmotor.motorBOn(speedRight);
            break;
        // speed
        case 'S':
            speedLeft = (uint8_t) packet.getByte(1);
            speedRight = (uint8_t) packet.getByte(2);
            if(speedLeft/10 == speedRight/10) uBit.display.print("^");
            else if(speedLeft/10 > speedRight/10) uBit.display.print("<");
            else if(speedLeft/10 < speedRight/10) uBit.display.print(">");
            uBit.serial.printf("SET SPEED A=%d, B=%d\r\n", speedLeft, speedRight);
            uBit.soundmotor.motorAOn(speedLeft);
            uBit.soundmotor.motorBOn(speedRight);
            break;
        default:
            break;
    }
}

int main() {
    uBit.init();

    uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onData);
    uBit.radio.enable();
    uBit.radio.setGroup(RADIO_GROUP);

    uBit.soundmotor.motorAOn(100);
    uBit.soundmotor.motorBOn(100);

    while (1) uBit.sleep(100);
}

#endif
