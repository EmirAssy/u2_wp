#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/keyboard.h>
#include <webots/distance_sensor.h>

#include <math.h>
#include <stdio.h>

#define TIME_STEP 64

int main(int argc, char **argv)
{

  wb_robot_init();
  wb_keyboard_enable(TIME_STEP);

  int pressed_key;

   // Motor devices
   WbDeviceTag wheel_right = wb_robot_get_device("motor_right");
   WbDeviceTag wheel_left = wb_robot_get_device("motor_left");

   wb_motor_set_position (wheel_right, INFINITY);
   wb_motor_set_position (wheel_left, INFINITY);

   //Distance sensor device
   WbDeviceTag dist_sensor = wb_robot_get_device("distance_sensor");
   wb_distance_sensor_enable(dist_sensor, TIME_STEP);
   double ds_value;

  while (wb_robot_step(TIME_STEP) != -1) {

     pressed_key= wb_keyboard_get_key();

     ds_value = wb_distance_sensor_get_value (dist_sensor);
     printf("Distance sensor: %lf\n", ds_value);

     if (pressed_key == WB_KEYBOARD_UP)
     {
       wb_motor_set_velocity (wheel_right, -6.28);
       wb_motor_set_velocity (wheel_left, -6.28);
     }
     else if (pressed_key == WB_KEYBOARD_DOWN)
     {
       wb_motor_set_velocity (wheel_right, 6.28);
       wb_motor_set_velocity (wheel_left, 6.28);
     }
     else if (pressed_key == WB_KEYBOARD_RIGHT)
     {
       wb_motor_set_velocity(wheel_right, 6.28);
       wb_motor_set_velocity(wheel_left, -6.28);
     }
     else if (pressed_key == WB_KEYBOARD_LEFT)
     {
       wb_motor_set_velocity(wheel_right, -6.28);
       wb_motor_set_velocity(wheel_left, 6.28);
     }
     else
     {
       wb_motor_set_velocity (wheel_right, 0);
       wb_motor_set_velocity (wheel_left, 0);
     }
  };
  wb_robot_cleanup();

  return 0;
}
