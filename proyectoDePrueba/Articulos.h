/*
Creado por: Winson Chen y Brandon Calderon 
Fecha de Creaccion: 27-Mar-2023 17:50
Fecha de Ultima Modificacion: 28-Mar-20:05
*/
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct Article
{
    string pcode; //Product code
    int amount;
    int time;
    char category;
    string ubication;
    int faltantes;
    string timeB1;
    string timeB;
    int bodega;
    char category2;
    Article * next, * prev;
    Article()
    {
        pcode = "";
        amount = 0;
        time = 0;
        category = 'A';
        ubication = "";
        int faltantes=0;
        timeB1="";
        timeB="";
        bodega=0;
        category2='A';
    }
    Article(string code, int number)
    {
        pcode = code;
        amount = number;
    }
    Article(string code, int number, int seconds, char clasification, string location)
    {
        pcode = code;
        amount = number;
        time = seconds;
        category = clasification;
        ubication = location;
        next = prev = NULL;

    }
    Article(string code, int number, int seconds, char clasification, string location, Article * _next, Article *_prev)
    {
        pcode = code;
        amount = number;
        time = seconds;
        category = clasification;
        ubication = location;
        next = _next;
        prev = _prev;    
    }
    void print()
    {
        cout << pcode << '\t'<< amount << '\t'<< time << '\t'<< category << '\t'<< ubication << endl;
    }
};