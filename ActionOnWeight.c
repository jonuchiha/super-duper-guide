/**********************
ActionOnWeight.c
Jonathan Somarib
A login program for entering patient files
December 2015
***********************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
/*Global Structure*/
struct data
{
	char buffer[256];
	char nursename[255];
	char nursepassword[255];
	char nursefullname[100][20];
	char username[100][20];
	char password[100][20];
	char encryptdata[255];
	char firstname[255];
	char surname[255];
	char dob[255];
	char height[255];
	char waist[255];
	char weight[255];
	char comment[255];
	char newuserfullname[255];
	char newusername[255];
	char newuserpassword[255];
	int count_lines;
	char chr;
	char loggedinuser[255];
	char loggedinusername[255];
	char loggedinpassword[255];
	int check;
	char test[255];
	int results;
};
/*Function Prototypes*/
struct data NurseLogIn(struct data action);
struct data decryption(struct data action);
struct data encryption(struct data action);
struct data EnterData(struct data action);
struct data GetNurseDetails(struct data action);
struct data AddNewUser(struct data action);
struct data CountFileLines(struct data action);
struct data Menu(struct data action);
struct data RemoveUser(struct data action);
struct data ChangePassword(struct data action);
struct data CheckString(struct data action);
int main()
{
	struct data action =
	{
		0
	};
	action = GetNurseDetails(action);
	action = NurseLogIn(action);
	return 0;
}
/*Menu Function that that gives the user 5 options to choose from
a switch case is then used to direct the user to their desired operation*/
struct data Menu(struct data action)
{
	int option;
	int valid1;
	system("cls");
	printf("Action on Weight - Menu | %s\n", action.loggedinuser);
	printf("***************************************\n\n");
	printf("1. Enter Patient Details\n");
	printf("2. Change Password\n");
	printf("3. Add A New User\n");
	printf("4. Remove A User\n");
	printf("5. Log Off\n\n");
	printf("Please select an option (1, 2, 3, 4 or 5): ");
	valid1 = scanf("%d", &option);
	fflush(stdin);
	while (option < 1 || option > 5 || valid1 != 1)
	{
		printf("\nPlease select an option (1, 2, 3, 4 or 5): ");
		valid1 = scanf("%d", &option);
		fflush(stdin);
	}
	switch (option)
	{
	case 1:
		action = EnterData(action);
		break;
	case 2:
		action = ChangePassword(action);
		break;
	case 3:
		action = AddNewUser(action);
		break;
	case 4:
		action = RemoveUser(action);
		break;
	case 5:
		printf("You have sucessfully logged out!");
		getch();
		action = NurseLogIn(action);
		break;
	}
	return action;
}
/*This function reads the text file and counts how many lines
there are in the text file this is then stored in a varible in the
global structure so that then infomation can be called into other functions*/
struct data CountFileLines(struct data action)
{
	FILE *fp3;
	action.count_lines = 0;
	/*Looks for and opens "username.txt" in read mode*/
	fp3 = fopen("username.txt", "r");
	action.chr = getc(fp3);
	while (action.chr != EOF)
	{
		if (action.chr == '\n')
		{
			action.count_lines = action.count_lines + 1;
		}
		action.chr = getc(fp3);
	}
	fclose(fp3);
	return action;
}
/*This is the function which is used to remove a user from the text file*/
struct data RemoveUser(struct data action)
{
	FILE *fp4;
	int position, c, n, k, valid1, option;
	action = CountFileLines(action);
	n = action.count_lines / 3;
	system("cls");
	printf("Action on Weight - Remove User Account | %s\n", action.loggedinuser);
	printf("**************************************************\n");
	printf("List Of Currently Registered Members\n\n");
	/*FOR loop that lists all the users currently in the text file*/
	for ( c = 0 ; c < n ; c++ )
	{
		k = c + 1;
		printf("%d: %s\n", k, action.nursefullname[c]);
	}
	printf("\nPlease select the user you would like to remove: ");
	valid1 = scanf("%d", &position);
	/*While loop for data validation*/
	while (position >= n + 1 || valid1 != 1)
	{
		printf("You have selected a user outside of the range");
		printf("\nPlease select the user you would like to remove: ");
		scanf("%d", &position);
		fflush(stdin);
	}
	printf("\nYou are about to remove: %s", action.nursefullname[position - 1]);
	printf("\nAre you sure?\n");
	printf("1. Yes\n");
	printf("2. No (Go Back To Menu)\n");
	printf("Please select an option (1 or 2): ");
	valid1 = scanf("%d", &option);
	fflush(stdin);
	/*While loop for data validation*/
	while (option < 1 || option > 2 || valid1 != 1)
	{
		printf("Please select an option (1 or 2): ");
		scanf("%d", &option);
		fflush(stdin);
	}
	/*A switch case that runs different parts of the code depending on the
	users option*/
	switch (option)
	{
	case 1:
		/*FOR loop that replaces the selected user's details with the next item in the array
		this effectively removes the selected user from the array*/
		for ( c = position - 1 ; c < n - 1 ; c++ )
		{
			strcpy(action.nursefullname[c], action.nursefullname[c+1]);
			strcpy(action.username[c], action.username[c+1]);
			strcpy(action.password[c], action.password[c+1]);
		}
		printf("\n%s has sucessfully been removed", action.nursefullname[position - 1]);
		printf("\nRemaining Registered Members: \n\n");
		fp4 = fopen("username.txt", "w");
		/*This for loop then prints the new array with the removed user to the text file
		and then displays the remaining users within the program*/
		for ( c = 0 ; c < n - 1 ; c++ )
		{
			k = c + 1;
			printf("%d: %s\n", k, action.nursefullname[c]);
			fprintf(fp4, "%s\n", action.nursefullname[c]);
			fprintf(fp4, "%s\n", action.username[c]);
			strcpy(action.encryptdata, action.password[c]);
			action = encryption(action);
			strcpy(action.password[c], action.encryptdata);
			fprintf(fp4, "%s\n", action.password[c]);
		}
		fclose(fp4);
		getch();
		action = GetNurseDetails(action);
		action = Menu(action);
		break;
	case 2:
		action = Menu(action);
		break;
	}
	return action;
}
/*Add new user function is used to add new users to the text file*/
struct data AddNewUser(struct data action)
{
	FILE *fp2;
	int valid1;
	int option;
	int len;
	int test;
	system("cls");
	fp2 = fopen("username.txt", "a");
	printf("Action on Weight - Add New User Account | %s\n", action.loggedinuser);
	printf("*************************************************\n\n");
	printf("Please Enter In The Users' Full Name: ");
	scanf(" %[^\n]", &action.newuserfullname);
	printf("Please Enter In The Users' Username: ");
	scanf(" %[^\n]", &action.newusername);
	printf("Please Enter In The Users' Password: ");
	scanf(" %[^\n]", &action.newuserpassword);
	len = strlen(action.newuserpassword);
	/*ISALPHA is used to check if the first character of the string is a number
	or not*/
	test = isalpha(action.newuserpassword[0]);
	while (len > 8 || len < 8 || test == 0)
	{
		printf("\nPassword must be exactly 8 characters long and start with a letter\n");
		printf("Enter New Password: ");
		scanf("%s", &action.newuserpassword);
		fflush(stdin);
		len = strlen(action.newuserpassword);
		test = isalpha(action.newuserpassword[0]);
	}
	printf("\n\nYou are about to add the user with the following details: ");
	printf("\nFull Name: %s", action.newuserfullname);
	printf("\nUserID: %s", action.newusername);
	printf("\nPassword: %s", action.newuserpassword);
	printf("\n\nAre you sure?\n");
	printf("1. Yes\n");
	printf("2. No (Go Back To Menu)\n");
	printf("Please select an option (1 or 2): ");
	valid1 = scanf("%d", &option);
	fflush(stdin);
	while (option < 1 || option > 2 || valid1 != 1)
	{
		printf("Please select an option (1 or 2): ");
		scanf("%d", &option);
		fflush(stdin);
	}
	switch (option)
	{
	case 1:
		/*Copies the password string into a varible in the global structure
		which is then passed into the encrypt function and then copied back
		in the gobal varible and finally back to the original varible*/
		strcpy(action.encryptdata, action.newuserpassword);
		action = encryption(action);
		strcpy(action.newuserpassword, action.encryptdata);
		fprintf(fp2, "%s\n", action.newuserfullname);
		fprintf(fp2, "%s\n", action.newusername);
		fprintf(fp2, "%s\n", action.newuserpassword);
		fclose(fp2);
		printf("\n%s has now been added\n\n", &action.newuserfullname);
		printf("Would You Like To Add Another User?\n");
		printf("1. Yes\n");
		printf("2. No (Go Back To Menu)\n");
		printf("Please select an option (1 or 2): ");
		valid1 = scanf("%d", &option);
		fflush(stdin);
		while (option < 1 || option > 2 || valid1 != 1)
		{
			printf("Please select an option (1 or 2): ");
			scanf("%d", &option);
			fflush(stdin);
		}
		switch (option)
		{
		case 1:
			action = AddNewUser(action);
			break;
		case 2:
			action = GetNurseDetails(action);
			action = Menu(action);
			break;
		}
		break;
	case 2:
		action = Menu(action);
		break;
	}
	return action;
}
/*Change password function,this takes the password from the text file
stores it in an array then the required password is then automatically chosen
depending on who logs into the system and is then replaced with the newly entered password
and finally printed to the text file*/
struct data ChangePassword(struct data action)
{
	FILE *fp5;
	char password[255];
	char password1[255];
	char password2[255];
	int len;
	int lines;
	int i;
	int test;
	action = CountFileLines(action);
	lines = action.count_lines / 3;
	system("cls");
	printf("Action on Weight - Change Password | %s\n", action.loggedinuser);
	printf("**************************\n\n");
	printf("Username: %s\n", action.loggedinusername);
	printf("Enter LogIn Password: ");
	scanf("%s", &password);
	fflush(stdin);
	/*Compares the entered LogIn password agaisnt the one stored int he array
	to make sure they match*/
	if ((strcmp(action.loggedinpassword, password) == 0))
	{
		printf("Enter New Password: ");
		scanf("%s", &password1);
		fflush(stdin);
		len = strlen(password1);
		test = isalpha(password1[0]);
		/*Ensures that the newly entered password meets the requirements of
		the specification*/
		while (len > 8 || len < 8 || test == 0)
		{
			printf("Password must be exactly 8 characters long and start with a letter\n");
			printf("Enter New Password: ");
			scanf("%s", &password1);
			fflush(stdin);
			len = strlen(password1);
			test = isalpha(password1[0]);
		}
		printf("Verify New Password: ");
		scanf("%s", &password2);
		fflush(stdin);
		/*Ensures that the new password and the verify password field
		are they same*/
		if ((strcmp(password1, password2) == 0))
		{
			/*Password is encryped and then written to the text file*/
			strcpy(action.encryptdata, password1);
			action = encryption(action);
			strcpy(password1, action.encryptdata);
			strcpy(action.password[action.check], password1);
			fp5 = fopen("username.txt", "w");
			for (i = 0; i < lines; i++)
			{
				fprintf(fp5, "%s\n", action.nursefullname[i]);
				fprintf(fp5, "%s\n", action.username[i]);
				fprintf(fp5, "%s\n", action.password[i]);
			}
			fclose(fp5);
			printf("\nYou have sucessfully changed your password %s\n", action.loggedinuser);
			getch();
			action = GetNurseDetails(action);
			action = Menu(action);
		}
		else
		{
			printf("Passwords don't match");
			getch();
			action = ChangePassword(action);
		}
	}
	else
	{
		printf("Incorrect Password!");
		getch();
		action = ChangePassword(action);
	}
	return action;
}
/* GetNurseDetails function looks for the "username.txt" where all the
nurse log in details are saved, reads them and then stores them in arrays*/
struct data GetNurseDetails(struct data action)
{
	FILE *fp;
	int i;
	char *posi;
	char *posi2;
	char *posi3;
	int lines;
	action = CountFileLines(action);
	lines = action.count_lines / 3;
	fp = fopen("username.txt", "r");
	for (i = 0; i < lines; i++)
	{
		fgets(action.nursefullname[i], 20, fp);
		/*This searches the read string from the file for a new line character
		and replaces it with a null character since fgets adds a trailing new line character
		at the end of every string it reads and stores*/
		if ((posi3 = strchr(action.nursefullname[i], '\n')) != NULL)
		{
			*posi3 = '\0';
		};
		fgets(action.username[i], 20, fp);
		if ((posi = strchr(action.username[i], '\n')) != NULL)
		{
			*posi = '\0';
		};
		fgets(action.password[i], 20, fp);
		/*The password is decypted as soon as it's read before it is finally
		stored in an array*/
		strcpy(action.encryptdata, action.password[i]);
		action = decryption(action);
		strcpy(action.password[i], action.encryptdata);
		if ((posi2 = strchr(action.password[i], '\n')) != NULL)
		{
			*posi2 = '\0';
		};
	}
	fclose(fp);
	return action;
}
/*The NurseLogIn function uses the data that was read and stored
from the GetNurseDetails function and checks it agaist the inputted username
and password to see if there is a correct match, if so the user will then
be able to access the system*/
struct data NurseLogIn(struct data action)
{
	char c;
	int i;
	int pos = 0;
	int check = 0;
	char *posi;
	char *posi2;
	int lines;
	action = CountFileLines(action);
	lines = action.count_lines / 3;
	system("cls");
	printf("Action on Weight - Log In\n");
	printf("**************************\n\n");
	printf("Please Enter In Your Username: ");
	scanf(" %s", &action.nursename);
	printf("Please Enter In Your Password: ");
	/*Prints asterisk instead of the actual password in the
	password field*/
	do
	{
		c = getch();
		if ( isprint(c) )
		{
			action.buffer[pos++] = c;
			printf("%c", '*');
		}
		else if ( c == 8 && pos )
		{
			action.buffer[pos--] = '\0';
			printf("%s", "\b \b");
		}
	}
	while ( c != 13 );
	for (i = 0; i < lines; i++)
	{
		if ((strcmp(action.nursename, action.username[i]) == 0) && (strcmp(action.buffer, action.password[i]) == 0))
		{
			/*Copies the logged in users detail into a new global varible
			which is then later used in the Change Password function*/
			action.check = i;
			strcpy(action.loggedinuser, action.nursefullname[i]);
			strcpy(action.loggedinusername, action.username[i]);
			strcpy(action.loggedinpassword, action.buffer);
			for (i = 0; i < lines; i++)
			{
				/*Decrypted passwords are then re-encrypted and stored back in the arrays*/
				strcpy(action.encryptdata, action.password[i]);
				action = encryption(action);
				strcpy(action.password[i], action.encryptdata);
			}
			printf("\n\nWelcome %s\n", action.loggedinuser);
			printf("You Have Logged on Succesfully!\n\n");
			printf("Press Enter To Enter To Go To The Menu");
			getch();
			action = Menu(action);
		}
	}
	printf("\n\nIncorrect login!\n\n");
	printf("Press Enter To Try Again");
	getch();
	action = NurseLogIn(action);
	return action;
}
/*Enter Data function is used for entering the patient details*/
struct data EnterData(struct data action)
{
	FILE *fp1;
	int i;
	int valid1;
	char filename[255];
	char name[255];
	char birth[255];
	int option;
	int len;
	system("cls");
	printf("Action on Weight - Enter Patient Details | %s\n", action.loggedinuser);
	printf("***************************************************\n\n");
	printf("Enter The Patient's First Name: ");
	scanf(" %s", &action.firstname);
	fflush(stdin);
	/*Copies the chosen string into a varible in the global structure
	which is then passed into the encrypt function and then copied back
	in the gobal varible and finally back to the original varible*/
	strcpy(action.encryptdata, action.firstname);
	action = encryption(action);
	strcpy(action.firstname, action.encryptdata);
	printf("Enter The Patient's Surename: ");
	scanf(" %s", &action.surname);
	fflush(stdin);
	strcpy(action.encryptdata, action.surname);
	strcpy(name, action.surname);
	action = encryption(action);
	strcpy(action.surname, action.encryptdata);
	printf("Enter The Patient's Date of Birth (e.g. 010196): ");
	scanf(" %s", &action.dob);
	fflush(stdin);
	len = strlen(action.dob);
	/*Copies the chosen string into a varible in the global structure
	which is then passed into the CheckFileLines function which then returns
	a value that is used in for the WHILE loop validation*/
	strcpy(action.test, action.dob);
	action = CheckString(action);
	while (len < 6 || len > 6 || action.results != 0)
	{
		printf("\nError: You need to enter in 6 digits for the DoB (dd/mm/yy)");
		printf("\nEnter The Patient's Date of Birth (e.g. 010196): ");
		scanf(" %s", &action.dob);
		fflush(stdin);
		len = strlen(action.dob);
		strcpy(action.test, action.dob);
		action = CheckString(action);
	}
	strcpy(action.encryptdata, action.dob);
	strcpy(birth, action.dob);
	action = encryption(action);
	strcpy(action.dob, action.encryptdata);
	printf("Enter The Patient's Height (In Centimetres): ");
	scanf(" %[^\n]", &action.height);
	fflush(stdin);
	strcpy(action.test, action.height);
	action = CheckString(action);
	while (action.results != 0)
	{
		printf("\nError: Only integer values should be entered");
		printf("\nEnter The Patient's Height (In Centimetres): ");
		scanf(" %[^\n]", &action.height);
		fflush(stdin);
		strcpy(action.test, action.height);
		action = CheckString(action);
	}
	strcpy(action.encryptdata, action.height);
	action = encryption(action);
	strcpy(action.height, action.encryptdata);
	printf("Enter The Patient's Waist Measurement (In Centimetres): ");
	scanf(" %s", &action.waist);
	fflush(stdin);
	strcpy(action.test, action.waist);
	action = CheckString(action);
	while (action.results != 0)
	{
		printf("\nError: Only integer values should be entered");
		printf("\nEnter The Patient's Waist Measurement (In Centimetres): ");
		scanf(" %s", action.waist);
		fflush(stdin);
		strcpy(action.test, action.waist);
		action = CheckString(action);
	}
	strcpy(action.encryptdata, action.waist);
	action = encryption(action);
	strcpy(action.waist, action.encryptdata);
	printf("Enter The Patient's Weight (In Kilograms): ");
	scanf(" %s", &action.weight);
	fflush(stdin);
	strcpy(action.test, action.weight);
	action = CheckString(action);
	while (action.results != 0)
	{
		printf("\nError: Only integer values should be entered");
		printf("\nEnter The Patient's Weight (In Kilograms): ");
		scanf(" %s", action.weight);
		fflush(stdin);
		strcpy(action.test, action.weight);
		action = CheckString(action);
	}
	strcpy(action.encryptdata, action.weight);
	action = encryption(action);
	strcpy(action.weight, action.encryptdata);
	printf("Enter In Any Patient Comments: ");
	scanf(" %[^\n]", &action.comment);
	fflush(stdin);
	strcpy(action.encryptdata, action.comment);
	action = encryption(action);
	strcpy(action.comment, action.encryptdata);
	/*The patient file names are automatically generated by the program
	by adding their surname to their date of birth followed by the ".pat" extention*/
	strcpy(filename, name);
	strcat(filename, birth);
	strcat(filename, ".pat");
	fp1 = fopen(filename, "w");
	fprintf(fp1, "%s\n", action.firstname);
	fprintf(fp1, "%s\n", action.surname);
	fprintf(fp1, "%s\n", action.dob);
	fprintf(fp1, "%s\n", action.height);
	fprintf(fp1, "%s\n", action.waist);
	fprintf(fp1, "%s\n", action.weight);
	fprintf(fp1, "%s", action.comment);
	fclose(fp1);
	system("cls");
	printf("%s has now been created\n\n", filename);
	printf("Would You Like To Enter In Details For Another Patient?\n");
	printf("1. Yes\n");
	printf("2. No (Go Back To Menu)\n");
	printf("Please select an option (1 or 2): ");
	valid1 = scanf("%d", &option);
	fflush(stdin);
	while (option < 1 || option > 2 || valid1 != 1)
	{
		printf("Please select an option (1 or 2): ");
		scanf("%d", &option);
		fflush(stdin);
	}
	switch (option)
	{
	case 1:
		action = EnterData(action);
		break;
	case 2:
		action = Menu(action);
		break;
	}
	return action;
}
/*The CheckString function is used to check if a string contains
any integer or alpha characters which the function will then output a 1 or a 0
which is then used by the WHILE loops in the EnterData function for validation*/
struct data CheckString(struct data action)
{
	int checking;
	int counting = 0;
	int len;
	int i;
	action.results = 0;
	len = strlen(action.test);
	for (i = 0; i < len; i++)
	{
		/*Checks every character in a string to see if there are any alpha characters*/
		checking = isalpha(action.test[i]);
		if (checking != 0)
		{
			counting = counting + 1;
		}
	}
	if (counting == len)
	{
		action.results = 1;
	}
	else
	{
		action.results = 0;
	}
	return action;
}
/*The encryption function is used to encypt the "encryptdata" varible that is stored in
the global structure, whatever string is stored there when the encyption function is called
will then be encrypted and the encryped string then returned back to the same "encryptdata" varible in
the structure which can then be called into any function where necessary*/
struct data encryption(struct data action)
{
	int len = 0;
	int i = 0;
	int encrypting[255] = {0};
	char encrypted[255] = {0};
	len = strlen(action.encryptdata);
	/*The loops works by coverting the string character by character into an int type varible
	from a char type varible, this will then display the ASCII code value of each character
	which is then be increased by 4 this new ASCII value will then be converted back character by
	character into a char type varible which will then store the newly encrypted characters.
	Special charcters are left alone and so they are not encrypted*/
	for (i = 0 ; i < len ; i++)
	{
		encrypting[i] = action.encryptdata[i];
		/*IF statements are used for conditioning of the various ASCII values*/
		if ((encrypting[i] < 48) && (encrypting[i] > 31))
		{
			encrypted[i] = encrypting[i];
		}
		if ((encrypting[i] < 123) && (encrypting[i] > 96))
		{
			if (encrypting[i] < 119)
			{
				encrypted[i] = encrypting[i] + 4;
			}
			else
			{
				/*To get the encryption to loop round the A-Z selection
				when it reached a vaue that would take it out of the A-Z range such as w
				it would then subtract instead of adding 4 which would take it back round
				to the start of the alphabet again*/
				encrypted[i] = encrypting[i] - 22;
			}
		}
		else
		{
			if ((encrypting[i] < 58) && (encrypting[i] > 47))
			{
				if (encrypting[i] < 54)
				{
					encrypted[i] = encrypting[i] + 4;
				}
				else
				{
					/*To get the encryption to loop round the 0-9 selection
					when it reached a vaue that would take it out of the 0-9 range such as 6
					it would then subtract instead of adding 4 which would take it back round
					to the start of the number range again*/
					encrypted[i] = encrypting[i] - 6;
				}
			}
			else
			{
				if ((encrypting[i] < 91) && (encrypting[i] > 64))
				{
					if (encrypting[i] < 87)
					{
						encrypted[i] = encrypting[i] + 4;
					}
					else
					{
						encrypted[i] = encrypting[i] - 22;
					}
				}
			}
		}
	}
	strcpy(action.encryptdata, encrypted);
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

