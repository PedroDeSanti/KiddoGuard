#include "entrance_detector.hpp"

EntranceDetector::EntranceDetector(SensorIR* outside_sensor, SensorIR* inside_sensor, SensorIR* top_sensor) :
    outside_sensor(outside_sensor), inside_sensor(inside_sensor), top_sensor(top_sensor) {
    this->child_count = 0;
    this->adult_count = 0;
}

void EntranceDetector::update() {
    // if (this->outside_sensor->is_rising_edge() && !this->is_passing) {
    // Serial.println("Entrando");
    // this->is_passing = true;
    // this->is_entering = true;
    // this->is_exiting = false;
    // reset_timer();
    // }

    // if (this->inside_sensor->is_rising_edge() && !this->is_passing) {
    // Serial.println("Saindo");
    // this->is_passing = true;
    // this->is_exiting = true;
    // this->is_entering = false;
    // reset_timer();
    // }

    // if (this->is_passing && this->top_sensor->is_rising_edge()) {
    // Serial.println("Adulto");
    // this->adult_identified = true;
    // }

    // if (this->is_passing && (this->get_timer() > 1000)) {
    // Serial.println("Contabilizando");

    // if (this->is_entering) {
    // if (!this->adult_identified) {
    // Serial.println("Add crianca");
    // this->child_count = this->child_count + 1;
    // } else {
    // this->adult_count = this->adult_count + 1;
    // Serial.println("Add adulto");
    // this->adult_identified = false;
    // }
    // } else if (this->is_exiting) {
    // if (!this->adult_identified) {
    // Serial.println("Sub crianca");
    // this->child_count = this->child_count - 1;
    // } else {
    // Serial.println("Sub adulto");

    // this->adult_count = this->adult_count - 1;
    // this->adult_identified = false;
    // }
    // }

    // this->is_passing = false;
    // this->is_entering = false;
    // this->is_exiting = false;
    // }

    // identify entering
    if (this->outside_sensor->is_rising_edge() && !this->inside_sensor->get_state() && !this->is_passing) {
        Serial.println("Entrando");
        this->is_passing = true;
        this->is_entering = true;
        this->is_exiting = false;
        reset_timer();
    }

    // identify exiting
    if (this->inside_sensor->is_rising_edge() && !this->outside_sensor->get_state() && !this->is_passing) {
        Serial.println("Saindo");
        this->is_passing = true;
        this->is_exiting = true;
        this->is_entering = false;
        reset_timer();
    }

    // identify child
    if (this->is_passing && this->top_sensor->is_rising_edge()) {
        Serial.println("Adulto");
        this->is_passing = false;
        this->adult_identified = true;
    }

    // ve se o segundo sensor viu
    if (this->is_entering) {
        if (this->inside_sensor->is_rising_edge()) {
            this->entered = true;
            Serial.println("Entrou");
        }
    } else if (this->is_exiting) {
        if (this->outside_sensor->is_rising_edge()) {
            this->exited = true;
            Serial.println("Saiu");
        }
    }

    // se o segundo computar, já tiver paadoss um segundo, e não computou adulto, então é criança

    if (this->is_entering && this->entered && (this->get_timer() > 700)) {
        Serial.println("Contabilizando entrada");

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
    } else if (this->is_exiting && this->exited && (this->get_timer() > 700)) {
        Serial.println("Contabilizando saida");

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
