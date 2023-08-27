#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "var.h"
#include <time.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

extern struct account v[10000];
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

		while (fgets(s, 400, f11))
		{
                s[strlen(s) - 1] = '\0';
				i = 1;
                //printf("%s\n", s);
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
					    {
                            strcpy(v[j].city, p_str);
                            //printf(RED "%s" RESET, v[j].city);
                        }
						if (i == 7)
								strcpy(v[j].adress, p_str);
						if (i == 8)
								v[j].balance = conversion(p_str);
						i++;
						p_str = strtok(NULL, ",");
				}
				j++;
				//printf("%s\n", s);

				free(p_str);
				//printf("%d,%d,%s,%s,%s,%s,%s,%d\n", v[i].id, v[i].password, v[i].first_name, v[i].last_name, v[i].phone_number, v[i].city, v[i].adress, v[i].balance);
		}
		fclose(f11);
		number = j;
}

void menu(void);
void	transact(void)
{
        //print();
        //extraction();
		int pass;
		int ok = 0;
		int ok1 = 0;
		int i = 0;
		int value;
		char try;
		char name[20];
		while (!ok1)
		{
				printf(YEL "\t\tPlease introduce the password of your account\n\t\t");
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
						printf("\t\tPlease introduce the first name of the account's owner\n\t\t" RESET);
						scanf("%s", name);
						if (strcmp(name, v[i].first_name) == 0)
								ok1 = 1;
				}
				else
				{
						printf(RED"\t\tThe introduced password is not valid\n"RESET);
				}
				if (ok1 == 0)
				{
						printf(RED"\t\tThe password is not connected to the first name of the account's owner\n"RESET);
						printf(YEL "\t\tWant to try again? (Y/N)\n\t\t" RESET);
						scanf(" %c", &try);
						if (try == 'N' || try == 'n')
								menu();
				}
		}
		if (ok1 == 1)
		{
				ok1 = 0;
				printf("\t\tAt the moment, you have %d dollars in your account\n", v[i].balance);
				printf("\t\tWhat do you want to do? Select by typing the number of each option\n");
				printf("\t\t1.Withdraw\t\t2.Deposit\n\t\t");
				ok = 0;
				scanf("%d", &ok);
				if (ok == 1)
				{
						while (!ok1)
						{
								printf("\t\tHow much money do you want to withdraw?\n\t\t");
								value = 0;
								scanf("%d", &value);
								if (value > v[i].balance)
										printf(RED"\t\tYou don't enough money in your account, please try again, if you want to cancel, just type 0\n"RESET);
								else
										ok1 = 1;
						}
						if (ok1 == 1)
						{
								v[i].balance = v[i].balance - value;
								printf(GRN"\t\tSucces! Now you have %d dollars in your account\n" RESET, v[i].balance);

						}

				}
				if (ok == 2)
				{
						printf("\t\tHow much money do you want to deposit? If you have changed your mind about depositting money, just type 0\n\t\t");
						scanf("%d", &value);
						v[i].balance += value;
						printf(GRN "\t\tSucces! Now you have %d dollars in your account\n" RESET, v[i].balance);
				}
		}
		print();
		ok1 = 0;
		printf(YEL "\t\tDo you want to return to the main menu?\n\t\t1.Yes\t\t2.No\n\t\t"RESET);
		scanf("%d", &ok1);
		if (ok1 == 1)
		{
				menu();
				return;
		}
        else
        transact();
}

void	view_account(void)
{
		printf("\e[1;1H\e[2J");
        int pass;
		int ok = 0;
		int ok1 = 0;
		int i = 0;
		char try;
		char name[20];
		while (!ok1)
		{
				printf("\t\tPlease introduce the password of your account\n\t\t");
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
						printf("\t\tPlease introduce the first name of the account's owner\n\t\t");
						scanf("%s", name);
						if (strcmp(name, v[i].first_name) == 0)
								ok1 = 1;
				}
				else
				{
						printf(RED"\t\tThe introduced password is not valid\n" RESET);
				}
				if (ok1 == 0)
				{
						printf(RED"\t\tThe password is not connected to the first name of the account's owner\n"RESET);
						printf(YEL "\t\tWant to try again? (Y/N)\n\t\t" RESET);
						scanf(" %c", &try);
						if (try == 'N' || try == 'n')
								menu();
				}
		}
		if (ok1 == 1)
		{
				printf(YEL "\t\tHere is the information of the account:\n"RESET);
				printf("\t\tFirst Name:	%s\n", v[i].first_name);
				printf("\t\tLast Name:	%s\n", v[i].last_name);
				printf("\t\tPhone Number:	%s\n", v[i].phone_number);
				printf("\t\tCity:		%s\n", v[i].city);
				printf("\t\tAdress:		%s\n", v[i].adress);
                if (v[i].balance <= 0)
				printf(RED "\t\tBallance:	%d\n" RESET, v[i].balance);
                else
                printf(GRN "\t\tBallance:   %d\n" RESET, v[i].balance);

		}
		ok1 = 0;
		printf(YEL "\t\tDo you want to return to the main menu?\n\t\t1.Yes\t\t2.No\n\t\t" RESET);
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
				printf("\t\tTo view the list of accounts, you must confirm that you are an admin. Introduce the admin password\n\t\t");
				scanf("%s", str);
				if (strcmp(str, "8312440") == 0)
				{
						printf(YEL "\t\tHere are the accounts:\n"RESET);
						for (i = 1; i <= 20; i++)
								printf("\e[1;1H\e[2J"); // cleans the window

						ok = 1;
						for (i = 0; i < number; i++)
						{
								printf("\t\tThe information of account nr %d:\n", i + 1);
								printf("\t\tFirst Name:	%s\n", v[i].first_name);
								printf("\t\tLast Name:	%s\n", v[i].last_name);
								printf("\t\tPhone Number:	%s\n", v[i].phone_number);
								printf("\t\tCity:		%s\n", v[i].city);
								printf("\t\tAdress:		%s\n", v[i].adress);
								printf("\t\tBallance:	%d\n", v[i].balance);
								printf("\t\tPassword:	%d\n\n\n", v[i].password);
						}
				}
				if (ok == 0)
				{
						printf(RED"\t\tThe password is incorrect, want to try again?   (Y/N)\n\t\t"RESET);
						scanf(" %c", &opt);
						if (opt == 'n' || opt == 'N')
						{
								menu();
								break;
						}
				}
		}
		ok1 = 0;
		printf(YEL "\t\tDo you want to return to the main menu?\n\t\t1.Yes\t\t2.No\n\t\t"RESET);
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
				printf("\t\tPlease introduce the password of your account\n\t\t");
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
						printf("\t\tPlease introduce the first name of the account's owner\n\t\t");
						scanf("%s", name);
						if (strcmp(name, v[i].first_name) == 0)
								ok1 = 1;
				}
				else
				{
						printf(RED "\t\tThe introduced password is not valid\n" RESET);
				}
				if (ok1 == 0)
				{
						printf(RED "\t\tThe password is not connected to the first name of the account's owner\n" RESET);
						printf(YEL "\t\tWant to try again? (Y/N)\n\t\t" RESET);
						scanf(" %c", &try);
						if (try == 'N' || try == 'n')
								menu();
				}
		}
		if (ok1 == 1)
		{
				if (v[i].balance)
				{
						printf(MAG "\t\tYou still have money in your account, make sure to withdraw all the money first\n" RESET);
						printf(YEL "\t\tDo you want to return to the main menu?\n\t\t1.Yes\t\t2.No\n\t\t" RESET);
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
						printf(RED "\t\tAre you sure you want to delete your account? Everything will be erased!  (Y/N)\n\t\t" RESET);
						scanf(" %c", &confirmation);
						if (confirmation == 'Y' || confirmation == 'y')
						{
								printf("\t\tDeleting your account, please wait\n");
								v[i].id = -1;
								printf(BLU "\t\tYour account has successfully been deleted\n" RESET);
								print();
								try = '\0';
								printf(YEL "\t\tDo you want to return to the main menu? (Y/N)\n\t\t" RESET);
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
		printf("\t\tIntroduce the information you want to replace\n\t\t");
        getchar();
        fgets(info, 200, stdin);
        info[strlen(info) - 1] = '\0';
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
				printf("\t\tPlease introduce the password of your account\n");
                printf("\t\t");
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
						printf("\t\tPlease introduce the first name of the account's owner\n");
                        printf("\t\t");
						scanf("%s", name);
						if (strcmp(name, v[i].first_name) == 0)
								ok1 = 1;
				}
				else
				{
						printf(RED "\t\tThe introduced password is not valid\n" RESET);
				}
				if (ok1 == 0)
				{
						printf(RED"\t\tThe password is not connected to the first name of the account's owner\n" RESET);
						printf(YEL "\t\tWant to try again? (Y/N)\n\t\t" RESET);
						scanf(" %c", &try);
						if (try == 'N' || try == 'n')
								menu();
				}
		}
		if (ok1 == 1)
		{
				while (finish == 1)
				{
						printf("\t\tWhat information do you want to change?\n");
						printf("\t\t1.First_name\t2.Last_name\t3.Phone_number\t4.City\n");
						printf("\t\t5.Adress\n\t\t");
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
						printf(YEL "\t\tDo you want to change anything else?\n\t\t1.Yes\t\t2.No\n" RESET);
						printf("\t\t");
                        scanf("%d", &finish);
						if (finish == 2)
						{
								print();
								menu();
								return;
						}
				}
				ok1 = 0;
				printf(YEL "\t\tDo you want to return to the main menu?\n\t\t1.Yes\t\t2.No\n\t\t" RESET);
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
		printf("\t\tIntroduce your first name:\n\t\t");
		scanf("%s", v[number].first_name);
		printf("\t\tIntroduce your last name:\n\t\t");	
		scanf("%s", v[number].last_name);
		printf("\t\tIntroduce your phone number:\n\t\t");
		scanf("%s",  v[number].phone_number);
		printf("\t\tIntroduce the name of your city\n\t\t");
        getchar();
		scanf(" %[^\n]", v[number].city);
        //v[number].city[strlen(v[number].city) - 1] = '\0';
		printf("\t\tIntroduce your adress\n\t\t");
		scanf(" %[^\n]", v[number].adress);
		printf("\t\tYour bank account has successfully been created\n");
		printf(MAG "\t\tMake sure to note your password  somewhere, you will need it\n" RESET);
		printf("\t\tYour password is: %d\n", v[number].password);
		printf(YEL "\t\tDo you want to return to the menu?\n");
		printf("\t\t1.Yes\t\t2.No\n\t\t" RESET);
		scanf("%d", &ok);
		print();	// save the updated data in the file
		number++;
		if (ok == 1)
				menu();
        else
                create();
}

void	menu(void)		// function that displays the main menu and calls a certain function when an option is selected
{
		short int option_selected;
		int i;

		for (i = 1; i <= 20; i++)
				printf("\e[1;1H\e[2J");// cleans the window, makes everything blank	
        extraction();
		printf(GRN "|\\---/|										|\\---/| \n");
		printf("| o_o |				WELCOME TO THOMAS BANK				| o_o |\n");
		printf(" \\_^_/									 	 \\_^_/ \n" RESET);
		printf(YEL "				<<<<MAIN MENU>>>>\n\n" RESET);
		printf(BLU "\t\t1.Create a new account\n");
		printf("\t\t2.Update information of existing account\n");
		printf("\t\t3.Make transactions\n");
		printf("\t\t4.Check the details of existing account\n");
		printf("\t\t5.Remove an existing account\n");
		printf("\t\t6.View customers list\n");
		printf("\t\t7.Exit\n\n");
		printf(YEL "\t\tEnter your choice: " RESET);
		scanf("%hu", &option_selected);
		while (option_selected > 7)
		{
				printf(RED "The option with number %d does not exist! Please try again!\n" RESET, option_selected);
				printf(YEL "Enter your choice: " RESET);
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
				printf(GRN "\t\tHave a good day!\n" RESET);
				exit(WEXITED);
		}
}

int     main()
{
    menu();
    //extraction();
}
