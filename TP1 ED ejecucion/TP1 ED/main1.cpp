/*
Creado por: Winson Chen
Fecha de Creaccion: 12-Mar-2023 17:50
Fecha de Ultima Modificacion: 12-Mar-20:05
*/
#include <cstdlib>
#include <iostream>
using namespace std;
#include "Almacen.h"
#include<thread>
#include<mutex>
#include<condition_variable>

/*void ProcesarArticulo(Empleado * e, Articulo * a, Procesamiento * p)
{
    p->removeEmployee(e);
    this_thread::sleep_for(chrono::seconds(e->tiempo));
    p->addEmployee(e);
}
*/

/*mutex m1,m2,m3,m4,m5,m6,m7,m8,m9,m10,m11,m12,m13,m14;
condition_variable cv1, cv2, cv3,cv4,cv5,cv6,cv7,cv8,cv9,cv10,cv11,cv12,cv14;
std::mutex mtx_balanceador;
std::condition_variable cv_balanceador;
std::mutex mtx_alisto;
std::condition_variable cv_alisto;
std::mutex mtx_listaAlistadores;
std::condition_variable cv_listaAlistadores;
std::mutex mtx_empaquetadora;
std::condition_variable cv_empaquetadora;
std::mutex mtx_facturacion;
std::condition_variable cv_facturacion;
bool ready1=false,ready2=false,ready3=false,ready4=false,ready5=false;
void conectarColaBalanceador(Balance* balanceador,ColaAlisto* alisto,Queue2 * fabrica1,Queue2 * fabrica2,Queue2 * fabrica3,Queue2 * fabrica4,LArticle* articulos);
void conectarAlistoAlistadores(ColaAlisto* alisto, Cola_Alistadores * lista,Cola_alisto * empaquetadora,AlistadorNodo * alistando,LArticle * articulos);
void facturar(Cola_alisto * empaquetadora,cola_facturacion * facturacion);
void facturarFinal(cola_facturacion*facturacion);*/
int main()
{
    LClients * clientes = new LClients();
    LArchivos * file1 = new LArchivos();
    file1->filePath("Clientes");
    LArchivos * file2 = new LArchivos();
    file2->filePath("Articulos");
    LArchivos * file3 = new LArchivos();
    file3->filePath("Ordenes");
    LArchivos * file4 = new LArchivos();
    string sigorden = "Orden_1.txt";
    string archivoerrores = file4->generatePath("Errores")+"\\"+sigorden;
    cout<<archivoerrores<<endl;
    string archivoclientes = file1->pathFind("Clientes.txt");
    cout<<archivoclientes<<endl;
    string archivoarticulos = file2->pathFind("Articulos.txt");
    cout<<archivoarticulos<<endl;
    string archivoordenes = file3->pathFind("Orden_1.txt");
    clientes->generateList(archivoclientes);
    LArticle * articulos = new LArticle();
    articulos->generateList(archivoarticulos);
    Order * order = new Order();
    order->generateOrder(archivoordenes);
    order->validation(archivoordenes, clientes, articulos, archivoerrores);
    order->print();
    PriorityQueue *  prioridad = new PriorityQueue();
    prioridad->addOrder(order);
}
    /*Queue2 * fabrica1=new Queue2();
    Queue2 * fabrica2=new Queue2();
    Queue2 * fabrica3=new Queue2();
    Queue2 * fabrica4=new Queue2();
    Balance * balanceador = new Balance(prioridad,fabrica1,fabrica2,fabrica3,fabrica4);
    
    AlistadorNodo * alistador1=new AlistadorNodo(1);
    AlistadorNodo * alistador2=new AlistadorNodo(2);
    AlistadorNodo * alistador3=new AlistadorNodo(3);
    AlistadorNodo * alistador4=new AlistadorNodo(4);
    AlistadorNodo * alistador5=new AlistadorNodo(5);
    AlistadorNodo * alistador6=new AlistadorNodo(6);
    AlistadorNodo * alistador7=new AlistadorNodo(7);
    ControlAlistadores* espera= new ControlAlistadores(alistador1,alistador2,alistador3,alistador4,alistador5,alistador6);
    Cola_Alistadores*alistadores=new Cola_Alistadores();
    Cola_alisto * empaquetadora= new Cola_alisto();
    ColaAlisto * alisto= new ColaAlisto();
    cola_facturacion * facturacion=new cola_facturacion();
    conectarColaBalanceador(balanceador,alisto,fabrica1,fabrica2,fabrica3,fabrica4, articulos);
    alistadores->encolarAlistador(alistador1);
    alistadores->encolarAlistador(alistador2);
    alistadores->encolarAlistador(alistador3);
    alistadores->encolarAlistador(alistador4);
    alistadores->encolarAlistador(alistador5);
    alistadores->encolarAlistador(alistador6);
    //std::thread  balanceador_thread(conectarColaBalanceador, std::ref(balanceador), std::ref(alisto),std::ref(fabrica1),std::ref(fabrica2),std::ref(fabrica3),std::ref(fabrica4),std::ref(articulos), std::ref(alistadores), std::ref( empaquetadora),std::ref(alistador7));
    //std::thread alistadores_thread(conectarAlistoAlistadores, std::ref(alisto), std::ref(alistadores), std::ref( empaquetadora),std::ref(alistador7),std::ref(articulos));
    //balanceador_thread.join();
    conectarAlistoAlistadores(alisto, alistadores, empaquetadora, alistador7, articulos);
    articulos->writeFile(archivoarticulos);

    //alistadores_thread.join();
    //facturacion_thread.join();

    }   
    void conectarColaBalanceador(Balance * balanceador, ColaAlisto* alisto, Queue2 * fabrica1, Queue2 * fabrica2, Queue2 * fabrica3, Queue2 * fabrica4, LArticle* articulos)
    {
        Order * orden = balanceador->order;
        Article * art = orden->acode->head;
        bool moveto = balanceador->moveToFabric(articulos);
        if (moveto == true)
        {
            while (art != NULL)
            {
                if (balanceador->verifyAmount(articulos, art) == true)
                {
                    Article * arto = balanceador->finder(articulos,art->pcode);
                    balanceador->addfromFabric(arto->category, articulos, fabrica1, fabrica2, fabrica3, fabrica4);
                }
                art = art->next;
            }
        }
        Order * toalisto = balanceador->updateInventory(articulos);
        alisto->insertarEnCola(toalisto);
    }
    void conectarAlistoAlistadores(ColaAlisto* alisto, Cola_Alistadores * listaAlistadores, Cola_alisto * empaquetadora, AlistadorNodo * alistando, LArticle * articulos)
    {
   
        //while(true)
        //{
            //cout<<"entro en segunda fase"<<endl;
            //std::unique_lock<std::mutex> lock_alisto(mtx_alisto);
            //cv_alisto.wait(lock_alisto, [&](){ return !alisto->vacia(); });
        
            //std::unique_lock<std::mutex> lock_listaAlistadores(mtx_listaAlistadores);
            //cv_listaAlistadores.wait(lock_listaAlistadores, [&](){ return !listaAlistadores->vacia(); });
            //cout<<"1"<<endl;
            alistando = listaAlistadores->desencolarAlistador();
    
            cout<<"paso1"<<endl;
            Order * Orden=alisto->frente->orden;
            cout<<"paso2"<<endl;
            alistando->ordenActual=Orden;
            cout<<"paso3"<<endl;
            alisto->eliminarEnCola();
            cout<<"se le asigno el pedido"<<endl;
            alistando->procesarPedido(articulos);
            Order* tranferir=alistando->ordenActual;
            empaquetadora->encolarOrden(tranferir);
            cout<<"lo empaco"<<endl;
            alistando->borrarOrden();
            cout<<"Se borro la orden"<<endl;
                
            listaAlistadores->encolarAlistador(alistando);
            cout<<"funka"<<endl;
           
    }

    /*void facturar(Cola_alisto * empaquetadora,cola_facturacion * facturacion)
    {
        Order * OFinal;
        cout<<"pokemon"<<endl;
        while(true)
        {   cout<<"entra en siclo"<<endl;
            cout<<"Esta es la orden"  <<empaquetadora->frente->orden<<endl;
            std::unique_lock<std::mutex> lock_empaquetadora(mtx_empaquetadora);
            cv_empaquetadora.wait(lock_empaquetadora, [&](){ return !empaquetadora->vacia(); });
            cout<<"entro papi "<<endl;
            OFinal=empaquetadora->descencolarOrden();
            facturacion->encolarFacturacion(OFinal);
            //empaquetadora->frente->orden->moveInvalid(archivoordenes, archivoerrores)
            cout<<"entro papi llore conmigo"<<endl;
        }
    }*/
    /*void facturarFinal(cola_facturacion*facturacion)
    {
        while(true)
        {
            std::unique_lock<std::mutex> lock_facturacion(mtx_facturacion);
            cv_facturacion.wait(lock_facturacion,[&](){return !facturacion->vacia();});
            facturacion->desencolarFacturacion();    
        }
    }*/

