#include "main.h"
#include "okapi/api.hpp"
using namespace okapi;

auto drive = ChassisControllerFactory::create(
    {1,2},{3,4},
    AbstractMotor::gearset::green,
    {4_in, 10.5_in} // change the width
);

Controller master;

ControllerButton armUpButton(ControllerDigital::R2);
ControllerButton armDownButton(ControllerDigital::R1);
Motor armMotor = 5_mtr;

ControllerButton intakeButton(ControllerDigital::L2);
ControllerButton outakeButton(ControllerDigital::L1);
Motor lIntakeMotor = 6_mtr;
Motor rIntakeMotor = 7_mtr;

ControllerButton trayUpButton(ControllerDigital::left);
ControllerButton trayDownButton(ControllerDigital::down);
Motor trayMotor = 8_mtr;

void drive_fn(void* param) {
  drive.arcade(master.getAnalog(ControllerAnalog::rightX),
               master.getAnalog(ControllerAnalog::rightY));
}

void arm_fn(void* param) {

  if(armUpButton.isPressed()){
    armMotor.moveVoltage(12000);
  }else if(armDownButton.isPressed()){
    armMotor.moveVoltage(-12000);
  }else{
    armMotor.moveVoltage(0);
  }
}

//Cube Intake and Tray Tilt Task
void intake_fn(void* param) {
  lIntakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  rIntakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  trayMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  if(intakeButton.isPressed()){
    rIntakeMotor.moveVoltage(12000);
    lIntakeMotor.moveVoltage(12000);
  }else if(outakeButton.isPressed()){
    rIntakeMotor.moveVoltage(-12000);
    lIntakeMotor.moveVoltage(-12000);
  }else{
    rIntakeMotor.moveVoltage(0);
    lIntakeMotor.moveVoltage(0);
  }
  if(trayUpButton.isPressed()){
    trayMotor.moveVoltage(12000);
  }else if(trayDownButton.isPressed()){
    trayMotor.moveVoltage(-12000);
  }else{
    trayMotor.moveVoltage(0);
  }
}

//Main (where the multitasking is occuring)
void opcontrol() {
  pros::Task drive (drive_fn, (void*)"PROS", TASK_PRIORITY_DEFAULT,TASK_STACK_DEPTH_DEFAULT, "drive");
  pros::Task arm (arm_fn, (void*)"PROS", TASK_PRIORITY_DEFAULT,TASK_STACK_DEPTH_DEFAULT, "arm");
  pros::Task intake (intake_fn, (void*)"PROS", TASK_PRIORITY_DEFAULT,TASK_STACK_DEPTH_DEFAULT, "intake");
}
