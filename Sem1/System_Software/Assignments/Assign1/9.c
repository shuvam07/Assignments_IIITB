#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define size 100

int main(){
	
	struct stat st;
	int fd = open("7.c",O_RDONLY);
	fstat(fd,&st);
	printf("inode = %lu\n",st.st_ino);
	printf("No of hard Links = %lu\n",st.st_nlink);
	printf("UserId = %u\n",st.st_uid);
	printf("GroupId = %u\n",st.st_gid);
	printf("Total Size  = %lu\n",st.st_size);
	printf("No of blocks = %lu\n",st.st_blocks);
	struct timespec s = st.st_atim;
	printf("Time of last access(in sec) = %lu\n",s.tv_sec);
	s = st.st_mtim;
	printf("Time of last modification(in sec) = %lu\n",s.tv_sec);
	s = st.st_ctim;
	printf("Time of last status change(in sec) = %lu\n",s.tv_sec);

	return 0;
}


