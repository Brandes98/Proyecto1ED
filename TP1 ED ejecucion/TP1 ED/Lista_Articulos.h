/*
Creado por: Winson Chen y Brandon Calderon 
Fecha de Creaccion: 27-Mar-2023 17:50
Fecha de Ultima Modificacion: 28-Mar-20:05
*/

#include "Articulos.h"

struct LArticle
{
    Article * head, * last;
    bool val = false;
    LArticle()
    {
        head = last = NULL;
    }
    bool isEmpty()
    {
		return head == NULL;
	}
	void insertStart (string code, int number, int seconds, char clasification, string location)
    {
		if (isEmpty())
			head = last = new Article (code, number, seconds, clasification, location);
		else
        {
			Article * item = new Article(code, number, seconds, clasification, location);
			item->next = head;
			head->prev = item;
			head = item;
        }
    }
    void generateList(string path)
    {   
        fstream file;
        file.open(path, ios::in);
        if (file.is_open()) 
        {
        string text[5];
        int n = 0; 
        int n1 = 0;
        int n2 = 0;
        while(getline(file,text[n],'\t'))
        {
            n++;
            if(n == 5)
            {
                n1 = stoi(trim(text[1]));
                n2 = stoi(trim(text[2]));
                stringstream convert3; convert3 << text[3]; char n3; convert3 >> n3;
                if (n1 < 0)
                {
                    cout << "Article: " << text[0] << " has an value less than 0"<<endl;
                    val = true;
                }
                if ((n3 == 'A'|| n3 == 'B' || n3 == 'C') == false)
                {
                    cout << "Article: " << text[0] << " with a wrong category input!!" <<endl;
                    val = true;
                }
                if (text[4].substr(1,1) == "0" && text[4].substr(2,1) == "0")
                {
                    cout << "Article: " << text[0] << " with an invalid location!!" <<endl;
                    val = true;
                }
                if (val == false)
                {
                    insertStart(trim(text[0]), n1, n2, n3, text[4]);
                }
                n = 0;
            }   
        }
        }	
        else
        {
            val = true;
            cout << "No such file";
        }   
        file.close();
        if(val == false)
            cout << "List of Articles, successfully generated"<<endl;
    }
    bool duplicate(Article * tmp1)
    {
        Article  * tmp2 = tmp1->next;
        while(tmp2 != NULL)
        {
            if (tmp2->pcode == tmp1->pcode)
            {
                val = true;
                return true;
            }
            tmp2 = tmp2->next;
        }
        return false;
    }
    bool valid()
    {
        Article  * tmp = head;
        while (tmp != NULL)
        {
            if (duplicate(tmp)==true)
            {
                cout<<"Duplicated article found!!"<<endl;
                return false;
            }
            tmp = tmp->next;
        }
        if (val == true)
            return false;
        return true;

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
    void writeFile (string path)
    {
        if(valid() == true)
        {
            Article * tmp = head;
            std::ofstream outputFile(path, std::ios::trunc);  // create a new output file stream with truncation flag
            if (!outputFile.is_open()) 
            { 
                std::cerr << "Unable to open file for writing.\n";
            }
            else
            {
                outputFile<<"";
                outputFile.close();
                std::ofstream outputFile(path, std::ios::app);
                if (!outputFile.is_open())   // check if the file was opened successfully
                    std::cerr << "Unable to open file for writing.\n";
                else
                {
                    while(tmp != NULL)
                    {
                        outputFile << tmp->pcode << "\t" << tmp->amount << "\t" << tmp->time << "\t" << tmp->category << "\t" << tmp->ubication << "\t\n";
                        //cout<<"Works";
                        tmp = tmp->next;
                    }
                    outputFile.close();
                }
            }
            
            
             // close the output file stream
            std::cout << "File successfully overwritten.\n";
        }
    }
    Article * finder(LArticle * a, string pcode) // Return a pointer of the article in the list
        {
            Article * tmp = a->head;
            while (tmp!=NULL)
            {
                if (trim(tmp->pcode) == trim(pcode))
                {
                    return tmp;
                }
                tmp = tmp->next;
                
            }
            cout<< "Article not found"<<endl;
            return NULL;
        }
    void print()
    {

        if(valid() == true)
        {
            Article * tmp = head;
            cout << "The complete list of all articles is:"<<endl;
            while(tmp != NULL)
            {
                tmp->print();
                tmp = tmp->next;
            }
        }
        else
            cout << "Selected list is not valid"<<endl;
    }
};
