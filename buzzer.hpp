#ifndef __BUZZER_HPP__
#define __BUZZER_HPP__

#include <Arduino.h>

class Buzzer {
    public:
        Buzzer(int pin);

        void beep();

        void stop();

    private:
        int pin;
};

#endif // __BUZZER_HPP__
