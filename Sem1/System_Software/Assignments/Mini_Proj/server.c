#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define MAX 50

#define ACC_DET_PATH "acc_det.txt"
#define JOINT_ACC_DET_PATH "joint_acc_det.txt"
#define ADMIN_UNAME "admin"
#define ADMIN_PASS "admin"

/* passwrd length of max 13*/


int account_id = 12454;
int joint_account_id = 10000;

struct account{
	char name[MAX];
	char pass[MAX];
	char accId[MAX];
};

void createAccFile();
int addEntry();
void addAccount();
int getBalance(int);
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
	char filename[MAX],buff[MAX];
	sprintf(filename,"%d.txt",acc_id);
	int fd=open(filename,O_RDWR);
	struct flock lock;
	lock.l_type=F_WRLCK;
	fcntl(fd,F_SETLKW,&lock);
	read(fd,buff,20);
	int bal = atoi(buff),amt;
	printf("\nEnter amount to be deposited : ");
	scanf("%d",&amt);
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
	char filename[MAX],buff[MAX];
	sprintf(filename,"%d.txt",acc_id);
	int fd=open(filename,O_RDWR);
	struct flock lock;
	lock.l_type=F_WRLCK;
	fcntl(fd,F_SETLKW,&lock);
	read(fd,buff,20);
	int bal = atoi(buff),amt;
	printf("\nEnter amount to be withdrawn : ");
	scanf("%d",&amt);
	if(amt>bal){
		printf("Sorry the maximum you can withdraw is %d\n",bal);
	}
	else{
		bal-=amt;
		lseek (fd,0,0);
		sprintf(buff, "%d", bal);
		write(fd,buff,strlen(buff));
	}
	// printf("Press enter to unlock");
	// getchar();
	lock.l_type = F_UNLCK;
    fcntl (fd, F_SETLKW, &lock);
    close(fd);
    return;
}

int getBalanceForJoint(int acc_id){
	char bal[10];
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
	return atoi(bal);
}

void getMenuForJoint(char name[MAX],int acc_id){
	int op;
	while(1){
		printf("\n\n1: Deposit\n");
		printf("2: Withdraw\n");
		printf("3: Balance Enquiry\n");
		printf("4: Password Change\n");
		printf("5: View details\n");
		printf("6: Exit\n\n");
		printf("Choose option : ");
		scanf("%d",&op);
		switch(op){
			case 1: depositInJoint(acc_id);
					break;
			case 2: withdrawFromJoint(acc_id);
					break;
			case 3: printf("\nBalance : %d\n", getBalanceForJoint(acc_id));
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
	printf("\nEnter username: ");
	scanf("%s",name);
	printf("Enter password: ");
	scanf("%s",pass);
	int acc_id=1;
	if((acc_id = checkDetails(name,pass,JOINT_ACC_DET_PATH))>0){
		getMenuForJoint(name,acc_id);
	}
	else{
		printf("\nSorry account doesn't exits\n");
		openScreen();
	}
}

void joint_acc(){
	int fd = open(JOINT_ACC_DET_PATH,O_CREAT|O_RDWR,0777),acc_id;
	char name[MAX],pass[MAX];
	printf("\nEnter username: ");
	scanf("%s",name);
	printf("\nEnter password: ");
	scanf("%s",pass);
	if((acc_id = addEntry(name,pass,-1,JOINT_ACC_DET_PATH))==0){
		printf("Account already exits please login\n");
		openScreen();
	}
	else{
		printf("\nAccount created Successfully\n");
		getMenuForJoint(name,acc_id);
	}
}

void password_change(char name[MAX],char filePath[MAX]){
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
			int id = atoi(strtok (NULL," "));
			// printf("%s\n",uname);
			if(!strcmp(uname,name)){
				// printf("size = %d\n",i);
				printf("\nYour old Password is : %s\n",pass1);
				printf("Enter the new Password : ");
				scanf("%s",pass);
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
				printf("Password Changed Successfully!\n");
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
			// printf("buff %s\n",buff);
			char *uname = strtok (buff," ");
			strtok (NULL," ");
			int id = atoi(strtok (NULL," "));
			// printf("%s\n",uname);
			if(id == acc_id){
				printf("%s ", uname);
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

void view_details(int acc_id,char filePath[MAX]){
	printf("\nAccount Details --- \n\nAccount holder(s) : ");
	getUsernamesFromId(acc_id,filePath);
	printf("\nBalance : %d",getBalance(acc_id));
}

void deposit(int acc_id){
	char filename[MAX],buff[MAX];
	int amt;
	sprintf(filename,"%d.txt",acc_id);
	// printf("acc %d\n", acc_id);
	int fd =open(filename,O_RDWR);
	read(fd,buff,20);
	int bal = atoi(buff);
	printf("\nEnter amount to deposit : ");
	scanf("%d",&amt);
	bal+=amt;
	printf("\nUpdated Balance %d\n",bal);
	lseek (fd,0,0);
	sprintf(buff, "%d\n", bal);
	write(fd,buff,strlen(buff));
	close(fd);
	return;
}

void withdraw(int acc_id){
	char filename[MAX],buff[MAX];
	int amt;
	sprintf(filename,"%d.txt",acc_id);
	int fd =open(filename,O_RDWR);
	read(fd,buff,20);
	int bal = atoi(buff);
	printf("\nEnter amount to withdraw : ");
	scanf("%d",&amt);
	if(amt>bal){
		printf("\nSorry the maximum you can withdraw is : %d\n",bal);
		return;
	}
	bal-=amt;
	printf("\nUpdated Balance %d\n",bal);
	sprintf(buff, "%d\n", bal);
	lseek (fd,0,0);
	write(fd,buff,strlen(buff));
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
		printf("Account already Exists please login\n");
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
		printf("id %d\n",acc_id);
		createAccount(account_id);
		account_id++;
		close(fd);
		return account_id-1;
	}
}

void addAccount(){
	char name[MAX],pass[MAX];
	printf("\nEnter username: ");
	scanf("%s",name);
	printf("\nEnter password: ");
	scanf("%s",pass);
	addEntry(name,pass,-1,ACC_DET_PATH);
	// createAccount();
}


int getBalance(int acc_id){
	char bal[10];
	char filename[MAX];
	sprintf(filename,"%d.txt",acc_id);
	int fd = open(filename,O_RDONLY);
	read(fd,bal,10);
	close(fd);
	return atoi(bal);
}

void deleteAccount(){
	char uname[MAX];
	printf("\nEnter accound username to be deleted : ");
	scanf("%s",uname);
	deleteEntry(uname,ACC_DET_PATH);
	printf("Account Deleted Successfully !! \n");
	//remove(filename);
}

void searchAccounts(char filePath[MAX]){
	// printf("\n\nAll Account Details ---\n");
	int fd = open(filePath,O_RDWR);
	int i=0;
	char c;
	char buff[MAX];
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
				printf("Username: %s   ",uname);
				uname = strtok (NULL," ");
				printf("Password: %s   ",uname);
				uname = strtok (NULL," ");
				printf("Acc_Id: %s   ",uname);
				printf("Balance: %d\n",getBalance(atoi(uname)));
			}
			i=0;
		}
		else{
			buff[i++]=c;
		}	
	}
	close(fd);
}

void getAdminMenu(){

	while(1){
		int op;

		printf("\n\n1: Add account\n");
		printf("2: Delete account\n");
		printf("3: Modify account\n");
		printf("4: Search account\n");
		printf("5: Exit\n\n");
		printf("Choose option : ");
		scanf("%d",&op);
		switch(op){
			case 1: addAccount();
					break;
			case 2: deleteAccount();
					break;
			case 3: ;
					break;
			case 4: {
						printf("\nSingle User Accounts --- \n");
						searchAccounts(ACC_DET_PATH);
						printf("\nJoint Accounts --- \n");
						searchAccounts(JOINT_ACC_DET_PATH);
					}break;
			default:openScreen();
		}
	}
}

void getMenu(char name[MAX],int acc_id){
	int op;
	while(1){
		printf("\n\n1: Deposit\n");
		printf("2: Withdraw\n");
		printf("3: Balance Enquiry\n");
		printf("4: Password Change\n");
		printf("5: View details\n");
		printf("6: Exit\n\n");
		printf("Choose option : ");
		scanf("%d",&op);
		switch(op){
			case 1: deposit(acc_id);
					break;
			case 2: withdraw(acc_id);
					break;
			case 3: printf("\nBalance : %d\n", getBalance(acc_id));
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
	printf("Hello\n");
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
	printf("\nEnter username: ");
	scanf("%s",name);
	printf("\nEnter password: ");
	scanf("%s",pass);
	if((acc_id = addEntry(name,pass,-1,ACC_DET_PATH))==0){
		printf("Account already exits please login\n");
		openScreen();
	}
	else{
		printf("\nAccount created Successfully\n");
		getMenu(name,acc_id);
	}

}

void login(){
	char name[MAX],pass[MAX];
	printf("\nEnter username: ");
	scanf("%s",name);
	printf("Enter password: ");
	scanf("%s",pass);
	int acc_id=1;
	if((acc_id = checkDetails(name,pass,ACC_DET_PATH))>0){
		getMenu(name,acc_id);
	}
	else{
		printf("\nSorry account doesn't exits\n");
		openScreen();
	}
}

void admin(){
	char name[MAX],pass[MAX];
	printf("\nEnter username: ");
	scanf("%s",name);
	printf("Enter password: ");
	scanf("%s",pass);
	if(!strcmp(name,ADMIN_UNAME) && !strcmp(pass,ADMIN_PASS))
		getAdminMenu();
	else{
		printf("\nSorry admin login unsuccessful\n");
		openScreen();
	}
}

void openScreen(){
	int op;
	printf("\n\n Login / SignUp \n\n");
	printf("1: Sign Up\n");
	printf("2: Normal User Login\n");
	printf("3: Admin Login \n");
	printf("4: New Joint Account\n");
	printf("5: Joint Account Login\n");
	printf("6: Exit\n\n\n");
	printf("Choose option : ");
	scanf("%d",&op);
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

int main(){
	int max_id=-1;
	createAccFile();

	getMaxAccountId(&max_id,ACC_DET_PATH);
	getMaxAccountId(&max_id,JOINT_ACC_DET_PATH);
	if(max_id != -1)
		account_id = max_id + 1;
	
	openScreen();
}