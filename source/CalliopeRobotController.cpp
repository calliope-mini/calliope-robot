#include "CalliopeRobot.h"

#include "MicroBit.h"

#ifdef CALLIOPE_ROBOT_CONTROLLER

MicroBit uBit;

uint8_t speedLeft = 0;
uint8_t speedRight = 0;

void sendBrake(MicroBitEvent e) {
    uBit.serial.printf("Robot: brake\r\n");
    uBit.radio.datagram.send("B");
}

const uint8_t Speeds[10] = {0, 20, 40, 70, 75, 80, 85, 90, 95, 100 };

int main() {
    uBit.init();

    uBit.serial.printf("Robot: controller start\r\n");
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, sendBrake);

    uBit.serial.printf("Robot: enable radio\r\n");
    if (uBit.radio.enable() != MICROBIT_OK) uBit.display.scroll("RADIO ERROR 1");
    if (uBit.radio.setGroup(RADIO_GROUP) != MICROBIT_OK) uBit.display.scroll("RADIO ERROR 2");

    uBit.serial.printf("Robot: ready\r\n");

    int x = 0, y = 0;
    while (1) {
        int dx = uBit.accelerometer.getX();
        int dy = uBit.accelerometer.getY();

        // scale the values ([-1024:-1024] => [0:4])
        int nx = (dx + 1024) * 5 / 2048;
        int ny = (dy + 1024) * 5 / 2048;

        // only change the pixel if the coordinates have changed
        if (nx != x || ny != y) {

            // set speed
            int speed = 100 - ((dx + 1024) * 100 / 2048);
            int direction = (dy * 100 / 1024) / 10;
            speedLeft = (uint8_t) ((speed - (direction * 10) / 2) / 10);
            speedRight = (uint8_t) ((speed + (direction * 10) / 2) / 10);
            uBit.serial.printf("L/R: %d/%d\r\n", speedLeft, speedRight);
            speedLeft = Speeds[speedLeft > 9 ? 9 : speedLeft];
            speedRight = Speeds[speedRight > 9 ? 9 : speedRight];
            uBit.serial.printf("speed speed=%d, direction=%d, ls=%d, rs=%d\r\n",
                               speed, direction, speedLeft, speedRight);
            uint8_t data[3] = {'S', speedLeft, speedRight};
            uBit.radio.datagram.send(data, 3);

            x = nx;
            y = ny;
            uBit.display.image.clear();
            uBit.display.image.setPixelValue(y, x, 255);
        }
    }
}

#endif
