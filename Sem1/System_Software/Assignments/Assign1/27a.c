#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
 


/* https://stackoverflow.com/questions/12596839/how-to-call-execl-in-c-with-the-proper-arguments */


int main(int argc,char *argv[])
{
    //printf("%s ",argv[2]);
    if(fork()==0){
        execl("bash.sh","bash.sh", (char*)NULL);
    }
    
    return 0;
}