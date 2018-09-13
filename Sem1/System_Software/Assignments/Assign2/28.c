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
    struct msqid_ds msqid_ds, *buf;
	buf = &msqid_ds;

    msgctl(msgid, IPC_STAT,buf);

    printf("Permission is : %d \n",  buf->msg_perm.mode);

	buf->msg_perm.mode = 439;

	msgctl(msgid, IPC_SET,buf);
  
    // msgrcv(msgid, &message, sizeof(message), 0, IPC_NOWAIT); 
    msgctl(msgid, IPC_STAT,buf);
  
    printf("Permission changed to : %d \n",  buf->msg_perm.mode); 
  
    return 0; 
} 