#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// -- Timings --

// Interval between rows
#define BUGGY_ROW_INTERVAL 1000  
// Time to move away from wall before turning
#define BUGGY_WALL_OFFSET_INTERVAL 1000  
// Time to complete a 90 degree turn
#define BUGGY_TURN_90_INTERVAL 2400  
// Time to wait after detecting a switch to read its input again (switch debounce)
#define BUGGY_SWITCH_COOLDOWN 3000  

// -- PID Controller --
#define PID_KP 0.05
#define PID_KI 0
#define PID_KD 0

#endif