#include "Balanceador.h"

struct Almacen
{
    string tiempo;
    Almacen * next;
    Order * orden;
    char state;
    bool start;
    std::mutex mutex;
    Almacen()
    {
        tiempo = "";
        next = NULL;
        orden = NULL; 
        start = false;
        state = 'I';
    }
    Almacen(Order * o)
    {
        tiempo = "";
        next = NULL;
        orden = o; 
        start = false;
        state = 'I';
    }
};

struct Queue3
{
    Almacen * head; 
    int inqueue;
    int outqueue;
    std::mutex mutexF;  
    bool para_avanza;
    Queue3()
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
    }
    }
    void addOrder(Order * o)
    {
        inqueue+=1;
       	if (empty() == true)
		    head = new Almacen(o);
		else 
		{
		    Almacen * actual = head;
		    while (actual->next != NULL)
            {
                actual = actual->next;
            }
		    Almacen * nextOrder = new Almacen(o);
		    actual->next = nextOrder;
            Tiempo * starttime = new Tiempo();
            nextOrder->tiempo = starttime->currentdate;
		}
	}
    void removeOrder()
    {
        if (empty() == false)
        {   
            Almacen * takeout = head;     
            head = head->next;
            takeout->next = NULL;
        }
        
    }
    void print()
    {
        Almacen * tmp = head;
        while (tmp!=NULL)
        {
            cout << "Orden: " << tmp->orden << endl;;
            tmp = tmp->next;
        }
    }
};

struct Empleado
{
    int id;
    bool estado;
    int tiempo;
    Empleado * next;
    
    Empleado(int _id, bool _estado)
    {
        id = _id;
        estado = _estado;
        tiempo = 0;
        next = NULL;
    }

};


struct Procesamiento
{
    Empleado * head;
    Order * orden;
    LArticle * articulos;
    int nume = 0; //max 6
    Procesamiento()
    {
        head = NULL;
        orden = NULL;
        articulos = NULL; 
    }
    void disable(Empleado * e, Article * a)
    {
        e->estado = false;
        e->tiempo = getTime(a);
    }
    int getTime(Article * a)
    {
        Article * art = articulos->finder(articulos, a->pcode);
        string objeto = art->ubication;
        const char * matrix = objeto.c_str();
        int columnas = int(matrix[0])-64;
        int row;
        if (int(matrix[1])==49)
        {
            row = 10;    
        }
        else
        {
            row = int(matrix[2])-47;
        }
        return columnas*row*2;                
    }
    bool empty()
    {
        if (head == NULL)
        {
            return true;
        }
        return false;
        
    }
    void addEmployee(Empleado * e)
    {
        if (empty() == true)
        {
                head = e;
        }
        else
        {
            Empleado * actual = head;
		    while (actual->next != NULL)
            {
                actual = actual->next;
            }
		    actual->next = e;
            e->estado = true;
        }
            
		    
    }    
    void removeEmployee(Empleado * e, Article * a)
    {
       
        if (empty() == false)
        {   
            Empleado * takeout = head;     
            head = head->next;
            takeout->next = NULL;
            disable(e,a);
        }
    }

    
};

