#include <iostream>
#include <cassert>

class Time {
private:
    unsigned hours;
    unsigned minutes;
    unsigned seconds;

public:
    Time(unsigned hours = 0, unsigned minutes = 0, unsigned seconds = 0)
        : hours(hours), minutes(minutes), seconds(seconds) {
        assert(hours <= 23);
        assert(minutes <= 59);
        assert(seconds <= 59);
    }

    unsigned getHours() const {
        return hours;
    }

    unsigned getMinutes() const {
        return minutes;
    }

    unsigned getSeconds() const {
        return seconds;
    }

    unsigned setHours(unsigned hours) {
        assert(hours <= 23);
        this->hours = hours;
    }

    unsigned setMinutes(unsigned minutes) {
        assert(minutes <= 59);
        this->minutes = minutes;
    }

    unsigned setSeconds(unsigned seconds) {
        assert(seconds <= 59);
        this->seconds;
    }

    void incrementSeconds() {
        seconds++;
        if (seconds == 60) {
            seconds = 0;
            minutes++;
        }
        if (minutes == 60) {
            minutes = 0;
            ++hours;
        }
        if (hours == 24) {
            hours = 0;
        }
    }
};

int main() {


    return 0;
}