// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>

double currentTimeStamp = 0, lastTimestamp = 0, dt = 0;
double matchTime = 0;


void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  driver = new frc::PS4Controller(0);

  R2 = new WPI_VictorSPX(1);
  L2 = new WPI_VictorSPX(4);
  R1 = new WPI_VictorSPX(2);
  L1 = new WPI_VictorSPX(3);

  arm = new WPI_TalonSRX(6);
  gripper = new WPI_TalonSRX(5);
}

/**
 * This function is called every 20 ms, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {matchTime = (double)frc::Timer::GetMatchTime();
  currentTimeStamp = (double)frc::Timer::GetFPGATimestamp();
  dt = currentTimeStamp - lastTimestamp;

  lastTimestamp = currentTimeStamp;}

  double timeAtTheStart = 0;

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  fmt::print("Auto selected: {}\n", m_autoSelected);

  timeAtTheStart = currentTimeStamp;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if(currentTimeStamp-timeAtTheStart >= 0 && currentTimeStamp-timeAtTheStart < 1){
  R2->Set(-0.5);
  L2->Set(-0.5);
  R1->Set(-0.5);
  L1->Set(-0.5);
  }

  if(currentTimeStamp-timeAtTheStart >= 1.1 && currentTimeStamp-timeAtTheStart < 2){
  R2->Set(0.5);
  L2->Set(0.5);
  R1->Set(0.5);
  L1->Set(0.5);
  }

  if(currentTimeStamp-timeAtTheStart >= 2.1 && currentTimeStamp-timeAtTheStart < 3.4){
  R2->Set(-1);
  L2->Set(-1);
  R1->Set(-1);
  L1->Set(-1);
  }

  if(currentTimeStamp-timeAtTheStart >= 3.5 && currentTimeStamp-timeAtTheStart < 10){
  R2->Set(0);
  L2->Set(0);
  R1->Set(0);
  L1->Set(0);
  }

  std::cout<<currentTimeStamp-timeAtTheStart<<std::endl;
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {}

int fast = 2;
void Robot::TeleopPeriodic() {

  if(driver->GetSquareButton() == 1){
    fast = 2.5;
  }
  if(driver->GetCircleButton() == 1){
    fast = 1;
  }

  L2->Set(-(driver->GetLeftY()/fast));
  R2->Set(-(driver->GetRightY()/fast));
  L1->Set(-(driver->GetLeftY()/fast));
  R1->Set(-(driver->GetRightY()/fast));

  if(driver->GetL2Axis() > 0.1){
    arm->Set(driver->GetL2Axis()/4);
  }
  else{
    if(driver->GetR2Axis() > 0.1){
      arm->Set(-(driver->GetR2Axis()/4));
    }
    else{
      arm->Set(0);
    }
  }

  if(driver->GetL1Button() == true){
    gripper->Set(1);
  }
  else{
    if(driver->GetR1Button() == true){
      gripper->Set(-1);
    }
    else{
      gripper->Set(0);
    }
  }
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif