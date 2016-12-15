/**********************
ActionOnWeight2.c
Jonathan Somarib
A reading program for reading patient files
December 2015
***********************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
struct data
{
	char encryptdata[255];
	char firstname[255];
	char surname[255];
	char dob[255];
	char height[255];
	char waist[255];
	char weight[255];
	char comment[255];
};
struct data decryption(struct data action);
struct data GetPatientDetails(struct data action);
int main()
{
	struct data action =
	{
		0
	};
	action = GetPatientDetails(action);
}
/*The GetPatientDetails function opens and reads the chosen text file
decrypts the data and then displays it*/
struct data GetPatientDetails(struct data action)
{
	FILE *fp;
	int i;
	char *posi1;
	char *posi2;
	char *posi3;
	char *posi4;
	char *posi5;
	char *posi6;
	char *posi7;
	char username[255];
	char filename[255];
	printf("Action on Weight - Read Patient File | Consultant\n");
	printf("***************************************************\n\n");
	/*Asks for the consultant to enter in the name of the file they wish to read*/
	printf("Please Enter In The Patient's File Name (Surname+Date of Birth): ");
	scanf("%s", &username);
	fflush(stdin);
	/*The program will then automatically add the ".pat" extention to the varible*/
	strcpy(filename, username);
	strcat(filename, ".pat");
	fp = fopen(filename, "r");
	for (i = 0; i < 1; i++)
	{
		fgets(action.firstname, 20, fp);
		/*This searches the read string from the file for a new line character
		and replaces it with a null character since fgets adds a trailing new line character
		at the end of every string it reads and stores*/
		if ((posi1 = strchr(action.firstname, '\n')) != NULL)
		{
			*posi1 = '\0';
		};
		/*The lines are then decrypted as they are read and stored into arrays*/
		strcpy(action.encryptdata, action.firstname);
		action = decryption(action);
		strcpy(action.firstname, action.encryptdata);
		fgets(action.surname, 20, fp);
		if ((posi2 = strchr(action.surname, '\n')) != NULL)
		{
			*posi2 = '\0';
		};
		strcpy(action.encryptdata, action.surname);
		action = decryption(action);
		strcpy(action.surname, action.encryptdata);
		fgets(action.dob, 20, fp);
		if ((posi3 = strchr(action.dob, '\n')) != NULL)
		{
			*posi3 = '\0';
		};
		strcpy(action.encryptdata, action.dob);
		action = decryption(action);
		strcpy(action.dob, action.encryptdata);
		fgets(action.height, 20, fp);
		if ((posi4 = strchr(action.height, '\n')) != NULL)
		{
			*posi4 = '\0';
		};
		strcpy(action.encryptdata, action.height);
		action = decryption(action);
		strcpy(action.height, action.encryptdata);
		fgets(action.waist, 20, fp);
		if ((posi5 = strchr(action.waist, '\n')) != NULL)
		{
			*posi5 = '\0';
		};
		strcpy(action.encryptdata, action.waist);
		action = decryption(action);
		strcpy(action.waist, action.encryptdata);
		fgets(action.weight, 20, fp);
		if ((posi6 = strchr(action.weight, '\n')) != NULL)
		{
			*posi6 = '\0';
		};
		strcpy(action.encryptdata, action.weight);
		action = decryption(action);
		strcpy(action.weight, action.encryptdata);
		fgets(action.comment, 255, fp);
		if ((posi7 = strchr(action.comment, '\n')) != NULL)
		{
			*posi7 = '\0';
		};
		strcpy(action.encryptdata, action.comment);
		action = decryption(action);
		strcpy(action.comment, action.encryptdata);
	}
	fclose(fp);
	/*Once all the lines have been read an decrypted they are then displayed nicely for the
	consultant to view*/
	printf("File Name: %s", filename);
	getch();
	system("cls");
	printf("Action on Weight - Patient Details\n");
	printf("**************************\n\n");
	printf("Name: %s %s\n", action.firstname, action.surname);
	printf("Date of Birth: %c%c/%c%c/%c%c \n", action.dob[0], action.dob[1], action.dob[2], action.dob[3], action.dob[4], action.dob[5]);
	printf("Height: %s centimetres\n", action.height);
	printf("Waist: %s centimetres\n", action.waist);
	printf("Weight: %s kilograms\n", action.weight);
	printf("Comment: %s", action.comment);
	printf("\n\nPress Enter To Select A New Patient File");
	getch();
	system("cls");
	action = GetPatientDetails(action);
	return action;
}
/*The decryption function is used to decrypt the "decryptdata" varible that is stored in
the global structure, whatever string is stored there when the encyption function is called
will then be encrypted and the encryped string then returned back to the same "decryptdata" varible in
the structure which can then be called into any function where necessary*/
struct data decryption(struct data action)
{
	int len = 0;
	int i = 0;
	int encrypting[255] = {0};
	char encrypted[255] = {0};
	len = strlen(action.encryptdata);
	/*The loops works by coverting the string character by character into an int type varible
	from a char type varible, this will then display the ASCII code value of each character
	which is then be decrease by 4 this new ASCII value will then be converted back character by
	character into a char type varible which will then store the newly encrypted characters.
	Special charcters are left alone and so they are not encrypted*/
	for (i = 0 ; i < len ; i++)
	{
		encrypting[i] = action.encryptdata[i];
		if ((encrypting[i] < 48) && (encrypting[i] > 31))
		{
			encrypted[i] = encrypting[i];
		}
		if ((encrypting[i] < 123) && (encrypting[i] > 96))
		{
			if (encrypting[i] >= 101)
			{
				encrypted[i] = encrypting[i] - 4;
			}
			else
			{
				encrypted[i] = encrypting[i] + 22;
			}
		}
		else
		{
			if ((encrypting[i] < 58) && (encrypting[i] > 47))
			{
				if (encrypting[i] >= 52)
				{
					encrypted[i] = encrypting[i] - 4;
				}
				else
				{
					encrypted[i] = encrypting[i] + 6;
				}
			}
			else
			{
				if ((encrypting[i] < 91) && (encrypting[i] > 64))
				{
					if (encrypting[i] >= 69)
					{
						encrypted[i] = encrypting[i] - 4;
					}
					else
					{
						encrypted[i] = encrypting[i] + 22;
					}
				}
			}
		}
	}
	strcpy(action.encryptdata, encrypted);
	return action;
}

