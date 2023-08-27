#ifndef DATA_MANAGEMENT
#define DATA_MANAGEMENT

#include <windows.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>
#include <string>
#include <vector>
using namespace std;

class ContBancar;

class ContBancar
{
    char *nume;
    char *prenume;
    char *adresa;
    char *numar_telefon;
    int id;
    int balanta;

public:
    ContBancar(char *, char *, char *, char *, int, int);
    ContBancar(const ContBancar &);
    ContBancar() { balanta = 0; };
    void setNume(char *nume)
    {
        strcpy(this->nume, nume);
    }

    void setPrenume(char *prenume)
    {
        strcpy(this->prenume, prenume);
    }

    void setAdresa(char *adresa)
    {
        strcpy(this->adresa, adresa);
    }
    void setTelefon(char *telefon)
    {
        strcpy(this->numar_telefon, telefon);
    }
    int getId()
    {
        return id;
    }
    int getBalanta()
    {
        return (balanta);
    }
    void setBalanta(int x)
    {
        balanta = x;
    }
    void afisare();
    char *creareLinie();
    bool operator==(int);
};

bool ContBancar::operator==(int x)
{
    if(this->id == x)
        return true;
    return false;
}

int strToNr(char *s)
{
    int i, nr = 0, len = strlen(s);
    for (i = 0; i < len; i++)
        nr = nr * 10 + s[i] - '0';
    return (nr);
}

int oglindit(int n)
{
    int x = 0;
    while (n)
    {
        x = x * 10 + n % 10;
        n /= 10;
    }
    return (x);
}

char *nrToStr(int n)
{
    int nr = oglindit(n);
    char *s = new char[30];
    int k = 0;
    if (nr == 0)
        s[k++] = '0';
    else
        while (nr)
        {
            s[k++] = nr % 10 + '0';
            nr /= 10;
        }
    s[k] = '\0';
    return (s);
}
char *ContBancar::creareLinie()
{
    char *s = new char[100];
    s[0] = '\0';
    strcat(s, prenume);
    strcat(s, ",");
    strcat(s, nume);
    strcat(s, ",");
    strcat(s, adresa);
    strcat(s, ",");
    strcat(s, numar_telefon);
    strcat(s, ",");
    strcat(s, nrToStr(id));
    strcat(s, ",");
    strcat(s, nrToStr(balanta));
    return (s);
}

void ContBancar::afisare()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (balanta == 0)
    {   SetConsoleTextAttribute(hConsole,FOREGROUND_RED);
        cout << "\t\tFirst Name: " << prenume << endl;
        cout << "\t\tLast Name: " << nume << endl;
        cout << "\t\tAdress: " << adresa << endl;
        cout << "\t\tPhone number: " << numar_telefon << endl;
        cout << "\t\tBalance:" << balanta << endl;
        cout << "\t\tID: " << id << endl;
        cout << endl;
    }
    else
    {   
        SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN);
        cout << "\t\tFirst Name: " << prenume << endl;
        cout << "\t\tLast Name: " << nume << endl;
        cout << "\t\tAdress: " << adresa << endl;
        cout << "\t\tPhone number: " << numar_telefon << endl;
        cout << "\t\tBalance:" << balanta << endl;
        cout << "\t\tID: " << id << endl;
        cout << endl;
        
    }
}

ContBancar::ContBancar(char *nume, char *prenume, char *adresa, char *numar_telefon, int id, int balanta = 0)
{
    this->nume = new char[strlen(nume + 1)];
    this->prenume = new char[strlen(prenume + 1)];
    this->adresa = new char[strlen(adresa + 1)];
    this->numar_telefon = new char[strlen(numar_telefon + 1)];
    strcpy(this->nume, nume);
    strcpy(this->prenume, prenume);
    strcpy(this->adresa, adresa);
    strcpy(this->numar_telefon, numar_telefon);
    this->id = id;
    this->balanta = balanta;
}

ContBancar::ContBancar(const ContBancar &c)
{
    this->nume = new char[strlen(c.nume + 1)];
    this->prenume = new char[strlen(c.prenume + 1)];
    this->adresa = new char[strlen(c.adresa + 1)];
    this->numar_telefon = new char[strlen(c.numar_telefon + 1)];
    strcpy(this->nume, c.nume);
    strcpy(this->prenume, c.prenume);
    strcpy(this->adresa, c.adresa);
    strcpy(this->numar_telefon, c.numar_telefon);
    this->id = c.id;
    this->balanta = c.balanta;
}

class Banca
{
    vector <ContBancar*> vectorul;
    public:
    void    push(ContBancar* c)
    {
        vectorul.push_back(c);
    }
    int     size()
    {
        return vectorul.size();
    }
    vector<ContBancar*> getVector()
    {
        vector<ContBancar*> v = vectorul;
        return v;
    }
    vector<ContBancar*> setVector(vector<ContBancar*> v)
    {
        vectorul = v;
    }
};

void citireDinFisier(vector<ContBancar*> &L)
{
    L.erase(L.begin(), L.end());
    ifstream f("data.csv");
    char nume[50], prenume[75], adresa[100], telefon[15];
    string t;
    char *s;
    int id = 0, i;
    int balanta = 0;
    if (!f)
    {
        cout << "Error opening file.";
    }
    while (getline(f, t))
    {
        s = new char[t.length()];
        for (i = 0; i < t.length(); i++)
            s[i] = t[i];
        s[i] = '\0';
        // cout << s << endl;
        char *p = strtok(s, ",");
        strcpy(prenume, p);
        p = strtok(nullptr, ",");
        strcpy(nume, p);
        p = strtok(nullptr, ",");
        strcpy(adresa, p);
        p = strtok(nullptr, ",");
        strcpy(telefon, p);
        p = strtok(nullptr, ",");
        int len = strlen(p);
        for (i = 0; i < len; i++)
            id = id * 10 + p[i] - '0';
        p = strtok(nullptr, ",");
        len = strlen(p);
        for (i = 0; i < len; i++)
            balanta = balanta * 10 + p[i] - '0';
        delete[] s;
        ContBancar *c = new ContBancar(prenume, nume, adresa, telefon, id, balanta);
        L.push_back(c);
        id = 0;
        balanta = 0;
    }
    f.close();
}
void afisareInFisier(vector<ContBancar*> L)
{   ofstream out("data.csv");
    for (int i=0; i<L.size(); i++)
        out<< L[i]->creareLinie() << endl;
    out.close();
}

#endif