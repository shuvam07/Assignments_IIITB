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

int cli_sock;

void error(char *msg)
{
    perror(msg);
    exit(0);
}

void getBalanceForJoint();
void getMenuForJoint();
void openScreen();
void password_change();
void view_details();
void getMenu();


void JointLogin(){
	char name[MAX],pass[MAX];
	printf("\nEnter username: ");
	scanf("%s",name);
	printf("Enter password: ");
	scanf("%s",pass);
	send(cli_sock,name,sizeof(name),0);
	send(cli_sock,pass,sizeof(pass),0);
	int acc_id=1;
	recv(cli_sock,&acc_id,sizeof(acc_id),0);
	if(acc_id>0){
		getMenuForJoint(name,acc_id);
	}
	else{
		printf("\nSorry account doesn't exits\n");
		openScreen();
	}
}

void getBalanceForJoint(){
	int bal;
	recv(cli_sock,&bal,sizeof(bal),0);
	printf("\nBalance : %d\n", bal);
}

void depositInJoint(){
	int amt;
	printf("\nEnter amount to be deposited : ");
	scanf("%d",&amt);
	send(cli_sock,&amt,sizeof(amt),0);
}

void withdrawFromJoint(){
	int amt,flag,bal;
	printf("\nEnter amount to be withdrawn : ");
	scanf("%d",&amt);
	send(cli_sock,&amt,sizeof(amt),0);
	recv(cli_sock,&flag,sizeof(flag),0);
	recv(cli_sock,&bal,sizeof(bal),0);
	if(!flag){
		printf("\nSorry the maximum you can withdraw is %d\n",bal);
	}
	else{
		printf("\nUpdated Balance : %d\n",bal);
	}
}


void getMenuForJoint(){
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
		send(cli_sock,&op,sizeof(op),0);
		switch(op){
			case 1: depositInJoint();
					break;
			case 2: withdrawFromJoint();
					break;
			case 3: getBalanceForJoint();
					break;
			case 4: password_change();
					 break;
			case 5: view_details();
					break;
			default:openScreen();
		}
	}
}


void joint_acc(){

	int acc_id;
	char name[MAX],pass[MAX];
	printf("\nEnter username: ");
	scanf("%s",name);
	printf("\nEnter password: ");
	scanf("%s",pass);

	send(cli_sock,name,sizeof(name),0);
	send(cli_sock,pass,sizeof(pass),0);
	recv(cli_sock,&acc_id,sizeof(acc_id),0);

	if(acc_id == 0){
		printf("\nAccount already exits please login\n");
		openScreen();
	}
	else{
		printf("\nAccount created Successfully\n");
		getMenuForJoint();
	}
}

void searchAccounts(){
	char uname[MAX];
	char flag[MAX] = "NULL";
	int bal;
	while(1){

		recv(cli_sock,uname,sizeof(uname),0);

		if(!strcmp(uname,flag))
			break;
		printf("Username: %s   ",uname);
		// send(cli_sock,uname,sizeof(uname),0);
		// uname = strtok (NULL," ");
		recv(cli_sock,uname,sizeof(uname),0);
		printf("Password: %s   ",uname);
		// send(_newSockfd,uname,sizeof(uname),0);
		// uname = strtok (NULL," ");
		recv(cli_sock,uname,sizeof(uname),0);
		printf("Acc_Id: %s   ",uname);
		
		recv(cli_sock,&bal,sizeof(bal),0);
		printf("Balance: %d\n",bal);
	}
}

void deleteAccount(){
	char uname[MAX];
	printf("\nEnter accound username to be deleted : ");
	scanf("%s",uname);
	send(cli_sock,&uname,sizeof(uname),0);
	printf("\nAccount Deleted Successfully !! \n");
}

void addAccount(){

	int acc_id;
	char name[MAX],pass[MAX];
	printf("\nEnter username: ");
	scanf("%s",name);
	printf("\nEnter password: ");
	scanf("%s",pass);
	send(cli_sock,name,sizeof(name),0);
	send(cli_sock,pass,sizeof(pass),0);
	recv(cli_sock,&acc_id,sizeof(acc_id),0);

	if(acc_id ==0){
		printf("\nAccount already exits please login\n");
		// openScreen();
	}
	else{
		printf("\nAccount created Successfully\n");
		// getMenu();
	}
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
		send(cli_sock,&op,sizeof(int),0);
		switch(op){
			case 1: addAccount();
					break;
			case 2: deleteAccount();
					break;
			case 3: ;
					break;
			case 4: {
						printf("\nSingle User Accounts --- \n");
						searchAccounts();
						printf("\nJoint Accounts --- \n");
						searchAccounts();
					}break;
			default:openScreen();
		}
	}
}

void deposit(){
	int amt,bal;
	printf("\nEnter amount to deposit : ");
	scanf("%d",&amt);
	send(cli_sock,&amt,sizeof(int),0);
	recv(cli_sock,&bal,sizeof(bal),0);
	printf("\nUpdated Balance : %d\n",bal);
	return;
}

void withdraw(){
	int amt,bal,flag;
	printf("\nEnter amount to withdraw : ");
	scanf("%d",&amt);
	send(cli_sock,&amt,sizeof(int),0);
	recv(cli_sock,&flag,sizeof(flag),0);
	recv(cli_sock,&bal,sizeof(bal),0);
	if(!flag){
		printf("\nSorry the maximum you can withdraw is : %d\n",bal);
		return;
	}
	else{
		printf("\nUpdated Balance : %d\n",bal);
	}
	return;
}

int getBalance(){
	int bal;
	recv(cli_sock,&bal,sizeof(bal),0);
	return bal;
}

void password_change(){
	char pass[MAX];
	recv(cli_sock,pass,sizeof(pass),0);
	printf("\nYour old Password is : %s\n",pass);
	printf("Enter the new Password : ");
	scanf("%s",pass);
	send(cli_sock,pass,sizeof(pass),0);
	printf("\nPassword Changed Successfully!\n");
	return;
}

void getUsernamesFromId(){
	char uname[MAX]="";
	while(1){
		recv(cli_sock,uname,sizeof(uname),0);
		if(!strcmp(uname,"NULL"))
			break;
		printf("%s ", uname);
	}
	
}

void view_details(){
	int bal;
	printf("\nAccount Details --- \n\nAccount holder(s) : ");
	getUsernamesFromId();
	recv(cli_sock,&bal,sizeof(bal),0);
	printf("\nBalance : %d",bal);
}


void getMenu(){
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
		send(cli_sock,&op,sizeof(int),0);
		switch(op){
			case 1: deposit();
					break;
			case 2: withdraw();
					break;
			case 3: printf("\nBalance : %d\n", getBalance());
					break;
			case 4: password_change();
					 break;
			case 5: view_details();
					break;
			default:openScreen();
		}
	}
	
}

void signUp(){

	int acc_id;
	char name[MAX],pass[MAX];
	printf("\nEnter username: ");
	scanf("%s",name);
	printf("\nEnter password: ");
	scanf("%s",pass);

	send(cli_sock,name,sizeof(name),0);
	send(cli_sock,pass,sizeof(pass),0);
	recv(cli_sock,&acc_id,sizeof(acc_id),0);

	if(acc_id ==0){
		printf("\nAccount already exits please login\n");
		openScreen();
	}
	else{
		printf("\nAccount created Successfully\n");
		getMenu();
	}
}

void login(){

	int acc_id;
	char name[MAX],pass[MAX];
	printf("\nEnter username: ");
	scanf("%s",name);
	printf("Enter password: ");
	scanf("%s",pass);
	send(cli_sock,name,sizeof(name),0);
	send(cli_sock,pass,sizeof(pass),0);
	recv(cli_sock,&acc_id,sizeof(acc_id),0);

	if(acc_id >0){
		getMenu();
	}
	else{
		printf("\nSorry account doesn't exits\n");
		openScreen();
	}
}

void admin(){
	int flag;
	char name[MAX],pass[MAX];
	printf("\nEnter username: ");
	scanf("%s",name);
	printf("Enter password: ");
	scanf("%s",pass);
	send(cli_sock,name,sizeof(name),0);
	send(cli_sock,pass,sizeof(pass),0);
	recv(cli_sock,&flag,sizeof(flag),0);
	if(flag)
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
	send(cli_sock,&op,sizeof(int),0);
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

int main(int argc ,char *argv[]){

	int _port, bufferLength;
	struct sockaddr_in serv_addr;
	char stream[MAX];
	struct hostent *server;
	int arr[MAX];
	int count = 0;
	char ack[10]={'\0'}, syn[10] = {'\0'};
    
    // printf("Hi!!!This is client...\n");
    // printf("How many numbers do you want to sort and average?\n");
    // scanf("%d",&count);
    
    // printf("Enter %d numbers separated by a space and then press enter...\n",count);
    // for(int i=0; i< count; i++){
    //     scanf("%d",&arr[i]);
    // }
    
    cli_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(cli_sock < 0){
		error("ERROR opening socket");
	}


	_port=atoi(argv[1]);
	server = gethostbyname(argv[2]);
	bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = _port;

    if (connect(cli_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
    {
    	error("ERROR connecting");
    	exit(0);
    }

    clear();

    printf("\n\t\t!!!  WELCOME TO THE ONLINE BANKING SYSTEM  !!!\n");

	openScreen();
	
}