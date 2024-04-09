#include "MPU6050.h"

void MPU6050_WriteReg(uint8_t RegAddress,uint8_t Data){
	MyIIC_Start();
	MyIIC_SendByte(MPU6050_ADDRESS);
	MyIIC_ReceiveAck();
	MyIIC_SendByte(RegAddress);
	MyIIC_ReceiveAck();
	MyIIC_SendByte(Data);
	MyIIC_ReceiveAck();
	MyIIC_Stop();
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress){
	uint8_t Data;
	MyIIC_Start();
	MyIIC_SendByte(MPU6050_ADDRESS);
	MyIIC_ReceiveAck();
	MyIIC_SendByte(RegAddress);
	MyIIC_ReceiveAck();
	
	MyIIC_Start();
	MyIIC_SendByte(MPU6050_ADDRESS|0x01);
	MyIIC_ReceiveAck();
	Data = MyIIC_ReceiveByte();
	MyIIC_SendAck(1);
	MyIIC_Stop();
	
	return Data;
}

void MPU6050_Init(void){
	MyIIC_Init();
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1,0x01);
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2,0x00);
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV,0x09);
	MPU6050_WriteReg(MPU6050_CONFIG,0x06);
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG,0x18);
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG,0x18);
	
}

uint8_t MPU6050_GetID(void){

	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}

void MPU6050_GetData(int16_t *AccX,int16_t *AccY,int16_t *AccZ,
					int16_t *GyroX,int16_t *GyroY,int16_t *GyroZ){
	uint8_t DataH,DataL;
	DataH=MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
	DataL=MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	*AccX = (DataH << 8)|DataL;
						
	DataH=MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DataL=MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*AccY = (DataH << 8)|DataL;
						
	DataH=MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	DataL=MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*AccZ = (DataH << 8)|DataL;
	
	DataH=MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	DataL=MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	*GyroX = (DataH << 8)|DataL;
						
	DataH=MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DataL=MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*GyroY = (DataH << 8)|DataL;
						
	DataH=MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL=MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	*GyroZ = (DataH << 8)|DataL;
}



