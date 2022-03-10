#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "var.h"
#include <time.h>

extern struct account v[100];
extern int number;
FILE *ptr;
void	delete_commas(int i)
{
		size_t len;
		len = strlen(v[i].first_name);
		while (v[i].first_name[len- 1] == ',')
		{
				v[i].first_name[len-- - 1] = '\0';
				len--;
		}
		len = strlen(v[i].last_name);
		while (v[i].last_name[len - 1] == ',')
		{
				v[i].last_name[len - 1] = '\0';
				len--;
		}
		len = strlen(v[i].city);
		while (v[i].city[len - 1] == ',')
		{
				v[i].city[len - 1] = '\0';
				len--;
		}
		len = strlen(v[i].adress);
		while (v[i].adress[len - 1] == ',')
		{
				v[i].adress[len - 1] = '\0';
				len--;
		}
}

void	print(void)
{
		FILE *f11;
		int i = 0;
		f11 = fopen("data.csv", "w");
		for (i = 0; i <= number; i++)
		{
				delete_commas(i);
				if (v[i].id != -1)
				{
						v[i].id = i + 1;
						if (v[i].password)
								fprintf(f11, "%d,%d,%s,%s,%s,%s,%s,%d\n", v[i].id, v[i].password, v[i].first_name, v[i].last_name, v[i].phone_number, v[i].city, v[i].adress, v[i].balance); 
				}
		}
		fclose(f11);
}

int		conversion(char *str)
{
		size_t i;
		int nr = 0;

		for (i = 0; i < strlen(str); i++)
				nr = nr * 10 + (int)(str[i] - 48);
		return (nr);
}

void	extraction(void) // get the data from the file
{
		FILE *f11 = fopen("data.csv", "r");
		char *p_str; // pointer to string
		char s[400]; // the string itself
		size_t i = 1;
		int j = 0;
		int a = 0;

		a = fscanf(f11, "%s", s);
		//printf("%s\n", s);
		while (a == 1)
		{
				i = 1;
				p_str = strtok(s, ",");
				while (p_str)
				{
						if (i == 1)
								v[j].id = conversion(p_str);
						if (i == 2)
								v[j].password = conversion(p_str);
						if (i == 3)
								strcpy(v[j].first_name, p_str);
						if (i == 4)
								strcpy(v[j].last_name, p_str);
						if (i == 5)
								strcpy(v[j].phone_number, p_str);
						if (i == 6)
								strcpy(v[j].city, p_str);
						if (i == 7)
								strcpy(v[j].adress, p_str);
						if (i == 8)
								v[j].balance = conversion(p_str);
						i++;
						p_str = strtok(NULL, ",");
				}
				j++;
				a = fscanf(f11, "%s", s);  	
				//printf("%s\n", s);

				free(p_str);
				//		printf("%d,%d,%s,%s,%s,%s,%s,%d\n", v[i].id, v[i].password, v[i].first_name, v[i].last_name, v[i].phone_number, v[i].city, v[i].adress, v[i].ballance);
		}
		fclose(f11);
		number = j;
}

void menu(void);
void	transact(void)
{
		int pass;
		int ok = 0;
		int ok1 = 0;
		int i = 0;
		int value;
		char try;
		char name[20];
		while (!ok1)
		{
				printf("		Please introduce the password of your account\n");
				scanf("%d", &pass);
				for (i = 0; i <= number; i++)
				{
						if (v[i].password == pass)
						{
								ok = 1;
								break;
						}
				}
				if (ok == 1)
				{
						printf("		Please introduce the first name of the account's owner\n");
						scanf("%s", name);
						if (strcmp(name, v[i].first_name) == 0)
								ok1 = 1;
				}
				else
				{
						printf("		The introduced password is not valid\n");
				}
				if (ok1 == 0)
				{
						printf("		The password is not connected to the first name of the account's owner\n");
						printf("		Want to try again? (Y/N)\n");
						scanf(" %c", &try);
						if (try == 'N' || try == 'n')
								menu();
				}
		}
		if (ok1 == 1)
		{
				ok1 = 0;
				printf("		At the moment, you have %d dollars in your account\n", v[i].balance);
				printf("		What do you want to do? Select by typing the number of each option\n");
				printf("		1.Withdraw		2.Deposit\n");
				ok = 0;
				scanf("%d", &ok);
				if (ok == 1)
				{
						while (!ok1)
						{
								printf("		How much money do you want to withdraw?\n");
								value = 0;
								scanf("%d", &value);
								if (value > v[i].balance)
										printf("		You don't enough money in your account, please try again, if you want to cancel, just type 0\n");
								else
										ok1 = 1;
						}
						if (ok1 == 1)
						{
								v[i].balance = v[i].balance - value;
								printf("		Succes! Now you have %d dollars in your account\n", v[i].balance);

						}

				}
				if (ok == 2)
				{
						printf("		How much money do you want to deposit? If you have changed your mind about depositting money, just type 0\n");
						scanf("%d", &value);
						v[i].balance += value;
						printf("		Succes! Now you have %d dollars in your account\n", v[i].balance);
				}
		}
		print();
		ok1 = 0;
		printf("		Do you want to return to the main menu?\n		1.Yes			2.No\n");
		scanf("%d", &ok1);
		if (ok1 == 1)
		{
				menu();
				return;
		}


}

void	view_account(void)
{
		int pass;
		int ok = 0;
		int ok1 = 0;
		int i = 0;
		char try;
		char name[20];
		while (!ok1)
		{
				printf("		Please introduce the password of your account\n");
				scanf("%d", &pass);
				for (i = 0; i <= number; i++)
				{
						if (v[i].password == pass)
						{
								ok = 1;
								break;
						}
				}
				if (ok == 1)
				{
						printf("		Please introduce the first name of the account's owner\n");
						scanf("%s", name);
						if (strcmp(name, v[i].first_name) == 0)
								ok1 = 1;
				}
				else
				{
						printf("		The introduced password is not valid\n");
				}
				if (ok1 == 0)
				{
						printf("		The password is not connected to the first name of the account's owner\n");
						printf("		Want to try again? (Y/N)\n");
						scanf(" %c", &try);
						if (try == 'N' || try == 'n')
								menu();
				}
		}
		if (ok1 == 1)
		{
				printf("		Here is the information of the account:\n");
				printf("First Name:	%s\n", v[i].first_name);
				printf("Last Name:	%s\n", v[i].last_name);
				printf("Phone Number:	%s\n", v[i].phone_number);
				printf("City:		%s\n", v[i].city);
				printf("Adress:		%s\n", v[i].adress);
				printf("Ballance:	%d\n", v[i].balance);
		}
		ok1 = 0;
		printf("		Do you want to return to the main menu?\n		1.Yes			2.No\n");
		scanf("%d", &ok1);
		if (ok1 == 1)
		{
				menu();
				return;
		}
}

void	view_list(void)
{
		char str[256];
		int ok = 0;
		int ok1;
		char opt;
		int i;
		while (!ok)
		{
				printf("		To view the list of accounts, you must confirm that you are an admin. Introduce the admin password\n");
				scanf("%s", str);
				if (strcmp(str, "jackharkness") == 0)
				{
						printf("		Here are the accounts:\n");
						for (i = 1; i <= 20; i++)
								printf("\e[1;1H\e[2J"); // cleans the window

						ok = 1;
						for (i = 0; i < number; i++)
						{
								printf("The information of account nr %d:\n", i + 1);
								printf("First Name:	%s\n", v[i].first_name);
								printf("Last Name:	%s\n", v[i].last_name);
								printf("Phone Number:	%s\n", v[i].phone_number);
								printf("City:		%s\n", v[i].city);
								printf("Adress:		%s\n", v[i].adress);
								printf("Ballance:	%d\n", v[i].balance);
								printf("Password:	%d\n\n\n", v[i].password);
						}
				}
				if (ok == 0)
				{
						printf("		The password is incorrect, want to try again?   (Y/N)\n");
						scanf(" %c", &opt);
						if (opt == 'n' || opt == 'N')
						{
								menu();
								break;
						}
				}
		}
		ok1 = 0;
		printf("		Do you want to return to the main menu?\n		1.Yes			2.No\n");
		scanf("%d", &ok1);
		if (ok1 == 1)
		{
				menu();
				return;
		}

}

void	erase(void)
{
		int pass;
		int ok = 0;
		int ok1 = 0;
		int i = 0;
		char try;
		char name[20];
		char confirmation;
		while (!ok1)
		{
				printf("		Please introduce the password of your account\n");
				scanf("%d", &pass);
				for (i = 0; i <= number; i++)
				{
						if (v[i].password == pass)
						{
								ok = 1;
								break;
						}
				}
				if (ok == 1)
				{
						printf("		Please introduce the first name of the account's owner\n");
						scanf("%s", name);
						if (strcmp(name, v[i].first_name) == 0)
								ok1 = 1;
				}
				else
				{
						printf("		The introduced password is not valid\n");
				}
				if (ok1 == 0)
				{
						printf("		The password is not connected to the first name of the account's owner\n");
						printf("		Want to try again? (Y/N)\n");
						scanf(" %c", &try);
						if (try == 'N' || try == 'n')
								menu();
				}
		}
		if (ok1 == 1)
		{
				if (v[i].balance)
				{
						printf("		You still have money in your account, make sure to withdraw all the money you first\n");
						printf("		Do you want to return to the main menu?\n		1.Yes			2.No\n");
						scanf("%d", &ok1);
						if (ok1 == 1)
						{
								menu();
								return;
						}
						return;
				}
				else
				{		
						printf("		Are you sure you want to delete your account? Everything will be erased!  (Y/N)\n");
						scanf(" %c", &confirmation);
						if (confirmation == 'Y' || confirmation == 'y')
						{
								printf("		Deleting your account, please wait\n");
								v[i].id = -1;
								printf("		Your account has successfully been deleted\n");
								print();
								try = '\0';
								printf("		Do you want to return to the main menu? (Y/N)\n");
								scanf(" %c", &try);
								if (try == 'Y' || try == 'y')
								{
										menu();
										return;
								}
						}
				}
		}
}

void	up(char *str)
{
		char info[200];
		printf("		Introduce the information you want to replace\n");
		scanf("%s", info);
		strcpy(str, info);
}

void	update(void)
{
		int pass;
		int ok = 0;
		int ok1 = 0;
		int i = 0;
		char try;
		int finish = 1;
		char name[20];
		int option = 0;
		while (!ok1)
		{
				printf("		Please introduce the password of your account\n");
				scanf("%d", &pass);
				for (i = 0; i <= number; i++)
				{
						if (v[i].password == pass)
						{
								ok = 1;
								break;
						}
				}
				if (ok == 1)
				{
						printf("		Please introduce the first name of the account's owner\n");
						scanf("%s", name);
						if (strcmp(name, v[i].first_name) == 0)
								ok1 = 1;
				}
				else
				{
						printf("		The introduced password is not valid\n");
				}
				if (ok1 == 0)
				{
						printf("		The password is not connected to the first name of the account's owner\n");
						printf("		Want to try again? (Y/N)\n");
						scanf(" %c", &try);
						if (try == 'N' || try == 'n')
								menu();
				}
		}
		if (ok1 == 1)
		{
				while (finish == 1)
				{
						printf("		What information do you want to change?\n");
						printf("		1.First_name	2.Last_name		3.Phone_number		4.City\n");
						printf("		5.Adress\n");
						scanf("%d", &option);
						if (option == 1)
								up(v[i].first_name);
						if (option == 2)
								up(v[i].last_name);
						if (option == 3)
								up(v[i].phone_number);
						if (option == 4)
								up(v[i].city);
						if (option == 5)
								up(v[i].adress);
						printf("		Do you want to change anything else?\n		1.Yes		2.No\n");
						scanf("%d", &finish);
						if (finish == 2)
						{
								print();
								menu();
								return;
						}
				}
				ok1 = 0;
				printf("		Do you want to return to the main menu?\n		1.Yes			2.No\n");
				scanf("%d", &ok1);
				if (ok1 == 1)
				{
						menu();
						return;
				}
		}


}

void	create(void)				// function to create a new  account
{
		int i;
		int ok = 0;	// represents the answer to question from line 129
		for (i = 1; i <= 20; i++)
				printf("\e[1;1H\e[2J"); // cleans the window
		v[number].id = number;
		v[number].balance = 0;
		srand (time(NULL));
		v[number].password = rand();
		printf("		Introduce your first name:\n		");
		scanf("%s", v[number].first_name);
		printf("		Introduce your last name:\n		");	
		scanf("%s", v[number].last_name);
		printf("		Introduce your phone number:\n		");
		scanf("%s",  v[number].phone_number);
		printf("		Introduce the name of your city\n		");
		scanf("%s", v[number].city);
		printf("		Introduce your adress\n		");
		scanf(" %[^\n]", v[number].adress);
		printf("		Your bank account has successfully been created\n");
		printf("		Make sure to note your password  somewhere, you will need it\n");
		printf("		Your password is: %d\n", v[number].password);
		printf("		Do you want to return to the menu?\n");
		printf("		1.Yes	2.No\n		");
		scanf("%d", &ok);
		print();	// save the updated data in the file
		number++;
		if (ok == 1)
				menu();
}

void	menu(void)		// function that displays the main menu and calls a certain function when an option is selected
{
		short int option_selected;
		int i;

		for (i = 1; i <= 20; i++)
				printf("\e[1;1H\e[2J");// cleans the window, makes everything blank	
		extraction(); // getting the data from the file
		printf("|\\---/|										|\\---/| \n");
		printf("| o_o |				WELCOME TO THOMAS BANK				| o_o |\n");
		printf(" \\_^_/									 	 \\_^_/ \n");
		printf("				<<<MAIN MENU>>>>\n");
		printf("		1.Create a new account\n");
		printf("		2.Update information of existing account\n");
		printf("		3.Make transactions\n");
		printf("		4.Check the details of existing account\n");
		printf("		5.Remove an existing account\n");
		printf("		6.View customers list\n");
		printf("		7.Exit\n\n");
		printf("		Enter your choice: ");
		scanf("%hu", &option_selected);
		while (option_selected > 7)
		{
				printf("The option with number %d does not exist! Please try again!\n", option_selected);
				printf("Enter your choice: ");
				scanf("%hu", &option_selected);
		}
		if (option_selected == 1)
				create();
		if (option_selected == 2)
				update();
		if (option_selected == 3)
				transact();
		if (option_selected == 4)
				view_account();
		if (option_selected == 5)
				erase();
		if (option_selected == 6)
				view_list();
		if (option_selected == 7)
		{
				printf("		Have a good day!\n");
				exit(WEXITED);
		}
}
