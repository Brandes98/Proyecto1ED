#include "Ordenes.h"
#include "Tiempo.h"
struct NodeQueueOrder
{
    
    int priority;
    Order * order;
    NodeQueueOrder * next;
    NodeQueueOrder()
    {
        priority = 0;
        next = NULL;
    }
    NodeQueueOrder(Order * o)
    {
        priority = o->priority;
        order = o;
        next = NULL;
    }
};


struct Queue1
{
    NodeQueueOrder * head; 
    int tiene;
    int salieron;
    Queue1()
    {
        head = NULL;
        tiene=0;
        salieron=0;
    }
    bool empty()
    {
        if (head == NULL)
        {
            return true;
        }
        return false;
        
    }
    void addOrder(Order * o)
    {   this->tiene+=1;
       	if (empty() == true){
		    head = new NodeQueueOrder(o);
        }else 
		{
		    NodeQueueOrder * actual = head;
		    while (actual->next != NULL)
            {
                actual = actual->next;
            }
		    NodeQueueOrder * nextOrder = new NodeQueueOrder(o);
		    actual->next = nextOrder;
		}
	}
    void removeOrder()
    {
       
        if (empty() == false)
        {   
            this->tiene-=1;
            this->salieron+=1;
            NodeQueueOrder * takeout = head;     
            head = head->next;
            takeout->next = NULL;
        }
        
    }
    
    void print()
    {
        NodeQueueOrder * tmp = head;
        int number = 0;
        while (tmp!=NULL)
        {
            number = tmp->order->ocode;
            cout << "Order: " << number <<endl;
            tmp = tmp->next;
        }
        
    }
}; 
struct PriorityQueue
{
    int inqueue = 0;
    int outqueue = 0;
    Queue1 * priority1;
    Queue1 * priority2;
    Queue1 * priority3;
    Queue1 * priority4;
    Queue1 * priority5;
    Queue1 * priority6;
    Queue1 * priority7;
    Queue1 * priority8;
    Queue1 * priority9;
    Queue1 * priority10;
    PriorityQueue()
    {
        priority1 = new Queue1;
        priority2 = new Queue1;
        priority3 = new Queue1;
        priority4 = new Queue1;
        priority5 = new Queue1;
        priority6 = new Queue1;
        priority7 = new Queue1;
        priority8 = new Queue1;
        priority9 = new Queue1;
        priority10 = new Queue1;
    }    
    void addOrder (Order * o)
    {
        if (o->val == true)
        {
            if (o->priority == 1)
                priority1->addOrder(o);
            else if (o->priority == 2)
                priority2->addOrder(o);
            else if (o->priority == 3)
                priority3->addOrder(o);
            else if (o->priority == 4)
                priority4->addOrder(o);
            else if (o->priority == 5)
                priority5->addOrder(o);
            else if (o->priority == 6)
                priority6->addOrder(o);
            else if (o->priority == 7)
                priority7->addOrder(o);
            else if (o->priority == 8)
                priority8->addOrder(o);
            else if (o->priority == 9)
                priority9->addOrder(o);
            else
                priority10->addOrder(o);
            Tiempo * starttime = new Tiempo();
            o->timeinQ1 = starttime->currentdate;
            inqueue++;
        }
    }
    void removeOrder(Order * o)
    {
        if (o->priority == 1)
       		priority1->removeOrder();
       	else if (o->priority == 2)
       		priority2->removeOrder();
        else if (o->priority == 3)
       		priority3->removeOrder();
        else if (o->priority == 4)
       		priority4->removeOrder();
        else if (o->priority == 5)
       		priority5->removeOrder();
        else if (o->priority == 6)
       		priority6->removeOrder();
        else if (o->priority == 7)
       		priority7->removeOrder();
        else if (o->priority == 8)
       		priority8->removeOrder();
        else if (o->priority == 9)
       		priority9->removeOrder();
        else 
            priority10->removeOrder();
        inqueue--;
        outqueue++;
        Tiempo * endtime = new Tiempo();
        o->timeoutQ1 = endtime->currentdate;
    }
    /*string printMovimientos(){
        stringstream movimientos;
        string almacena;
        string move;
        movimientos<<inqueue<<'_'<<outqueue;
        move=movimientos.str();
        almacena="Tiene actualmente_han salido "+ move;
        return almacena;

    }*/
    /*void print(int p)
    {
        if (p == 1)
        {
            cout << "Priority 1: "<<endl;
            if (priority1->empty() == true)
            {
                cout << "NONE" <<endl;
            }
            priority1->print();
        }
        else if (p == 2)
        {
            cout << "Priority 2: "<<endl;
            if (priority2->empty() == true)
            {
                cout << "NONE" <<endl;
            }
            priority2->print();
        }
        else if (p == 3)
        {
            cout << "Priority 3: "<<endl;
            if (priority3->empty() == true)
            {
                cout << "NONE" <<endl;
            }
            priority3->print();            
        }
        else if (p == 4)
        {
            cout << "Priority 4: "<<endl;
            priority4->print();
        }
        else if (p == 4)
        {
            cout << "Priority 4: "<<endl;
            if (priority4->empty() == true)
            {
                cout << "NONE" <<endl;
            }
            priority4->print();
        }
        else if (p == 5)
        {
            cout << "Priority 5: "<<endl;
            if (priority5->empty() == true)
            {
                cout << "NONE" <<endl;
            }
            priority5->print();
        }
        else if (p == 6)
        {
            cout << "Priority 6: "<<endl;
            if (priority6->empty() == true)
            {
                cout << "NONE" <<endl;
            }            
            priority6->print();
        }
        else if (p == 7)
        {
            cout << "Priority 7: "<<endl;
            if (priority7->empty() == true)
            {
                cout << "NONE" <<endl;
            }            
            priority7->print();
        }
        else if (p == 8)
        {
           cout << "Priority 8: "<<endl;
            if (priority8->empty() == true)
            {
                cout << "NONE" <<endl;
            }
            priority8->print();
        }
        else if (p == 9)
        {
            cout << "Priority 9: "<<endl;
            if (priority9->empty() == true)
            {
                cout << "NONE" <<endl;
            }
            priority9->print();
        }
        else
        {
            cout << "Priority 10: "<<endl;
            if (priority10->empty() == true)
            {
                cout <<'\t'<< "<NONE>" <<endl;
            }
            priority10->print();
        }
    }*/ 

};





