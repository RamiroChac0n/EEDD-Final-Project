#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    Fecha anioObtencion;
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

//Crea un método para buscar un docente segun id en una universidad y retornar el docente.
Docente buscarDocente(Universidad *universidad){
    int id;
    printf("Ingrese el id del docente:\n");
    scanf("%d", &id);
    Nodo_docente *nodoActual = universidad->listaDocentes;
    while(nodoActual != NULL){
        if(nodoActual->docente.id == id){
            printf("%p\n", nodoActual);
            return nodoActual->docente;
        }
        nodoActual = nodoActual->siguiente;
    }
    printf("El id del docente no existe.\n");
    printf("%p\n", nodoActual);
}


//Crea un método para agregar un docente en orden segun id en una universidad.
void agregarDocente(Universidad *universidad){
    Nodo_docente *nodoActual = universidad->listaDocentes;
    Nodo_docente *nodoAnterior = NULL;
    Nodo_docente *nodoNuevo = (Nodo_docente*)malloc(sizeof(Nodo_docente));
    printf("Ingrese el id del docente:\n");
    scanf("%d", &nodoNuevo->docente.id);
    fflush(stdin);
    printf("Ingrese el nombre del docente:\n");
    fgets(nodoNuevo->docente.nombre, 50, stdin);
    printf("Ingrese el apellido del docente:\n");
    fgets(nodoNuevo->docente.apellido, 50, stdin);
    printf("Ingrese la edad del docente:\n");
    scanf("%d", &nodoNuevo->docente.edad);
    fflush(stdin);
    printf("Ingrese el telefono del docente:\n");
    fgets(nodoNuevo->docente.telefono, 50, stdin);
    printf("Ingrese la ciudad del docente:\n");
    fgets(nodoNuevo->docente.ciudad, 50, stdin);
    nodoNuevo->siguiente = NULL;
    if(nodoActual == NULL){
        universidad->listaDocentes = nodoNuevo;
        return;
    }
    while(nodoActual != NULL){
        if(nodoActual->docente.id > nodoNuevo->docente.id){
            if(nodoAnterior == NULL){
                nodoNuevo->siguiente = nodoActual;
                universidad->listaDocentes = nodoNuevo;
                return;
            }else{
                nodoNuevo->siguiente = nodoActual;
                nodoAnterior->siguiente = nodoNuevo;
                return;
            }
        }
        nodoAnterior = nodoActual;
        nodoActual = nodoActual->siguiente;
    }
    nodoAnterior->siguiente = nodoNuevo;
}

//Crea un método para eliminar un docente de una universidad segun un id.
void eliminarDocente(Universidad *universidad){
    int id;
    printf("Ingrese el id del docente:\n");
    scanf("%d", &id);
    Nodo_docente *nodoActual = universidad->listaDocentes;
    Nodo_docente *nodoAnterior = NULL;
    while(nodoActual != NULL){
        if(nodoActual->docente.id == id){
            if(nodoAnterior == NULL){
                universidad->listaDocentes = nodoActual->siguiente;
            }else{
                nodoAnterior->siguiente = nodoActual->siguiente;
            }
            free(nodoActual);
            printf("El docente se elimino correctamente.\n");
            return;
        }
        nodoAnterior = nodoActual;
        nodoActual = nodoActual->siguiente;
    }
    printf("El id del docente no existe.\n");
}

/* ******* TEST ******* */
//Crea un metodo que imprima todos los docentes de una universidad.
void mostrarDocentes(Universidad *universidad){
    Nodo_docente *nodoActual = universidad->listaDocentes;
    while(nodoActual != NULL){
        printf("%d->", nodoActual->docente.id);
        nodoActual = nodoActual->siguiente;
    }
}

void docentesQuemados(Universidad *universidad){
    //Docente 1
    Nodo_docente *docente1 = (Nodo_docente*)malloc(sizeof(Nodo_docente));
    docente1->docente.id = 5;
    strcpy(docente1->docente.nombre, "Juan");
    strcpy(docente1->docente.apellido, "Perez");
    docente1->docente.edad = 30;
    strcpy(docente1->docente.telefono, "123456");
    strcpy(docente1->docente.ciudad, "Cochabamba");
    //Docente 2
    Nodo_docente *docente2 = (Nodo_docente*)malloc(sizeof(Nodo_docente));
    docente2->docente.id = 10;
    strcpy(docente2->docente.nombre, "Maria");
    strcpy(docente2->docente.apellido, "Lopez");
    docente2->docente.edad = 25;
    strcpy(docente2->docente.telefono, "123456");
    strcpy(docente2->docente.ciudad, "Cochabamba");
    //Docente 3
    Nodo_docente *docente3 = (Nodo_docente*)malloc(sizeof(Nodo_docente));
    docente3->docente.id = 15;
    strcpy(docente3->docente.nombre, "Pedro");
    strcpy(docente3->docente.apellido, "Gomez");
    docente3->docente.edad = 35;
    strcpy(docente3->docente.telefono, "123456");
    strcpy(docente3->docente.ciudad, "Cochabamba");
    docente1->siguiente = docente2;
    docente2->siguiente = docente3;
    docente3->siguiente = NULL;
    universidad->listaDocentes = docente1;
}
/* ******* TEST ******* */

int main(){
    //Haz un menú para agregar, eliminar, mostrar y ordenar docentes.
    Universidad *universidad = (Universidad*)malloc(sizeof(Universidad));
    universidad->listaDocentes = NULL;

    docentesQuemados(universidad);

    int opcion;
    do{
        printf("\n0. Mostrar docentes.\n");
        printf("1. Agregar docente.\n");
        printf("2. Buscar docente\n");
        printf("3. Eliminar docene.\n");
        printf("5. SALIR.\n");
        printf("Ingrese una opcion:\n");
        scanf("%d", &opcion);
        switch(opcion){
            case 0:
                mostrarDocentes(universidad);
                break;
            case 1:
                agregarDocente(universidad);
                break;
            case 2:
                buscarDocente(universidad);
                break;
            case 3:
                eliminarDocente(universidad);
                break;
            case 5:
                printf("Adios.\n");
                break;
            default:
                printf("Opcion invalida.\n");
                break;
        };
    }while(opcion != 5);
    return 0;
}