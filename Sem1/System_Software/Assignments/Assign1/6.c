#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define size 50

int main(){
	
	char buff[size];
	read(0,buff,size);
	write(1,buff,strlen(buff));

}


