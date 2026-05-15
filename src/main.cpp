#include "mbed.h"
#include "FP.hpp"
#include "key.hpp"
// #include "serial_read.hpp"

BufferedSerial pc(USBTX, USBRX, 115200);

// serial_unit serial(pc);

CAN can1(PA_11, PA_12, (int)1e6);

DigitalIn limit_sw1(PC_10);
DigitalIn bt1(BUTTON1);

FP fp(35, can1);

bool is_button_pressed = false;

// void button_read() {
//     while (true) {
//         if (Triangle) {
//             if (limit_sw1.read() == 1) {
//                 fp.pwm[1] = -6500;
//             } else {
//                 fp.pwm[1] = 0;
//             }
//         } else if (Cross) {
//             fp.pwm[1] = 2000;
//         } else {
//             fp.pwm[1] = 0;
//         }
//         printf("pwm[1]: %d\n", fp.pwm[1]);
//         ThisThread::sleep_for(10ms);
//     }
// }

// user button で操作
void button_read() {
    while (true) {
        if (bt1.read() == 0) {
            is_button_pressed = true;
            if (limit_sw1.read() == 1) {
                fp.pwm[1] = -6775;
            } else {
                fp.pwm[1] = 0;
            }
        } else {
            if (is_button_pressed) {
                fp.pwm[1] = 2000;
            } else {
                fp.pwm[1] = 0;
            }
        }
        printf("pwm[1]: %d\n", fp.pwm[1]);
        ThisThread::sleep_for(10ms);
    }
}

void can_send() {
    while (true) {
        fp.send();
        ThisThread::sleep_for(10ms);
    }
}

int main () {
    limit_sw1.mode(PullUp);
    bt1.mode(PullUp);
    // Thread serial_thread;
    // serial_thread.start(serial_read);
    Thread button_thread;
    button_thread.start(button_read);
    Thread can_thread;
    can_thread.start(can_send);
    while (true) {
    }
}