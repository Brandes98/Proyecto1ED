#include <iostream>
#include "empaquetadora.h"
#include <thread>
#include <chrono>
#include <fstream>
#include <sstream>
#include <ctime>
using  namespace std;

struct FNodo
{ 
    int numeroOrden;
    Order * orden;
    FNodo * siguiente;
    bool parar_avanzar;
   
FNodo(Order * ordenado)
{
    numeroOrden= ordenado->ocode;
    siguiente=NULL;
    orden=ordenado;
    parar_avanzar=true;
}
void imprimir(){
    orden->print();
}
};
struct cola_facturacion
{
    FNodo*alfrente;
    FNodo* poseido;
    int pasadosComponente;
    int inqueue;
    int outqueue;
    std::mutex mutex;
std::condition_variable condicion;
    bool para_avanza;
    cola_facturacion(){
        
        alfrente=NULL;
       inqueue=0;
       outqueue=0;
        poseido=NULL;
        pasadosComponente=0;
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
    bool vacia()
    {
        if(alfrente=NULL)
            return true;
        else
            return false;
    }
    void encolarFacturacion(Order * facturar)
    {
        inqueue++;
        if(vacia())
            alfrente= new FNodo(facturar);
        else
        {
            FNodo* actual = alfrente;
		            // recorre la lista hasta llegar al penultimo nodo
		            while (actual->siguiente != NULL)
		                          actual = actual->siguiente; 
		              
		            // Crea nuevo nodo, lo apunta con uN  
		            FNodo* nuevo = new FNodo (facturar);
		            //le quita el enlace al que era ultimo
		            actual->siguiente = nuevo;

        }

    }
    void desencolarFacturacion()
    {
        std::unique_lock<std::mutex> lock(mutex);
    if (para_avanza==true){
    
         if (!vacia())
      {
        
          // un puntero que apunta al nodo que se
          // "despegara" de la lista y se retorna
          FNodo* borrado = alfrente;     
          poseido=alfrente;
          pasadosComponente+=1;
          outqueue++;
          // pN se pasa al segundo de la lista
          // porque el primero se eliminara
          alfrente = alfrente->siguiente;
          // el nodo borrado, se debe despegar
          // entonces siguiente apunta a null y no
          // al segundo de la lista que ahora es pN
          borrado->siguiente = NULL;
          // aca se deberia liberar la memoria si no se
          // retornara el borrado
          Order*alfrentel= borrado->orden;
          
         time_t t = time(nullptr);
    struct tm *now = localtime(&t);

    // Convertir la fecha y hora a un string
    stringstream datetime;
    stringstream eYsCola;
    stringstream eYsBalanceador;
    stringstream eYsFabrica;
    stringstream eYsAlistado;
    stringstream aEmpacado;
    stringstream finalizado;
    datetime << now->tm_year + 1900 << '-'
             << now->tm_mon + 1 << '-'
             << now->tm_mday << '_'
             << now->tm_hour << '-'
             << now->tm_min << '-'
             << now->tm_sec;
    eYsCola<<alfrentel->timeinQ1<<'_'<<alfrentel->timeoutQ1;
    string cola=eYsCola.str();
    //----------------------------------------------------------//
    eYsBalanceador<<alfrentel->timeinQ2<<'_'<<alfrentel->timeoutQ2;
    string balanceador=eYsBalanceador.str();
    //---------------------------------------------------------//
    eYsFabrica<<alfrentel->timeinQ3;
    eYsAlistado<<alfrentel->timeinQ4<<'_'<<alfrentel->timeOutQ4;
    string fabrica=eYsFabrica.str();
    string alistado=eYsAlistado.str();
    //----------------------------------------------------------//
    aEmpacado<<alfrentel->timeInQ5;
    finalizado<<alfrentel->timeOutQ5;
    string emp=aEmpacado.str();
    string finalz=finalizado.str();
    string empacado="A empaque: "+emp;
    string finalized="Finalizado: "+finalz;
    string datetime_str = datetime.str();
    stringstream numeroPedido;
    stringstream numeroCliente;
    numeroPedido<< alfrentel->ocode;
    numeroCliente<<alfrentel->ccode;
    string numP=numeroPedido.str();
    string numC=numeroCliente.str();

    string filename=" "+numP+"_"+numC+"_"+datetime_str+".txt";
    string numeroDelPedido="Pedido: "+numP+" ";
    string numeroDelCliente="Cliente: "+numC+" ";
    string inprentaCola= "Cola inicio y finalizacion: "+cola;
    string inprentaBalanceador="A balanceador inicio y finalizacion: "+balanceador;
    string inprentaFabrica="A fabrica: "+fabrica;
    string inprentaAlisto="A alisto inicio y finalizacion: "+alistado;
        std::ofstream archivo(filename); //crea el archivo y lo abre en modo escritura
        if (archivo.is_open()) 
  { //verifica que el archivo se haya abierto correctamente
    archivo << numeroDelPedido <<std::endl;
    archivo << numeroDelCliente<< std::endl;
    archivo << inprentaCola<<endl;
    archivo<< inprentaBalanceador<<endl;
    archivo<<inprentaFabrica<<endl;
    archivo<<inprentaAlisto<<endl;
    
    archivo<<empacado<<endl;
    archivo<<finalized<<endl;
     archivo<<"Fabrica"<<endl;
    Article * tmp= alfrentel->acode->head;
    while(tmp!=NULL)
    {
       if(tmp->faltantes!=0){
        stringstream articuloCode;
        articuloCode<<tmp->pcode;
        string ac=articuloCode.str();
        stringstream articuloIdentidad;
        articuloIdentidad << tmp->category;
        string ai=articuloIdentidad.str();
        stringstream unidades;
        unidades<<tmp->faltantes;
        string au=unidades.str();
        string datosArticle="Articulo "+ac+" fabricado en "+ai+" faltantes "+ au+" unidades.";
        archivo<<datosArticle<<endl;
        tmp = tmp->next;
       }
       else
       tmp=tmp->next;
    }
    archivo<<"Alisto"<<endl;
    stringstream iden;
    iden<<alfrentel->idAlistador;
    string ide=iden.str();
    string alistadorfinal="Alistador"+ide;
    archivo<<alistadorfinal<<endl;
    Article * tmp1=alfrentel->acode->head;
     while(tmp1!=NULL)
    {
       
        stringstream codigo;
        codigo<<tmp1->pcode;
        stringstream posicion;
        posicion << tmp1->ubication;
        stringstream segundos;
        segundos<<tmp1->bodega;
        string codigo1=codigo.str();
        string posicion1=posicion.str();
        string segundos1=segundos.str();
        string informacionAlmacenable=codigo1+" Ubicacion "+posicion1+" "+segundos1+" segundos.";
        archivo<<informacionAlmacenable<<endl;

        
        tmp1 = tmp1->next;
    }
    
    archivo.close(); //cierra el archivo
    std::cout << "Archivo creado exitosamente." << std::endl;
  }
  else {
    std::cout << "No se pudo crear el archivo." << std::endl;
  }

      }
    }else{
        condicion.wait(lock);
    }
    }
    string printFacturacion()
    {
       stringstream movimientos;
        string almacena;
        string move;
        movimientos<<inqueue<<'_'<<outqueue;
        move=movimientos.str();
        almacena="Tiene actualmente_han salido "+ move;
        return almacena;
    
    }
string printComponente()
{
    stringstream movimientos;
        string almacena;
        string move;
        movimientos<<poseido->orden->name<<'_'<<pasadosComponente;
        move=movimientos.str();
        almacena="Tiene actualmente_han salido "+ move;
        return almacena;
}
};