#ifndef PATH_PROCESSOR_HPP
#define PATH_PROCESSOR_HPP

#include "buggy_controller.hpp"

#include "pid_controller.hpp"

class PathProcessor {
private:
  // Stores the timer value when the current section starts
  long sectionTimer = 0;

  // Stores the timer value when the previous switch input was recorded
  long prevSwitchTime = 0;

public:
  PathProcessor();
  ~PathProcessor();
  // Constructs the path processor with pointers to the buggy controller and
  // PID controller
  PathProcessor(BuggyController *buggyInterface,
                PIDController *linkedPIDContorller);

  // Moves the buggy straight, with the wheels spinning at equal speeds
  // +ve dir= fwd, -ve dir = bwd
  void straight(int direction, int interval = 0);

  // Turns the buggy 90 degrees clockwise by default. If 'false' is passed in
  // the buggy rotates counter-clockwise
  void rotate90(bool clockwise = true);

  // Returns if the sequence has reached the end of the assigned time
  // If no time has been assigned, the function will instead return if a valid
  // switch input has been detected
  bool checkSequenceTime();

  // Pointers to buggy controller and PID controller
  BuggyController *buggyInterface;
  PIDController *linkedPIDController;

  // Stores the duration, in ms, of the current section of the sequence
  long sectionLength = 0;
};

#endif