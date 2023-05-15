#ifndef _PWM_TONE_H_
#define _PWM_TONE_H_

#include "pgmspace.h"

// Defines each note and how to store their desired durations as well as their
// frequency in a single 16-bit unsigned integer
//
// The duration is passed in when the note is referenced and is immediately
// shifted 8 bits left before a bitwise or is carried out between the current
// data and an 8-bit binary number correlating to the frequency of the note
// In doing this, both the duration and frequency of the note can be stored in a
// single 16-bit unsigned integer.
// In order to calculate the exact frequency, a small lookup table containing
// just 12 integers is used alongside the least significant 8-bits of the data

// Octave 0 Note Codes
#define NOTE_C_0(DURATION) ((((uint16_t)DURATION) << 8) | 0b00000000)
#define NOTE_CS_0(DURATION) ((((uint16_t)DURATION) << 8) | 0b00000001)
#define NOTE_D_0(DURATION) ((((uint16_t)DURATION) << 8) | 0b00000010)
#define NOTE_DS_0(DURATION) ((((uint16_t)DURATION) << 8) | 0b00000011)
#define NOTE_E_0(DURATION) ((((uint16_t)DURATION) << 8) | 0b00000100)
#define NOTE_F_0(DURATION) ((((uint16_t)DURATION) << 8) | 0b00000101)
#define NOTE_FS_0(DURATION) ((((uint16_t)DURATION) << 8) | 0b00000110)
#define NOTE_G_0(DURATION) ((((uint16_t)DURATION) << 8) | 0b00000111)
#define NOTE_GS_0(DURATION) ((((uint16_t)DURATION) << 8) | 0b00001000)
#define NOTE_A_0(DURATION) ((((uint16_t)DURATION) << 8) | 0b00001001)
#define NOTE_AS_0(DURATION) ((((uint16_t)DURATION) << 8) | 0b00001010)
#define NOTE_B_0(DURATION) ((((uint16_t)DURATION) << 8) | 0b00001011)

// Octave 1 Note Codes
#define NOTE_C_1(DURATION) ((((uint16_t)DURATION) << 8) | 0b00010000)
#define NOTE_CS_1(DURATION) ((((uint16_t)DURATION) << 8) | 0b00010001)
#define NOTE_D_1(DURATION) ((((uint16_t)DURATION) << 8) | 0b00010010)
#define NOTE_DS_1(DURATION) ((((uint16_t)DURATION) << 8) | 0b00010011)
#define NOTE_E_1(DURATION) ((((uint16_t)DURATION) << 8) | 0b00010100)
#define NOTE_F_1(DURATION) ((((uint16_t)DURATION) << 8) | 0b00010101)
#define NOTE_FS_1(DURATION) ((((uint16_t)DURATION) << 8) | 0b00010110)
#define NOTE_G_1(DURATION) ((((uint16_t)DURATION) << 8) | 0b00010111)
#define NOTE_GS_1(DURATION) ((((uint16_t)DURATION) << 8) | 0b00011000)
#define NOTE_A_1(DURATION) ((((uint16_t)DURATION) << 8) | 0b00011001)
#define NOTE_AS_1(DURATION) ((((uint16_t)DURATION) << 8) | 0b00011010)
#define NOTE_B_1(DURATION) ((((uint16_t)DURATION) << 8) | 0b00011011)

// Octave 2 Note Codes
#define NOTE_C_2(DURATION) ((((uint16_t)DURATION) << 8) | 0b00100000)
#define NOTE_CS_2(DURATION) ((((uint16_t)DURATION) << 8) | 0b00100001)
#define NOTE_D_2(DURATION) ((((uint16_t)DURATION) << 8) | 0b00100010)
#define NOTE_DS_2(DURATION) ((((uint16_t)DURATION) << 8) | 0b00100011)
#define NOTE_E_2(DURATION) ((((uint16_t)DURATION) << 8) | 0b00100100)
#define NOTE_F_2(DURATION) ((((uint16_t)DURATION) << 8) | 0b00100101)
#define NOTE_FS_2(DURATION) ((((uint16_t)DURATION) << 8) | 0b00100110)
#define NOTE_G_2(DURATION) ((((uint16_t)DURATION) << 8) | 0b00100111)
#define NOTE_GS_2(DURATION) ((((uint16_t)DURATION) << 8) | 0b00101000)
#define NOTE_A_2(DURATION) ((((uint16_t)DURATION) << 8) | 0b00101001)
#define NOTE_AS_2(DURATION) ((((uint16_t)DURATION) << 8) | 0b00101010)
#define NOTE_B_2(DURATION) ((((uint16_t)DURATION) << 8) | 0b00101011)

// Octave 3 Note Codes
#define NOTE_C_3(DURATION) ((((uint16_t)DURATION) << 8) | 0b00110000)
#define NOTE_CS_3(DURATION) ((((uint16_t)DURATION) << 8) | 0b00110001)
#define NOTE_D_3(DURATION) ((((uint16_t)DURATION) << 8) | 0b00110010)
#define NOTE_DS_3(DURATION) ((((uint16_t)DURATION) << 8) | 0b00110011)
#define NOTE_E_3(DURATION) ((((uint16_t)DURATION) << 8) | 0b00110100)
#define NOTE_F_3(DURATION) ((((uint16_t)DURATION) << 8) | 0b00110101)
#define NOTE_FS_3(DURATION) ((((uint16_t)DURATION) << 8) | 0b00110110)
#define NOTE_G_3(DURATION) ((((uint16_t)DURATION) << 8) | 0b00110111)
#define NOTE_GS_3(DURATION) ((((uint16_t)DURATION) << 8) | 0b00111000)
#define NOTE_A_3(DURATION) ((((uint16_t)DURATION) << 8) | 0b00111001)
#define NOTE_AS_3(DURATION) ((((uint16_t)DURATION) << 8) | 0b00111010)
#define NOTE_B_3(DURATION) ((((uint16_t)DURATION) << 8) | 0b00111011)

// Octave 4 Note Codes
#define NOTE_C_4(DURATION) ((((uint16_t)DURATION) << 8) | 0b01000000)
#define NOTE_CS_4(DURATION) ((((uint16_t)DURATION) << 8) | 0b01000001)
#define NOTE_D_4(DURATION) ((((uint16_t)DURATION) << 8) | 0b01000010)
#define NOTE_DS_4(DURATION) ((((uint16_t)DURATION) << 8) | 0b01000011)
#define NOTE_E_4(DURATION) ((((uint16_t)DURATION) << 8) | 0b01000100)
#define NOTE_F_4(DURATION) ((((uint16_t)DURATION) << 8) | 0b01000101)
#define NOTE_FS_4(DURATION) ((((uint16_t)DURATION) << 8) | 0b01000110)
#define NOTE_G_4(DURATION) ((((uint16_t)DURATION) << 8) | 0b01000111)
#define NOTE_GS_4(DURATION) ((((uint16_t)DURATION) << 8) | 0b01001000)
#define NOTE_A_4(DURATION) ((((uint16_t)DURATION) << 8) | 0b01001001)
#define NOTE_AS_4(DURATION) ((((uint16_t)DURATION) << 8) | 0b01001010)
#define NOTE_B_4(DURATION) ((((uint16_t)DURATION) << 8) | 0b01001011)

// Octave 5 Note Codes
#define NOTE_C_5(DURATION) ((((uint16_t)DURATION) << 8) | 0b01010000)
#define NOTE_CS_5(DURATION) ((((uint16_t)DURATION) << 8) | 0b01010001)
#define NOTE_D_5(DURATION) ((((uint16_t)DURATION) << 8) | 0b01010010)
#define NOTE_DS_5(DURATION) ((((uint16_t)DURATION) << 8) | 0b01010011)
#define NOTE_E_5(DURATION) ((((uint16_t)DURATION) << 8) | 0b01010100)
#define NOTE_F_5(DURATION) ((((uint16_t)DURATION) << 8) | 0b01010101)
#define NOTE_FS_5(DURATION) ((((uint16_t)DURATION) << 8) | 0b01010110)
#define NOTE_G_5(DURATION) ((((uint16_t)DURATION) << 8) | 0b01010111)
#define NOTE_GS_5(DURATION) ((((uint16_t)DURATION) << 8) | 0b01011000)
#define NOTE_A_5(DURATION) ((((uint16_t)DURATION) << 8) | 0b01011001)
#define NOTE_AS_5(DURATION) ((((uint16_t)DURATION) << 8) | 0b01011010)
#define NOTE_B_5(DURATION) ((((uint16_t)DURATION) << 8) | 0b01011011)

// Octave 6 Note Codes
#define NOTE_C_6(DURATION) ((((uint16_t)DURATION) << 8) | 0b01100000)
#define NOTE_CS_6(DURATION) ((((uint16_t)DURATION) << 8) | 0b01100001)
#define NOTE_D_6(DURATION) ((((uint16_t)DURATION) << 8) | 0b01100010)
#define NOTE_DS_6(DURATION) ((((uint16_t)DURATION) << 8) | 0b01100011)
#define NOTE_E_6(DURATION) ((((uint16_t)DURATION) << 8) | 0b01100100)
#define NOTE_F_6(DURATION) ((((uint16_t)DURATION) << 8) | 0b01100101)
#define NOTE_FS_6(DURATION) ((((uint16_t)DURATION) << 8) | 0b01100110)
#define NOTE_G_6(DURATION) ((((uint16_t)DURATION) << 8) | 0b01100111)
#define NOTE_GS_6(DURATION) ((((uint16_t)DURATION) << 8) | 0b01101000)
#define NOTE_A_6(DURATION) ((((uint16_t)DURATION) << 8) | 0b01101001)
#define NOTE_AS_6(DURATION) ((((uint16_t)DURATION) << 8) | 0b01101010)
#define NOTE_B_6(DURATION) ((((uint16_t)DURATION) << 8) | 0b01101011)

// Octave 7 Note Codes
#define NOTE_C_7(DURATION) ((((uint16_t)DURATION) << 8) | 0b01110000)
#define NOTE_CS_7(DURATION) ((((uint16_t)DURATION) << 8) | 0b01110001)
#define NOTE_D_7(DURATION) ((((uint16_t)DURATION) << 8) | 0b01110010)
#define NOTE_DS_7(DURATION) ((((uint16_t)DURATION) << 8) | 0b01110011)
#define NOTE_E_7(DURATION) ((((uint16_t)DURATION) << 8) | 0b01110100)
#define NOTE_F_7(DURATION) ((((uint16_t)DURATION) << 8) | 0b01110101)
#define NOTE_FS_7(DURATION) ((((uint16_t)DURATION) << 8) | 0b01110110)
#define NOTE_G_7(DURATION) ((((uint16_t)DURATION) << 8) | 0b01110111)
#define NOTE_GS_7(DURATION) ((((uint16_t)DURATION) << 8) | 0b01111000)
#define NOTE_A_7(DURATION) ((((uint16_t)DURATION) << 8) | 0b01111001)
#define NOTE_AS_7(DURATION) ((((uint16_t)DURATION) << 8) | 0b01111010)
#define NOTE_B_7(DURATION) ((((uint16_t)DURATION) << 8) | 0b01111011)

// Octave 8 Note Codes
#define NOTE_C_8(DURATION) ((((uint16_t)DURATION) << 8) | 0b10000000)
#define NOTE_CS_8(DURATION) ((((uint16_t)DURATION) << 8) | 0b10000001)
#define NOTE_D_8(DURATION) ((((uint16_t)DURATION) << 8) | 0b10000010)
#define NOTE_DS_8(DURATION) ((((uint16_t)DURATION) << 8) | 0b10000011)
#define NOTE_E_8(DURATION) ((((uint16_t)DURATION) << 8) | 0b10000100)
#define NOTE_F_8(DURATION) ((((uint16_t)DURATION) << 8) | 0b10000101)
#define NOTE_FS_8(DURATION) ((((uint16_t)DURATION) << 8) | 0b10000110)
#define NOTE_G_8(DURATION) ((((uint16_t)DURATION) << 8) | 0b10000111)
#define NOTE_GS_8(DURATION) ((((uint16_t)DURATION) << 8) | 0b10001000)
#define NOTE_A_8(DURATION) ((((uint16_t)DURATION) << 8) | 0b10001001)
#define NOTE_AS_8(DURATION) ((((uint16_t)DURATION) << 8) | 0b10001010)
#define NOTE_B_8(DURATION) ((((uint16_t)DURATION) << 8) | 0b10001011)

#define NOTE_SILENT(DURATION) ((((uint16_t)DURATION) << 8) | 0b00001111)

#endif
