#include <stdio.h>
#include <stdlib.h>

//Crea una estructura que representa un titulo universitario con los siguientes campos: id, nombre, universidad, anio de obtencion.
typedef struct{
    int id;
    char nombre[50];
    char universidad[50];
    int anioObtencion;
}Titulo;

//Crea una estructura que representa un nodo de una lista enlazada de titulos universitarios.
typedef struct nodo{
    Titulo titulo;
    struct nodo *siguiente;
}Nodo;

//Crea una estructura que representa a un docente con los siguientes campos: id, nombre, apellido, edad, telefono, ciudad, lista de titulos universitarios.
typedef struct{
    int id;
    char nombre[50];
    char apellido[50];
    int edad;
    char telefono[50];
    char ciudad[50];
    Nodo *listaTitulos;
}Docente;

//Crea una estructura que representa un nodo de una lista enlazada de docentes.
typedef struct nodoDocente{
    Docente docente;
    struct nodoDocente *siguiente;
}NodoDocente;

//Crea una estructura que representa a una universidad con los siguientes campos: id, nombre, ciudad, lista de docentes.
typedef struct{
    int id;
    char nombre[50];
    char ciudad[50];
    NodoDocente *listaDocentes;
}Universidad;

int main(){
    printf("Hello World!\n");
    return 0;
}