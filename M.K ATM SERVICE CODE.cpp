//M.K ATM WITHDRAWAL PROGRAM
//c program to operate ATM services
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<conio.h>
#include<time.h>
struct customer{
	char account[20];
	char password[8];
	char name[20];
	int balance;
};
void delay(int seconds)
{
	int start=clock();
	while(clock()<start+seconds*CLOCKS_PER_SEC);
}
void transfer()
{
	struct customer s;
	char temp_account[20];
	char temp_password[8];
	char temp_account2[20];
	int amount,tax,bal,yes;
	printf("\n\t\t\t\t\t\t**************************");
	printf("\n\t\t\t\t\t\tEnter your account number:");
	scanf("\n\t\t\t\t\t\t%s",temp_account);
	printf("\n\t\t\t\t\t\tEnter your password:");
	scanf("\n\t\t\t\t\t\t%s",temp_password);
	printf("\n\t\t\t\t\t\t**************************");
	FILE* file=fopen("atm.txt","r");
	FILE* temp=fopen("temp.txt","w");
	if(file==NULL)
	{
		printf("\n\t\t\t\t\tFile failed to open");
		exit(0);
	}
	if(temp==NULL)
	{
		printf("\n\t\t\t\t\tThe temporary file does not exist");
		exit(0);
	}
	int found=0,found2=0;
	while(fscanf(file,"%[^,],%[^,],%[^,],%d",s.name,s.account,s.password,&s.balance)!=EOF)
	{
		if((strcmp(temp_account,s.account)==0)&&(strcmp(temp_password,s.password)==0))
		{
			found=0;
			printf("\n\t\t\t\t\t\tEnter the account to transfer to");
			scanf("\n\t\t\t\t\t\t%s",temp_account2);
			printf("\n\t\t\t\t\t\tEnter amount to transfer to account %s",temp_account);
			scanf("\n\t\t\t\t\t\t%d",&amount);
			tax=amount*0.045;
			if((amount+tax)>s.balance)
			{
				printf("\n\t\t\t\t\t\tYour account is too low to make such transfer");
				return;
			}
			printf("\n\t\t\t\tYou are about to transfer %d to %s",amount,temp_account2);
			printf("\n\t\t\t\tPress 1 to accept or 2 to decline");
			scanf("\n\t\t\t\t%d",&yes);
			if(yes==2)
			{
				return;
			}
			s.balance-=amount+tax;
			bal=s.balance;
			fprintf(temp,"%s,%s,%s,%d",s.name,s.account,s.password,s.balance);
			
		}
		while(fscanf(file,"%[^,],%[^,],%[^,],%d",s.name,s.account,s.password,&s.balance)!=EOF)
			{
				if(strcmp(temp_account2,s.account)==0)
				{
					s.balance+=amount;
					fprintf(temp,"%s,%s,%s,%d",s.name,s.account,s.password,s.balance);
					found2=1;
				}
				else
				{
					fprintf(temp,"%s,%s,%s,%d",s.name,s.account,s.password,s.balance);
				}
			}
		
	}
	fclose(file);
	fclose(temp);
	if(!found&&!found2)
	{
		printf("\n\t\t\t\t\t\tIncorrect account");
		remove("temp.txt");
		getch();
	}
	else
	{
		printf("\n\t\t\tYou have transfered %d successfully to %s and your balance is %d",amount,temp_account2,bal);
		remove("atm.txt");
		rename("temp.txt","atm.txt");
	}
}
void reset_password()
{
	srand(time(NULL));
	struct customer s;
	char temp_account[20];
	char temp_password[8];
	char new_password[8];
	int otp=0,otp1,b=1;
	printf("\n\t\t\t\t\t\t**************************");
	printf("\n\t\t\t\t\t\tEnter your account number:");
	scanf("\n\t\t\t\t\t\t%s",temp_account);
	printf("\n\t\t\t\t\t\tEnter your password:");
	scanf("\n\t\t\t\t\t\t%s",temp_password);
	printf("\n\t\t\t\t\t\t**************************");
	FILE* file=fopen("atm.txt","r");
	FILE* temp=fopen("temp.txt","w");
	if(file==NULL)
	{
		printf("\n\t\t\t\t\tFile failed to open");
		exit(0);
	}
	if(temp==NULL)
	{
		printf("\n\t\t\t\t\tThe temporary file does not exist");
		exit(0);
	}
	int found=0;
	while(fscanf(file,"%[^,],%[^,],%[^,],%d",s.name,s.account,s.password,&s.balance)!=EOF)
	{
		if((strcmp(temp_account,s.account))&&(strcmp(temp_password,s.password))!=0)
		{
			fprintf(temp,"%s,%s,%s,%d",s.name,s.account,s.password,s.balance);
		}
		else
		{
			printf("\n\t\t\t\t\t\tYou will receive an OTP shortly");
			for(int i=1;i<=4;i++)
			{
				otp+=(rand()%9)*b;
				b=b*10;
			}
			delay(3);
			printf("\n\t\t\t\t\t\tOTP= %d Do not share your otp with anyone else",otp);
			printf("\n\t\t\t\t\t\tEnter your OTP to continue");
			scanf("\n\t\t\t\t\t\t%d",&otp1);
			if(otp!=otp1)
			{
				printf("\n\t\t\t\t\t\tThe OTP is wrong");
				return;
			}
			printf("\n\t\t\t\t\t\tEnter your new password");
			scanf("\n\t\t\t\t\t\t%s",new_password);
			if((strlen(new_password)<4)||(strlen(new_password)>8))
			{
				printf("\n\t\t\t\t\tMinimum password is 4 and maximum 8");
				return;
			}
			strcpy(s.password,new_password);
			fprintf(temp,"%s,%s,%s,%d",s.name,s.account,s.password,s.balance);
			found=1;
		}
	}
	fclose(file);
	fclose(temp);
	if(!found)
	{
		printf("\n\t\t\t\t\t\tIncorrect password or account");
		remove("temp.txt");
		getch();
	}
	else
	{
		printf("\n\t\t\tPassword changed successfully");
		remove("atm.txt");
		rename("temp.txt","atm.txt");
	}
}
void create_account()
{
	struct customer s;
	char account[20];
	printf("\n\t\t\t\t\t\t**************************");
	printf("\n\t\t\t\t\t\tEnter your name:");
	scanf("\n\t\t\t\t\t\t%s",s.name);
	printf("\n\t\t\t\t\t\tEnter your account number:");
	scanf("\n\t\t\t\t\t\t%s",account);
	printf("\n\t\t\t\t\t\tEnter your password(min 4 max 8):");
	scanf("\n\t\t\t\t\t\t%s",s.password);
	printf("\n\t\t\t\t\t\t**************************");
	if((strlen(s.password)<4)||(strlen(s.password)>8))
	{
		printf("\n\t\t\t\t\tMinimum password is 4 and maximum 8");
		return;
	}
	system("cls");
	FILE* file=fopen("atm.txt","a");
	if(file==NULL)
	{
		printf("\n\t\t\t\t\t\tThe file failedto open");
		exit(0);
	}
	while(fscanf(file,"%[^,],%[^,],%[^,],%d",s.name,s.account,s.password,&s.balance)!=EOF)
	{
		if(strcmp(account,s.account)==0)
		{
			printf("\n\t\t\t\t\t\tAccount number already used");
			return;
		}
	}
	strcpy(s.account,account);
	printf("\n\t\t\tYou have to deposit a minimum of 1000 to make account active");
	scanf("\n\t\t\t%d",&s.balance);
	if(s.balance<1000)
	{
		printf("\n\t\t\t\tMinimum amount to activate account is 1000");
		return;
	}
	fprintf(file,"%s,%s,%s,%d",s.name,s.account,s.password,s.balance);
	fclose(file);
	printf("\n\t\t\t\t\t\tAccount created successfully");
}
void deposit()
{
	struct customer s;
	char temp_account[20];
	char temp_password[8];
	int amount=0;
	int bal;
	printf("\n\t\t\t\t\t\t**************************");
	printf("\n\t\t\t\t\t\tEnter your account number:");
	scanf("\n\t\t\t\t\t\t%s",temp_account);
	printf("\n\t\t\t\t\t\tEnter your password:");
	scanf("\n\t\t\t\t\t\t%s",temp_password);
	printf("\n\t\t\t\t\t\t**************************");
	FILE* file=fopen("atm.txt","r");
	FILE* temp=fopen("temp.txt","w");
	if(file==NULL)
	{
		printf("\n\t\t\t\t\tFile failed to open");
		exit(0);
	}
	if(temp==NULL)
	{
		printf("\n\t\t\t\t\tThe temporary file does not exist");
		exit(0);
	}
	int found=0;
	while(fscanf(file,"%[^,],%[^,],%[^,],%d",s.name,s.account,s.password,&s.balance)!=EOF)
	{
		if((strcmp(temp_account,s.account))&&(strcmp(temp_password,s.password))!=0)
		{
			fprintf(temp,"%s,%s,%s,%d",s.name,s.account,s.password,s.balance);
		}
		else
		{
			printf("\n\t\t\t\t\t\tEnter amount to deposit");
			scanf("\n\t\t\t\t\t\t%d",&amount);
			s.balance+=amount;
			bal=s.balance;
			fprintf(temp,"%s,%s,%s,%d",s.name,s.account,s.password,s.balance);
			found=1;
		}
	}
	fclose(file);
	fclose(temp);
	if(!found)
	{
		printf("\n\t\t\t\t\t\tIncorrect password or account");
		remove("temp.txt");
		getch();
	}
	else
	{
		char date[50];
        strcpy(date,__DATE__);
		printf("\n\t\t\tYou have deposited ksh %d  on %s",amount,date);
		printf("\n\t\t\tYour current account balance is ksh %d",bal);
		remove("atm.txt");
		rename("temp.txt","atm.txt");
	}
}
void check_balance()
{
	struct customer s;
	char temp_account[20];
	char temp_password[8];
	printf("\n\t\t\t\t\t\t**************************");
	printf("\n\t\t\t\t\t\tEnter your account number:");
	scanf("\n\t\t\t\t\t\t%s",temp_account);
	printf("\n\t\t\t\t\t\tEnter your password:");
	scanf("\n\t\t\t\t\t\t%s",temp_password);
	printf("\n\t\t\t\t\t\t**************************");
	system("cls");
	FILE* file=fopen("atm.txt","r");
	if(file==NULL)
	{
		printf("\n\t\t\t\t\t\tThat account does not exist");
		exit(0);
	}
	int found=0;
	while(fscanf(file,"%[^,],%[^,],%[^,],%d",s.name,s.account,s.password,&s.balance)!=EOF)
	{
		if((strcmp(temp_account,s.account)==0)&&(strcmp(temp_password,s.password))==0)
		{
			found=1;
			char date[50];
            strcpy(date,__DATE__);
			printf("\n\t\t\t\t\t\t**********************");
			printf("\n\t\t\t\t\t\tName: %s",s.name);
			printf("\n\t\t\t\t\t\tAccount: %s",s.account);
			printf("\n\t\t\t\t\t\tBalance: %d",s.balance);
			printf("\n\t\t\t\t\t\t%s",date);
			printf("\n\t\t\t\t\t\t**********************");
			found=1;
		}
			
	}
	fclose(file);
	if(!found)
	{
		printf("\n\t\t\tIncorrect password or account");
	}
}
void withdraw()
{
	struct customer s;
	int amount=0;
	char temp_account[20];
	char temp_password[8];
	int bal,tax,yes;
	printf("\n\t\t\t\t\t\t*************************");
	printf("\n\t\t\t\t\t\tEnter your account number:");
	scanf("\n\t\t\t\t\t\t%s",temp_account);
	printf("\n\t\t\t\t\t\tEnter your password:");
	scanf("\n\t\t\t\t\t\t%s",temp_password);
	printf("\n\t\t\t\\t\t\t*************************");
	system("cls");
	FILE* file=fopen("atm.txt","r");
	FILE* temp=fopen("temp.txt","w");
	if(file==NULL)
	{
		printf("\n\t\t\t\tFile failed to open");
		exit(0);
	}
	if(temp==NULL)
	{
		printf("\n\t\t\t\tThe temporary file does not exist");
		exit(0);
	}
	int found=0;
	while(fscanf(file,"%[^,],%[^,],%[^,],%d",s.name,s.account,s.password,&s.balance)!=EOF)
	{
		if((strcmp(temp_account,s.account))&&(strcmp(temp_password,s.password))!=0)
		{
			fprintf(temp,"%s,%s,%s,%d",s.name,s.account,s.password,s.balance);
		}
		else
		{
			printf("\n\t\t\t\tEnter amount to withdraw");
			scanf("\n\t\t\t\t%d",&amount);
			if(amount<100)
			{
				printf("\n\t\t\t\tMinimum withdrawal is 100");
				return;
			}
			if(amount>1000000)
			{
				printf("\n\t\t\t\tMaximum withdraw amount is 1,000,000");
				return;
			}
			if(amount<=2500)
              {
            	tax=30;
              }
            else if(amount<=5000)
              {
            	tax=54;
              }
             else if(amount<=10000)
              {
	            tax=90;
              }
            else if(amount<=20000)
              {
	            tax=174;
              }
            else if(amount<=35000)
              {
            	tax=204;
              }
            else if(amount<=50000)
              {
            	tax=234;
              }
            else if(amount<=100000)
              {
            	tax=270;
              }
            else if(amount<=200000)
              {
            	tax=300;
              }
            else if(amount<=300000)
              {
             	tax=327;
              }
            else
              {
            	tax=0.0021*amount;
              }
			if((amount+tax)>s.balance)
			{
				printf("\n\t\t\t\tAccount too low to withdraw such amount");
				return;
			}
			printf("\n\t\t\t\tYou are about to withdraw %d transaction cost %d",amount,tax);
			printf("\n\t\t\t\tPress 1 to continue else press other number");
			scanf("\n\t\t\t\t%d",&yes);
			if(yes!=1)
			{
				return;
			}
			s.balance-=amount+tax;
			bal=s.balance;
			fprintf(temp,"%s,%s,%s,%d",s.name,s.account,s.password,s.balance);
			found=1;
		}
	}
	fclose(file);
	fclose(temp);
	if(!found)
	{
		printf("\n\t\t\t\t\tAccount not found");
		remove("temp.txt");
		getch();
	}
	else
	{
		system("cls");
		char date[50];
        strcpy(date,__DATE__);
		printf("\n\t\t\t\t\tYou have withdrawn ksh %d successfully on %s",amount,date);
		printf("\n\t\t\t\t\tYour current account balance is ksh %d",bal);
		remove("atm.txt");
		rename("temp.txt","atm.txt");
	}
}
void my_account()
{
	int ch,menu=0;
	do
	{
    system("cls");
	printf("\n\t\t\t\t\t\t__________________");
	printf("\n\t\t\t\t\t\t****************");
    printf("\n\t\t\t\t\t\t[1].Deposit");
    printf("\n\t\t\t\t\t\t[2].Check Balance");
    printf("\n\t\t\t\t\t\t[3].Withdraw");
    printf("\n\t\t\t\t\t\t[4].Transfer money");
    printf("\n\t\t\t\t\t\t[5].Reset Password");
    printf("\n\t\t\t\t\t\t[6].Main menu");
    printf("\n\t\t\t\t\t\t****************");
    printf("\n\t\t\t\t\t\t__________________");
    scanf("\n\t\t\t\t\t\t%d",&ch);
    switch(ch)
    {
		case 1:
			system("cls");
			deposit();
			printf("\n\t\t\t\t\t\tPress any key to return to menu");
            getch();
			break;
		case 2:
			system("cls");
			check_balance();
			printf("\n\t\t\t\t\t\tPress any key to return to menu");
            getch();
			break;
		case 3:
			system("cls");
			withdraw();
			printf("\n\t\t\t\t\t\tPress any key to return to menu");
            getch();
			break;
		case 4:
			system("cls");
			transfer();
			printf("\n\t\t\t\t\t\tPress any key to return to menu");
            getch();
			break;
		case 5:
			system("cls");
			reset_password();
			printf("\n\t\t\t\t\t\tPress any key to return to menu");
            getch();
			break;
		case 6:
			system("cls");
			menu=3;
			break;
		default:
			printf("\n\t\t\t\t\t\tEnter valid choice");
			getch();
			break;
	}
	}while(menu==0);
}
int main()
{
	int m=0,choice;
	    system("cls");
	    printf("\n\t\t\t\t\tWait for system to load\n");
	    int i=1;
	    while(i<=5)
		{
			printf("\t\t\t\t\tloading...%d%%\r",i*20);
			delay(1);
			i++;
		}
	    system("cls");
		printf("\n\t\t\t\t\t\t   ========================");
		printf("\n\t\t\t\t\t\t   ||     WELCOME        ||");
	    printf("\n\t\t\t\t\t\t   |*        TO          *|");
	    printf("\n\t\t\t\t\t\t   ||  M.K ATM SERVICE   ||");
	    printf("\n\t\t\t\t\t\t   ========================\n");
	    printf("\n\t\t\t\t\t\t   press any key to continue");
	    getch();
	do
	{
		system("cls");
		printf("\n\t\t\t\t\t\t______________________");
		printf("\n\t\t\t\t\t\t**********************");
	    printf("\n\t\t\t\t\t\t[1].Create New Account");
	    printf("\n\t\t\t\t\t\t[2].My account");
	    printf("\n\t\t\t\t\t\t[3].Exit");
	    printf("\n\t\t\t\t\t\t**********************");
	    printf("\n\t\t\t\t\t\t______________________");
	    scanf("\n\t\t\t\t\t\t%d",&choice);
		switch(choice)
		{
			case 1:
				system("cls");
                create_account();
                printf("\n\t\t\t\t\t\tPress any key to return to main menu");
                getch();
				break;
			case 2:
				system("cls");
				my_account();
				printf("\n\t\t\t\t\t\tPress any key to return to main menu");
				getch();
				break;
			
			case 3:
				system("cls");
				printf("\n\t\t\t\t\t  *********************************************");
				printf("\n\t\t\t\t\t  |             ~Thanks~                      |");
				printf("\n\t\t\t\t\t  | ~Our Dear Customer For Accessing Our~     |");
				printf("\n\t\t\t\t\t  |             ~A T M~                       |");
				printf("\n\t\t\t\t\t  |            ~Services~                     |");
				printf("\n\t\t\t\t\t  |          ~Welcome Again~                  |");
				printf("\n\t\t\t\t\t  |              ~Byee~                       |");
				printf("\n\t\t\t\t\t  *********************************************");
				exit(0);
				break;				
			default:
				system("cls");
				printf("\n\t\t\t\t\t\tEnter valid choice");
				getch();
				break;
		}
	}while (m==0);
}
//two accounts available (1).[\\eb3\\password:1111\\name:brian] (2).[\\eb4\\password:2222\\name:mikel]
//loading screen
//password reset(use of otp)
//money transfer to other account
//maximum amount  per transaction(1,000,000-withdraw)
//transaction cost taxation