/* A simple server in the internet domain using TCP
   The port number is passed as an argument 
   This version runs forever, forking off a separate 
   process for each connection
   gcc server2.c -lsocket
*/

#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#define MAX 256
#define FILE_DOES_NOT_EXIST	"-1"
#define FILE_READ 		"2"
#define FILE_WRITTEN		"3"
#define READ			"0"
#define WRITE			"1"
			    
void dostuff(int); /* function prototype */
void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen, pid;
     struct sockaddr_in serv_addr, cli_addr;

     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     int sys;
     clilen = sizeof(cli_addr);
     while (1) 
     {
         newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
         if (newsockfd < 0) 
             error("ERROR on accept");
         pid = fork();
         if (pid < 0)
             error("ERROR on fork");
         if (pid == 0)  
         {
             close(sockfd);
	     while(1)
	     {
             	dostuff(newsockfd);
	     }
             exit(0);
         }
         else 
         {
	 	// wait(&sys);
		close(newsockfd);
	 }
     } /* end of while */
     return 0; /* we never get here */
}

/******** DOSTUFF() *********************
 There is a separate instance of this function 
 for each connection.  It handles all communication
 once a connnection has been established.
 *****************************************/

void dostuff (int sock)
{
   int n,fd=0,sys=0;
   off_t cur=0,prev=0;
   char buffer[MAX],com[MAX];     
   char ack[20]={'\0'},req[20]={'\0'};
   char file[MAX];
   char path[MAX]="/bin/";
   int success=0;
   bzero(com,MAX);
   n = read(sock,com,255);
   if (n < 0) error("ERROR reading from socket");
   if(!strcmp(com,"get"))				//Server sending one or more file(s) to client
   {
   	strcpy(req,"<<CONTINUE>>");
    	while(!strcmp(req,"<<CONTINUE>>")){
    	printf(">>>Need to send file...\n");
   	bzero(ack,0);
   	bzero(file,MAX);
   	n = write(sock,"<<ACK>>",10);
   	while(1)
   	{
   		n=read(sock,ack,20);
   		if(!strcmp(ack,"<<REQ>>"))
   		{
   			write(sock,"<<ACK>>",10);
   			break;
   		}
   	};
   	while(!read(sock,file,20));
   	fd = open(file,O_RDONLY);
  	printf(">>>Client requested for %s\n",file);
  	if(fd<0)						//file does not exist
    	{
    		n=write(sock,"FILE_DOES_NOT_EXIST",19);
    		/*if (n < 0)
    		{
    			error("ERROR writing to socket");
    			exit(0);
    		}
    		else
    			return;*/
    	}
    	bzero(buffer,MAX);
    	n=100;
    	while(n==100)
    	{
    		int m=0;
    		bzero(buffer,MAX);
    		n = read(fd,buffer,100);
    		n = write(sock,buffer,n);
    		if (n < 0) 
    		{
    			error("ERROR writing to socket");
    			success=1;
    			break;
    		}
  	}
   	(close(fd));
   	bzero(req,20);	
   //	printf("cola\n");
   	while(!read(sock,req,20));
   	//if()
   //	printf("hola\n");
   	//bzero(buffer,255);
   	//n = read(sock,buffer,20);
   	if(success)
   		printf(">>>FILE TRANSFER FAILED!!!\n");
   	else
   		printf(">>>FILE TRANSFER COMPLETE!!!\n");
	}
   }
   else if(!strcmp(com,"put"))
   {
   //	char ack[20]={'\0'},req[20]={'\0'};
    	strcpy(req,"<<CONTINUE>>");
    	while(!strcmp(req,"<<CONTINUE>>")){
    	printf("Need to save file\n");
   //	char file[MAX];
   	bzero(ack,20);
   	bzero(file,MAX);
   	bzero(buffer,MAX);
   	n = write(sock,"<<ACK>>",10);
   	while(!read(sock,file,20)) ;
   	creat(file,0777);
   	fd = open(file,O_WRONLY);
  	n = write(sock,"<<REQ>>",10);
   	printf(">>>Client uploading %s\n",file);
  	bzero(buffer,MAX);
    	while(!(n=read(sock, buffer, 100)))  ;//  printf("emmppppp\n");
	do
	{
		write(fd, buffer, n);
		if(n<100)	break;
	}while(n=read(sock, buffer, 100));
	(close(fd));
   	//printf("holli\n");		
	write(sock,"<<OK>>",10);
   	bzero(req,20);	
   	while(!read(sock,req,14));
   	//printf("polli\n");		
	//printf("hola\n");
	//bzero(buffer,255);
	//n = read(sock,buffer,20);
   	}								
   	if(success)
   		printf(">>>FILE TRANSFER FAILED!!!\n");
   	else
   		printf(">>>FILE TRANSFER COMPLETE!!!\n");
   }
   else if(!strcmp(com,"ls"))
   {
   //	char ack[20]={'\0'},req[20]={'\0'};
    //	char file[MAX];
   	struct dirent **cdir; 
   	int m=0,i=0;
   	bzero(ack,20);
   	bzero(file,MAX);
   	bzero(buffer,MAX);
   	//n = write(sock,"<<ACK>>",10);
   	/*while(1)
   	{
   		read(sock,ack,10);
   		if(!strcmp(ack,"<<REQ>>"))
   		{
   			getcwd(buffer,MAX);
   			write(sock,buffer,MAX);
   			break;
   		}
   	}*/
   	getcwd(buffer,MAX);
   	write(sock,buffer,MAX);
   	while(1)
   	{
   		read(sock,ack,10);
   		if(!strcmp(ack,"<<REQ>>"))
   		{
   			m=scandir(".",&cdir,0,alphasort);
   			break;
   		}
   	}
   	i=2;
   	while(i<m)
   	{
   		
   		bzero(file,MAX);
   		strcpy(file,cdir[i]->d_name);
   		if(cdir[i]->d_type==DT_DIR)	strcat(file,"(directory)");
		else				strcat(file,"(file)");        
		write(sock,file,strlen(file));
		while(1)
		{
			read(sock,ack,10);
			if(!strcmp(ack,"<<ACK>>"))
			{		
				break;
			}
		}
		i++;
   	}
   	write(sock,"<<OK>>",10);
   }
   else if(!strcmp(com,"lcd"))
   {
   	bzero(file,MAX);
   	bzero(buffer,MAX);
   	n=write(sock,"<<ACK>>",10);
   	while(!read(sock,file,20));
   	printf("%s\n",file);
   	struct stat owner;
	stat(file,&owner);	
        if(S_ISDIR(owner.st_mode))
	{
        	chdir(file);
                //system("clear");
		//opendir(ownerfer);
		getcwd(buffer,MAX);
        	printf("%s\n",buffer);
        	write(sock,buffer,MAX);
        	printf("%s\n",buffer);
        }	
        else
        	write(sock,"<<NAK>>",10);
   }
		
}
