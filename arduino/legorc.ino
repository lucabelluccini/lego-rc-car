// -*- mode:c++; mode: flymake -*-
#include <PowerFunctions.h>

PowerFunctions pf(12, 0, true /* <= Enable debug mode on pin 13? */); 

void setup() {
   Serial.begin(115200);
}


/*PWM speed steps
#define PWM_FLT 0x0
#define PWM_FWD1 0x1
#define PWM_FWD2 0x2
#define PWM_FWD3 0x3
#define PWM_FWD4 0x4
#define PWM_FWD5 0x5
#define PWM_FWD6 0x6
#define PWM_FWD7 0x7
#define PWM_BRK 0x8
#define PWM_REV7 0x9
#define PWM_REV6 0xA
#define PWM_REV5 0xB
#define PWM_REV4 0xC
#define PWM_REV3 0xD
#define PWM_REV2 0xE
#define PWM_REV1 0xf
*/

int left = 0;
int right = 0;

uint8_t toPwmSpeedSteps(int value) {
  switch(value) {
    case -7: return PWM_REV7;
    case -6: return PWM_REV6;
    case -5: return PWM_REV5;
    case -4: return PWM_REV4;
    case -3: return PWM_REV3;
    case -2: return PWM_REV2;
    case -1: return PWM_REV1;
    case 0: return PWM_FLT;
    case 1: return PWM_FWD1;
    case 2: return PWM_FWD2;
    case 3: return PWM_FWD3;
    case 4: return PWM_FWD4;
    case 5: return PWM_FWD5;
    case 6: return PWM_FWD6;
    case 7: return PWM_FWD7;
    default: return PWM_BRK;
  }
}

void loop() {

     while (Serial.available() > 0) {
        // FIXME Not safe as no max length
        String s = Serial.readStringUntil('\n');
        if (sscanf(s.c_str(), "%d,%d", &left, &right) != 2) {
          left = 0;
          right = 0;
        }
     }
     pf.combo_pwm(toPwmSpeedSteps(left),toPwmSpeedSteps(-right));
     delay(100);
}