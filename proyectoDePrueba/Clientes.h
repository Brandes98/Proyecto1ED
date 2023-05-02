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
struct Client
{
    int ccode;
    string name;
    int priority;
    Client * next;
    Client()
    {
        ccode = 0;
        name = "";
        priority = 0;
        next = NULL;
    }
    Client(int code, string cname, int position)
    {
        ccode = code;
        name = cname;
        priority = position;
        next = NULL;
    }
    Client(int code, string cname, int position, Client * NextElement)
    {
        ccode = code;
        name = cname;
        priority = position;
        next = NextElement;
    }
    void print()
    {
        cout << ccode << '\t' << name << '\t' << priority << endl;
    }

};
