#include <iostream>
#include <string.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Balanceador.h"
using namespace std;
string objeto;
int column;
int qeue; 


struct AlistadorNodo
{
int id;
int tiempoTrabajo;
AlistadorNodo* siguiente;
Order * ordenActual;
string estado;
bool para_avanza;
std::mutex mutex;
std::condition_variable condicion;
    AlistadorNodo (int ID)
    {
        int id=ID;
        tiempoTrabajo=0;
        siguiente=NULL;
        ordenActual=NULL;
        estado="Libre";
        para_avanza=true;
    }
    void insertarOrden(Order * o)
    {
        ordenActual=o;
    }
    void borrarOrden()
    {
        ordenActual=NULL;
        
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
    void parar()
    {
        std::unique_lock<std::mutex> lock(mutex);
        para_avanza=false;
    }
    void avanzar()
    {
        std::unique_lock<std::mutex> lock(mutex);
        para_avanza=true;
        condicion.notify_one();
    }
    string retornarActual()
    {
        string retornable;
        if (ordenActual==NULL) 
        {
            retornable="vacio";
        
        }
        else
        {
            retornable=ordenActual->ocode;
            
        }
        return retornable;
    }
    void print()
    {
        if(ordenActual!=NULL)
        ordenActual->print();
        else
        cout<<"Esta libre"<<endl;
    }
    Order *  procesarPedido(LArticle * lista) 
    {
        std::unique_lock<std::mutex> lock(mutex);
        if (para_avanza==true)
        {
            
            Article * tmp2 = ordenActual->acode->head;
            while (tmp2!=NULL)
            {
                Article * tmp1 = lista->head;
                while (tmp1!=NULL)
                {
                    if (tmp1->pcode == tmp2->pcode)
                    {
                        tmp2->ubication = tmp1->ubication;        
                    }
                    tmp1 = tmp1->next;
                }
                cout<<"Esta es la ubicacion"<<tmp2->pcode<<endl;
                tmp2 = tmp2->next;
            }
        }
        if (para_avanza==true)
        {   
            Article * temp = ordenActual->acode->head;
            while(temp!=NULL)
            {
                cout<<"temporal"<<temp->ubication<<endl;
                string objeto=temp->ubication;
                const char * matrix = objeto.c_str();
                cout<<"este es el objeto"<<matrix<<endl;
                cout<< " este es int objeto "<< matrix[0]<<endl;
                cout<< " este es int objeto "<< matrix[2]<<endl;
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
                int tiempo = columnas*row*2;            
                //this_thread::sleep_for(chrono::seconds(timeespera));
                temp->bodega=tiempo;
                cout<<tiempo<<endl;
                temp=temp->next;
            } 
        return ordenActual;  
        }
        else
        {
            condicion.wait(lock);
        } 
    }
    
};
struct Cola_Alistadores
{
    AlistadorNodo * frente;
    int inqueue;
    int outqueue;
    Cola_Alistadores()
    {
        frente=NULL;
        inqueue=0;
        outqueue=0;
    }
   
    bool vacia()
    {
        if(frente==NULL)
            return true;
        else
            return false;
    }
    void encolarAlistador(AlistadorNodo * alistador)
    {   inqueue+=1;
     alistador->estado="Libre";
        if(vacia()){
           
            frente= alistador;
        }
        else
        {
            
            AlistadorNodo* actual = frente;
		            // recorre la lista hasta llegar al penultimo nodo
		            while (actual->siguiente != NULL)
		                          actual = actual->siguiente; 
		              
		            // Crea nuevo nodo, lo apunta con uN  
		            AlistadorNodo* nuevo = alistador;
		            //le quita el enlace al que era ultimo
		            actual->siguiente = nuevo;

        }

    }
AlistadorNodo *desencolarAlistador()
{
    cout<<"Entro en descencolar alistador"<<endl;
      // si no hay elementos, no borra nada, retorna null
      if (frente!=NULL)
      {
        cout<<"logro entrar a descencolarAlistador"<<endl;
          // un puntero que apunta al nodo que se
          // "despegara" de la lista y se retorna
          outqueue+=1;
          inqueue-=1;
          AlistadorNodo* borrado = frente;     
          // pN se pasa al segundo de la lista
          // porque el primero se eliminara
          frente = frente->siguiente;
          // el nodo borrado, se debe despegar
          // entonces siguiente apunta a null y no
          // al segundo de la lista que ahora es pN
          borrado->siguiente = NULL;
          // aca se deberia liberar la memoria si no se
          // retornara el borrado
          cout<<"cambio el estado"<<endl;
          borrado->estado="ocupado";
          cout<<"si retorna "<<endl;
          return borrado;
      }
      
}
AlistadorNodo *tope()
{
return frente;
}
AlistadorNodo *obtenerSiguienteAlistador()
{
    cout<<"entro en obtener siguiente Alistador"<<endl;
    AlistadorNodo * siguiente= tope();
    desencolarAlistador();
    return siguiente;
}
string buscar_actuales(){
    stringstream movimientos;
        string almacena="en espera: ";
        string move;
    AlistadorNodo* tmp=frente;
    while(tmp!=NULL)
    {
         movimientos<<tmp->id<<'_';
        move=movimientos.str();
        almacena+=move+ " ";
        
        tmp=tmp->siguiente;
    }
    return almacena;
}
};
struct ControlAlistadores{
    AlistadorNodo  * q;
    AlistadorNodo  * q1;
    AlistadorNodo  * q2;
    AlistadorNodo  * q3;
    AlistadorNodo  * q4;
    AlistadorNodo  * q5;
    
    ControlAlistadores(AlistadorNodo* n1,AlistadorNodo* n2,AlistadorNodo* n3,AlistadorNodo* n4,AlistadorNodo* n5,AlistadorNodo* n6)
    {
        q=n1;
        q1=n2;
        q2=n3;
        q3=n4;
        q4=n5;
        q5=n6;
    }
    string retornarEstadoGeneral()
    {
        string madre;
        madre="Estado1= "+q->estado+"Estado2"+q1->estado+"Estado3= "+q2->estado+"Estado4"+q3->estado+"Estado5= "+q4->estado+"Estado6"+q5->estado;
        return madre;
    }
    void AvanzarTodos(){
        
       q->avanzar();
       q1->avanzar();
       q2->avanzar();
       q3->avanzar();
       q4->avanzar();
       q5->avanzar();
       
    }
    void pararTodos(){
         q->parar();
       q1->parar();
       q2->parar();
       q3->parar();
       q4->parar();
       q5->parar();
       
    }
};
//--------------------------------Empieza Alisto---------------------------------------------------//
struct NodoAlisto
{
    Order * orden;
    NodoAlisto * siguiente;

    NodoAlisto(Order * o)
    {
        orden=o;
        siguiente=NULL;


    }
    void print()
    {
        orden->print();
    }
};
struct ColaAlisto{
    NodoAlisto * frente;
    int inqueue;
    int outqueue;
    ColaAlisto()
    {
        frente=NULL;
        inqueue=0;
        outqueue=0;
    }
    bool vacia()
    {
        if (frente==NULL)
        return true;
        else
        return false;
    }
    void insertarEnCola(Order * o)
    {cout<<"se ha recibido en alisto"<<endl;
        inqueue+=1;
        if(vacia())
        frente=new NodoAlisto(o);
        else 
        {

            NodoAlisto * Actual=frente;
            while(Actual->siguiente!=NULL)
            {
                Actual=Actual->siguiente;
            }
            NodoAlisto * nuevo=new NodoAlisto(o);
            Actual->siguiente=nuevo;
        }
        Tiempo now;
        o->timeinQ4= now.currentdate;

    }
    void  eliminarEnCola(){
         if (vacia())
      {
         cout<<"esta vacia"<<endl;
      }
      else
      {
         inqueue--;
         outqueue++;
          // un puntero que apunta al nodo que se
          // "despegara" de la lista y se retorna
          NodoAlisto* borrado = frente;     
          // pN se pasa al segundo de la lista
          // porque el primero se eliminara
          frente = frente->siguiente;
          // el nodo borrado, se debe despegar
          // entonces siguiente apunta a null y no
          // al segundo de la lista que ahora es pN
          borrado->siguiente = NULL;
          // aca se deberia liberar la memoria si no se
          // retornara el borrado
        Tiempo now;
        borrado->orden->timeOutQ4= now.currentdate;          
      }
    }
    string printMovimiento()
    {
      stringstream movimientos;
      string almacena;
      string move;
      movimientos<<inqueue<<'_'<<outqueue;
      move=movimientos.str();
      almacena="Tiene actualmente_han salido "+ move;
      return almacena;
    }
};
