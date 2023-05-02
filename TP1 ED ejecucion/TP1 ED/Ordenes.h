#include "Lista_Articulos.h"
#include "Lista_Clientes.h"
#include "NombreArchivo.h"

#include <sstream>
struct LProduct
{
    Article * head, * last;
    LProduct ()
    {
        head = last = NULL;
    }
    void insertStart (string product, int amount) 
    {
        if (head == NULL)
        {
            head = new Article(product, amount);
            last = head;           
        }
        else
        {
            Article * newElem = new Article(product, amount); 
  		    newElem->next = head; 
            head = newElem; 
        }
    }
};

struct Order
{
    int ocode; //Order Code
    int ccode; //Client Code
    string name;
    LProduct * acode; // Products Code
    bool val;
    int priority;
    string timeinQ1; //Queue 1: Order Queue
    string timeoutQ1;//Queue 1 :Order Queue
    string timeinQ2;
    string timeoutQ2;
    string timeinQ3;
    string timeoutQ3;
    string timeinQ4;
    string timeOutQ4;
    string timeInQ5;
    string timeOutQ5;
    string timeInQ6;
    string timeOutQ6;
    string timeInQ7;
    string timeOutQ7;
    int idAlistador;
    bool ready;
    Order()
    {
        ocode = 0;
        ccode = 0;
        acode = new LProduct();
        priority = 0;
        name = "";
        timeinQ1 = "";
        timeoutQ1 = "";
        timeinQ2 = "";
        timeoutQ2 = "";
        timeinQ3 = "";
        timeoutQ3 = "";
        timeinQ4 = "";
        timeOutQ4 = "";
        timeInQ5 = "";
        timeOutQ5 = "";
        timeInQ6 = "";
        timeOutQ6 = "";
        timeInQ7 = "";
        timeOutQ7 = "";
        idAlistador=0;
        ready = false;
    }

    bool validClient(LClients * client)
    {
        Client * tmp = client->head;
        while(tmp != NULL)
        {
            if (ccode == tmp->ccode)
            {
                priority = tmp->priority;
                name = tmp->name;
                return true;
            }
            
            tmp = tmp->next;
        }
        return false;
    }
    bool validArticle(LArticle * article, Article * val)
    {
        Article * tmp = article->head;
        Article * tmp1 = val;

        while(tmp != NULL)
        {
            if (trim(tmp1->pcode) == trim(tmp->pcode))
            {
                return true;
            }
            tmp = tmp->next;
        }
        return false;
    }
    string trim(const std::string& str)
    {
        auto start = str.find_first_not_of(" \t\r\n"); // Find first non-whitespace character
        auto end = str.find_last_not_of(" \t\r\n"); // Find last non-whitespace character

        if (start == std::string::npos) // If the string is all whitespace
        {
            return "";
        }
        else
        {
            return str.substr(start, end - start + 1); // Extract the non-whitespace substring
        }   
    }
    bool valid(LClients * client, LArticle * article)
    {
        Article * tmp = acode->head; 
        if (validClient(client) == true)
        {
            while (tmp != NULL)
            {
                if (validArticle(article, tmp) == false)
                {
                    return false;
                }
                tmp = tmp->next;
            }
            return true;
            
        }
        return false;
        
    }
    void generateOrder(string path)
    {   
        fstream file;
        file.open(path, ios::in);
        if (file.is_open()) 
        {
            string text[4];
            int n = 0; 
            int n1 = 0;
            while(getline(file,text[n],'\t'))
            {
                n++;
                if(n == 4)
                {
                    n1 = stoi(trim(text[3]));
                    acode->insertStart(text[2], n1);
                    n = 2;
                }
            }
            int n2 = stoi(trim(text[0]));
            int n3 = stoi(trim(text[1]));
            ocode = n2;
            ccode = n3;       
        }	
        else
        {
            cout << "No such file";
        }   
        file.close();
    }
    void validation(string path, LClients * clients, LArticle * inventory, string pathout)
    {
        if (valid(clients, inventory) == true)
        {
            val = true;
            cout << "Order, successfully generated"<<endl;
        }
        else if (validClient(clients) == false)
        {
            cout<<"Invalid Client"<<endl;
            moveInvalid(path, pathout);
        }
        else
        {
            cout << "Invalid Products" << endl;
            moveInvalid(path, pathout);
        }
    }
    void moveInvalid(string pathin, string pathout)
    {
        const char* old_filename = pathin.c_str();
        const char* new_filename = pathout.c_str();

        int result = std::rename(old_filename, new_filename);
        if (result != 1)
        {
            cout<<"File moved out"<<endl;
        }
        
    }
    void print()
    {
        if (val == true)
        {
            cout <<"Order Number: " << ocode << endl;
            cout <<"Client's Name: "<< name << '\t' << " Client's Code: " << ccode <<endl;
            Article * tmp = acode->head;
            while(tmp != NULL)
            {
                cout << tmp->pcode << '\t' << tmp->amount;
                tmp = tmp->next;
            }
        }
        else
            cout << "Order invalid" << endl;
    }
        
        


    
};