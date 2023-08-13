#include "buzzer.hpp"

Buzzer::Buzzer(int pin) {
    this->pin = pin;
    pinMode(pin, OUTPUT);
}

void Buzzer::beep(int freq, int duration) {
    tone(this->pin, freq, duration);
}

void Buzzer::beep(int freq) {
    tone(this->pin, freq);
}

void Buzzer::beep() {
    tone(this->pin, 1000);
}

void Buzzer::stop() {
    noTone(this->pin);
}
