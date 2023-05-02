#include "Clientes.h"
struct LClients 
{
    Client * head, * last;
    LClients()
    {
        head = last = NULL;
    }
    void insertStart (int code, string cname, int position) 
    {
        if (head == NULL)
        {
            head = new Client(code, cname, position);
            last = head;           
        }
        else
        {
            Client * newElem = new Client(code, cname, position); 
  		    newElem->next = head; 
            head = newElem; 
        }
    }
    void generateList(string path)
    {   
        fstream file;
        file.open(path, ios::in);
        if (file.is_open()) 
        {
            string text[3];
            int n = 0; 
            while(getline(file,text[n],'\t'))
            {
                n++;
                if(n == 3)
                {
                    stringstream convert1; convert1 << text[0]; int n1; convert1 >> n1;
                    stringstream convert2; convert2 << text[2]; int n2; convert2 >> n2;
                    insertStart(n1, text[1], n2);
                    n = 0;
                }
            }       
        }	
        else
        {
            cout << "No such file";
        }   
        file.close();
        cout << "List of Clients, successfully generated"<<endl;
    }
    void print()
    {
        Client * tmp = head;
        cout << "The complete list of all customers is:"<<endl;
        while(tmp != NULL)
        {
            tmp->print();
            tmp = tmp->next;
        }
    }

};