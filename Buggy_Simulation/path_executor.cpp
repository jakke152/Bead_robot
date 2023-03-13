#include "path_executor.hpp"

#include "path_processor.hpp"

#include <vector>

PathExecutor::PathExecutor() {}
PathExecutor::~PathExecutor() {}
PathExecutor::PathExecutor(PathProcessor *pathProcessor)
{
    linkedPathProcessor = pathProcessor;

    sequenceFunctions = {&backwardsUntilInterrupted, &forwardsUntilInterrupted, &backwardsUntilInterrupted, &forwardsToStart, &clockwise, &forwardsToNextRow, &counterclockwise};

    iterateSequence();
}

void PathExecutor::forwardsUntilInterrupted()
{
    linkedPathProcessor->straight(1);
}
void PathExecutor::backwardsUntilInterrupted()
{
    linkedPathProcessor->straight(-1);
}

void PathExecutor::forwardsToStart()
{
    linkedPathProcessor->straight(1, BUGGY_WALL_OFFSET_INTERVAL / SPEED_SCALE);
}
void PathExecutor::forwardsToNextRow()
{
    linkedPathProcessor->straight(1, BUGGY_ROW_INTERVAL / SPEED_SCALE);
}

void PathExecutor::clockwise()
{
    linkedPathProcessor->rotate90();
}
void PathExecutor::counterclockwise()
{
    linkedPathProcessor->rotate90(false);
}

void PathExecutor::iterateSequence()
{
    sequencePosition += 1;
    linkedPathProcessor->buggyInterface->motor1PWM = linkedPathProcessor->buggyInterface->motor2PWM = 0;
    if (sequencePosition >= sequenceLength)
        sequencePosition = 0;
    (this->*sequenceFunctions[sequencePosition])();
}