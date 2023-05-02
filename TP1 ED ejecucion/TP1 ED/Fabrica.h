#include "Cola_Ordenes.h"
#include<thread>
#include<chrono>
#include <mutex>

struct Fabric
{
    string pcode;
    char category;
    int amount;
    int time;
    string timein;
    string timeout;
    Fabric * next;
    int atendidos;
    string actual;
    
    Fabric()
    {
        pcode = "";
        category = '0';
        amount = 0;
        time = 0; 
        next = NULL;
        atendidos=0;
        
        
    }
    Fabric(Article * a, int quantity)
    {
        pcode = a->pcode;
        category = a->category;
        time = a->time;
        amount = quantity;
        next = NULL;
        

    }
};

struct Queue2
{
    Fabric * head; 
    int inqueue;
    int outqueue;
    std::mutex mutexF;
//std::condition_variable condicionF;
bool para_avanza;
    Queue2()
    {
        head = NULL;
        inqueue=0;
        outqueue=0;
        para_avanza=true;
    }
    bool empty()
    {
        if (head == NULL)
        {
            return true;
        }
        return false;
        
    }
    void pararAvanzar()
{
    std::unique_lock<std::mutex> lock(mutex);
    if(para_avanza==true)
    {
         para_avanza=false;
    }
   
    else
    {
    para_avanza=true;
    //condicionF.notify_one();
    }
}
    void addOrder(Article * a, int n)
    {
         std::unique_lock<std::mutex> lock(mutexF);
        if(para_avanza==true){
        inqueue+=1;
       	if (empty() == true)
		    head = new Fabric(a,n);
		else 
		{
		    Fabric * actual = head;
		    while (actual->next != NULL)
            {
                actual = actual->next;
            }
		    Fabric * nextOrder = new Fabric(a, n);
		    actual->next = nextOrder;
            Tiempo * starttime = new Tiempo();
            nextOrder->timein = starttime->currentdate;
		}
        }else
        {
            //condicionF.wait(lock);
        }
	}
    void removeOrder(LArticle * a)
    {
        if (empty() == false)
        {   
            LArticle * modify = a;
            Article * tmp = modify->head;
            Fabric * takeout = head; 
            Tiempo * endtime = new Tiempo();
            while (tmp!=NULL)
            {
                if(tmp->pcode == head->pcode)
                {
                    int numero = head->amount;
                    tmp->amount = tmp->amount+numero;
                    tmp->timeB=endtime->currentdate;
                }
                tmp = tmp->next;
            }    
            head = head->next;
            takeout->next = NULL;
            takeout->timeout = endtime->currentdate;
            outqueue+=1;
        }
        
    }
    void print()
    {
        Fabric * tmp = head;
        while (tmp!=NULL)
        {
            cout << "Article: " << tmp->pcode <<'\t'<<"Produced amount: " << tmp->amount <<endl;;
            tmp = tmp->next;
        }
        
    }
    string printMovimientos(){
        stringstream movimientos;
        string almacena;
        string move;
        movimientos<<inqueue<<'_'<<outqueue;
        move=movimientos.str();
        almacena="Tiene actualmente_han salido "+ move;
        return almacena;
    }
    string printComponent()
    {
        stringstream movimientos;
        string almacena;
        string move;
        movimientos<<head->pcode<<'_'<<outqueue;
        move=movimientos.str();
        almacena="Tiene actualmente_han salido "+ move;
        return almacena;
    }

};
