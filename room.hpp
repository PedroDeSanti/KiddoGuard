#ifndef __ROOM_HPP__
#define __ROOM_HPP__

#include <Arduino.h>
#include <array>
#include "entrance_detector.hpp"
#include "buzzer.hpp"

class Room {
    public:
        Room(EntranceDetector** entrances, int num_of_entrances, Buzzer* buzzer, int room_id);

        void update();

        int get_child_count();

        int get_adult_count();

        int get_room_id();

        bool has_children_alone();

    private:
        int room_id;
        int child_count;
        int adult_count;

        Buzzer* buzzer;

        EntranceDetector** entrance_detectors;
        int num_of_entrances;
};

#endif // __ROOM_HPP__
