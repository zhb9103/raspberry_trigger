/*
*
* Created by Bill.Zhang
* Copyright reserved.
*
*/

#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <iostream>
#include "fcntl.h"
#include "termios.h"
#include "errno.h"
#include "pthread.h"
#include "signal.h"
#include <unistd.h>
#include "sys/reboot.h"
#include "time.h"
#include "sys/time.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "bits/types.h"
#include "linux/rtc.h"
#include "sys/ioctl.h"
#include "BaseFunction.h"
#include "SerialPort.h"


#define FALSE -1
#define TRUE 0


typedef struct
{
	char serialport[200];
} COMMON_CFG_STRUCT;
extern COMMON_CFG_STRUCT COMMON_CFG_STRUCTApp;

#endif


