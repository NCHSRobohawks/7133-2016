#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    arm,            sensorPotentiometer)
#pragma config(Sensor, in2,    clawPot,        sensorPotentiometer)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           claw,          tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           BR,            tmotorVex393HighSpeed_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port3,           FR,            tmotorVex393HighSpeed_MC29, openLoop, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port4,           FL,            tmotorVex393HighSpeed_MC29, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port5,           BL,            tmotorVex393HighSpeed_MC29, openLoop, reversed, encoderPort, I2C_4)
#pragma config(Motor,  port6,           RightLift1,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           RightLift2,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           LeftLift1,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           LeftLift2,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          claw2,         tmotorVex393_HBridge, openLoop)

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
  // .....................................................................................
  // Insert user code here.
  // .....................................................................................

	AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
#define C1LX vexRT[Ch4]
#define C1LY -vexRT[Ch3]
#define C1RX vexRT[Ch1]

while(1==1){
    clearLCDLine(0);
    clearLCDLine(1);
		displayLCDNumber(0, 0, SensorValue(arm), 5);
  	displayLCDNumber(1, 0, SensorValue(clawPot), 5);
		//holonomic drive code
		motor[FL] = -C1LY - C1LX - C1RX;
		motor[FR] =  C1LY - C1LX - C1RX;
		motor[BR] =  C1LY + C1LX - C1RX;
		motor[BL] = -C1LY + C1LX - C1RX;

		//Lift
		if(VexRT[Btn5U] && sensorValue(arm) < 2500){
			motor[RightLift1] = 127;
			motor[RightLift2] = 127;
			motor[LeftLift1] = 127;
			motor[LeftLift2] = 127;
		}
		//Lift reverse
		else if (VexRT[Btn5D]&& sensorValue(arm) > 0){
			motor[RightLift1] = -127;
			motor[RightLift2] = -127;
			motor[LeftLift1] = -127;
			motor[LeftLift2] = -127;
		}
		//Do nothing
		else{
			motor[RightLift1] = 0;
			motor[RightLift2] = 0;
			motor[LeftLift1] = 0;
			motor[LeftLift2] = 0;
		}

		//Opens claw
		if(VexRT[Btn6D] && sensorValue(clawPot) <= 2960){
			motor[claw] = -127;
    	motor[claw2] = -127;
		}
		//closes claw
		else if(VexRT[Btn6u] && sensorValue(clawPot) >= 50){
			motor[claw] = 127;
    	motor[claw2] = 127;
		}
		else if(VexRT[Btn8D]){
			motor[claw] = -127;
    	motor[claw2] = -127;
		}

		//Do nothing
		else{
			motor[claw] = 0;
			motor[claw2] = 0;
		}

}
}
