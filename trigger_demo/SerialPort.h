/*
*
* Created by Bill.Zhang
* Copyright reserved.
*
*/


#ifndef __SERIALPORT_H__
#define __SERIALPORT_H__

// define comport baudrate;
#define COM_BDR_2000000 2000000
#define COM_BDR_921600 921600
#define COM_BDR_460800 460800
#define COM_BDR_230400 230400
#define COM_BDR_115200 115200
#define COM_BDR_38400 38400
#define COM_BDR_19200 19200
#define COM_BDR_9600 9600
#define COM_BDR_4800 4800
#define COM_BDR_2400 2400
#define COM_BDR_1200 1200









// this function is for opening comport;
int ComPort_Open(char* p_devicename);
// this function is for comport speed setting;
int Comport_SetSpeed(int fdvar, int speedvar);
// this funciton is for comport parity setting;
int Comport_SetParity(int fd,int databits,int stopbits,int parity);
// this function is for close comport;
int ComPort_Close(int fd);


#endif







