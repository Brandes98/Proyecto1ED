#include <cstdlib>
#include <iostream>
#include <filesystem>
using namespace std;
#include <dirent.h>
/*
Instrucciones para usar:

Use la funcion filePath(nombre del folder) este va leer todos los archivos en y generar una lista con los archivos y generara el path
Path find va devolver el path del archivo a buscar

*/




struct NombreArchivo
{
    string nombre;
    NombreArchivo * next;
    string path;
    string folder;
    NombreArchivo()
    {
        nombre = "";
        path = "";
        folder = "";
        next = NULL;
    }
    NombreArchivo(string name)
    {
        nombre = name;
        path = "";
        folder = "";
        next = NULL;
    }
    NombreArchivo(string name, NombreArchivo * _next)
    {
        nombre = name;
        path = "";
        folder = "";
        next = new NombreArchivo(name,_next);
    }
    void print()
    {
        cout<<nombre<<" "<<path<<endl;
    }
};

struct LArchivos
{
    NombreArchivo * head;
    LArchivos()
    {
        head = NULL;
    }
    bool isEmpty()
    {
		return head == NULL;
	}
    void insertStart(string name)
    {
        if (isEmpty())
            head = new NombreArchivo(name);
        else
        {
            NombreArchivo * newElem = new NombreArchivo(name); 
  		    newElem->next = head; 
            head = newElem; 
        }
    }
    void generateList(string path)
    {   
        const char * way = path.c_str();
        DIR *dr;
        struct dirent *en;
        dr = opendir(way); //open all directory
        if (dr) 
        {
            while ((en = readdir(dr)) != NULL) 
            {
                string d(en->d_name, en->d_name + strlen(en->d_name));
                if ((d.size() > 3))
                {
                    insertStart(en->d_name);
                }
            }
            closedir(dr); //close all directory
        }
    }
    string generatePath(string file)
    {
        std::filesystem::path file_path = file; // Path to the file
        std::filesystem::path absolute_path = std::filesystem::current_path() / file_path; // Absolute path
        string way = absolute_path.string();
        return way;
    }
    void filePath(string file/*Ingresar Nombre del Folder a leer*/)
    {
        string cam = generatePath(file);
        generateList(cam);
        NombreArchivo * tmp = head;
        while(tmp != NULL)
        {
            tmp->folder = file;
            string way = file+"\\"+tmp->nombre;
            tmp->path = generatePath(way);
            tmp = tmp->next;
        }
    }
    string pathFind(string name)   
    {
        NombreArchivo * tmp = head;
        while(tmp != NULL)
        {
            if (tmp->nombre == name)
            {
                
                return tmp->path;
            }
            
            tmp = tmp->next;
        }
        return "Archivo no encontrado";
    }
   
    void print()
    {
        NombreArchivo * tmp = head;
        while(tmp != NULL)
        {
            tmp->print();
            tmp = tmp->next;
        }
    }
    

};