#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h> 
#include <unistd.h>

#define MAX 256
#define SYNACK 10
#define READ			"0"
#define WRITE			"1"
#define PORT 12345

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char* argv[]){
	int tcp_sock, _port, bufferLength;
	struct sockaddr_in serv_addr;
	char stream[MAX];
	struct hostent *server;
	int arr[MAX];
	int count = 0;
	char ack[10]={'\0'}, syn[10] = {'\0'};
    
    printf("Hi!!!This is client...\n");
    printf("How many numbers do you want to sort and average?\n");
    scanf("%d",&count);
    
    printf("Enter %d numbers separated by a space and then press enter...\n",count);
    for(int i=0; i< count; i++){
        scanf("%d",&arr[i]);
    }
    
    tcp_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(tcp_sock < 0){
		error("ERROR opening socket");
	}


	_port=atoi(argv[1]);
	server = gethostbyname(argv[2]);
	bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = _port;

    if (connect(tcp_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
    {
    	error("ERROR connecting");
    	exit(0);
    }
    
    bufferLength = send(tcp_sock,&count,sizeof(int),0);     
	for(int i=0; i< count; i++){
    	send(tcp_sock,&arr[i],sizeof(int),0);
    }
	
	if (bufferLength < 0){
         error("ERROR writing to socket");
    }
    

	int *sorted_arr;
    printf("Bytes recv = %d\n",bufferLength);
    float avg=0;
    printf("Bytes recv = %d\n",bufferLength);
    
    for(int i=0; i< count; i++){
    	recv(tcp_sock,&arr[i],sizeof(int),0);
    }
    printf("Sorted Array - ");
    for(int i=0; i< count; i++){
    	printf("%d ",arr[i]);
    }
    recv(tcp_sock,&avg,sizeof(float),0);
    printf("\nAvg of nos is- %g\n",avg);
    sleep(3);
    return 0;
}
