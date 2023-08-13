#ifndef __SENSOR_IR_HPP__
#define __SENSOR_IR_HPP__

#include <Arduino.h>

class SensorIR {
    public:
        SensorIR(int pin);

        bool get_state();

    private:
        int pin;
        bool state;
};

#endif // __SENSOR_IR_HPP__
