#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
 
#define MAX 256
#define PORT 8090
#define SYNACK 10
 void error(char *msg)
{
    perror(msg);
    exit(0);
}

int compare(const void* a, const void * b){
    return (*(int *)a - *(int *)b);
}
// Driver code
int main(int argc, char* argv[]) {
    int udp_sock, cli_addr_len, bufferLength;
    struct sockaddr_in serv_addr, cli_addr;
    struct hostent *server;
    char stream[MAX];
    int myPort=atoi(argv[1]);
    char *hello = "Received 5 nums"; 
    cli_addr_len=sizeof(cli_addr);
    printf("Hi!!!This is server...\n");
    memset(&serv_addr, 0, sizeof(serv_addr));
    memset(&cli_addr, 0, sizeof(cli_addr));
    
    udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(udp_sock < 0){
        error("ERROR opening socket");
    }

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=INADDR_ANY;//INADDR_ANY;
    serv_addr.sin_port=htons(myPort);
    
    if (bind(udp_sock, (const struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
        error("ERROR on binding");
    }
    int len, n,count=5;
    while(1){
        n = recvfrom(udp_sock, (int *)&count, sizeof(int), MSG_WAITALL, ( struct sockaddr *) &cli_addr,
                    &len);
        
        printf("Client : %d numbers to sort and average\n", count);
        int A[count];
        float sum=0,avg=0;
        recvfrom(udp_sock, (int *)&A, sizeof(A), MSG_WAITALL, ( struct sockaddr *) &cli_addr, &len);
        for(int i=0;i<count;i++){
             sum+=A[i];
        }
        printf("\n%d nos received from client\n",count);
        
        printf("\nSum of nos is %g\n",sum);
        avg = (sum/count);
        printf("\nAvg of nos is %g\n",avg);
        qsort(A,count,sizeof(int),compare);
        for(int i=0; i< count; i++){
            printf("%d ",A[i]);
        }
        int ack=0;
        ack=0;
        sendto(udp_sock,(const int*)&A,sizeof(A), MSG_CONFIRM, (const struct sockaddr *)&cli_addr, sizeof(cli_addr));
        printf("\nSorted nos sent\n");
        // for(int i=0; i< count; i++){
        //     printf("%d ",A[i]);
        //     sendto(udpSock,(const int*)&A[i],sizeof(int), MSG_CONFIRM, (const struct sockaddr *)&cli_addr, sizeof(cli_addr));
        //     recvfrom(udp_sock, (int *)&ack, sizeof(int), MSG_WAITALL, ( struct sockaddr *) &cli_addr, &len);
        //     ack=0;
        // }
        recvfrom(udp_sock, (int *)&ack, sizeof(int), MSG_WAITALL, ( struct sockaddr *) &cli_addr, &len);
        printf("%d -- Sorted nums received by client\n",ack);
        bufferLength = sendto(udp_sock,(const float*)&avg,sizeof(float), MSG_CONFIRM, (const struct sockaddr *)&cli_addr, sizeof(cli_addr));
        printf("\nSent avg to client\n");
        recvfrom(udp_sock, (int *)&ack, sizeof(int), MSG_WAITALL, ( struct sockaddr *) &cli_addr, &len);
    
    }
    return 0;
}
