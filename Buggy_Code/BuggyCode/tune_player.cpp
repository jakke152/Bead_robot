#include "tune_player.hpp"

TunePlayer::TunePlayer() : buzzer(D5) {}

void TunePlayer::updatePlayer(int ticks) {
  if (noteIndex >= songLength)
    noteIndex = 0;

  /**if (noteIndex == 0 && !resting) {
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
  }**/

  if (ticks - prevTime >= noteDuration || noteIndex == 0) {
    uint16_t data = pgm_read_word((uint16_t *)&song[noteIndex]);
    int16_t duration = (data >> 8);
    noteDuration = duration;
    if ((data & 0xF) == 0xF) {
      buzzer.write(0.0f);
    } else {
      buzzer.write(0.50f);
      uint16_t freq =
          pgm_read_word(&freq8[data & 0xF]) / (1 << (8 - (data >> 4 & 0xF)));
      if (freq != 0)
        buzzer.period_us(1e6 / freq);
    }
    prevTime = ticks;
    noteIndex++;
  }
}

void TunePlayer::playTune(int frequency, int duration) {
  if (frequency != 0) {
    buzzer.period_us(1e6 / frequency);
    buzzer.write(0.50f);
  }
}