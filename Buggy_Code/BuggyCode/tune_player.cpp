#include "tune_player.hpp"

TunePlayer::TunePlayer() : buzzer(D5) {}

void TunePlayer::updatePlayer(int ticks) {
  // Resets song if it reaches the end
  if (noteIndex >= songLength)
    noteIndex = 0;

  // Checks if the current note should be finished playing or if no note has
  // been played yet
  if (ticks - prevTime >= noteDuration || noteIndex == 0) {
    // Fetches the combined duration and note data
    uint16_t data = pgm_read_word((uint16_t *)&song[noteIndex]);
    // Shifts the data 8 bits right and casts the data to a signed integer which
    // stores the original most significant 8 bits of data as their own
    // signed integer. This seperates those 8 bits into a readable integer
    int16_t duration = (data >> 8);
    noteDuration = duration;
    if ((data & 0xF) == 0xF) {
      // If all bits are zero, don't play any sound
      buzzer.write(0.0f);
    } else {
      // Sends a PWM signal to the buzzer of 50% duty cycle
      buzzer.write(0.50f);
      // I wish I understood how this next line works. I'm sure its not too
      // complicated realistically...
      uint16_t freq =
          pgm_read_word(&freq8[data & 0xF]) / (1 << (8 - (data >> 4 & 0xF)));
      if (freq != 0)
        // Sets buzzer PWM period to the frequency of the requested note
        buzzer.period_us(1e6 / freq);
    }
    prevTime = ticks;
    noteIndex++;
  }
}