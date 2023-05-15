#ifndef PATH_EXECUTOR_HPP
#define PATH_EXECUTOR_HPP

#include "path_processor.hpp"

#include "constants.hpp"

#include <vector>

class PathExecutor {
private:
  // Stores all the pointers to functions which define the sequence that the
  // buggy will follow
  std::vector<void (PathExecutor::*)()> sequenceFunctions;

  int sequenceLength = 7;

public:
  PathExecutor();
  ~PathExecutor();
  // Constructs the path executor with a pointer to the path processor in which
  // all moves will be carried out
  PathExecutor(PathProcessor *linkedPathProcessor);

  // -- Sequence section functions --
  void forwardsUntilInterrupted();
  void backwardsUntilInterrupted();

  // Short move to get away from wall to starting position
  void forwardsToStart();
  // Move from current row into the next row
  void forwardsToNextRow();

  // Turning 90 degrees clockwise or counter-clockwise
  void clockwise();
  void counterclockwise();

  // Moves the sequence onto the next section
  void iterateSequence();

  // Stores the section that the sequence is in
  int sequencePosition = -1;

  // Path processor that carries out all the specified moves
  PathProcessor *linkedPathProcessor;
};

#endif