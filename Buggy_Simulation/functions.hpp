#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#define SCREEN_WIDTH 1410
#define SCREEN_HEIGHT 720

#define ARENA_SCREEN_WIDTH 1000
#define ARENA_SCREEN_HEIGHT 700

#define ARENA_SCREEN_OFFSET_X 400
#define ARENA_SCREEN_OFFSET_Y 10

// Speed of entire simulation
#define SPEED_SCALE 1.0f

// Scales size to an 18x18 buggy in a 100x70 arena (x & y should be almost equal)
#define BUGGY_WIDTH (ARENA_SCREEN_WIDTH / 100.0f) * 18.0f / 1.2
#define BUGGY_HEIGHT (ARENA_SCREEN_HEIGHT / 70.0f) * 18.0f / 1.2
#define BUGGY_SWITCH_RADIUS BUGGY_WIDTH * 1.2 / 2

// Screen speed if both motors are going max speed in the same direction (pixels/frame)
#define BUGGY_MAX_SCREEN_SPEED 3.5

// Rotation speed if both motors are going max speed in opposing directions (rads/frame)
#define BUGGY_MAX_ROTATION_SPEED M_PI_2 *((BUGGY_MAX_SCREEN_SPEED * 2) / (BUGGY_WIDTH * M_PI))

#define BUGGY_WHEEL_CIRCUMFERENCE 4

#define BUGGY_ROW_INTERVAL 600
#define BUGGY_WALL_OFFSET_INTERVAL 100
#define BUGGY_TURN_90_INTERVAL 1450
#define BUGGY_SWITCH_COOLDOWN 200

#define PID_KP 0.05
#define PID_KI 0
#define PID_KD 0

#endif