#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    arm,            sensorPotentiometer)
#pragma config(Sensor, in2,    clawPot,        sensorPotentiometer)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           claw,          tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           FL,            tmotorVex393HighSpeed_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port3,           BL,            tmotorVex393HighSpeed_MC29, openLoop, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port4,           BR,            tmotorVex393HighSpeed_MC29, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port5,           FR,            tmotorVex393HighSpeed_MC29, openLoop, reversed, encoderPort, I2C_4)
#pragma config(Motor,  port6,           RightLift1,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           RightLift2,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           LeftLift1,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           LeftLift2,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          claw2,         tmotorVex393_HBridge, openLoop)
#pragma competitionControl(Competition)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

#define C1LX vexRT[Ch4]
#define C1LY vexRT[Ch3]
#define C1RX vexRT[Ch1]
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
  bStopTasksBetweenModes = true;

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

	 nMotorEncoder[FL] = 0;
  //Drive back
  while(nmotorEncoder[FL] < 627.2){
    motor[FL] = 127;
    motor[FR] = -127;
    motor[BR] = -127;
    motor[BL] = 127;
}
  nMotorEncoder[FL] = 0;
  //Grab preloads
  while(sensorValue(claw) > 125){
    motor[claw] = 127;
    motor[claw2] = 127;
  }
  //Drive back to wall
  while(nmotorEncoder[FL] < 627.2){
    motor[FL] = 127;
    motor[FR] = -127;
    motor[BR] = -127;
    motor[BL] = 127;
}
  nMotorEncoder[FL] = 0;
  //Throw stars over
  while(SensorValue(arm) < 2500){
    motor[RightLift1] = 127;
		motor[RightLift2] = 127;
		motor[LeftLift1] = 127;
		motor[LeftLift2] = 127;
		if(sensorValue(arm) > 1900 && sensorValue(claw) < 750){
		motor[claw] = -127;
    motor[claw2] = -127;
		}
  }

	//Drive forward
	while(NmotorEncoder[FL] < 627.2){
    motor[FL] = -127;
    motor[FR] = 127;
    motor[BR] = 127;
    motor[BL] = -127;
}
  nMotorEncoder[FL] = 0;
while(sensorValue(claw) > 125){
    motor[claw] = 127;
    motor[claw2] = 127;
  }
  //Drive back to wall
  while(nmotorEncoder[FL] < 627.2){
    motor[FL] = 127;
    motor[FR] = -127;
    motor[BR] = -127;
    motor[BL] = 127;
}
  nMotorEncoder[FL] = 0;
  //Throw stars over
  while(SensorValue(arm) < 2500){
    motor[RightLift1] = 127;
		motor[RightLift2] = 127;
		motor[LeftLift1] = 127;
		motor[LeftLift2] = 127;
		if(sensorValue(arm) > 1900 && sensorValue(claw) < 750){
		motor[claw] = -127;
    motor[claw2] = -127;
		}

	//Drive forwards
	while(NmotorEncoder[FL] < 627.2){
    motor[FL] = -127;
    motor[FR] = 127;
    motor[BR] = 127;
    motor[BL] = -127;
}
  nMotorEncoder[FL] = 0;
while(sensorValue(claw) > 125){
    motor[claw] = 127;
    motor[claw2] = 127;
  }
  //Drive back to wall
  while(NmotorEncoder[FL] < 627.2){
    motor[FL] = 127;
    motor[FR] = -127;
    motor[BR] = -127;
    motor[BL] = 127;
}
  nMotorEncoder[FL] = 0;
  //Throw stars over
  while(SensorValue(arm) < 2500){
    motor[RightLift1] = 127;
		motor[RightLift2] = 127;
		motor[LeftLift1] = 127;
		motor[LeftLift2] = 127;
		if(sensorValue(arm) > 1900 && sensorValue(claw) < 750){
		motor[claw] = -127;
    motor[claw2] = -127;
		}
  }
}
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
		if(VexRT[Btn6D] && sensorValue(claw) <= 100){
			motor[claw] = -50;
    	motor[claw2] = -50;
		}
			else if(VexRT[Btn6D] && sensorValue(claw) <= 350){
			motor[claw] = -80;
    	motor[claw2] = -80;
		}
			else if(VexRT[Btn6D] && sensorValue(claw) <= 650){
			motor[claw] = -100;
    	motor[claw2] = -100;
		}
		else if(VexRT[Btn6D] && sensorValue(claw) <= 850){
			motor[claw] = -127;
    	motor[claw2] = -127;
		}
		//closes claw
		else if(VexRT[Btn6u] && sensorValue(claw) >= 50){
			motor[claw] = 127;
    	motor[claw2] = 127;
		}
		else if(VexRT[Btn8D]){
			motor[claw] = -127;
    	motor[claw2] = -127;
		}
		else if(VexRT[Btn8U]){
			motor[claw] = 127;
    	motor[claw2] = 127;
		}
		//Do nothing
		else{
			motor[claw] = 0;
			motor[claw2] = 0;
		}


}
}
