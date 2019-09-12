#include "main.h"
#include "okapi/api.hpp"
using namespace okapi;

auto drive = ChassisControllerFactory::create(
    {1,2},{3,4},
    AbstractMotor::gearset::green,
    {4_in, 10.5_in}
);

auto profileController = AsyncControllerFactory::motionProfile(1.0,2.0,10.0,drive);

void autonomous() {

  profileController.setTarget("A");
  profileController.generatePath({Point{0_ft,0_ft,0_deg}, Point{2_ft, 2_ft, 90_deg}}, "B");
  profileController.waitUntilSettled();
  profileController.removePath("A");


  profileController.setTarget("B");
  profileController.waitUntilSettled();
  profileController.setTarget("B");
  profileController.waitUntilSettled();
  profileController.generatePath({Point{0_ft,0_ft,0_deg}, Point{0_ft, 2_ft, 0_deg}}, "C");
  profileController.setTarget("C");
  profileController.waitUntilSettled();
  profileController.generatePath({Point{0_ft,0_ft,0_deg}, Point{0_ft, 0_ft, 45_deg}}, "D");
  profileController.setTarget("D");
  profileController.waitUntilSettled();
  profileController.generatePath({Point{0_ft,0_ft,0_deg}, Point{0_ft, 2.85_ft, 0_deg}}, "C");
  profileController.setTarget("C");
  profileController.waitUntilSettled();
}

// Notes
// When you generate a path, it takes time. You can generate a new path whil.
// When you geretate too many paths, the computer will run out of memory. Solution: profileController.remove("Path");
//
