#include "buzzer.hpp"

Buzzer::Buzzer(int pin) {
    this->pin = pin;
    ledcSetup(0, 1000, 10);
    ledcAttachPin(pin, 0);
    ledcWriteTone(0, 0);
}

void Buzzer::beep() {
    ledcWriteTone(0, 1000);
}

void Buzzer::stop() {
    ledcWriteTone(0, 0);
}
