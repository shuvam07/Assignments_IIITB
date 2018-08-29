#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h> 
#include <unistd.h> 
#include <arpa/inet.h>

#define MAX 256
#define MAX_CONN 5
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

int comp(const void * a, const void * b)
{
	return ( *(int*)a - *(int*)b );
}

int computeAvg_Sort(int a[MAX],int n){
	int sum=0;
	qsort(a,n,sizeof(int),comp);
	for(int i=0;i<n;i++)
		sum+=a[i];
	return (sum/n);
}


void doStuff(int cliSockfd){

    
    char buffer[MAX];
    int c;

    int bufferLen = read(cliSockfd,buffer,MAX);
    printf("%s\n",buffer);
    int a[MAX],n=0,bytesread;
    char *input1= buffer;
    while (sscanf(input1, "%d%n", &c, &bytesread) > 0) {
        a[n++] = c;
        input1 += bytesread;
    }
    
    int avg = computeAvg_Sort(a,n);
	
	bzero(buffer,MAX);

	sprintf (buffer, "Avg = %d \nSorted Array : ", avg);
	char number[100];
	for(int i=0;i<n;i++){
		snprintf (number, sizeof(number), "%d",a[i]);
		strcat(buffer,number);
		strcat(buffer," ");
	}
    
    write(cliSockfd, buffer , MAX);
    

}

int main(int argc, char *argv[]){

	unsigned char buf[sizeof(struct in_addr)];

	int sockfd, cliSockfd, PORT=atoi(argv[2]), cli_addr_len;
	struct sockaddr_in serv_addr, cli_addr;
	struct hostent *server;

	/* Creating Socket Connection */

	sockfd = socket(AF_INET, TYPE, 0);
	if(sockfd < 0){
		error("ERROR opening socket");
	}

	/* Binding the server address*/

	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=PORT;
	inet_pton(AF_INET, argv[1], &(serv_addr.sin_addr));

	if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
    	error("ERROR on binding");
    }

    /* Listening to the client connections */

    listen(sockfd,MAX_CONN);

    cli_addr_len = sizeof(cli_addr);

    /* Accepting any pending queue request of client */

    cliSockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &cli_addr_len);
    if (cliSockfd < 0){
        error("ERROR on accept");
    }

    doStuff(cliSockfd);
	
	return 0;
	
}