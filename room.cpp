#include "room.hpp"

Room::Room(EntranceDetector** entrance_detectors, int num_of_entrances, Buzzer buzzer, int room_id) : buzzer(buzzer) {
    this->entrance_detectors = entrance_detectors;
    this->num_of_entrances = num_of_entrances;
    this->room_id = room_id;
    this->child_count = 0;
    this->adult_count = 0;
}

void Room::update() {
    for (int i = 0; i < this->num_of_entrances; i++) {
        this->entrance_detectors[i]->update();
        this->child_count += this->entrance_detectors[i]->get_child_count();
        this->adult_count += this->entrance_detectors[i]->get_adult_count();
    }
}

int Room::get_child_count() {
    return this->child_count;
}

int Room::get_adult_count() {
    return this->adult_count;
}

int Room::get_room_id() {
    return this->room_id;
}
