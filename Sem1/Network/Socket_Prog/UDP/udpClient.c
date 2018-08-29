#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h> 

#define MAX 256
#define READ			"0"
#define WRITE			"1"
#define TCP SOCK_STREAM
#define UDP SOCK_DGRAM
#define TYPE UDP

void error(char *msg)
{
    perror(msg);
    exit(0);
}

void doStuff(int sockfd){

    
    char buffer[MAX];
    int bufferLen;
    fgets(buffer,MAX,stdin);
    bufferLen = write(sockfd,buffer,strlen(buffer));

    bzero(buffer,MAX);
    bufferLen = read(sockfd,buffer,MAX);
    printf("%s\n",buffer);
    
}

int main(int argc, char *argv[]){

	int sockfd, PORT=atoi(argv[2]);
	struct sockaddr_in serv_addr;
	struct hostent *server;


    /* Creating Socket Connection */

	sockfd = socket(AF_INET, TYPE, 0);        
	if(sockfd < 0){
		error("ERROR opening socket");
	}


    /* setting server address to connect to */

	server = gethostbyname(argv[1]);              
	bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = PORT;

    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");


    doStuff(sockfd);
    
    return 0;

}