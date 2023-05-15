#include "path_executor.hpp"

#include "path_processor.hpp"

PathExecutor::PathExecutor() {}
PathExecutor::~PathExecutor() {}
PathExecutor::PathExecutor(PathProcessor *pathProcessor) {
  // Links the passed in path processor
  linkedPathProcessor = pathProcessor;

  // Assings the sequence which the buggy will follow, defined using pointers to
  // the functions that must be executed
  sequenceFunctions = {&PathExecutor::backwardsUntilInterrupted,
                       &PathExecutor::forwardsUntilInterrupted,
                       &PathExecutor::backwardsUntilInterrupted,
                       &PathExecutor::forwardsToStart,
                       &PathExecutor::clockwise,
                       &PathExecutor::forwardsToNextRow,
                       &PathExecutor::counterclockwise};

  // Sequence position is initialised as -1, so this moves it to 0 and begins
  // the actual sequence
  iterateSequence();
}

void PathExecutor::forwardsUntilInterrupted() {
  linkedPathProcessor->straight(1, 0);
}
void PathExecutor::backwardsUntilInterrupted() {
  linkedPathProcessor->straight(-1, 0);
}

void PathExecutor::forwardsToStart() {
  linkedPathProcessor->straight(1, BUGGY_WALL_OFFSET_INTERVAL);
}
void PathExecutor::forwardsToNextRow() {
  linkedPathProcessor->straight(1, BUGGY_ROW_INTERVAL);
}

void PathExecutor::clockwise() { linkedPathProcessor->rotate90(); }
void PathExecutor::counterclockwise() { linkedPathProcessor->rotate90(false); }

void PathExecutor::iterateSequence() {
  sequencePosition += 1;

  // Resets both motors to 0 before moving onto the next section
  linkedPathProcessor->buggyInterface->motor1PWM =
      linkedPathProcessor->buggyInterface->motor2PWM = 0;
  if (sequencePosition >= sequenceLength)
    // Checks if the sequence has finished and resets if so
    sequencePosition = 0;
  (this->*sequenceFunctions[sequencePosition])();
}