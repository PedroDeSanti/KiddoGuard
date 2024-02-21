#ifndef __ENTRANCE_DETECTOR_HPP__
#define __ENTRANCE_DETECTOR_HPP__

#include <Arduino.h>
#include "sensor_ir.hpp"

class EntranceDetector {
    public:
        EntranceDetector(SensorIR* outside_sensor, SensorIR* inside_sensor, SensorIR* top_sensor);

        void update();

        int get_child_count();

        int get_adult_count();

    private:
        SensorIR* outside_sensor;
        SensorIR* inside_sensor;
        SensorIR* top_sensor;
        int child_count;
        int adult_count;

        int passing_timer = 0;

        bool is_passing = false;
        bool is_entering = false;
        bool is_exiting = false;

        bool is_processing = false;

        bool adult_identified = false;

        bool exited = false;
        bool entered = false;

        void reset_timer();

        int get_timer();
};

#endif // __ENTRANCE_DETECTOR_HPP__
