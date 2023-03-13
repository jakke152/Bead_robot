#ifndef PATH_PROCESSOR_HPP
#define PATH_PROCESSOR_HPP

#include "buggy_controller.hpp"

#include "pid_controller.hpp"

class PathProcessor
{
private:
    long sectionTimer = 0;
    long sectionLength = 0;
    long prevSwitchTime = 0;

public:
    PathProcessor();
    ~PathProcessor();
    PathProcessor(BuggyController *buggyInterface, PIDController *linkedPIDContorller);

    void straight(int direction, int interval = 0);  // Direction -> 1 = Forwards, -1 = Backwards

    void rotate90(bool clockwise = true);

    bool checkSequenceTime();

    BuggyController *buggyInterface;
    PIDController *linkedPIDController;
};

#endif