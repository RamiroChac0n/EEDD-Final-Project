#include <stdio.h>
#include <stdlib.h>

//Crea un struct para fecha con los siguientes campos: dia, mes, anio.
typedef struct{
    int dia;
    int mes;
    int anio;
}Fecha;

//Crea una estructura que representa un titulo universitario con los siguientes campos: id, nombre, universidad, anio de obtencion.
typedef struct{
    int id;
    char nombre[50];
    char universidad[50];
    int anioObtencion;
}Titulo;

//Crea un arbol binario equilibrado de titulos universitarios.
typedef struct arbol_titulos{
    Titulo titulo;
    struct arbol_titulos *izquierda;
    struct arbol_titulos *derecha;
}Arbol_titulos;

//Crea una estructura que representa a un docente con los siguientes campos: id, nombre, apellido, edad, telefono, ciudad, arbol de titulos universitarios.
typedef struct{
    int id;
    char nombre[50];
    char apellido[50];
    int edad;
    char telefono[50];
    char ciudad[50];
    Arbol_titulos *arbolTitulos;
}Docente;

//Crea una estructura que representa un nodo de una lista enlazada de docentes.
typedef struct nodo_docente{
    Docente docente;
    struct nodo_docente *siguiente;
}Nodo_docente;

//Crea una estructura que representa a una universidad con los siguientes campos: id, nombre, ciudad, lista de docentes.
typedef struct{
    int id;
    char nombre[50];
    char ciudad[50];
    Nodo_docente *listaDocentes;
}Universidad;

//Crea un método para ordenar la lista de docentes de una universidad por id.
void ordenarListaDocentes(Universidad *universidad){
    Nodo_docente *nodoActual = universidad->listaDocentes;
    Nodo_docente *nodoSiguiente = nodoActual->siguiente;
    Nodo_docente *nodoAnterior = NULL;
    Nodo_docente *nodoAuxiliar = NULL;
    int flag = 1;
    while(flag){
        flag = 0;
        while(nodoSiguiente != NULL){
            if(nodoActual->docente.id > nodoSiguiente->docente.id){
                flag = 1;
                if(nodoAnterior == NULL){
                    nodoActual->siguiente = nodoSiguiente->siguiente;
                    nodoSiguiente->siguiente = nodoActual;
                    nodoAnterior = nodoSiguiente;
                    nodoSiguiente = nodoActual->siguiente;
                    universidad->listaDocentes = nodoSiguiente;
                }else{
                    nodoActual->siguiente = nodoSiguiente->siguiente;
                    nodoSiguiente->siguiente = nodoActual;
                    nodoAnterior->siguiente = nodoSiguiente;
                    nodoAnterior = nodoSiguiente;
                    nodoSiguiente = nodoActual->siguiente;
                }
            }else{
                nodoAnterior = nodoActual;
                nodoActual = nodoSiguiente;
                nodoSiguiente = nodoActual->siguiente;
            }
        }
        nodoAnterior = NULL;
        nodoActual = universidad->listaDocentes;
        nodoSiguiente = nodoActual->siguiente;
    }
}

//Crea un método para ordenar de forma equilibrada el arbol de titulos de un docente.
void ordenarArbolTitulos(Arbol_titulos *arbolTitulos){
    Arbol_titulos *nodoActual = arbolTitulos;
    Arbol_titulos *nodoSiguiente = nodoActual->derecha;
    Arbol_titulos *nodoAnterior = NULL;
    Arbol_titulos *nodoAuxiliar = NULL;
    int flag = 1;
    while(flag){
        flag = 0;
        while(nodoSiguiente != NULL){
            if(nodoActual->titulo.id > nodoSiguiente->titulo.id){
                flag = 1;
                if(nodoAnterior == NULL){
                    nodoActual->derecha = nodoSiguiente->derecha;
                    nodoSiguiente->derecha = nodoActual;
                    nodoAnterior = nodoSiguiente;
                    nodoSiguiente = nodoActual->derecha;
                    arbolTitulos = nodoSiguiente;
                }else{
                    nodoActual->derecha = nodoSiguiente->derecha;
                    nodoSiguiente->derecha = nodoActual;
                    nodoAnterior->derecha = nodoSiguiente;
                    nodoAnterior = nodoSiguiente;
                    nodoSiguiente = nodoActual->derecha;
                }
            }else{
                nodoAnterior = nodoActual;
                nodoActual = nodoSiguiente;
                nodoSiguiente = nodoActual->derecha;
            }
        }
        nodoAnterior = NULL;
        nodoActual = arbolTitulos;
        nodoSiguiente = nodoActual->derecha;
    }
}

int main(){
    printf("Hello World!\n");
    return 0;
}