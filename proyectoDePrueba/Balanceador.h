#include "Fabrica.h"
#include<thread>
#include<chrono>
#include<mutex>
#include<condition_variable>
struct Balance
{
    int outqueue;
    PriorityQueue * colaOrdenes;
    Order * order;
    Queue2 * fabrica1;
    Queue2 * fabrica2;
    Queue2 * fabrica3;
    Queue2 * fabrica4;
    bool para_avanza;
    std::mutex mutex;
    std::condition_variable condicion;
    Balance()
    {
        colaOrdenes = NULL;
        fabrica1 = NULL;
        fabrica2 = NULL;
        fabrica3 = NULL;
        fabrica4 = NULL;
        order = NULL;
    }
    Balance(PriorityQueue * q, Queue2 * f1, Queue2 * f2, Queue2 * f3, Queue2 * f4)
    {
        para_avanza=true;
        colaOrdenes = q;
        fabrica1 = f1;
        fabrica2 = f2;
        fabrica3 = f3;
        fabrica4 = f4;
        outqueue=0;
        if(colaOrdenes->priority10->empty() == false)
        {
            order = colaOrdenes->priority10->head->order;
            
            colaOrdenes->removeOrder(order);
        }
        else if(colaOrdenes->priority9->empty() == false)
        {
            order = colaOrdenes->priority9->head->order;
            colaOrdenes->removeOrder(order);
        }
        if(colaOrdenes->priority8->empty() == false)
        {
            order = colaOrdenes->priority8->head->order;
            colaOrdenes->removeOrder(order);
        }
        else if(colaOrdenes->priority7->empty() == false)
        {
            order = colaOrdenes->priority7->head->order;
            colaOrdenes->removeOrder(order);
        }
        else if(colaOrdenes->priority6->empty() == false)
        {
            order = colaOrdenes->priority6->head->order;
            colaOrdenes->removeOrder(order);
        }
        if(colaOrdenes->priority5->empty() == false)
        {
            order = colaOrdenes->priority5->head->order;
            colaOrdenes->removeOrder(order);
        }
        else if(colaOrdenes->priority4->empty() == false)
        {
            order = colaOrdenes->priority4->head->order;
            colaOrdenes->removeOrder(order);
        }
        else if(colaOrdenes->priority3->empty() == false)
        {
            order = colaOrdenes->priority3->head->order;
            colaOrdenes->removeOrder(order);
        }
        if(colaOrdenes->priority2->empty() == false)
        {
            order = colaOrdenes->priority2->head->order;
            colaOrdenes->removeOrder(order);
        }
        else 
        {
            order = colaOrdenes->priority1->head->order;
            colaOrdenes->removeOrder(order);
        } 
        Tiempo now;

        order->timeinQ2=now.currentdate;   
        cout<<"ingreso el dato"<<endl;           
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
        condicion.notify_one();
        }
    }
    bool vacia(){
        if(order==NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    Order * removeit()
    {
        Order * borrar=order;
        order = NULL;
        Tiempo now;
        borrar->timeoutQ2=now.currentdate;
        return borrar;
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

    int countQueue(Queue2 * q)
    {
        Fabric * tmp = q->head;
        int count = 0;
        while (tmp != NULL)
        {
            count++;
            tmp = tmp->next;
        }
        return count;

    }

    bool verifyAmount(LArticle * a, Article * amo)
    {
        Article * tmp = finder(a,amo->pcode);
        if (amo->amount > tmp->amount)
        {
            return true; /*Cantidad de orden superior a la de inventario*/
        }
        return false;
    }

    bool moveToFabric(LArticle * a)
    {
        std::unique_lock<std::mutex> lock(mutex);
        if(para_avanza==true)
        {
            Article * tmp = order->acode->head; // cantidad en orden
            int f1 = countQueue(fabrica1);
            int f2 = countQueue(fabrica2);
            int f3 = countQueue(fabrica3);
            int f4 = countQueue(fabrica4);
            while (tmp != NULL)
            {
                if (verifyAmount(a, tmp) == true)
                {
                    Tiempo now;
                    stringstream datetime;
                    Article * tmp1 = finder(a,tmp->pcode);
                    datetime<<now.currentdate<<" "<<"A falta de "<<((tmp->amount)-(tmp1->amount))<<" de "<< tmp->pcode;
                    order->timeinQ3=datetime.str();
                    tmp->faltantes=(tmp->amount)-(tmp1->amount);
                    if (tmp->category == 'A')
                    {
                        if (f1<=f4)
                        {fabrica1->addOrder(tmp, tmp->amount); order->timeinQ2 = fabrica1->head->timein;tmp->category2='A';}
                        else
                        {fabrica4->addOrder(tmp, tmp->amount); order->timeinQ2 = fabrica4->head->timein;tmp->category='A';tmp->category2='D';}

                    }
                    else if (tmp->category == 'B')
                    {
                        if (f2<=f4)
                        {fabrica2->addOrder(tmp, tmp->amount); order->timeinQ2 = fabrica2->head->timein;tmp->category2='B';}
                        else
                        {fabrica4->addOrder(tmp, tmp->amount); order->timeinQ2 = fabrica4->head->timein;tmp->category='B';tmp->category2='D';}
                    }
                    else if (tmp->category == 'C')
                    {
                        if (f3<=f4)
                        {fabrica3->addOrder(tmp, tmp->amount); order->timeinQ2 = fabrica3->head->timein;tmp->category2='C';}
                        else
                        {fabrica4->addOrder(tmp, tmp->amount); order->timeinQ2 = fabrica4->head->timein;tmp->category='C';tmp->category2='D';}

                    }
                    return true;
                    this_thread::sleep_for(std::chrono::seconds(1));
                }
                tmp = tmp->next;
            }
            return false;
        }
        else
        {
            //condicion.wait(lock);
        }
    }
    Order * updateInventory(LArticle * a)
    {
        if (moveToFabric(a) == false) // restar del inventario
        {
            Article * tmp = order->acode->head;
            outqueue+=1;
            while (tmp != NULL)
            {
                Article * tmp1 = finder(a,tmp->pcode);
                tmp1->amount = tmp1->amount-tmp->amount;
                tmp= tmp->next;
            }
            return order;
        }
        return NULL;
    }
    void addfromFabric(char fabrica, LArticle * a, Queue2 * f1, Queue2 * f2, Queue2 * f3, Queue2 * f4)//,ColaAlisto * c//
    {   //std::unique_lock<std::mutex> lock(mutex);
        //if(para_avanza==true)
        //{
        if (fabrica == 'A')
        {
            //this_thread::sleep_for(chrono::seconds(f1->head->time));
            f1->removeOrder(a);
        }
        else if (fabrica == 'B')
        {
            //this_thread::sleep_for(chrono::seconds(f2->head->time));
            f2->removeOrder(a);
        }
        else if (fabrica == 'C')
        {
            //this_thread::sleep_for(chrono::seconds(f3->head->time));
            f3->removeOrder(a);
        }
        else
        {
            //this_thread::sleep_for(chrono::seconds(f4->head->time));
            f4->removeOrder(a);
        }
    }
    /*else
    {
        condicion.wait(lock);
    }
    }*/
    string printComponente(){
        stringstream movimientos;
        string almacena;
        string move;
        movimientos<<order->name<<'_'<<outqueue;
        move=movimientos.str();
        almacena="Tiene actualmente_han salido "+ move;
        return almacena;
    }
};
