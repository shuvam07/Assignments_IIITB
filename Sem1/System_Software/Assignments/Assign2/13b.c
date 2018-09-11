#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void handler(){}

int main(int argc,char *argv[]){
    kill(atoi(argv[1]),SIGSTOP);
    return 0;
}