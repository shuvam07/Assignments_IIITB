#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 

struct mesg_buffer { 
    long mesg_type; 
    char mesg_text[100]; 
} message; 
  
int main() 
{ 
	int msgid;
    printf("Enter msg queue id ");
    scanf("%d",&msgid); 
  
    msgrcv(msgid, &message, sizeof(message), 0, IPC_NOWAIT); 
  
    printf("Data Received is : %s \n",  message.mesg_text); 
  
    return 0; 
} 