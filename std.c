#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"miniproject.h"
struct student stu;
void verification(){
	char u_pass[8] = {"user"};
	char s_pass[8] = {"student"};
	char a_pass[8] = {"admin"};
	char user[16];
	char student[16];
	char admin[16];
	int vchoice;
	printf("1.Enter 1 if you are an user\n"\
		"2.Enter 2 if you are a student\n"\
		"3.Enter 3 if you are an admin \n"\
		"4.Enter 4 to exit \n");
	scanf("%d",&vchoice);
	while(1){
		
		switch (vchoice){
			case 1: /*User*/
				printf("Enter the password\n");
				scanf("%s", user);
				if (strcmp(user, "user") == 0){
					printf("\t\t********\n");
					printf("\t\tWelcome\n");
					printf("\t\t********\n");
				}
				else 
					printf("Wrong password.Please try again.\n");
				break;
			case 2:/*Student*/
				printf("Enter the password\n");
				scanf("%s", student);
				if (strcmp(student, "student") == 0){
					printf("\t\t********\n");
					printf("\t\tWelcome\n");
					printf("\t\t********\n");
				}
				else 
					printf("Wrong password.Please try again.\n");
				break;
			case 3:/*Admin*/
				printf("Enter the password\n");
				scanf("%s", admin);
				if (strcmp(admin, "admin") == 0){
					printf("\t\t********\n");
					printf("\t\tWelcome\n");
					printf("\t\t********\n");
					main_window();
				}
				else 
					printf("Wrong password.Please try again.\n");
				break;
			case 4:/*exit*/
				exit(0);
				break;
		}
	}
}

void print_heading(const char st[]){
	printf("SRS : %s",st);
}
void add_student(){
	print_heading("Add Record");
	FILE *fp;
	fp = fopen("record.txt","a");
	if(fp == NULL)
		printf("Error in Opening file\n");
	else{
		printf("ID: ");
		scanf("%s", stu.ID);
		printf("Name: ");
		scanf("%s", stu.name);
		printf("Address: ");
		scanf("%s", stu.add);
		printf("Parent's name: ");
		scanf("%s", stu.parname);
		printf("Class: ");
		scanf("%d",&stu.Class);
		printf("Phone Number: ");
		scanf("%ld",&stu.phone_no);
		fwrite(&stu, sizeof(stu), 1, fp);
		printf("The record is sucessfully added\n");
	}
	fclose(fp);
	return;
}
void search_student(){
	print_heading("Search Record\n");
	char s_id[15];
	int isFound = 0;
	FILE *fp;
	fp = fopen("record.txt","r");
	printf("Enter ID to Search: ");
	scanf("%s",s_id);
	while(fread(&stu,sizeof(stu),1,fp) == 1){
		if(strcmp(stu.ID,s_id) == 0){
		isFound = 1;
		break;
		}
	}
	if(isFound == 1){
	printf("The record is Found\n");
	printf("ID: %s\n",stu.ID);
	printf("Name: %s\n",stu.name);
	printf("Address: %s\n",stu.add);
	printf("Parent's Name: %s\n",stu.parname);
	printf("Class: %d\n",stu.Class);
	printf("Phone No: %ld\n",stu.phone_no);
	}
	else{
	printf("Sory, No record found in the database\n");
	fclose(fp);
	}
	return;
}
void mod_student(){
	print_heading("Modify Record");
	char s_id[15];
	int isFound = 0, print = 37;
	printf("Enter ID to Modify: ");
	scanf("%s",s_id);
	FILE *fp;
	fp = fopen("record.txt","rb+");
	while(fread(&stu, sizeof(stu),1,fp) == 1){
        	if(strcmp(stu.ID,s_id) == 0){
        		printf("ID: ");
			scanf("%s",stu.ID);
			fgets(stu.ID,sizeof(stu.ID), fp);
            		printf("Name: ");
			scanf("%s", stu.name);
			fgets(stu.name,sizeof(stu.name),fp);
            		printf("Address: ");
			scanf("%s", stu.add);
			fgets(stu.add,sizeof(stu.add),fp);
            		printf("Parent's name: ");
			scanf("%s", stu.parname);
			fgets(stu.parname,sizeof(stu.parname),fp);
                	printf("Class: ");scanf("%d",&stu.Class);
                	printf("Phone Number: ");scanf("%ld",&stu.phone_no);
                	fseek(fp,-sizeof(stu), SEEK_CUR);
                	fwrite(&stu,sizeof(stu), 1, fp);
                	isFound = 1;
       	         	break;
		}
	}
	if(!isFound)
		printf("No Record Found");
	fclose(fp);
	return;
}
void delete_student(){
	print_heading("Delete Record");
	char s_id[15];
	int isFound = 0;
	printf("Enter ID to Modify: ");
	scanf("%s",s_id);
	FILE *fp, *temp;
	fp = fopen("record.txt","rb");
	temp = fopen("temp.txt", "wb");
	while(fread(&stu, sizeof(stu),1,fp) == 1){
		if(strcmp(s_id, stu.ID) != 0){
			fwrite(&stu,sizeof(stu),1,temp);
		}
		else
		printf("The record has been successfully deletd\n");
	}
	fclose(fp);
	fclose(temp);
	remove("record.txt");
	rename("temp.txt","record.txt");
	return;
}
void main_window(){
	int choice;
	while(1){
	printf("1. Add Student:\n");
	printf("2. Search Student:\n");
	printf("3. Modify Student Record:\n");
	printf("4. Delete Student Record:\n");
	printf("5. Display the record\n");
	printf("6. Exit:\n");
	printf("Enter your choice: ");
	scanf("%d",&choice);
		switch(choice){
			case 1:
			add_student();
			break;
			case 2:
			search_student();
			break;
			case 3:
			mod_student();
			break;     
			case 4:
			delete_student();
			break;
			case 5:
			display();
			break;
			case 6:
			exit(0);
			break;
			default:
			break;
		}
	}
}
void display(){
	FILE *fp;
	fp = fopen("record.txt", "r");
	fseek(fp, 0, SEEK_SET); 
	while(fread(&stu, sizeof(stu), 1, fp) == 1){ 
		printf("ID:%s\n", stu.ID); 
		printf("Name:%s\n", stu.name);
		printf("Add:%s\n", stu.add);
		printf("Parname:%s\n",stu.parname);
		printf("Class:%d\n",stu.Class);
		printf("Phone_no.:%ld\n",stu.phone_no);	
	}
}


