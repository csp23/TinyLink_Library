#include "Grove_IMU9_Accelerometer_RPI.h"
#include "MPU9250_RPI.h"

Grove_IMU9_Accelerometer_RPI::Grove_IMU9_Accelerometer_RPI():accelgyro(),status(0),gx(0),gy(0),gz(0),state(0){
}

int Grove_IMU9_Accelerometer_RPI::read(){
	if (state == 0){
		accelgyro.initialize();
		if(accelgyro.testConnection()){
			status = 1;
		}else{
			status = 0;
		}
		state = 1;
	}
	if(status == 1){
		gx = accelgyro.getAccelerationX();
		gy = accelgyro.getAccelerationY();
		gz = accelgyro.getAccelerationZ();
		return 0;
	}else{
		return -1;
	}
}

double Grove_IMU9_Accelerometer_RPI::data_x(){
	return (double) gx * 250 / 32768;
}

double Grove_IMU9_Accelerometer_RPI::data_y(){
	return (double) gy * 250 / 32768;
}

double Grove_IMU9_Accelerometer_RPI::data_z(){
	return (double) gz * 250 / 32768;
}

#if TINYLINK_ACCELEROMETER == GROVE_IMU9
	Grove_IMU9_Accelerometer_RPI TL_Accelerometer;
#endif
