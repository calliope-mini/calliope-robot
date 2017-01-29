/**
 * Calliope Robot.
 *
 * The robot is very simple, it only knows how to handle motor speeds it receives.
 *
 * @copyright (c) Calliope gGmbH.
 *
 * Licensed under the Apache Software License 2.0 (ASL 2.0)
 * Portions (c) Copyright British Broadcasting Corporation under MIT License.
 *
 * @author Matthias L. Jugel <leo@calliope.cc>
 */

#include "CalliopeRobot.h"

#include "MicroBit.h"
#include "CalliopeRGB.h" 
#include "CalliopeSoundMotor.h" 

#ifdef CALLIOPE_ROBOT

MicroBit uBit;

uint8_t speedLeft = 0;
uint8_t speedRight = 0;

/**
 * This function is called whenever we receive data. The data packets
 * contain control information for the robot, what to do.
 */
void onData(MicroBitEvent event) {
    (void)event;
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

    // initialize the radio and hookup function
    uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onData);
    uBit.radio.enable();
    uBit.radio.setGroup(RADIO_GROUP);

    // start the engines!
    uBit.soundmotor.motorAOn(100);
    uBit.soundmotor.motorBOn(100);

    while (1) uBit.sleep(100);
}

#endif
