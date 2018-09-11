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
#define TYPE TCP

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int comp(const void * a, const void * b)
{
	return ( *(int*)a - *(int*)b );
}

float computeAvg_Sort(int a[MAX],int n){
	float sum=0;
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
    
    float avg = computeAvg_Sort(a,n);
	
	bzero(buffer,MAX);

	sprintf (buffer, "Avg = %f \nSorted Array : ", avg);
	char number[100];
	for(int i=0;i<n;i++){
		snprintf (number, sizeof(number), "%d",a[i]);
		strcat(buffer,number);
		strcat(buffer," ");
	}

	sleep(3);
    
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
	// char str[MAX];
	// inet_ntop(AF_INET, &(serv_addr.sin_addr), str, INET_ADDRSTRLEN);

	if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
    	error("ERROR on binding");
    }

    /* Listening to the client connections */

    listen(sockfd,MAX_CONN);

    cli_addr_len = sizeof(cli_addr);

    /* Accepting any pending queue request of client */

    while(1){

    	cliSockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &cli_addr_len);
	    if (cliSockfd < 0){
	        error("ERROR on accept");
	    }

	    pid = fork();
	    if (pid == 0)  
        {
	         close(sockfd);
		     while(1)
		     {
	             	dostuff(cliSockfd);
		     }
	         exit(0);
	    }
        else 
        {
	 	// wait(&sys);
			close(newsockfd);
		}
	}

	return 0;

}