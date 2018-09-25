#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<netdb.h> 
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>


#define MAX 50

#define clear() printf("\033[H\033[J")

#define ACC_DET_PATH "acc_det.txt"
#define JOINT_ACC_DET_PATH "joint_acc_det.txt"
#define ADMIN_UNAME "admin"
#define ADMIN_PASS "admin"

int _newSockfd ;

/* passwrd length of max 13*/


int account_id = 12454;
int joint_account_id = 10000;

struct account{
	char name[MAX];
	char pass[MAX];
	char accId[MAX];
};

void error(char *msg)
{
    perror(msg);
    exit(0);
}

void createAccFile();
int addEntry();
void addAccount();
void getBalance(int);
void deleteAccount();
void getAdminMenu();
void getMenu(char s[],int);
int checkDetails();
int checkAccExists();
void login();
void signUp();
void admin();
void openScreen();
void createAccount();
void password_change();
void view_details();


void depositInJoint(int acc_id){
	int amt;
	char filename[MAX],buff[MAX];
	sprintf(filename,"%d.txt",acc_id);
	recv(_newSockfd,&amt,sizeof(amt),0);
	int fd=open(filename,O_RDWR);
	struct flock lock;
	lock.l_type=F_WRLCK;
	fcntl(fd,F_SETLKW,&lock);
	read(fd,buff,20);
	int bal = atoi(buff);
	// printf("\nEnter amount to be deposited : ");
	// scanf("%d",&amt);
	bal+=amt;
	lseek (fd,0,0);
	sprintf(buff, "%d", bal);
	write(fd,buff,strlen(buff));
	lock.l_type = F_UNLCK;
    fcntl (fd, F_SETLKW, &lock);
    close(fd);
    return;
}

void withdrawFromJoint(int acc_id){
	int flag = 1,amt;
	char filename[MAX],buff[MAX];
	sprintf(filename,"%d.txt",acc_id);
	recv(_newSockfd,&amt,sizeof(amt),0);
	int fd=open(filename,O_RDWR);
	struct flock lock;
	lock.l_type=F_WRLCK;
	fcntl(fd,F_SETLKW,&lock);
	read(fd,buff,20);
	int bal = atoi(buff);
	// printf("\nEnter amount to be withdrawn : ");
	// scanf("%d",&amt);
	if(amt>bal){
		flag = 0;
		// printf("Sorry the maximum you can withdraw is %d\n",bal);
	}
	else{
		// flag = 1;
		bal-=amt;
		printf("%d\n", bal);
		lseek (fd,0,0);
		sprintf(buff, "%d", bal);
		write(fd,buff,strlen(buff));
	}
	send(_newSockfd,&flag,sizeof(flag),0);
	send(_newSockfd,&bal,sizeof(bal),0);
	// printf("Press enter to unlock");
	// getchar();
	lock.l_type = F_UNLCK;
    fcntl (fd, F_SETLKW, &lock);
    close(fd);
    return;
}

void getBalanceForJoint(int acc_id){
	char bal[10];
	int balance;
	char filename[MAX];
	sprintf(filename,"%d.txt",acc_id);
	int fd = open(filename,O_RDONLY);
	struct flock lock;
	lock.l_type=F_RDLCK;
	fcntl(fd,F_SETLKW,&lock);
	read(fd,bal,10);
	lock.l_type = F_UNLCK;
    fcntl (fd, F_SETLKW, &lock);
	close(fd);
	balance = atoi(bal);
	send(_newSockfd,&balance,sizeof(balance),0);
	return;
}

void getMenuForJoint(char name[MAX],int acc_id){
	int op;
	while(1){
		// printf("\n\n1: Deposit\n");
		// printf("2: Withdraw\n");
		// printf("3: Balance Enquiry\n");
		// printf("4: Password Change\n");
		// printf("5: View details\n");
		// printf("6: Exit\n\n");
		// printf("Choose option : ");
		// scanf("%d",&op);
		recv(_newSockfd,&op,sizeof(op),0);
		switch(op){
			case 1: depositInJoint(acc_id);
					break;
			case 2: withdrawFromJoint(acc_id);
					break;
			case 3: getBalanceForJoint(acc_id);
					break;
			case 4: password_change(name,JOINT_ACC_DET_PATH);
					 break;
			case 5: view_details(acc_id,JOINT_ACC_DET_PATH);
					break;
			default:openScreen();
		}
	}
	
}

void JointLogin(){
	char name[MAX],pass[MAX];
	// printf("\nEnter username: ");
	// scanf("%s",name);
	// printf("Enter password: ");
	// scanf("%s",pass);
	recv(_newSockfd,name,sizeof(name),0);
	recv(_newSockfd,pass,sizeof(pass),0);
	int acc_id=checkDetails(name,pass,JOINT_ACC_DET_PATH);
	send(_newSockfd,&acc_id,sizeof(acc_id),0);
	if(acc_id >0){
		getMenuForJoint(name,acc_id);
	}
	else{
		// printf("\nSorry account doesn't exits\n");
		openScreen();
	}
}

void joint_acc(){
	int fd = open(JOINT_ACC_DET_PATH,O_CREAT|O_RDWR,0777);
	char name[MAX],pass[MAX];
	// printf("\nEnter username: ");
	// scanf("%s",name);
	// printf("\nEnter password: ");
	// scanf("%s",pass);
	recv(_newSockfd,name,sizeof(name),0);
	recv(_newSockfd,pass,sizeof(pass),0);
	int acc_id = addEntry(name,pass,-1,JOINT_ACC_DET_PATH);
	send(_newSockfd,&acc_id,sizeof(acc_id),0);

	if(acc_id == 0){
		// printf("Account already exits please login\n");
		openScreen();
	}
	else{
		// printf("\nAccount created Successfully\n");
		getMenuForJoint(name,acc_id);
	}
	
}

void password_change(char name[MAX],char filePath[MAX]){
	printf("%s\n", name);
	char pass[MAX];
	int fd = open(filePath,O_RDWR);
	int i=0,k=0;char c;
	char space[MAX];
	char buff[MAX],details[MAX];
	while(1){
		int rd = read(fd,&c,1);
		if(rd<=0){
			break;
		}	
		else if(c=='\n'){
			buff[i]='\0';
			// printf("buff %s\n",buff);
			char *uname = strtok (buff," ");
			char *pass1 = strtok (NULL," ");
			// send(_newSockfd,pass1,sizeof(pass1),0);
			int id = atoi(strtok (NULL," "));
			// printf("%s\n",uname);
			if(!strcmp(uname,name)){
				// printf("size = %d\n",i);
				// printf("\nYour old Password is : %s\n",pass1);
				// printf("Enter the new Password : ");
				// scanf("%s",pass);
				send(_newSockfd,pass1,sizeof(pass1),0);
				recv(_newSockfd,pass,sizeof(pass),0);
				sprintf(details,"%s %s %d",name,pass,id);
				lseek(fd,-i-1,SEEK_CUR);
				write(fd,details,strlen(details));
				// printf("size = %lu\n",i-strlen(details));
				for(int j=0;j<i-strlen(details)-1;j++)
					space[k++]=' ';
				// space[k++]='\n';
				space[k]='\0';
				write(fd,space,strlen(space));
				close(fd);
				// printf("Password Changed Successfully!\n");
			}
			i=0;
		}
		else{
			buff[i++]=c;
		}	
	}
	close(fd);
	return;
}


void getUsernamesFromId(int acc_id,char filePath[MAX]){
	int fd = open(filePath,O_RDWR);
	int i=0;char c;
	char buff[MAX],filename[MAX];
	while(1){
		int rd = read(fd,&c,1);
		if(rd<=0){
			break;
		}	
		else if(c=='\n'){
			buff[i]='\0';
			char *uname = strtok (buff," ");
			strtok (NULL," ");
			int id = atoi(strtok (NULL," "));
			// printf("%s\n",uname);
			if(id == acc_id){
				send(_newSockfd,uname,sizeof(uname),0);
				printf("%s ", uname);
			}
			i=0;
		}
		else{
			buff[i++]=c;
		}	
	}
	char end[MAX] = "NULL";
	send(_newSockfd,end,sizeof(end),0);
	close(fd);
	return;
}

void view_details(int acc_id,char filePath[MAX]){
	int bal;
	// printf("\nAccount Details --- \n\nAccount holder(s) : ");
	getUsernamesFromId(acc_id,filePath);
	getBalance(acc_id);
	// send(_newSockfd,&bal,sizeof(bal),0);
	// printf("\nBalance : %d",);
}

void deposit(int acc_id){
	char filename[MAX],buff[MAX];
	int amt;
	sprintf(filename,"%d.txt",acc_id);
	// printf("acc %d\n", acc_id);
	int fd =open(filename,O_RDWR);
	read(fd,buff,20);
	int bal = atoi(buff);
	// printf("\nEnter amount to deposit : ");
	// scanf("%d",&amt);
	recv(_newSockfd,&amt,sizeof(amt),0);
	bal+=amt;
	// printf("\nUpdated Balance %d\n",bal);
	send(_newSockfd,&bal,sizeof(bal),0);
	lseek (fd,0,0);
	sprintf(buff, "%d\n", bal);
	write(fd,buff,strlen(buff));
	close(fd);
	return;
}

void withdraw(int acc_id){
	char filename[MAX],buff[MAX];
	int amt,flag = 1;
	sprintf(filename,"%d.txt",acc_id);
	int fd =open(filename,O_RDWR);
	read(fd,buff,20);
	int bal = atoi(buff);
	// printf("\nEnter amount to withdraw : ");
	// scanf("%d",&amt);
	recv(_newSockfd,&amt,sizeof(amt),0);
	if(amt>bal){
		flag = 0;
		// printf("\nSorry the maximum you can withdraw is : %d\n",bal);
		// return;
	}
	else{
		bal-=amt;
		sprintf(buff, "%d\n", bal);
		lseek (fd,0,0);
		write(fd,buff,strlen(buff));
	}
	send(_newSockfd,&flag,sizeof(bal),0);
	// printf("\nUpdated Balance %d\n",bal);
	send(_newSockfd,&bal,sizeof(bal),0);
	close(fd);
	return;
}

void checkIdAndRemoveFile(int acc_id,char filePath[MAX]){
	int fd = open(filePath,O_RDWR);
	int i=0;char c;
	char buff[MAX],filename[MAX];
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
			int id = atoi(strtok (NULL," "));
			// printf("%s\n",uname);
			if(id == acc_id){
				return;
			}
			i=0;
		}
		else{
			buff[i++]=c;
		}	
	}
	sprintf(filename,"%d.txt",acc_id);
	remove(filename);
	close(fd);
	return;
}

void deleteEntry(char username[MAX],char filePath[MAX]){
	int fd = open(filePath,O_RDWR);
	int i=0;char c;
	char buff[MAX];
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
				lseek(fd,-i-1,SEEK_CUR);
				write(fd,"NULL NULL NULL\n",13);
				close(fd);
				checkIdAndRemoveFile(acc_id,filePath);
			}
			i=0;
		}
		else{
			buff[i++]=c;
		}	
	}
	return;
}


void createAccFile(){
	open(ACC_DET_PATH,O_CREAT|O_RDWR,0777);
}

int addEntry(char name[MAX],char pass[MAX],int acc_id,char filePath[MAX]){
	char details[200],buff[200];
	
	struct  account det;
	
	if(checkAccExists(name,&det,filePath)){
		// printf("Account already Exists please login\n");
		return 0;
	}
	else{
		// printf("Account doesn't Exists\n");
		int fd = open(filePath,O_RDWR|O_APPEND);
		acc_id = acc_id > 0?acc_id : account_id;
		sprintf(details, "%s %s         %d\n", name,pass,acc_id);
		write(fd,details,strlen(details));
		close(fd);
		fd = open(filePath,O_RDWR|O_APPEND);
		read(fd,buff,200);
		// printf("id %d\n",acc_id);
		createAccount(account_id);
		account_id++;
		close(fd);
		return account_id-1;
	}
}

void addAccount(){
	char name[MAX],pass[MAX];
	// printf("\nEnter username: ");
	// scanf("%s",name);
	// printf("\nEnter password: ");
	// scanf("%s",pass);
	recv(_newSockfd,name,sizeof(name),0);
	recv(_newSockfd,pass,sizeof(pass),0);
	int acc_id = addEntry(name,pass,-1,ACC_DET_PATH);
	send(_newSockfd,&acc_id,sizeof(int),0);
	// createAccount();
}


void getBalance(int acc_id){
	char bal[MAX];
	int balance;
	char filename[MAX];
	sprintf(filename,"%d.txt",acc_id);
	int fd = open(filename,O_RDONLY);
	read(fd,bal,MAX);
	close(fd);
	balance = atoi(bal);
	send(_newSockfd,&balance,sizeof(balance),0);
	return;
}

void deleteAccount(){
	char uname[MAX];
	// printf("\nEnter accound username to be deleted : ");
	// scanf("%s",uname);
	recv(_newSockfd,uname,sizeof(uname),0);
	deleteEntry(uname,ACC_DET_PATH);
	// printf("Account Deleted Successfully !! \n");
	//remove(filename);
}

void searchAccounts(char filePath[MAX]){
	// printf("\n\nAll Account Details ---\n");
	int fd = open(filePath,O_RDWR);
	int i=0,bal;
	char c;
	char buff[MAX],flag[MAX] = "NULL";
	while(1){
		int rd = read(fd,&c,1);
		if(rd<=0){
			break;
		}	
		else if(c=='\n'){
			buff[i]='\0';
			// printf("%s\n",buff);
			char *uname = strtok (buff," ");
			if(strcmp(uname,"NULL")){
				// printf("Username: %s   ",uname);
				send(_newSockfd,uname,sizeof(uname),0);
				uname = strtok (NULL," ");
				// printf("Password: %s   ",uname);
				send(_newSockfd,uname,sizeof(uname),0);
				uname = strtok (NULL," ");
				// printf("Acc_Id: %s   ",uname);
				send(_newSockfd,uname,sizeof(uname),0);
				getBalance(atoi(uname));
				// send(_newSockfd,&bal,sizeof(bal),0);
				// printf("Balance: %d\n",);
			}
			i=0;
		}
		else{
			buff[i++]=c;
		}	
	}
	send(_newSockfd,flag,sizeof(flag),0);
	close(fd);
}

void getAdminMenu(){

	while(1){
		int op;

		// printf("\n\n1: Add account\n");
		// printf("2: Delete account\n");
		// printf("3: Modify account\n");
		// printf("4: Search account\n");
		// printf("5: Exit\n\n");
		// printf("Choose option : ");
		// scanf("%d",&op);
		recv(_newSockfd,&op,sizeof(op),0);
		switch(op){
			case 1: addAccount();
					break;
			case 2: deleteAccount();
					break;
			case 3: ;
					break;
			case 4: {
						// printf("\nSingle User Accounts --- \n");
						searchAccounts(ACC_DET_PATH);
						// printf("\nJoint Accounts --- \n");
						searchAccounts(JOINT_ACC_DET_PATH);
					}break;
			default:openScreen();
		}
	}
}

void getMenu(char name[MAX],int acc_id){
	int op;
	while(1){
		// printf("\n\n1: Deposit\n");
		// printf("2: Withdraw\n");
		// printf("3: Balance Enquiry\n");
		// printf("4: Password Change\n");
		// printf("5: View details\n");
		// printf("6: Exit\n\n");
		// printf("Choose option : ");
		// scanf("%d",&op);
		recv(_newSockfd,&op,sizeof(int),0);
		switch(op){
			case 1: deposit(acc_id);
					break;
			case 2: withdraw(acc_id);
					break;
			case 3: getBalance(acc_id);
					break;
			case 4: password_change(name,ACC_DET_PATH);
					 break;
			case 5: view_details(acc_id,ACC_DET_PATH);
					break;
			default:openScreen(acc_id);
		}
	}
	
}

int checkDetails(char name[MAX],char pass[MAX],char filepath[MAX]){
	int fd = open(filepath,O_RDONLY);
	int i=0;char c;
	char buff[MAX];
	while(1){
		int rd = read(fd,&c,1);
		if(rd<=0){
			break;
		}	
		else if(c=='\n'){
			buff[i]='\0';
			// printf("%s\n",buff);
			char *uname = strtok(buff," ");
			// printf("%s\n",uname);
			if(!strcmp(uname,name)){
				char *pass1 = strtok(NULL," ");
				// printf("%s\n",pass1);
				if(!strcmp(pass,pass1))
					return atoi(strtok(NULL," "));
				return 0;
			}
			i=0;
		}
		else{
			buff[i++]=c;
		}	
	}
	close(fd);
	return 0;
}

int checkAccExists(char name[MAX],struct account *det,char filePath[MAX]){
	int fd = open(filePath,O_RDWR);
	int i=0;char c;
	char buff[MAX];
	while(1){
		int rd = read(fd,&c,1);
		if(rd<=0){
			break;
		}	
		else if(c=='\n'){
			buff[i]='\0';
			// printf("buff %s\n",buff);
			char *uname = strtok (buff," ");
			// printf("%s\n",uname);
			if(!strcmp(uname,name)){
				strcpy(det->name,name);
				strcpy(det->pass,strtok (NULL," "));
				strcpy(det->accId,strtok (NULL," "));
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

void createAccount(int account_id){
	// printf("Hello\n");
	char filename[MAX];
	char balance[MAX];
	sprintf(filename,"%d.txt",account_id);
	int fd = creat(filename,0666);
	int bal = 0;
	sprintf(balance,"%d",bal);
	write(fd,balance,sizeof(bal));
	close(fd);
}

void signUp(){
	int acc_id;
	char name[MAX],pass[MAX];
	// printf("\nEnter username: ");
	// scanf("%s",name);
	recv(_newSockfd,name,sizeof(name),0);
	// printf("\nEnter password: ");
	// scanf("%s",pass);
	recv(_newSockfd,pass,sizeof(pass),0);
	acc_id = addEntry(name,pass,-1,ACC_DET_PATH);
	send(_newSockfd,&acc_id,sizeof(int),0);
	if(acc_id ==0){
		// send(_newSockfd,&acc_id,sizeof(int),0);
		// printf("Account already exits please login\n");
		openScreen();
	}
	else{
		// printf("\nAccount created Successfully\n");
		getMenu(name,acc_id);
	}

}

void login(){
	char name[MAX],pass[MAX];
	recv(_newSockfd,name,sizeof(name),0);
	recv(_newSockfd,pass,sizeof(pass),0);
	// printf("\nEnter username: ");
	// scanf("%s",name);
	// printf("Enter password: ");
	// scanf("%s",pass);
	int acc_id=1;
	acc_id = checkDetails(name,pass,ACC_DET_PATH);
	send(_newSockfd,&acc_id,sizeof(acc_id),0);
	if(acc_id >0){
		getMenu(name,acc_id);
	}
	else{
		// printf("\nSorry account doesn't exits\n");
		openScreen();
	}
}

void admin(){
	char name[MAX],pass[MAX];
	int flag;
	// printf("\nEnter username: ");
	// scanf("%s",name);
	// printf("Enter password: ");
	// scanf("%s",pass);
	recv(_newSockfd,name,sizeof(name),0);
	recv(_newSockfd,pass,sizeof(pass),0);
	flag = (!strcmp(name,ADMIN_UNAME) && !strcmp(pass,ADMIN_PASS));
	send(_newSockfd,&flag,sizeof(flag),0);
	if(flag)
		getAdminMenu();
	else{
		// printf("\nSorry admin login unsuccessful\n");
		openScreen();
	}
	return;
}

void openScreen(){
	int op;
	// printf("\n\n Login / SignUp \n\n");
	// printf("1: Sign Up\n");
	// printf("2: Normal User Login\n");
	// printf("3: Admin Login \n");
	// printf("4: New Joint Account\n");
	// printf("5: Joint Account Login\n");
	// printf("6: Exit\n\n\n");
	// printf("Choose option : ");
	recv(_newSockfd,&op,sizeof(int),0);
	// scanf("%d",&op);
	switch(op){
		case 1: signUp();
				break;
		case 2: login();
				break;
		case 3: admin();
				break;
		case 4: joint_acc();
				break;
		case 5: JointLogin();
				break;
		default: exit(1);
	}
}

void getMaxAccountId(int *max_id,char filePath[MAX]){
	int fd = open(filePath,O_RDWR);
	int i=0;char c;
	char buff[MAX],filename[MAX];
	while(1){
		int rd = read(fd,&c,1);
		if(rd<=0){
			break;
		}	
		else if(c=='\n'){
			buff[i]='\0';
			char *uname = strtok (buff," ");
			strtok (NULL," ");
			int id = atoi(strtok (NULL," "));
			if(id>*max_id)
				*max_id = id;
			i=0;
		}
		else{
			buff[i++]=c;
		}	
	}
	close(fd);
	return;
}

void startExecution(){
	int max_id=-1;
	createAccFile();
	getMaxAccountId(&max_id,ACC_DET_PATH);
	getMaxAccountId(&max_id,JOINT_ACC_DET_PATH);
	if(max_id != -1)
		account_id = max_id + 1;

	openScreen();
}

int main(int argc ,char *argv[]){

	int _sockfd, cli_addr_len, bufferLength;
	struct sockaddr_in serv_addr, cli_addr;
	struct hostent *server;
	char stream[MAX];
	char ack[10]={'\0'}, syn[10] = {'\0'};
	clear();
	printf("Hi!!!The banking server is up and running...\n");

	_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(_sockfd < 0){
		error("ERROR opening socket");
	}

	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=atoi(argv[1]);
	serv_addr.sin_addr.s_addr=INADDR_ANY;//INADDR_ANY;
	if (bind(_sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
    	error("ERROR on binding");
    }

    listen(_sockfd,5);

    while(1){
    	cli_addr_len = sizeof(cli_addr);
	    _newSockfd = accept(_sockfd, (struct sockaddr *) &cli_addr, &cli_addr_len);
	    if (_newSockfd < 0){
	        error("ERROR on accept");
	    	exit(0);
		}
		if(fork()==0){
            close(_sockfd);
			startExecution();
	    }
	    else
	    
	    close(_newSockfd);

		// close(_newSockfd);
	}
	
	return 0;
	
}