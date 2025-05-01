/*
*
* Created by Bill.Zhang
* Copyright reserved.
*
*/



#include "include.h"
#include "sys/time.h"


char *configFileName=(char *)"./config.cfg";

#define SERIAL_REV_BUFFLEN 256

pthread_t Thread_SerialPort_DataReceive;
pthread_t Thread_SerialPort_DataProcess;

COMMON_CFG_STRUCT COMMON_CFG_STRUCTApp;

int SerialPort_fd;

char * pVersion="Ver 0.0.3";

void *SerialPort_DataReceivefun(void *arg);
int SerialPort_Open();
int SerialPort_Send(char * databuf, int databuflen);
void SerialPort_Close();
void LoadCfgFile();

// #define BLOCKING_EN

int main(int argc, char **argv)
{
    struct timeval tv;
    long long t_start,t_stop;
    char revbuff[SERIAL_REV_BUFFLEN];
    printf("Trigger, %s\n",pVersion);
    LoadCfgFile();
    SerialPort_Open();

    gettimeofday(&tv,NULL);
    t_start = tv.tv_sec * 1000000LL + tv.tv_usec;
    for (int i=0;i<1000;i++)
    {
        SerialPort_Send("\n",strlen("\n"));
#ifdef BLOCKING_EN
	memset(revbuff,0,SERIAL_REV_BUFFLEN);
	while(1)
	{
		int revlen = read(SerialPort_fd,revbuff,SERIAL_REV_BUFFLEN);
		if ((revlen>0)&&(revbuff[0]==0x0a))
		{
			//gettimeofday(&tv,NULL);
			//long long milliseconds = tv.tv_sec * 1000LL + tv.tv_usec;
			//long long usecond = tv.tv_usec;
			//printf("%d,%lld\n",i,milliseconds);
	    		printf("%d,%02x\n",i,revbuff[0]);
			break;
		}
	}
#endif	
	//if(i==19) break;
        //usleep(10);
    }
    gettimeofday(&tv,NULL);
    t_stop = tv.tv_sec * 1000000LL + tv.tv_usec;
    printf("%lld\n",t_stop-t_start);
    sleep(1);
    SerialPort_Close();
}

void LoadCfgFile()
{
    FILE *common_fp;
	int common_c;
	char common_filereadbuff[5*1024]={0};
	int common_filereadbuffcounter;
	int common_positionvar=0;
    // parse common_cfg.cfg file content;
	if (access(configFileName,F_OK)!=-1)//configFile
	{
        
		common_fp=fopen(configFileName,"r");
        
		common_filereadbuffcounter=0;
		while((common_c=fgetc(common_fp))!=EOF)
		{
			// printf("%c",common_c);
			common_filereadbuff[common_filereadbuffcounter]=common_c;
			common_filereadbuffcounter++;
		}
		fclose(common_fp);
        
		/*
		comport=/dev/ttyUSB0
		 */
		memset(&COMMON_CFG_STRUCTApp,0,sizeof(COMMON_CFG_STRUCT));
        
		//uhfcomport=/dev/ttyUSB0
		common_positionvar=stringSearchInStr(common_filereadbuff,common_filereadbuffcounter,(char *)"serial_port=",strlen((char *)"serial_port="));
		if (common_positionvar<0)
		{
			printf((char *)"Configure file err.\r\n");
			exit(-1);
		}
		//memset(common_tempbuff,0,TEMPBUFFLEN);
		memcpy(COMMON_CFG_STRUCTApp.serialport,&common_filereadbuff[common_positionvar+strlen("serial_port=")],indexofstring(&common_filereadbuff[common_positionvar+strlen("serial_port=")],'\n'));
	}
	else
	{
		printf((char *)"Load common config file fail.\r\n");
		exit(-1);
	}
}

void *SerialPort_DataReceivefun(void *arg)
{
	char revbuff[SERIAL_REV_BUFFLEN];
	for (;;)
	{
		// pthread_testcancel();
		memset(revbuff,0,SERIAL_REV_BUFFLEN);
		int revlen = read(SerialPort_fd,revbuff,SERIAL_REV_BUFFLEN);
		if (revlen>0)
		{
            printf("%s",revbuff);
		}
		usleep(100);
	}
	//return ((void*)0);
	 pthread_exit((void*)11);
}



int SerialPort_Open()
{

	SerialPort_fd=ComPort_Open(COMMON_CFG_STRUCTApp.serialport);
	if (SerialPort_fd==FALSE)
	{
		printf((char *)"comport open fail.\r\n");
		return 1;
	}
	//if(Comport_SetSpeed(SerialPort_fd,COM_BDR_2000000)==FALSE)
	if(Comport_SetSpeed(SerialPort_fd,12000000)==FALSE)
	{
		printf((char *)"comport set speed fail.\r\n");
		return 2;
	}
	if(Comport_SetParity(SerialPort_fd,8,1,'N')==FALSE)
	{
		printf((char *)"comport set parity fail.\r\n");
		return 3;
	}
	// create the data receive thread;
	/*
	if (pthread_create(&Thread_SerialPort_DataReceive,NULL,SerialPort_DataReceivefun,NULL) !=TRUE )
	{
		printf((char *)"created thread error\r\n");
		return 4;
	}
	*/
	return TRUE;
}


int SerialPort_Send(char * databuf, int databuflen)
{
	int datalen=0;
	datalen=write(SerialPort_fd,databuf,databuflen);
	return datalen;
}

void SerialPort_Close()
{
	//pthread_kill(Thread_SerialPort_DataReceive,0);
	sleep(1);
	ComPort_Close(SerialPort_fd);
}

