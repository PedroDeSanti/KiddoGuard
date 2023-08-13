#include "sensor_ir.hpp"

SensorIR::SensorIR(int pin) {
    this->pin = pin;
    pinMode(pin, INPUT);
}

bool SensorIR::get_state() {
    this->state = digitalRead(this->pin);
    return this->state;
}
