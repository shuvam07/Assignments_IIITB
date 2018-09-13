#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
  
struct mesg_buffer { 
    long mesg_type; 
    char mesg_text[100]; 
} message; 
  
int main() 
{ 
    key_t key; 
    int msgid; 
    printf("Enter msg queue id to remove ");
    scanf("%d",&msgid); 

    // key_t key; 
    // int msgid; 
  
    msgctl(msgid, IPC_RMID, NULL);  

    printf("Removed\n");
  
    return 0; 
} 