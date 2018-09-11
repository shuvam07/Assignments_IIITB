#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
 
#define PORT     8090
 
void error(char *msg)
{
    perror(msg);
    exit(0);
}

// Driver code
int main(int argc, char* argv[]) {
    int _sock;
    char buffer[sizeof(int)];
    char *hello = "Hello from client";
    struct sockaddr_in     serv_addr;
    int s_size=sizeof(serv_addr),_port;
    // Creating socket file descriptor
    if ( (_sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
 
    memset(&serv_addr, 0, sizeof(serv_addr));
    _port = atoi(argv[1]);
    // Filling server information
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(_port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    
    int n, len,count=5;
    printf("Hi!!!This is client...\n");
    printf("Enter no of nos to sort and avg...\n");
    scanf("%d",&count);
    
    printf("Enter %d numbers press enter...\n",count);
    int A[count];
    for(int i=0; i< count; i++){
        scanf("%d",&A[i]);
    }
    
    n = sendto(_sock, (const int*)&count, sizeof(int), MSG_CONFIRM, (const struct sockaddr *)&serv_addr, sizeof(serv_addr));
    n=sendto(_sock,(const int*)&A,sizeof(A), MSG_CONFIRM, (const struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (n < 0){
         error("ERROR writing to socket");
    }
    printf("Nums sent\n");
    

    float avg=0;
    int B[count];
    int ack=1;
    printf("\nWaiting for nums\n");
    recvfrom(_sock,(int *)&B,sizeof(B), MSG_WAITALL, (struct sockaddr * )&serv_addr, &s_size);
    printf("\nSorted Array - ");
    for(int i=0; i< count; i++){
        printf("%d ",B[i]);
    }
    sendto(_sock,(const int*)&ack,sizeof(int), MSG_CONFIRM, (const struct sockaddr *)&serv_addr, sizeof(serv_addr));
    recvfrom(_sock,(float *)&avg,sizeof(float), MSG_WAITALL, (struct sockaddr * )&serv_addr, &s_size);
    printf("\nAvg of nos is- %g\n",avg);
    printf("\n");
    close(_sock);
    return 0;
}
