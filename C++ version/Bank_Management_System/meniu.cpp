#include <iostream>
#include <windows.h>
#include <time.h>
#include <vector>
#include "data_management.h"
using namespace std;

void menu();
/*Creare cautare stergere editare view all(cu parola)*/
Banca b;
int nr_argumente = 1;
char **argumente;
vector<ContBancar *> v;
void creare()
{ // Nume Prenume Adresa Telefon

    int id = rand();
    int choice;
    char nume[50], prenume[75], adresa[100], telefon[15];
    cout << "                <<<<CREATE A NEW ACCOUNT>>>>\n\n";

    if (nr_argumente != 1)
    {
        strcpy(prenume, argumente[2]);
        strcpy(nume, argumente[3]);
        strcpy(adresa, argumente[4]);
        strcpy(telefon, argumente[5]);
    }
    else
    {
        cout << "\t\tFirst Name:";
        cin.ignore();
        cin.getline(prenume, 75);

        cout << "\n\t\tLast name:";
        cin >> nume;

        cout << "\n\t\tAdress:";
        cin.ignore();
        cin.getline(adresa, 100);

        cout << "\n\t\tPhone number:";
        cin >> telefon;
    }
    ContBancar *x = new ContBancar(nume, prenume, adresa, telefon, id);

    /*Aici introducem in lista*/

    v.push_back(x);
    cout << "\n\t\tAccount with id '" << id << "' was succesfully added\n\n";
    if (nr_argumente == 1)
    {
        cout << "\t\t1.Menu\n";
        cout << "\t\t2.Create another account\n";
        cout << "\t\tEnter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            system("cls");
            menu();
            break;
        case 2:
            system("cls");
            creare();
            break;
        default:
            system("cls");
            menu();
            break;
        }
    }
}

void update_account()
{
    int choice, id;
    int temp_choice;
    char s[100];
    cout << "                <<<<UPDATE INFORMATION OF EXISTING ACCOUNT>>>>\n\n";
    if (nr_argumente > 1)
    {
        id = strToNr(argumente[2]);
        temp_choice = strToNr(argumente[3]);
        strcpy(s, argumente[4]);
        bool ok = false;
        int i;
        for (i = 0; i < v.size(); i++)
        {
            if (*v[i] == id)
            {
                ok = !ok;
                break;
            }
        }
        ContBancar *c;
        if (ok)
        {
            c = v[i];
            switch (temp_choice)
            {
            case 1:
                c->setPrenume(s);
                break;
            case 2:
                c->setNume(s);
                break;
            case 3:
                c->setAdresa(s);
                break;
            case 4:
                c->setTelefon(s);
                break;
            }
            cout << "\n\n\t\tField succesfully modified.\n";

            return;
        }
    }
    cout << "\t\tEnter the ID:";
    cin >> id;

    bool ok = false;
    int i;
    for (i = 0; i < v.size(); i++)
    {
        if (*v[i] == id)
        {
            ok = !ok;
            break;
        }
    }

    if (ok)
    {
        ContBancar *temp = v[i];
        int temp_choice;
        cout << "\n\t\tAccount found. What field would you like to modify?\n";
        cout << "\t\t1.First name\n";
        cout << "\t\t2.Last name\n";
        cout << "\t\t3.Adress\n";
        cout << "\t\t4.Phone number\n";
        cout << "\t\tEnter your choice: ";
        cin >> temp_choice;
        switch (temp_choice)
        {
        case 1:
            char first_name[50];
            cout << "\n\t\tFirst name: ";
            cin.ignore();
            cin.getline(first_name, 75);
            /*Aici updatam*/
            temp->setPrenume(first_name);
            cout << "\n\t\tLast name updated to '" << first_name << "'.";
            break;
        case 2:
            char last_name[75];
            cout << "\n\t\tLast name: ";
            cin >> last_name;
            temp->setNume(last_name);
            /*Aici updatam*/
            cout << "\n\t\tFirst name updated to '" << last_name << "'.";
            break;
        case 3:
            char adress[100];
            cout << "\n\t\tAdress: ";
            cin.ignore();
            cin.getline(adress, 100);
            temp->setAdresa(adress);
            /*Aici updatam*/
            cout << "\n\t\tAdress updated to '" << adress << "'.";
            break;
        case 5:
            char phone_number[15];
            cout << "\n\t\tAdress: ";
            cin.ignore();
            cin.getline(phone_number, 15);
            temp->setTelefon(phone_number);
            /*Aici updatam*/
            cout << "\n\t\tPhone number updated to '" << phone_number << "'.";
            break;
        default:
            system("cls");
            menu();
            break;
        }

        cout << "\n\n\t\tField succesfully modified.\n";
        cout << "\t\t1.Menu\n";
        cout << "\t\t2.Modify another account\n\n";
        cout << "\t\tEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system("cls");
            menu();
            break;
        case 2:
            system("cls");
            update_account();
            break;
        default:
            system("cls");
            menu();
            break;
        }
    }
    else
    {
        int temp_choice;
        cout << "\n\t\tAccount not found. \n";
        cout << "\t\t1.Menu\n";
        cout << "\t\t2.Try again\n";
        cout << "\t\tEnter your choice: ";
        cin >> temp_choice;
        switch (temp_choice)
        {
        case 1:
            system("cls");
            menu();
            break;
        case 2:
            system("cls");
            update_account();
            break;
        default:
            system("cls");
            menu();
            break;
        }
    }
}

void transactions()
{
    int sum;
    int choice, choice_temp, id;
    cout << "                <<<<TRANSACTIONS>>>>\n\n";
    if (nr_argumente > 1)
    {
        id = strToNr(argumente[2]);
        choice_temp = strToNr(argumente[3]);
        sum = strToNr(argumente[4]);
        bool ok = false;
        int i;
        for (i = 0; i < v.size(); i++)
        {
            if (*v[i] == id)
            {
                ok = !ok;
                break;
            }
        }
        if (ok)
        {
            ContBancar *temp = v[i];
            if (choice_temp == 1)
            {
                temp->setBalanta(temp->getBalanta() + sum);
                cout << "Transaction complete\n";
            }
            else if (choice_temp == 2)
            {
                if (temp->getBalanta() >= sum)
                {
                    temp->setBalanta(temp->getBalanta() - sum);
                    cout << "\n\n\t\tTransaction complete\n";
                }
                else
                    cout << "\n\n\t\tSum exceeds account balance\n";
            }

            return;
        }
    }
    cout << "\t\tEnter the ID:";
    cin >> id;

    bool ok = false;
    int i;
    for (i = 0; i < v.size(); i++)
    {
        if (*v[i] == id)
        {
            ok = !ok;
            break;
        }
    }

    if (ok)
    {
        ContBancar *temp = v[i];
        cout << "\t\tChoose the type of transaction you would like to make:\n";
        cout << "\t\t1.Deposit\n";
        cout << "\t\t2.Withdraw\n\n";
        cout << "\t\tEnter your choice: ";
        cin >> choice_temp;
        switch (choice_temp)
        {
        case 1:

            cout << "\n\n\t\tSpecify sum: ";
            cin >> sum;
            /* Aici introducem suma*/
            temp->setBalanta(temp->getBalanta() + sum);

            cout << "\n\n\t\tTransaction complete\n";
            cout << "\n\n\t\t1.Menu\n";
            cout << "\t\t2.Do another transaction\n";
            cout << "\t\tEnter your choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                system("cls");
                menu();
                break;
            case 2:
                system("cls");
                transactions();
                break;
            default:
                system("cls");
                menu();
                break;
            }
            break;
        case 2:
            cout << "\n\n\t\tSpecify sum: ";
            cin >> sum;
            /*Aici verificam daca suma e mai mare decat ce avem in cont*/
            /*Aici updatam suma din cont*/
            if (temp->getBalanta() >= sum)
            {
                temp->setBalanta(temp->getBalanta() - sum);
                cout << "\n\n\t\tTransaction complete\n";

                cout << "\n\n\t\t1.Menu\n";
                cout << "\t\t2.Do another transaction\n";
                cout << "\t\tEnter your choice: ";
                cin >> choice;
                switch (choice)
                {
                case 1:
                    system("cls");
                    menu();
                    break;
                case 2:
                    system("cls");
                    transactions();
                    break;
                default:
                    system("cls");
                    menu();
                    break;
                }
            }
            else
            {
                cout << "\n\n\t\tSum exceeds account balance\n";
                cout << "\n\n\t\t1.Menu\n";
                cout << "\t\t2.Try again\n";
                cout << "\t\tEnter your choice: ";
                cin >> choice;
                switch (choice)
                {
                case 1:
                    system("cls");
                    menu();
                    break;
                case 2:
                    system("cls");
                    transactions();
                    break;
                default:
                    system("cls");
                    menu();
                    break;
                }
            }
            break;
        default:
            system("cls");
            menu();
            break;
        }
    }
    else
    {
        int temp_choice;
        cout << "\n\t\tAccount not found. \n";
        cout << "\t\t1.Menu\n";
        cout << "\t\t2.Try again\n";
        cout << "\t\tEnter your choice: ";
        cin >> temp_choice;
        switch (temp_choice)
        {
        case 1:
            system("cls");
            menu();
            break;
        case 2:
            system("cls");
            transactions();
            break;
        default:
            system("cls");
            menu();
            break;
        }
    }
}
void view_customer()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    int choice, id;
    cout << "                <<<<CHECK THE DETAILS OF EXISTING ACCOUNT>>>>\n\n";
    bool ok = false;
    int i;

    if (nr_argumente == 1)
    {
        cout << "\t\tEnter the ID:";
        cin >> id;
        for (i = 0; i < v.size(); i++)
        {
            if (*v[i] == id)
            {
                ok = !ok;
                break;
            }
        }
    }
    if (nr_argumente > 1)
    {
        id = strToNr(argumente[2]);
        for (i = 0; i < v.size(); i++)
        {
            if (*v[i] == id)
            {
                ok = !ok;
                break;
            }
        }
        if (ok)
            v[i]->afisare();
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
        return;
    }

    if (ok)
    {
        /*Afisare aici*/
        cout << "\n\n";
        v[i]->afisare();
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
        cout << "\n\n\t\t1.Menu\n";
        cout << "\t\t2.Check another account\n";
        cout << "\t\tEnter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            system("cls");
            menu();
            break;
        case 2:
            system("cls");
            view_customer();
            break;
        default:
            system("cls");
            menu();
            break;
        }
    }
    else
    {
        int temp_choice;
        cout << "\n\t\tAccount not found. \n";
        cout << "\t\t1.Menu\n";
        cout << "\t\t2.Try again\n";
        cout << "\t\tEnter your choice: ";
        cin >> temp_choice;
        switch (temp_choice)
        {
        case 1:
            system("cls");
            menu();
            break;
        case 2:
            system("cls");
            view_customer();
            break;
        default:
            system("cls");
            menu();
            break;
        }
    }
}
void stergere_client()
{
    int choice, id;
    cout << "                <<<<REMOVE AN EXISTING ACCOUNT>>>>\n\n";
    if (nr_argumente > 1)
    {
        bool ok = false;
        int i;
        id = strToNr(argumente[2]);
        for (i = 0; i < v.size(); i++)
        {
            if (*v[i] == id)
            {
                ok = true;
                break;
            }
        }
        if (ok == true)
        {

            v.erase(v.begin() + i);

            cout << "\n\t\tAccount with id '" << id << "' was succesfully deleted\n\n";
            return;
        }
        else
        {
            cout << "\n\t\tID ul nu corespunde unui cont";
        }
    }
    cout << "\t\tEnter the ID:";
    cin >> id;
    bool ok = false;
    int i;
    for (i = 0; i < v.size(); i++)
    {
        if (*v[i] == id)
        {
            ok = true;
            break;
        }
    }
    if (ok == true)
    {

        v.erase(v.begin() + i);

        cout << "\n\t\tAccount with id '" << id << "' was succesfully deleted\n\n";
        cout << "\t\t1.Menu\n";
        cout << "\t\t2.Delete another account\n";
        cout << "\t\tEnter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            system("cls");
            menu();
            break;
        case 2:
            system("cls");
            stergere_client();
            break;
        default:
            system("cls");
            menu();
            break;
        }
    }
    else
    {
        int temp_choice;
        cout << "\n\t\tAccount not found. \n";
        cout << "\t\t1.Menu\n";
        cout << "\t\t2.Try again\n";
        cout << "\t\tEnter your choice: ";
        cin >> temp_choice;
        switch (temp_choice)
        {
        case 1:
            system("cls");
            menu();
            break;
        case 2:
            system("cls");
            stergere_client();
            break;
        default:
            system("cls");
            menu();
            break;
        }
    }
}
void view_customers_list()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    int choice;
    cout << "                <<<<CUSTOMERS LIST>>>>\n\n";
    /*Afisare aici*/
    int i;
    for (i = 0; i < v.size(); i++)
    {

        v[i]->afisare();
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    if (nr_argumente == 1)
    {
        cout << "\n\n\t\t1.Menu\n";
        cout << "\t\tEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system("cls");
            menu();
            break;
        default:
            system("cls");
            menu();
            break;
        }
    }
}
void commands_help()
{
    system("cls");
    cout << "\t\tIn order to make actions directly from the command line\n";
    cout << "\t\tthe program must be compiled like this:\n";
    cout << "\t\tg++ meniu.cpp -o meniu\n";
    cout << "\t\tAfterwards you must run the program like this:\n";
    cout << "\t\tmeniu arg1, arg2, arg3...\t    where arg1 must be the option value\n";
    cout << "\t\tHere is how to use commands for each menu option:\n";
    cout << "\t\t1.Create a new account:\n";
    cout << "\t\tmeniu 1 \"first_name\" \"last_name\" \"adress\" \"phone_number\" \n\n";
    cout << "\t\t2.Update information of existing account\n";
    cout << "\t\tmeniu 2 id_cont nr valoare_noua\t unde nr = {1, 2, 3, 4}\n";
    cout << "\t\t {1 = first_name, 2 = last_name, 3 = phone_number, 4 = adress}\n\n";
    cout << "\t\t3.Make transactions\n";
    cout << "\t\tmeniu 3 id_cont 1=deposit/2=withdraw sum\n\n";
    cout << "\t\t4.Check the details of existing account\n";
    cout << "\t\tmeniu 4 id_cont\n\n";
    cout << "\t\t5.Remove an existing account\n";
    cout << "\t\tmeniu 5 id_cont\n\n";
    cout << "\t\t6.View customers list\n";
    cout << "\t\tmeniu 6 admin_password\n\n";
    cout << "\t\t7.Commands Help\n";
    cout << "\t\tmeniu 7\n\n";
    if (nr_argumente == 1)
    {
        cout << "\t\tDo you want to return to the main menu?\n";
        cout << "\t\t1.Yes\t2.No\n";
        int ok;
        cout << "\t\t";
        cin >> ok;
        if (ok == 1)
        {
            system("cls");
            menu();
        }
        else
            exit(EXIT_SUCCESS);
    }
}

void menu()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);

    int choice;
    cout << "|\\---/|                                        |\\---/| \n";
    cout << "| o_o |          WELCOME TO THOMAS BANK        | o_o |\n";
    cout << " \\_^_/                                          \\_^_/ \n";
    cout << "                <<<<MAIN MENU>>>>\n\n";
    cout << "\t\t1.Create a new account\n";
    cout << "\t\t2.Update information of existing account\n";
    cout << "\t\t3.Make transactions\n";
    cout << "\t\t4.Check the details of existing account\n";
    cout << "\t\t5.Remove an existing account\n";
    cout << "\t\t6.View customers list\n";
    cout << "\t\t7.Commands Help\n";
    cout << "\t\t8.Exit\n\n";
    cout << "\t\tEnter your choice: ";
    cin >> choice;
    system("cls");

    switch (choice)
    {
    case 1:
        creare();
        break;
    case 2:
        update_account();
        break;
    case 3:
        transactions();
        break;
    case 4:
        view_customer();
        break;
    case 5:
        stergere_client();
        break;
    case 6:
        view_customers_list();
        break;
    case 7:
        
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        commands_help();
        break;
    case 8:
        afisareInFisier(v);
        exit(EXIT_SUCCESS);
        break;
    default:
        menu();
        break;
    }
}

int main(int argc, char *argv[])
{
    system("cls");
    srand(time(0));
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    if (argc > 1)
    {
        citireDinFisier(v);
        nr_argumente = argc;
        argumente = new char *[argc];
        for (int i = 0; i < argc; i++)
        {
            argumente[i] = new char[strlen(argv[i]) + 1];
            strcpy(argumente[i], argv[i]);
        }
        // for (int i = 0; i < nr_argumente; i++)
        switch (int(argumente[1][0] - '0'))
        {
        case 1:
            creare();
            break;
        case 2:
            update_account();
            break;
        case 3:
            transactions();
            break;
        case 4:
            view_customer();
            break;
        case 5:
            stergere_client();
            break;
        case 6:
            view_customers_list();
            break;
        case 7:
            commands_help();
            break;
        case 8:
            exit(EXIT_SUCCESS);
            break;
        }
        afisareInFisier(v);
    }
    else
    {
        citireDinFisier(v);
        menu();
    }
    b.setVector(v);
    return 0;
}