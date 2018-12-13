/*
 * TH02_dev.cpp
 * Driver for DIGITAL I2C HUMIDITY AND TEMPERATURE SENSOR
 *  
 * Copyright (c) 2014 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Oliver Wang
 * Create Time: April 2014
 * Change Log :
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#ifndef RPI_TH02_CPP
#define RPI_TH02_CPP
#include "RPI_th02.h"


/****************************************************************************/
/***       Class member Functions                                         ***/
/****************************************************************************/

void TH02_dev::begin(void)
{
    /* Start IIC */
	this->DEVICE_FILE = initDevice(TH02_I2C_DEV_ID );
	if(this->DEVICE_FILE<0)
	std::cout<<"handle open fail"<<endl;
	/* TH02 don't need to software reset */
}

TH02_dev::TH02_dev(){
	this->DEVICE_FILE = initDevice(TH02_I2C_DEV_ID );
	if(this->DEVICE_FILE<0)
	std::cout<<"handle open fail"<<endl;
}

TH02_dev& TH02_dev::getSingleItem(){
        static TH02_dev singleton;
        return singleton;
}

float TH02_dev::ReadTemperature(void)
{    
    /* Start a new temperature conversion */
	TH02_IIC_WriteReg(REG_CONFIG, CMD_MEASURE_TEMP);	 	 
    //delay(100);
	/* Wait until conversion is done */
	while(!isAvailable());
	uint16_t value = TH02_IIC_ReadData();
	//std::cout<<"value==0x"<<hex<<value<<endl;
	value = value >> 2;
	/* 
	  Formula:
      Temperature(C) = (Value/32) - 50	  
	*/	
	float temper = (value/32.0)-50.0;
	
	return temper;
}
 
float TH02_dev::ReadHumidity(void)
{
 /* Start a new humility conversion */
	TH02_IIC_WriteReg(REG_CONFIG, CMD_MEASURE_HUMI);
	
	/* Wait until conversion is done */
	//delay(100);
	while(!isAvailable());
	uint16_t value = TH02_IIC_ReadData();
	
	value = value >> 4;
 
	/* 
	  Formula:
      Humidity(%) = (Value/16) - 24	  
	*/	

	float humility = (value/16.0)-24.0;
	
	return humility;
}

/****************************************************************************/
/***       Local Functions                                                ***/
/****************************************************************************/
uint8_t TH02_dev::isAvailable()
{
    uint8_t status =  TH02_IIC_ReadReg(REG_STATUS);
	if(status & STATUS_RDY_MASK)
	{
	    return 0;    //ready
	}
	else
	{
	    return 1;    //not ready yet
	}
}

void TH02_dev::TH02_IIC_WriteCmd(uint8_t u8Cmd)
{		
	i2c_smbus_write_i2c_block_data( DEVICE_FILE, 0x00, 1, &u8Cmd); 
	/* Port to arduino */
/*
	Wire.beginTransmission(TH02_I2C_DEV_ID);
	Wire.write(u8Cmd);
	Wire.endTransmission();
*/
}

uint8_t TH02_dev::TH02_IIC_ReadReg(uint8_t u8Reg)
{
    /* Port to arduino */
    uint8_t Temp = 0;


	i2c_smbus_read_i2c_block_data(DEVICE_FILE, u8Reg, 1, &Temp);

	/* Send a register reading command */
/*
    TH02_IIC_WriteCmd(u8Reg);	
		 
	Wire.requestFrom(TH02_I2C_DEV_ID, 1);	 
	while(Wire.available())
	{
	    Temp = Wire.read();	 
	}
*/		
	return Temp;
} 

void TH02_dev::TH02_IIC_WriteReg(uint8_t u8Reg,uint8_t u8Data)
{       
	i2c_smbus_write_i2c_block_data( DEVICE_FILE, u8Reg, 1, &u8Data);    
	/*Wire.beginTransmission(TH02_I2C_DEV_ID);	 
	Wire.write(u8Reg);	 
	Wire.write(u8Data);	 
	Wire.endTransmission();*/	 
}

uint16_t TH02_dev::TH02_IIC_ReadData(void)
{                        
	/* Port to arduino */	 
	uint16_t Temp = TH02_IIC_ReadData2byte(); 
	return Temp;
}

uint16_t TH02_dev::TH02_IIC_ReadData2byte()
{
    uint16_t TempData = 0;
	uint8_t tmpArray[2]={0};

	int cnt = 0;

	i2c_smbus_read_i2c_block_data(DEVICE_FILE, REG_DATA_H, 2, tmpArray);

	/*TH02_IIC_WriteCmd(REG_DATA_H);	
	
	Wire.requestFrom(TH02_I2C_DEV_ID, 3);	 
	while(Wire.available())
	{
	    tmpArray[cnt] = (uint16_t)Wire.read();        	        	
		cnt++;
	}*/
	/* MSB */
	//std::cout<<"Tmp==0x"<<hex<<(int)tmpArray[0]<<" 0x"<<(int)tmpArray[1]<<endl;
	TempData = (tmpArray[0]<<8)|(tmpArray[1]); 
	return TempData;
}
#endif