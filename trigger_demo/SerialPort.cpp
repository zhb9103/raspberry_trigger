
/*
*
* Created by Bill.Zhang
* Copyright reserved.
*
*/

#include "SerialPort.h"
#include "stdio.h"
#include "stdlib.h"
#include "fcntl.h"
#include "unistd.h"
#include "termios.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "errno.h"
#include "include.h"
#include <pthread.h>
#include <signal.h>
#include <unistd.h>


int speed_arr[]=
{
		B2000000,B921600,B460800,B230400,B115200,B38400,B19200,B9600,B4800,B2400,B1200
};
int name_arr[]=
{
		2000000,921600,460800,230400,115200,38400,19200,9600,4800,2400,1200
};



int ComPort_Open(char* p_devicename)
{
	int fd;
	fd=open(p_devicename,O_RDWR | O_NOCTTY | O_NDELAY);
	printf("dev name:%s\r\n", p_devicename);
	// fd=open(p_devicename,O_RDWR);
	if(fd==FALSE)
	{
		//perror("can't open the device\r\n");
		return FALSE;
	}
	else
	{
		fcntl(fd,F_SETFL,0);
		return fd;
	}
}

int ComPort_Close(int fd)
{
	// fd=open(p_devicename,O_RDWR | O_NOCTTY | O_NDELAY);
	printf("comport closing.\r\n");
	close(fd);
	return 0;
}

int Comport_SetSpeed(int fdvar, int speedvar)
{
	//int i;
	int status;
	struct termios Opt;
	tcgetattr(fdvar,&Opt);
	for (int i=0;i<sizeof(speed_arr)/sizeof(int);i++)
	{
		if(speedvar == name_arr[i])
		{
			tcflush(fdvar,TCIOFLUSH);
			cfsetispeed(&Opt,speed_arr[i]);
			cfsetospeed(&Opt,speed_arr[i]);
			status=tcsetattr(fdvar,TCSANOW,&Opt);
			if (status != 0)
			{
				perror("tcsetattr fdvar\r\n");
				return FALSE;
			}
			tcflush(fdvar,TCIOFLUSH);
		}
	}
	return TRUE;
}

int Comport_SetParity(int fd,int databits,int stopbits,int parity)
{
	struct termios options;
	if(tcgetattr(fd,&options) != 0)
	{
		perror("SetupSerial 1\r\n");
		//printf("error \r\n");
		return FALSE;
	}
	//options.c_cflag |= CLOCAL | CREAD;
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	//options.c_cflag &= ~CSIZE;
	// options.c_iflag &= ~(ICRNL | IXON);
	options.c_iflag = ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	options.c_oflag &= ~OPOST;
	// options.c_cflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	// options.c_cflag &= ~OPOST;
	options.c_cc[VSWTC] = 0;
	options.c_lflag = 0;
	options.c_oflag = 0;
	options.c_iflag = 0;
	options.c_iflag &= ~(IXON | IXOFF | IXANY);
	switch(databits)
	{
		case 7:
		{
			options.c_cflag |= CS7;
			break;
		}
		case 8:
		{
			options.c_cflag |= CS8;
			break;
		}
		default:
			printf("Unsuppored data size\r\n");
			return FALSE;
	}
	switch(parity)
	{
		case 'n':
		case 'N':
		{
			options.c_cflag &= ~PARENB;
			options.c_cflag &= ~INPCK;
			break;
		}
		case 'o':
		case 'O':
		{
			options.c_cflag |= (PARODD | PARENB);
			options.c_cflag |= INPCK;
			break;
		}
		case 'e':
		case 'E':
		{
			options.c_cflag |= PARENB;
			options.c_cflag &= ~PARODD;
			options.c_cflag |= INPCK;
			break;
		}
		case 's':
		case 'S':
		{
			options.c_cflag &= ~PARENB;
			options.c_cflag &= ~CSTOPB;
			break;
		}
		default:
			printf("Unable supported parity\r\n");
			return FALSE;
	}
	switch(stopbits)
	{
		case 1:
		{
			options.c_cflag &= ~CSTOPB;
			break;
		}
		case 2:
		{
			options.c_cflag |= CSTOPB;
			break;
		}
		default:
			printf("Unsupported stop bits\r\n");
			return FALSE;
	}
	if (parity != 'n')
	{
		options.c_cflag |= INPCK;
		tcflush(fd,TCIFLUSH);
		options.c_cc[VTIME]=0;
		options.c_cc[VMIN]=1;
		if(tcsetattr(fd,TCSANOW,&options) !=0 )
		{
			perror("SetupSerial 3\r\n");
			return FALSE;
		}
	}
	return TRUE;
}

















