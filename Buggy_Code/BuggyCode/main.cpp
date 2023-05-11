#include "functions.hpp"

#include "buggy_controller.hpp"

#include "path_executor.hpp"

#include "path_processor.hpp"

#include "tune_player.hpp"

#include <cstdio>

bool running;

static BuggyController buggyController =
    BuggyController(D4, D3, D13, D11, D9, D10);

static PIDController pidController = PIDController(&buggyController);

static PathProcessor pathProcessor =
    PathProcessor(&buggyController, &pidController);

static PathExecutor pathExecutor = PathExecutor(&pathProcessor);

static TunePlayer tunePlayer = TunePlayer();

void initializeBuggy() {
  pidController.current[0] = &buggyController.motor1PWM;
  pidController.current[1] = &buggyController.motor2PWM;
}

int main() {
  initializeBuggy();

  bool running = true;

  while (running) {
    /**printf("poll -- seq pos = %d | section length = %ld | session length = %d "
           "| motor1 = %d, sp = %d | motor2 = %d, sp = %d\n",
           pathExecutor.sequencePosition, pathProcessor.sectionLength,
           (int)(buggyController.ticks * 1000),
           (int)(buggyController.motor1PWM * 100), pidController.setPoints[0],
           (int)(buggyController.motor2PWM * 100), pidController.setPoints[1]);**/

    if (pathExecutor.linkedPathProcessor->checkSequenceTime())
      pathExecutor.iterateSequence();

    pathExecutor.linkedPathProcessor->linkedPIDController
        ->updatePIDController();

    tunePlayer.updatePlayer((int)(buggyController.ticks * 1000));
  }

  return 0;
}