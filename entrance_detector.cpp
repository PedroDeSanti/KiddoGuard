#include "entrance_detector.hpp"

EntranceDetector::EntranceDetector(SensorIR outside_sensor, SensorIR inside_sensor, SensorIR top_sensor) :
    outside_sensor(outside_sensor), inside_sensor(inside_sensor), top_sensor(top_sensor) {
    this->child_count = 0;
    this->adult_count = 0;
}

void EntranceDetector::update() {
    // identify entering
    if (this->outside_sensor.get_state() && !this->inside_sensor.get_state() && !this->is_passing) {
        this->is_passing = true;
        this->is_entering = true;
        this->is_exiting = false;
        this->is_processing = true;
        reset_timer();
    }

    // identify exiting
    if (this->inside_sensor.get_state() && !this->outside_sensor.get_state() && !this->is_passing) {
        this->is_passing = true;
        this->is_exiting = true;
        this->is_entering = false;
        this->is_processing = true;
        reset_timer();
    }

    // identify child
    if (this->is_passing && this->top_sensor.get_state() && this->is_processing) {
        this->is_passing = false;
        this->adult_identified = true;
        this->is_processing = false;
    }

    // ve se o segundo sensor viu
    if (this->is_entering) {
        if (this->inside_sensor.get_state()) {
            this->entered = true;
        }
    } else if (this->is_exiting) {
        if (this->outside_sensor.get_state()) {
            this->exited = true;
        }
    }

    // se o segundo computar, já tiver paadoss um segundo, e não computou adulto, então é criança

    if (this->is_entering && this->entered && (this->get_timer() > 500)) {
        if (!this->adult_identified) {
            this->child_count++;
        } else {
            this->adult_count++;
            this->adult_identified = false;
        }

        this->is_passing = false;
        this->is_entering = false;
        this->is_exiting = false;

        this->entered = false;
        this->exited = false;
    } else if (this->is_exiting && this->exited && (this->get_timer() > 500)) {
        if (!this->adult_identified) {
            this->child_count--;
        } else {
            this->adult_count--;
            this->adult_identified = false;
        }

        this->is_passing = false;
        this->is_entering = false;
        this->is_exiting = false;

        this->entered = false;
        this->exited = false;
    }
}

int EntranceDetector::get_child_count() {
    return this->child_count;
}

int EntranceDetector::get_adult_count() {
    return this->adult_count;
}

void EntranceDetector::reset_timer() {
    this->passing_timer = millis();
}

int EntranceDetector::get_timer() {
    return millis() - this->passing_timer;
}
