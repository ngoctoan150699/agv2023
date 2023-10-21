
#include <Arduino.h>
#ifdef AGV_MCP
//AGV
#define motor_left_start 24
#define motor_left_dir 25
#define motor_right_start 27
#define motor_right_dir 28
#define motor_brake 29
#else
#define motor_left_start 28
#define motor_left_dir 29
#define motor_right_start 39
#define motor_right_dir 30
#define motor_brake 31
#endif

// #define motor_left_start 28
// #define motor_left_dir 29
// #define motor_right_start 39
// #define motor_right_dir 30
// #define motor_brake 31

// //AGV
// #define motor_left_start 24
// #define motor_left_dir 25
// #define motor_right_start 27
// #define motor_right_dir 28
// #define motor_brake 29

#define guide_sensor_sil1 22
#define guide_sensor_sil2 23

#define analog_magnetic A0
#define out1_safe_sensor A15
#define out2_safe_sensor A14
#define out3_safe_sensor A13

#define lidar_select_1 42
#define lidar_select_2 43

#define over_left A9
#define over_right A10

#define out_guide_sensor A4

#define battery_voltage A1
#define buzzer_sound1 34
#define buzzer_sound2 35
#define freertos_status 36

#define PIN_LINE_TU A2
void IO()
{
  pinMode(motor_left_start, OUTPUT);  // chân bắt đầu trái
  pinMode(motor_left_dir, OUTPUT);    // chân đảo trái
  pinMode(motor_right_start, OUTPUT); // chân bắt đầu trái
  pinMode(motor_right_dir, OUTPUT);   // chân đảo phải
  pinMode(motor_brake, OUTPUT);       // chân phanh
  pinMode(guide_sensor_sil1, OUTPUT); // chân 1 chọn chế độ cảm biến dò line
  pinMode(guide_sensor_sil2, OUTPUT); // chân 2 chọn chế độ cảm biến dò line

  pinMode(out1_safe_sensor, INPUT_PULLUP); // Cảm biến lidar gần nhất
  pinMode(out2_safe_sensor, INPUT_PULLUP); // Cảm biến lidar trung bình
  pinMode(out3_safe_sensor, INPUT_PULLUP); // Cảm biến lidar xa nhất

  pinMode(lidar_select_1, OUTPUT); // chọn chế độ preset lidar 1
  pinMode(lidar_select_2, OUTPUT); // chọn chế độ preset lidar 2

  pinMode(over_left, INPUT_PULLUP);        // cảm biến giới hạn trái
  pinMode(over_right, INPUT_PULLUP);       // cảm biến giới hạn phải
  pinMode(out_guide_sensor, INPUT_PULLUP); // cảm biến nhận biết line
}