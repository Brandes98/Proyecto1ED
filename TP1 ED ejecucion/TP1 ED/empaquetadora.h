#include <iostream>


#include <thread>
#include <chrono>
#include <fstream>
#include <sstream>
#include <ctime>

#include "Almacen.h"
using  namespace std;

struct Nodo
{ 
    int numeroOrden;
    Order * orden;
    Nodo * siguiente;
Nodo(Order * ordenado)
{
    numeroOrden= ordenado->ocode;
    siguiente=NULL;
    orden=ordenado;
}
void imprimir(){
    orden->print();
}
};


struct Cola_alisto
{
    int outqueue;
    int inqueue;
    Nodo * poseido;
    int pasados;
    Nodo * frente;
    bool para_avanza;
    std::mutex mutex;
std::condition_variable condicion;
    Cola_alisto()
    {
        frente=NULL;
        outqueue=0;
        inqueue=0;
        poseido=NULL;
        pasados=0;
        para_avanza=true;
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
         if (frente == NULL)
        return true;
     else
         return false;
    }
    void encolarOrden(Order * pedido){
        inqueue+=1;
        if (vacia())
		        frente = new Nodo (pedido);
		    else 
		    {
		            // referencia al primero para recorrer la lista
		            Nodo* actual = frente;
		            // recorre la lista hasta llegar al penultimo nodo
		            while (actual->siguiente != NULL)
		                          actual = actual->siguiente; 
		              
		            // Crea nuevo nodo, lo apunta con uN  
		            Nodo* nuevo = new Nodo (pedido);
		            //le quita el enlace al que era ultimo
		            actual->siguiente = nuevo;
		    }
            Tiempo now;
            pedido->timeInQ5=now.currentdate;
    }
    
    Order * descencolarOrden(){
     std::unique_lock<std::mutex> lock(mutex);
    if(para_avanza==true){
        if (vacia())
      {
        return NULL;
      }
      else
      {
        inqueue-=1;
        outqueue+=1;
         Tiempo now;
         
          Nodo* borrado = frente;     
          
          frente = frente->siguiente;
         
          borrado->siguiente = NULL;
          Article * tmp= borrado->orden->acode->head;
          while(tmp!=NULL)
          {
            this_thread::sleep_for(chrono::seconds(1));
            tmp=tmp->next;
          }
         borrado->orden->timeOutQ5=now.currentdate;
         Order* returnable= borrado->orden;
        return returnable;
      } 
    
      }else{
        condicion.wait(lock);
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
    string printComponentes()
    {
        stringstream movimientos;
        string almacena;
        string move;
        movimientos<<poseido->orden->name<<'_'<<pasados;
        move=movimientos.str();
        almacena="Tiene actualmente_han salido "+ move;
        return almacena;
    }
};