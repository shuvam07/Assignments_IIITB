#include <stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define ACC_DET_PATH "acc_det1.txt"
#define MAX 50

int main(){
	char *username = "us01";
	char *string = "us01 abcde 1245";
	int fd = open(ACC_DET_PATH,O_RDWR);
	int i=0;char c;
	char buff[MAX];
	char space[MAX];
	int k=0;
	while(1){
		int rd = read(fd,&c,1);
		if(rd<=0){
			break;
		}	
		else if(c=='\n'){
			buff[i]='\0';
			// printf("buff %s\n",buff);
			char *uname = strtok (buff," ");
			strtok (NULL," ");
			int acc_id = atoi(strtok (NULL," "));
			// printf("%s\n",uname);
			if(!strcmp(uname,username)){
				printf("size = %d\n",i);
				lseek(fd,-i-1,SEEK_CUR);
				write(fd,string,strlen(string));
				printf("size = %d\n",i-strlen(string));
				for(int j=0;j<i-strlen(string);j++)
					space[k++]=' ';
				space[k]='\0';
				write(fd,space,strlen(space));
				return 1;
			}
			i=0;
		}
		else{
			buff[i++]=c;
		}	
	}
	return 0;
}