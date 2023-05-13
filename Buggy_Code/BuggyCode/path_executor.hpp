#ifndef PATH_EXECUTOR_HPP
#define PATH_EXECUTOR_HPP

#include "path_processor.hpp"

#include "constants.hpp"

#include <vector>

class PathExecutor
{
private:
    std::vector<void (PathExecutor::*)()> sequenceFunctions;

    int sequenceLength = 7;

public:
    PathExecutor();
    ~PathExecutor();
    PathExecutor(PathProcessor *linkedPathProcessor);

    void forwardsUntilInterrupted();
    void backwardsUntilInterrupted();

    void forwardsToStart();
    void forwardsToNextRow();

    void clockwise();
    void counterclockwise();

    void iterateSequence();

    int sequencePosition = -1;

    PathProcessor *linkedPathProcessor;
};

#endif