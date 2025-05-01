
#ifndef __TRIGGER_SERVER_H__
#define __TRIGGER_SERVER_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "sys/socket.h"
#include "sys/types.h"
#include "unistd.h"
#include "errno.h"
#include "stdarg.h"
#include "time.h"
#include <sys/stat.h> 
#include <fcntl.h> 
#include <pthread.h>
#include <signal.h>	    /* for signal */
#include <execinfo.h> 	/* for backtrace() */
#include "log.h"
#include "BaseFunction.h"


#define TRUE 0
#define FALSE -1

#define PORT 8080
#define BUF_SIZE 1024

#define TCPSERVER_TIMEOUT_MAX_COUNT 20


#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))


#endif