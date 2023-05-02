
#include "mainwindow.h"

#include <QApplication>
#include"facturacion.h"
#include <cstdlib>
#include <iostream>
#include "ui_mainwindow.h"
#include<thread>

#include<mutex>
#include<condition_variable>
using namespace std;
mutex m1,m2,m3,m4,m5,m6,m7,m8,m9,m10,m11,m12,m13,m14;
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
void facturarFinal(cola_facturacion*facturacion);
void escritura(LArticle * articulos,string archivoArticulos);
void constanteLectura(LArchivos*file3,Order * orden);
int main(int argc, char *argv[])
{
    //string x= std::filesystem:: absolute();
    string x = filesystem::current_path().string();
    cout<<x<<endl;
    QApplication a(argc, argv);
    MainWindow w;
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
    cout<<order->val<<endl;
    PriorityQueue *  prioridad = new PriorityQueue();
    prioridad->addOrder(order);
    Queue2 * fabrica1=new Queue2();
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
    alistadores->encolarAlistador(alistador1);
    alistadores->encolarAlistador(alistador2);
    alistadores->encolarAlistador(alistador3);
    alistadores->encolarAlistador(alistador4);
    alistadores->encolarAlistador(alistador5);
    alistadores->encolarAlistador(alistador6);
    cout<<"entroaca"<<endl;
    QObject::connect(w.ui->BotonPedidos, &QPushButton::clicked, [prioridad, &w](){
        string conversion=prioridad->printMovimientos();
        QString movimientosPrioridad=QString::fromStdString(conversion);
        w.ui->label_pedidos->setText(movimientosPrioridad);
    });
    QObject::connect(w.ui->BotonBalanceador, &QPushButton::clicked, [balanceador, &w](){
        string conversion=balanceador->printComponente();
        QString movimientosPrioridad=QString::fromStdString(conversion);
        w.ui->balanceadorLabel->setText(movimientosPrioridad);
    });
    QObject::connect(w.ui->colaFA, &QPushButton::clicked, [fabrica1, &w](){
        string conversion=fabrica1->printMovimientos();
        QString movimientosPrioridad=QString::fromStdString(conversion);
        w.ui->labelCA->setText(movimientosPrioridad);
    });
    QObject::connect(w.ui->ColaFB, &QPushButton::clicked, [fabrica2, &w](){
        string conversion=fabrica2->printMovimientos();
        QString movimientosPrioridad=QString::fromStdString(conversion);
        w.ui->labelColaB->setText(movimientosPrioridad);
    });
    QObject::connect(w.ui->ColaFC, &QPushButton::clicked, [fabrica3, &w](){
        string conversion=fabrica3->printMovimientos();
        QString movimientosPrioridad=QString::fromStdString(conversion);
        w.ui->labelColaC->setText(movimientosPrioridad);
    });
    QObject::connect(w.ui->pushButton_FabricaMixta, &QPushButton::clicked, [fabrica4, &w](){
        string conversion=fabrica4->printMovimientos();
        QString movimientosPrioridad=QString::fromStdString(conversion);
        w.ui->vercolaf4->setText(movimientosPrioridad);
    });
    QObject::connect(w.ui->vercompfA, &QPushButton::clicked, [fabrica1, &w](){
        string conversion=fabrica1->printComponent();
        QString movimientosPrioridad=QString::fromStdString(conversion);
        w.ui->labelverfA->setText(movimientosPrioridad);
    });
    QObject::connect(w.ui->pushButton_9, &QPushButton::clicked, [fabrica2, &w](){
        string conversion=fabrica2->printComponent();
        QString movimientosPrioridad=QString::fromStdString(conversion);
        w.ui->label_19->setText(movimientosPrioridad);
    });
    QObject::connect(w.ui->pushButton_10, &QPushButton::clicked, [fabrica3, &w](){
        string conversion=fabrica3->printComponent();
        QString movimientosPrioridad=QString::fromStdString(conversion);
        w.ui->label_20->setText(movimientosPrioridad);
    });
    QObject::connect(w.ui->ver_f4, &QPushButton::clicked, [fabrica4, &w](){
        string conversion=fabrica4->printComponent();
        QString movimientosPrioridad=QString::fromStdString(conversion);
        w.ui->vercompf4->setText(movimientosPrioridad);

    });
    QObject::connect(w.ui->pushButton_16, &QPushButton::clicked, [alisto, &w](){
        string conversion=alisto->printMovimiento();
        QString movimientosPrioridad=QString::fromStdString(conversion);
        w.ui->label_23->setText(movimientosPrioridad);
    });
    QObject::connect(w.ui->pushButton_26, &QPushButton::clicked, [alistador1, &w](){
        string conversion=alistador1->retornarActual();
        QString movimientosPrioridad=QString::fromStdString(conversion);
        w.ui->label_26->setText(movimientosPrioridad);

    });
    QObject::connect(w.ui->pushButton_18, &QPushButton::clicked, [alistador2, &w](){
        string conversion=alistador2->retornarActual();
        QString movimientosPrioridad=QString::fromStdString(conversion);
        w.ui->label_27->setText(movimientosPrioridad);

    });
    QObject::connect(w.ui->pushButton_20, &QPushButton::clicked, [alistador3, &w](){
        string conversion=alistador3->retornarActual();
        QString movimientosPrioridad=QString::fromStdString(conversion);
        w.ui->label_35->setText(movimientosPrioridad);

    });
    QObject::connect(w.ui->pushButton_33, &QPushButton::clicked, [alistador4, &w](){
        string conversion=alistador4->retornarActual();
        QString movimientosPrioridad=QString::fromStdString(conversion);
        w.ui->label_42->setText(movimientosPrioridad);

    });
    QObject::connect(w.ui->pushButton_24, &QPushButton::clicked, [alistador5, &w](){
        string conversion=alistador5->retornarActual();
        QString movimientosPrioridad=QString::fromStdString(conversion);
        w.ui->label_37->setText(movimientosPrioridad);

    });
    QObject::connect(w.ui->pushButton_22, &QPushButton::clicked, [alistador6, &w](){
        string conversion=alistador6->retornarActual();
        QString movimientosPrioridad=QString::fromStdString(conversion);
        w.ui->label_38->setText(movimientosPrioridad);

    });
    QObject::connect(w.ui->pushButton_30, &QPushButton::clicked, [espera, &w](){
        string conversion=espera->retornarEstadoGeneral();
        QString movimientosPrioridad=QString::fromStdString(conversion);
        w.ui->label_24->setText(movimientosPrioridad);

    });
    QObject::connect(w.ui->pushButton_28, &QPushButton::clicked, [alistadores, &w](){
        string conversion=alistadores->buscar_actuales();
        QString movimientosPrioridad=QString::fromStdString(conversion);
        w.ui->label_25->setText(movimientosPrioridad);

    });
    QObject::connect(w.ui->pushButton_31, &QPushButton::clicked, [empaquetadora, &w](){
        string conversion=empaquetadora->printMovimientos();
        QString movimientosPrioridad=QString::fromStdString(conversion);
        w.ui->label_39->setText(movimientosPrioridad);

    });
    QObject::connect(w.ui->pushButton_37, &QPushButton::clicked, [empaquetadora, &w](){
        string conversion=empaquetadora->printComponentes();
        QString movimientosPrioridad=QString::fromStdString(conversion);
        w.ui->label_34->setText(movimientosPrioridad);

    });
    QObject::connect(w.ui->pushButton_34, &QPushButton::clicked, [facturacion, &w](){
        string conversion=facturacion->printFacturacion();
        QString movimientosPrioridad=QString::fromStdString(conversion);
        w.ui->label_33->setText(movimientosPrioridad);

    });
    QObject::connect(w.ui->pushButton_35, &QPushButton::clicked, [facturacion, &w](){
        string conversion=facturacion->printComponente();
        QString movimientosPrioridad=QString::fromStdString(conversion);
        w.ui->label_32->setText(movimientosPrioridad);

    });
    QObject::connect(w.ui->pushButton_15, &QPushButton::clicked, [balanceador, &w](){
        balanceador->pararAvanzar();

    });
    QObject::connect(w.ui->pOsfA, &QPushButton::clicked, [fabrica1, &w](){
        fabrica1->pararAvanzar();

    });
    QObject::connect(w.ui->pushButton_12, &QPushButton::clicked, [fabrica2, &w](){
        fabrica2->pararAvanzar();

    });
    QObject::connect(w.ui->pushButton_13, &QPushButton::clicked, [fabrica3, &w](){
        fabrica3->pararAvanzar();

    });
    QObject::connect(w.ui->pOsf4, &QPushButton::clicked, [fabrica4, &w](){
       fabrica4->pararAvanzar();

    });
    QObject::connect(w.ui->pushButton_25, &QPushButton::clicked, [alistador1, &w](){
       alistador1->pararAvanzar();

    });
    QObject::connect(w.ui->pushButton_17, &QPushButton::clicked, [alistador2, &w](){
       alistador2->pararAvanzar();

    });
    QObject::connect(w.ui->pushButton_32, &QPushButton::clicked, [alistador4, &w](){
        alistador4->pararAvanzar();

    });
    QObject::connect(w.ui->pushButton_23, &QPushButton::clicked, [alistador5, &w](){
       alistador5->pararAvanzar();

    });
    QObject::connect(w.ui->pushButton_21, &QPushButton::clicked, [alistador6, &w](){
        alistador6->pararAvanzar();

    });
    QObject::connect(w.ui->pushButton_19, &QPushButton::clicked, [alistador3, &w](){
       alistador3->pararAvanzar();

    });
    QObject::connect(w.ui->pushButton_29, &QPushButton::clicked, [espera, &w](){
        espera->pararTodos();

    });

    QObject::connect(w.ui->pushButton_27, &QPushButton::clicked, [espera, &w](){
        espera->AvanzarTodos();

    });
    QObject::connect(w.ui->pushButton_38, &QPushButton::clicked, [empaquetadora, &w](){
        empaquetadora->pararAvanzar();

    });
    QObject::connect(w.ui->pushButton_2, &QPushButton::clicked, [facturacion, &w](){
        facturacion->pararAvanzar();

    });
   conectarColaBalanceador(balanceador,alisto,fabrica1,fabrica2,fabrica3,fabrica4, articulos);
    conectarAlistoAlistadores(alisto,alistadores,empaquetadora,alistador7,articulos);
   facturar(empaquetadora,facturacion);
    facturarFinal(facturacion);
    //std::thread  balanceador_thread(conectarColaBalanceador, std::ref(balanceador), std::ref(alisto),std::ref(fabrica1),std::ref(fabrica2),std::ref(fabrica3),std::ref(fabrica4),std::ref(articulos), std::ref(alistadores), std::ref( empaquetadora),std::ref(alistador7));
    cout<<"entrolaca"<<endl;
    //std::thread alistadores_thread(conectarAlistoAlistadores, std::ref(alisto), std::ref(alistadores), std::ref( empaquetadora),std::ref(alistador7),std::ref(articulos));
    cout<<"SIII paso aca"<<endl;
   // balanceador_thread.join();
    //articulos->writeFile(archivoarticulos);
    escritura(articulos,archivoarticulos);
    //alistadores_thread.join();

    //facturacion_thread.join();

    w.show();

    return a.exec();
}
void escritura(LArticle* articulos,string  archivarticulos)
{
    //while(true){
    articulos->writeFile(archivarticulos);
    //}
}
void constanteLectura(LArchivos * file3,Order* orden){
    while(true){
    string archivoordenes = file3->pathFind("Orden_1.txt");
    orden->generateOrder(archivoordenes);
        }
}
void conectarColaBalanceador(Balance * balanceador, ColaAlisto* alisto, Queue2 * fabrica1, Queue2 * fabrica2, Queue2 * fabrica3, Queue2 * fabrica4, LArticle* articulos)
{
    //std::unique_lock<std::mutex> lock_balanceador(mtx_balanceador);
    //cout<<0123<<endl;
    //cv_balanceador.wait(lock_balanceador, [&](){ return !balanceador->vacia(); });

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
void conectarAlistoAlistadores(ColaAlisto* alisto,Cola_Alistadores * listaAlistadores,Cola_alisto * empaquetadora,AlistadorNodo* alistando,LArticle*articulos)
{

    while(true)
    {
        cout<<"entro en segunda fase"<<endl;
        /*std::unique_lock<std::mutex> lock_alisto(mtx_alisto);
        cv_alisto.wait(lock_alisto, [&](){ return !alisto->vacia(); });

        std::unique_lock<std::mutex> lock_listaAlistadores(mtx_listaAlistadores);
        cv_listaAlistadores.wait(lock_listaAlistadores, [&](){ return !listaAlistadores->vacia(); });
       */
         cout<<"1"<<endl;
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
}

void facturar(Cola_alisto * empaquetadora,cola_facturacion * facturacion)
{
    Order * OFinal;

    while(true)
    {   cout<<"entra en siclo"<<endl;
        cout<<"Esta es la orden"  <<empaquetadora->frente->orden<<endl;
        /*std::unique_lock<std::mutex> lock_empaquetadora(mtx_empaquetadora);
        cv_empaquetadora.wait(lock_empaquetadora, [&](){ return !empaquetadora->vacia(); });
        */
        cout<<"entro p "<<endl;
        OFinal=empaquetadora->descencolarOrden();
        facturacion->encolarFacturacion(OFinal);
        cout<<"entro pap"<<endl;
    }
}
void facturarFinal(cola_facturacion*facturacion)
{
   /* while(true)
    {*/
        /*std::unique_lock<std::mutex> lock_facturacion(mtx_facturacion);
        cv_facturacion.wait(lock_facturacion,[&](){return !facturacion->vacia();});
        */
        facturacion->desencolarFacturacion();
   // }
}

