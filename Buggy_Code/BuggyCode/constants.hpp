#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// Screen speed if both motors are going max speed in the same direction (pixels/frame)
#define BUGGY_MAX_SCREEN_SPEED 3.5

// Rotation speed if both motors are going max speed in opposing directions (rads/frame)
#define BUGGY_MAX_ROTATION_SPEED M_PI_2 *((BUGGY_MAX_SCREEN_SPEED * 2) / (BUGGY_WIDTH * M_PI))

#define BUGGY_ROW_INTERVAL 1000
#define BUGGY_WALL_OFFSET_INTERVAL 1000
#define BUGGY_TURN_90_INTERVAL 2400*0.7
#define BUGGY_SWITCH_COOLDOWN 3000

#define PID_KP 0.05
#define PID_KI 0
#define PID_KD 0

#endif