



#include "TriggerClient.h"



pthread_t Thread_TCPServer_DataReceive;

struct sockaddr_in saddr;
int sockfd;
int process_done;
int send_buff_len;


#define MAX_PACKETS_COUNT 100000



void *TCPServer_DataReceivefun(void *arg)
{
    unsigned int packet_counter=0;
    char receive_buff[128]={0};
    for(;;)
    {
        recv(sockfd,receive_buff,send_buff_len,0);
        printf("receive buff=%s\n",receive_buff);
        packet_counter++;
        if(packet_counter>=MAX_PACKETS_COUNT)
        {
            break;
        }
    }
    printf("rev packets:%d\n",packet_counter);
    process_done=1;
}

int main(int argc, char **argv)
{
    struct timeval tv;
    long long t_start,t_stop;
    long long total_start,total_stop;
    char send_buff[128]={0};
    char receive_buff[128]={0};
    int ret;


    printf("Trigger Client ver: 0.0.1\n");
    process_done=0;

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1)
    {
        exit(1);
    }
 
/*
    int enable = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
*/
// sysctl -a | grep low_latency
// sudo sysctl -w net.ipv4.tcp_low_latency=1
// sudo sysctl -w net.ipv4.tcp_low_latency=0
// sudo sysctl -p

///*
    int flag = 1;
    ret = setsockopt(sockfd, IPPROTO_TCP, O_NDELAY, (char *)&flag, sizeof(flag));
    if (ret < 0) 
    {
        perror("setsockopt");
    }
//*/
    
    memset(&saddr,0,sizeof(saddr));
    saddr.sin_family=AF_INET;
    saddr.sin_port=htons(8080);
    saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    int res=connect(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
    if(res==-1)
    {
        exit(1);
    }
 
 /*
     if (pthread_create(&Thread_TCPServer_DataReceive,NULL,TCPServer_DataReceivefun,NULL) !=TRUE ){
      perror("thread");
      //return -6;
    }
 */



    //printf("input:\n");
    //fgets(buff,128,stdin);
    send_buff_len=strlen("hello world");
    memset(send_buff,0,128);
    sprintf(send_buff,"hello world",send_buff_len);
    
    gettimeofday(&tv,NULL);
    total_start = tv.tv_sec * 1000000LL + tv.tv_usec;
    for(int i=0;i<MAX_PACKETS_COUNT;i++)
    {
        gettimeofday(&tv,NULL);
        t_start = tv.tv_sec * 1000000LL + tv.tv_usec;
        send(sockfd,send_buff,strlen(send_buff),0);
        // send(sockfd,send_buff,strlen(send_buff),0);
        // send(sockfd,send_buff,strlen(send_buff),0);
        // send(sockfd,send_buff,strlen(send_buff),0);
        memset(receive_buff,0,sizeof(receive_buff));
        recv(sockfd,receive_buff,strlen(send_buff),0);
        // recv(sockfd,receive_buff,strlen(send_buff),0);
        // recv(sockfd,receive_buff,strlen(send_buff),0);
        // recv(sockfd,receive_buff,strlen(send_buff),0);
        gettimeofday(&tv,NULL);
        t_stop = tv.tv_sec * 1000000LL + tv.tv_usec;
        printf("receive buff=%s, time: %lld\n",receive_buff,(t_stop-t_start));
        
    }
    process_done=1;
    //sleep(10);
    while(!process_done)
    {
        // wait;
        sleep(1);
    }

    gettimeofday(&tv,NULL);
    total_stop = tv.tv_sec * 1000000LL + tv.tv_usec;
    printf("packets:%d, elapse time: %lld\n",MAX_PACKETS_COUNT,(total_stop-total_start));
    //sleep(1);
    close(sockfd);
    exit(0);
    
}





