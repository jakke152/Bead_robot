#include "path_processor.hpp"

#include "buggy_controller.hpp"

PathProcessor::PathProcessor() {}
PathProcessor::~PathProcessor() {}
PathProcessor::PathProcessor(BuggyController *buggyController,
                             PIDController *pidController) {
  // Links buggy iterface and PID controller to passed in pointers
  buggyInterface = buggyController;
  linkedPIDController = pidController;
}

void PathProcessor::straight(int direction, int interval) {
  sectionLength = interval;
  // Sets section timer to the current timer value multiplied by 1000
  sectionTimer = (buggyInterface->ticks * 1000);

  linkedPIDController->setPoints[0] = linkedPIDController->setPoints[1] =
      direction / abs(direction);
}

void PathProcessor::rotate90(bool clockwise) {
  // Sets section timer to the current timer value multiplied by 1000
  sectionTimer = (buggyInterface->ticks * 1000);
  // Uses predefined constant from constants.hpp
  sectionLength = BUGGY_TURN_90_INTERVAL;

  // Sets motors spinning alternate directions in order to turn the buggy either
  // clockwise or counter-clockwise
  if (clockwise) {
    linkedPIDController->setPoints[0] = 1;
    linkedPIDController->setPoints[1] = -1;
  }

  else {
    linkedPIDController->setPoints[0] = -1;
    linkedPIDController->setPoints[1] = 1;
  }
}

bool PathProcessor::checkSequenceTime() {
  // Stores combined value of both switches in single bool, meaning either one
  // can be used to iterate sequence
  bool switchesPressed = (sectionLength == 0 && (buggyInterface->switch1 == 1 ||
                                                 buggyInterface->switch2 == 1));

  // Checks if the assigned section time has passed or a switch has been pressed
  // after the switch cooldown has passed
  if ((sectionLength > 0 &&
       (buggyInterface->ticks * 1000) - sectionTimer >= sectionLength) ||
      (switchesPressed && (buggyInterface->ticks * 1000) - prevSwitchTime >=
                              BUGGY_SWITCH_COOLDOWN)) {
    if (switchesPressed)
      // Resets previous switch time if switch was pressed
      prevSwitchTime = (buggyInterface->ticks * 1000);
    sectionLength = 0;
    return true;
  }
  return false;
}
