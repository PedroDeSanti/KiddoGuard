#include "sensor_ir.hpp"

SensorIR::SensorIR(int pin) {
    this->pin = pin;
    pinMode(pin, INPUT_PULLUP);
}

bool SensorIR::get_state() {
    return this->current_state;
}

void SensorIR::update() {
    this->last_state = this->current_state;
    this->current_state = !digitalRead(this->pin);
}

bool SensorIR::has_changed() {
    return this->last_state != this->current_state;
}

bool SensorIR::is_rising_edge() {
    return (!this->last_state && this->current_state);
}

bool SensorIR::is_falling_edge() {
    return (this->last_state && !this->current_state);
}
