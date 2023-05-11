#include "tune_player.hpp"

TunePlayer::TunePlayer() : buzzer(D5) {}

void TunePlayer::updatePlayer(int ticks) {
  if (noteIndex >= songLength)
    noteIndex = 0;

  if (noteIndex == 0 && !resting) {
    playTune(1e6 / songNotes[noteIndex], songDurations[noteIndex]);
    prevTime = ticks;
    resting = true;
    noteDuration *= 1.3;
  } else if (ticks - prevTime >= noteDuration) {
    if (resting) {
      noteIndex++;
      playTune(songNotes[noteIndex], songDurations[noteIndex]);
      resting = false;
    } else {
      resting = true;
      buzzer.write(0.0f);
      noteDuration *= 1.3;
    }
    prevTime = ticks;
  }
}

void TunePlayer::playTune(int frequency, int duration) {
  if (frequency != 0) {
    buzzer.period_us(1e6 / frequency);
    buzzer.write(0.50f);
  }
  noteDuration = 500/duration;
}