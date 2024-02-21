#ifndef __SENSOR_IR_HPP__
#define __SENSOR_IR_HPP__

#include <Arduino.h>

class SensorIR {
    public:
        SensorIR(int pin);

        bool get_state();

        void update();

        bool has_changed();

        bool is_rising_edge();

        bool is_falling_edge();

    private:
        int pin;
        bool current_state;
        bool last_state;
};

#endif // __SENSOR_IR_HPP__
