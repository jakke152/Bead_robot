#include "path_processor.hpp"

#include "buggy_controller.hpp"

PathProcessor::PathProcessor() {}
PathProcessor::~PathProcessor() {}
PathProcessor::PathProcessor(BuggyController *buggyController,
                             PIDController *pidController) {
  buggyInterface = buggyController;
  linkedPIDController = pidController;
}

void PathProcessor::straight(int direction, int interval) {
  sectionLength = interval;
  sectionTimer = (buggyInterface->ticks*1000);

  linkedPIDController->setPoints[0] = linkedPIDController->setPoints[1] =
      direction;
}

void PathProcessor::rotate90(bool clockwise) {
  sectionTimer = (buggyInterface->ticks*1000);
  sectionLength = BUGGY_TURN_90_INTERVAL;

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
  bool switchesPressed = (sectionLength == 0 && (buggyInterface->switch1 == 1 ||
                                                 buggyInterface->switch2 == 1));
  if ((sectionLength > 0 &&
       (buggyInterface->ticks*1000) - sectionTimer >= sectionLength) ||
      (switchesPressed &&
       (buggyInterface->ticks*1000) - prevSwitchTime >= BUGGY_SWITCH_COOLDOWN)) {
    if (switchesPressed)
      prevSwitchTime = (buggyInterface->ticks*1000);
    sectionLength = 0;
    return true;
  }
  return false;
}
