#include <stdio.h>
#include <stdlib.h>  //for random function

void registration();				//Function(Module) definition
void login();
void Update(int ind);
void Position();
void Vote(int choice, int candidate);

char arrayofid[100], arrayofpass[100], arrayoffname[100], arrayoflname[100], arrayofdob[100];

int agecalc(int present_date, int present_month, int present_year, int birth_date, int birth_month, int birth_year){
   int month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
   if (birth_date > present_date) {
      present_date = present_date + month[birth_month - 1];
      present_month = present_month - 1;
   }
   if (birth_month > present_month) {
      present_year = present_year - 1;
      present_month = present_month + 12;
   }
   int final_date = present_date - birth_date;
   int final_month = present_month - birth_month;
   int final_year = present_year - birth_year;
   return (final_year);
}


int * voterid(char abc[], char pass[], char fname[], char lname[], int dob){
	static char vid[10];
	int num = rand()%9999999 + 1000000;		//generates randon number between 9999999 and 1000000
	
	int i;
	for(i=0;i<3;i++){		//Assigning character part of unique id in vid
		vid[i]=abc[i];
	}
	
	char num1[7];
	int x;
	for(i=7;i>=1;i--){		//convert num to string position by position
		x=num%10;
		num=num/10;
		num1[i-1]=(char)(x+48);
	}
	
	
	for(i=0;i<7;i++){		//Assigning numeric part of unique id in vid
		vid[i+3]=num1[i];
	}
	
	int isElementPresent=1;
	static int count=0;
	char reg[20]="Already Registered!";
	char ret[20];
	int j;
	
	
	for (i=0; i<100; i++) {						//Checking the presence of current entry in array
        if (arrayoffname[i] == fname) {			
        	if (arrayoflname[i]==lname){
	        	if (arrayofdob[i]==dob){
	        		isElementPresent = 0;
	        		for(j=0;j<20;j++){
	        			ret[j]=reg[j];
					}
				}
			}
        }
    }
	
	if (isElementPresent){						//If the entry is unique, storing it in the array
		arrayofid[count]=vid;
		arrayofpass[count]=pass;
		arrayoffname[count]=fname;
		arrayoflname[count]=lname;
		arrayofdob[count]=dob;
		count+=1;
		for(j=0;j<20;j++){
			if (j<10){
				ret[j]=vid[j];
			}
			else{
				ret[j]=" ";					//Filling the remaining indexes with blank spaces
			}
		}
	}
	
	return(ret);
}


void registration(){
	FILE *fptr;
	fptr = fopen("voting_sys.txt","w+");
	char fname[20], lname[20], abc[3], pass[25];
	int dd, mm, yy, age;
	
	printf("\n\t\t\t\t\t\tRegistration portal!\n");
	printf("\nFirst name: ");
	scanf("%s",fname);
	printf("Last name: ");
	scanf("%s",lname);
	
	int i;
	for(i=0;i<3;i++){					//for alphabetical part of voter id
		abc[i]=fname[i];
	}
	
	int date;
	printf("Dob (ddmmyy): ");
	scanf("%d",&date);
	int dob=date;
	
	yy=date%100;					//extracting date, mon, year from entered dob
	date=date/100;
	mm=date%100;
	date=date/100;
	dd=date;
	
	int day=20, mon=04, year=23;					//For current date
	
	age = agecalc(day, mon, year, dd, mm, yy);
	printf("\nYou're %d years old.\n",age);
	
	if (age>=18){
		printf("You're eligible to vote.\n");
		fprintf(fptr, "%s", fname);
		fprintf(fptr,"%s", " ");
		fprintf(fptr, "%s", lname);
		fprintf(fptr,"%s", " ");
		fprintf(fptr,"%s", date);
		fprintf(fptr,"%s", "\n");
		fclose(fptr);
	
		char pass0[25], pass1[25];

		A:
			printf("\nCreate Password: ");
			scanf("%s",&pass0);
			printf("\nEnter Password again: ");
			scanf("%s",&pass1);
			
			int k=0;
			int x= sizeof(pass0)/sizeof(pass0[0]);
			for(i=0;i<10;i++){							//Validating password
				if (pass0[i]!=pass1[i]){
					k=k+1;
				}
			}
			
			if (k==0){
				printf("Password generated. Do not forget it.");
				}
			else {
				printf("Password do not match.");
				goto A;									//redirecting to enter new password
			}
		
		char *vid;
		
		vid=voterid(abc,pass,fname,lname,dob);
		
		if (vid[19]!="!"){
			printf("\n\nYour unique VoterId is: ");
			for(i=0;i<10;i++){
				printf("%c",vid[i]);
			}
		}
		else{
			for(i=0;i<20;i++){
				printf("%c",vid[i]);
			}
		}
		
	}
	else{
		printf("You're not eligible to vote.");
	}
	
}


void Update(int ind){
	
	printf("First name: ");
	scanf("%s",&arrayoffname[ind]);
	printf("Last name: ");
	scanf("%s",&arrayoflname[ind]);
	printf("Password: ");
	scanf("%s",&arrayofpass[ind]);
	printf("\nSuccessfully updated!\n");
	login();
}


void Position(){
	int choice;
	int candidate;
	printf("\nChoose one of the following position you'd like to vote for: \n1.University Secretary\n2.Hostel Secretary\n");
	printf("Enter your choice: ");
	scanf("%d",&choice);
	if(choice==1){
		printf("\nFollowing are the candidates contesting University Elections:\n1.Gulshan Sherawat\n2.Monica Singh\n");
		printf("Choose your candidate: ");
		scanf("%d",&candidate);
		Vote(choice, candidate);
	}
	else if(choice==2){
		printf("\nFollowing are the candidates contesting Hostel Elections:\n1.Sandeep Pandey\n2.Sudheer kumar\n3.Priyanka Verma");
		printf("Choose your candidate: ");
		scanf("%d",&candidate);
		Vote(choice, candidate);
	}
	
}


void Vote(int choice, int candidate){
	char confirm;
	int count_gulshan=0, count_monica=0, count_sandeep=0, count_sudheer=0, count_priyanka=0;
	if(choice==1){
		if(candidate==1){
			printf("\nYou've chosen Gulshan Sherawat.");
			printf("\nPress y to confirm/n to go back: ");
			scanf("%c",&confirm);
			if (confirm=="y"){
				count_gulshan+=1;
				printf("\nYour vote has been recorded.");
				login();
			}
			else if(confirm=="n"){
				Position();
			}
			else{
				printf("\nInvalid input!");
			}
		}
		
		else if(candidate==2){
			printf("\nYou've chosen Monica Singh.");
			printf("\nPress y to confirm/n to go back: ");
			scanf("%c",&confirm);
			if (confirm=="y"){
				count_monica+=1;
				printf("\nYour vote has been recorded.");
				login();
			}
			else if(confirm=="n"){
				Position();
			}
			else{
				printf("\nInvalid input!");
			}
		}
	}
	
	else if(choice==2){
		if(candidate==1){
			printf("\nYou've chosen Sandeep Pandey.");
			printf("\nPress y to confirm/n to go back: ");
			scanf("%c",&confirm);
			if (confirm=="y"){
				count_sandeep+=1;
				printf("\nYour vote has been recorded.");
				login();
			}
			else if(confirm=="n"){
				Position();
			}
			else{
				printf("\nInvalid input!");
			}
		}
		
		else if(candidate==2){
			printf("\nYou've chosen Sudheer Kumar.");
			printf("\nPress y to confirm/n to go back: ");
			scanf("%c",&confirm);
			if (confirm=="y"){
				count_sudheer+=1;
				printf("\nYour vote has been recorded.");
				login();
			}
			else if(confirm=="n"){
				Position();
			}
			else{
				printf("\nInvalid input!");
			}
		}
		
		else if(candidate==3){
			printf("\nYou've chosen Priyanka Verma.");
			printf("\nPress y to confirm/n to go back: ");
			scanf("%c",&confirm);
			if (confirm=="y"){
				count_priyanka+=1;
				printf("\nYour vote has been recorded.");
				login();
			}
			else if(confirm=="n"){
				Position();
			}
			else{
				printf("\nInvalid input!");
			}
		}
	}
}


void login(){
	
	char vid[10], pass[10];
	printf("\n\t\t\t\t\t\tLogin portal!\n");
	printf("\nVoter Id: ");
	scanf("%s",&vid);
	printf("Password: ");
	scanf("%s",&pass);
	
	int i,k=0;
	int ind;
	for(i=0;i<100;i++){
		if (arrayofid[i]==vid && arrayofpass[i]==pass){
			printf("Successfully logged in.");
			printf("\n\nWelcome %s %s",arrayoffname,arrayoflname);
			ind=i;														//Storing index no. of current user in array
			k=1;
			break;
		}
	}
	if(k==0){
		printf("\nIncorrect username or password.");
		login();
	}	
	
	int choice;
	printf("\n1. Update Profile\n2. Choose positions for voting\n");
	printf("\nChoose the operation: ");
	scanf("%d",&choice);
	
	if (choice==1){
		Update(ind);
	}
	else if (choice==2){
		Position();
	}
	else{
		printf("Invalid Input.");
	}
}


void main(){
	printf("\t\t\t\t\tWelcome to Online Voting Portal!\n\t\t\tYour vote matters. It's you who decides the future of the country.");
	int menu;
	
	while(1){
		printf("\n\nChoose the operation:\n1. Registration\n2. Login Portal\n");
		printf("\n\nEnter the SNo. of the desired function: ");
		scanf("%d",&menu);
		if (menu==1){
			registration();
		}
		else if(menu==2){
			login();
		}
	}	
}
