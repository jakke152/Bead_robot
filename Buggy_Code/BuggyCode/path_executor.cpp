#include "path_executor.hpp"

#include "path_processor.hpp"

#include <vector>

PathExecutor::PathExecutor() {}
PathExecutor::~PathExecutor() {}
PathExecutor::PathExecutor(PathProcessor *pathProcessor)
{
    linkedPathProcessor = pathProcessor;

    sequenceFunctions = {&PathExecutor::backwardsUntilInterrupted, &PathExecutor::forwardsUntilInterrupted, &PathExecutor::backwardsUntilInterrupted, &PathExecutor::forwardsToStart, &PathExecutor::clockwise, &PathExecutor::forwardsToNextRow, &PathExecutor::counterclockwise};

    iterateSequence();
}

void PathExecutor::forwardsUntilInterrupted()
{
    linkedPathProcessor->straight(1, 0);
}
void PathExecutor::backwardsUntilInterrupted()
{
    printf("\n***----bwd until interrupted----***\n");
    linkedPathProcessor->straight(-1, 0);
}

void PathExecutor::forwardsToStart()
{
    linkedPathProcessor->straight(1, BUGGY_WALL_OFFSET_INTERVAL);
}
void PathExecutor::forwardsToNextRow()
{
    linkedPathProcessor->straight(1, BUGGY_ROW_INTERVAL);
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