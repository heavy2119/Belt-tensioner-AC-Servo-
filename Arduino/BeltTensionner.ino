// ---------------------------------------------------------------------
// ---------------------- SETTINGS SECTION -----------------------------
// ---------------------------------------------------------------------

// GLOBAL SETTINGS : How many steps maximum the stepper can travel
const int totalWorkingRange = 1500; //토탈 회전거리 (이값에따라 초기화 위치가 결정되고, 아이들위치도 결정됨)

// Sensor sensitivity
// lower value will make it more sensitive, higher less sensitive (default 100)
// tune this setting in case of issue
const int sensorTriggerLevel = 100;

// Simply test the sensor values. Use the arduino serial monitor (250000 bps) and move the lever to check the values and triggers)
// In this mode the motors will always kept disabled and no motion will occur
const bool sensorTestMode = false;

// Position after calibration, either centered or fully released
const bool centerAfterCalibration = false;

// Position after calibration, either centered or fully released
const bool calibrateAtBoot = false;

// Inactivity delay after the actuators will be parked.
const unsigned long idleDelay = 5000; //수정

// STEPPER 1 SETTINGS
const int stepper1_pulsePin = 9; // Must be either 9 or 10
const int stepper1_directionPin = 7;
const int stepper1_enablePin = 11;
const int stepper1_hallSensorPin = 2; // Must be an analog pin 아날로그A1 대신 2번핀사용
const int stepper1_reverseDirection = true; //모터회전 방향 초기화(캘리브레이션과도 연관)

// STEPPER 2
#define ENABLE_STEPPER_2;
#if defined(ENABLE_STEPPER_2)
const int stepper2_pulsePin = 10; // Must be either 9 or 10
const int stepper2_directionPin = 8;
const int stepper2_enablePin = 13;
const int stepper2_hallSensorPin = 3; // Must be an analog pin 아날로그A2대신 3번핀사용
const int stepper2_reverseDirection = false; //모터회전 방향 초기화(캘리브레이션과도 연관)
#endif

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------

#include "src/FastAccelStepper/FastAccelStepper.h"
#include "src/FastAccelStepper/AVRStepperPins.h"
#include "AxisDriver.h"
#define FirmwareVersion "2.0"

FastAccelStepperEngine engine = FastAccelStepperEngine();

AxisDriver axisDriver1 = AxisDriver();
AxisSettings axisSettings1 = AxisSettings(
	1,
	stepper1_hallSensorPin,
	stepper1_pulsePin,
	stepper1_directionPin,
	stepper1_enablePin,
	totalWorkingRange,
	stepper1_reverseDirection,
	sensorTriggerLevel,
	centerAfterCalibration);

#if defined(ENABLE_STEPPER_2)
AxisDriver axisDriver2 = AxisDriver();
AxisSettings axisSettings2 = AxisSettings(
	2,
	stepper2_hallSensorPin,
	stepper2_pulsePin,
	stepper2_directionPin,
	stepper2_enablePin,
	totalWorkingRange,
	stepper2_reverseDirection,
	sensorTriggerLevel,
	centerAfterCalibration);
#endif

AxisDriver* axisDrivers[] = {
   &axisDriver1
#if defined(ENABLE_STEPPER_2)
	,&axisDriver2
#endif
};

AxisSettings* axisSettings[] = {
   &axisSettings1
#if defined(ENABLE_STEPPER_2)
	,&axisSettings2
#endif
};

const int axisDriversCount = sizeof(axisDrivers) / sizeof(AxisDriver*);

void setup() {
	Serial.begin(250000);
	Serial.print(String(axisDriversCount));
	Serial.println(F(" steppers enabled"));

	engine.init();

	for (int i = 0; i < axisDriversCount; i++) {
		axisDrivers[i]->begin(&engine, axisSettings[i], calibrateAtBoot);
	}
}

byte readByte() {
	while (!Serial.available()) {}
	return Serial.read();
}

bool CheckSequence(byte b1, byte b2) {
	// 0xFF 0xFF
	if (b1 != readByte()) return false;
	if (b2 != readByte()) return false;

	return true;
}

void DumpSensor(int axis) {
	int sensorValue = axisDrivers[axis]->ReadHallSensor();
	Serial.print(F("Sensor #"));
	Serial.print(axis);
	Serial.print(':');
	Serial.print(sensorValue);
	Serial.print(F(":Trigger level:"));
	Serial.print(sensorTriggerLevel);
	Serial.print(F(":Triggered:"));
	Serial.print(sensorValue > sensorTriggerLevel ? 1 : 0);
	Serial.println();
}

#define read16Bits() ((uint16_t)(((uint16_t)readByte()) << 8) + (uint16_t)readByte())
#define read32Bits() ((uint32_t)( (((uint32_t)read16Bits() )<< 16) + (uint32_t)read16Bits() )   )

void readCommand() {
	if (!CheckSequence(0xFF, 0xFF)) return;

	byte cmd = readByte();

	if (cmd == 1 || cmd == 2) {
		int val1 = read16Bits();
		int val2 = read16Bits();

		if (!CheckSequence(0x0A, 0x0D)) return;

		if (cmd == 1) {
			axisDrivers[0]->setPosition16Bits(val1);
			if (axisDriversCount > 1) {
				axisDrivers[1]->setPosition16Bits(val2);
			}
			return;
		}
		if (cmd == 2) {
			axisDrivers[0]->setMaxSpeed16Bits(val1);
			if (axisDriversCount > 1) {
				axisDrivers[1]->setMaxSpeed16Bits(val2);
			}
			return;
		}
	}
	else if (cmd == 3) {
		uint32_t  val1 = read32Bits();
		uint32_t  val2 = read32Bits();

		if (!CheckSequence(0x0A, 0x0D)) return;

		axisDrivers[0]->setMaxAcceleration32Bits(val1);
		if (axisDriversCount > 1) {
			axisDrivers[1]->setMaxAcceleration32Bits(val2);
		}
	}
	else if (cmd == 10) {
		if (!CheckSequence(0x0A, 0x0D)) return;

		Serial.print(F("Enabled motors:"));
		Serial.println(axisDriversCount);
	}
	else if (cmd == 11) {
		int axis = readByte();
		if (!CheckSequence(0x0A, 0x0D)) return;

		if (axis < axisDriversCount) {
			DumpSensor(axis);
		}
	}
	else if (cmd == 12) {
		if (!CheckSequence(0x0A, 0x0D)) return;

		for (int i = 0; i < axisDriversCount; i++) {
			axisDrivers[i]->parkNow();
		}
	}
	else if (cmd == 13) {
		if (!CheckSequence(0x0A, 0x0D)) return;

		for (int i = 0; i < axisDriversCount; i++) {
			axisDrivers[i]->discardCalibration();
		}
	}
	else if (cmd == 14) {
		if (!CheckSequence(0x0A, 0x0D)) return;
		Serial.println(F(FirmwareVersion));
	}
}

void loop() {
	if (sensorTestMode) {
		for (int i = 0; i < axisDriversCount; i++) {
			DumpSensor(i);
		}
		delay(500);
		return;
	}

	if (Serial.available()) {
		readCommand();
	}

	for (int i = 0; i < axisDriversCount; i++) {
		axisDrivers[i]->update();
	}
}
