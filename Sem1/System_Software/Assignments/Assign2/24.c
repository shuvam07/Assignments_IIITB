#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <sys/types.h>


int main() 
{ 
	key_t key =ftok("msg_queue1",22);
	int msgid = msgget(key,0666 | IPC_CREAT);

	printf("Key = %d\n",key);
	printf("Msgid = %d\n", msgid);


	return 0; 
} 
