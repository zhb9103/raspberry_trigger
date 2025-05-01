
#include "TriggerServer.h"


pthread_t Thread_TCPServer_DataReceive;
pthread_t Thread_TCPServer_Accept;
pthread_t Thread_TCPServer_TimeoutCheck;


int server_fd, new_socket;
struct sockaddr_in server_address;
struct sockaddr_in client_address;

unsigned int timeout_counter;
int timeout_counter_enable;



void dump_stack(void)
{
	void *array[16];
	size_t size = backtrace(array, ARRAY_SIZE(array));
	char **strings = backtrace_symbols(array, size);
	size_t i;

	log_write("Obtained %zd stack frames.\n", size);

	for (i = 0; i < size; i++)
		log_write("%s\n", strings[i]);

	free(strings);
}

void signal_handler(int signo)
{
	log_write("=========>>>catch signal %d <<<=========\n", signo);
	
	log_write("Dump stack start...\n");
	dump_stack();
	log_write("Dump stack end...\n");
 
	signal(signo, SIG_DFL); /* 恢复信号默认处理 */
	raise(signo);           /* 重新发送信号 */
}



void *TCPServer_TimeoutCheckfun(void *arg)
{
  int ret;
  for(;;)
  {
    if(timeout_counter_enable)
    {
      timeout_counter++;
      if (timeout_counter>=TCPSERVER_TIMEOUT_MAX_COUNT)
      {
        // 
        timeout_counter_enable=0;
        // close socket
        close(new_socket);
        // kill data receive thread;
        ret = pthread_cancel(Thread_TCPServer_DataReceive);
        if (ret) {
            fprintf(stderr, "pthread_cancel error: %s\n", strerror(ret));
            log_write("pthread_cancel error: %s\n", strerror(ret));
            exit(-1);
        }
      }
    }
    else
    {
      timeout_counter=0;
    }
    sleep(1);
  }
}


void *TCPServer_DataReceivefun(void *arg)
{
  char buffer[BUF_SIZE] = {0};
  int read_bytes;
  timeout_counter_enable=1;
  for(;;)
  {
    //printf("r1.\n");
    //memset(buffer,0,BUF_SIZE);
    read_bytes = read(new_socket, buffer, BUF_SIZE);
    //printf("r2.\n");
    if(read_bytes < 0){
      perror("read");
      log_write("read data fail:%d\n",read_bytes);
      close(new_socket);
      timeout_counter_enable=0;
      return NULL;
    }
    if(read_bytes == 0){
      //disconnect
      log_write("tcp close:%d\n",read_bytes);
      printf("close %d\n",new_socket);
      close(new_socket);
      timeout_counter_enable=0;
      return NULL;
    }
    if(read_bytes > 0){
      timeout_counter=0;
      printf("Received: %s\n", buffer);
      send(new_socket, buffer, read_bytes, 0);
      memset(buffer, 0, BUF_SIZE);
    }
    //sleep(1);
  }
}


void *TCPServer_Acceptfun(void *arg)
{
  int addrlen = sizeof(client_address);
  
  for(;;)
  {
    if ((new_socket = accept(server_fd, (struct sockaddr *)&client_address,(socklen_t*)&addrlen)) < 0) {
      perror("accept");
      log_write("accept fail\n");
      exit(EXIT_FAILURE);
    }
    printf("New connection accepted\n");
/*
    int enable = 1;
    if (setsockopt(new_socket, IPPROTO_TCP,O_NDELAY , (char *)&enable, sizeof(int)) < 0) { //TCP_NODELAY
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
*/
  if (pthread_create(&Thread_TCPServer_DataReceive,NULL,TCPServer_DataReceivefun,NULL) !=TRUE ){
      perror("thread");
      log_write("create data receive thread fail\n");
      //return -6;
  }

    //sleep(1);
  }
}


int TCPServer_Init()
{
  int opt = 1;

  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    log_write("server socket fail\n");
    //exit(EXIT_FAILURE);
    return -1;
  }
/*
    int enable = 1;
    if (setsockopt(server_fd, IPPROTO_TCP,O_NDELAY , (char *)&enable, sizeof(int)) < 0) { //TCP_NODELAY
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
*/
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt))) {
    perror("setsockopt");
    log_write("setsocketopt fail\n");
    //exit(EXIT_FAILURE);
    return -2;
  }

  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(PORT);

  if (bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
    perror("bind failed");
    //exit(EXIT_FAILURE);
    log_write("bind fail\n");
    return -3;
  }

  if (listen(server_fd, 3) < 0) {
    perror("listen");
    log_write("listen fail\n");
    //exit(EXIT_FAILURE);
    return -4;
  }

  if (pthread_create(&Thread_TCPServer_Accept,NULL,TCPServer_Acceptfun,NULL) !=TRUE ){
    perror("thread");
    log_write("create accept thread fail\n");
    return-5;
  }

  if (pthread_create(&Thread_TCPServer_TimeoutCheck,NULL,TCPServer_TimeoutCheckfun,NULL) !=TRUE ){
    perror("thread");
    log_write("create timeout check fail\n");
    return-5;
  }

  printf("Server listening on port %d\n", PORT);
  log_write("Server listening on port %d\n", PORT);

  return 0;
}

int main(int argc, char ** argv)
{
  time_t server_time;
  struct tm* server_localtime;
  char server_time_buffer[10];

  timeout_counter_enable=0;
  timeout_counter=0;
  signal(SIGINT, signal_handler);
  signal(SIGSEGV, signal_handler);
  
  printf("Trigger Server ver: 0.0.1\n");
  log_write("Trigger Server ver: 0.0.1\n");

  if(TCPServer_Init()!=0)
  {
   log_write((char *)"bind error.\r\n");
    return -1;
  }

  for(;;){
/*
    server_time=time(NULL);
    server_localtime=localtime(&server_time);
    memset(server_time_buffer,0,10);
    sprintf(server_time_buffer,"%02d:%02d:%02d",server_localtime->tm_hour,server_localtime->tm_min,server_localtime->tm_sec);
    printf("%s running\n",server_time_buffer);
*/
    sleep(1);
  }

  return 0;
}


/*
int main(void)
{
    pthread_t tid;
    void *tret;
    int ret;
    ret = pthread_create(&tid, NULL, new_thread_start, NULL);
    if (ret) {
        fprintf(stderr, "pthread_create error: %s\n", strerror(ret));
        exit(-1);
    }
    sleep(1);
 
    ret = pthread_cancel(tid);
    if (ret) {
        fprintf(stderr, "pthread_cancel error: %s\n", strerror(ret));
        exit(-1);
    }
 
    ret = pthread_join(tid, &tret);
    if (ret) {
        fprintf(stderr, "pthread_join error: %s\n", strerror(ret));
        exit(-1);
    }
 
    printf("���߳���ֹ, code=%ld\n", (long)tret);
    exit(0);
}
*/

