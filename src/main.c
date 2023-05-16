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

//Crea un nodo de un arbol binario de titulos universitarios.
typedef struct nodo_titulos{
    Titulo titulo;
    int altura;
    struct nodo_titulos *izquierda;
    struct nodo_titulos *derecha;
}Nodo_titulos;

//Crea una estructura que representa a un docente con los siguientes campos: id, nombre, apellido, edad, telefono, ciudad, arbol de titulos universitarios.
typedef struct{
    int id;
    char nombre[50];
    char apellido[50];
    int edad;
    char telefono[50];
    char ciudad[50];
    Nodo_titulos *arbolTitulos;
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

/*********** Arbol de titulos *************/
int max(int a, int b) {
    return (a > b) ? a : b;
}

int altura(Nodo_titulos *nodo) {
    if (nodo == NULL)
        return 0;
    return nodo->altura;
}

Nodo_titulos* nuevoNodo(Nodo_titulos *nodo_padre, int id, char nombre[50], char universidad[50], Fecha anioObtencion) {
    Nodo_titulos* nodo = (Nodo_titulos*)malloc(sizeof(Nodo_titulos));
    nodo->titulo.id = id;
    strcpy(nodo->titulo.nombre, nombre);
    strcpy(nodo->titulo.universidad, universidad);
    nodo->titulo.anioObtencion = anioObtencion;
    nodo->izquierda = NULL;
    nodo->derecha = NULL;
    nodo->altura = 1;
    return nodo;
}

Nodo_titulos *rotacionDerecha(Nodo_titulos *y) {
    Nodo_titulos *x = y->izquierda;
    Nodo_titulos *T2 = x->derecha;

    x->derecha = y;
    y->izquierda = T2;

    y->altura = max(altura(y->izquierda), altura(y->derecha)) + 1;
    x->altura = max(altura(x->izquierda), altura(x->derecha)) + 1;

    return x;
}

Nodo_titulos *rotacionIzquierda(Nodo_titulos *x) {
    Nodo_titulos *y = x->derecha;
    Nodo_titulos *T2 = y->izquierda;

    y->izquierda = x;
    x->derecha = T2;

    x->altura = max(altura(x->izquierda), altura(x->derecha)) + 1;
    y->altura = max(altura(y->izquierda), altura(y->derecha)) + 1;

    return y;
}

int balance(Nodo_titulos *nodo) {
    if (nodo == NULL)
        return 0;
    return altura(nodo->izquierda) - altura(nodo->derecha);
}

Nodo_titulos* insertar_titulo(Nodo_titulos* nodo, int clave, char nombre[50], char universidad[50], Fecha anioObtencion) {
    if (nodo == NULL)
        return (nuevoNodo(nodo, clave, nombre, universidad, anioObtencion)); //Crea un nuevo nodo si el arbol esta vacio.

    if (clave < nodo->titulo.id)
        nodo->izquierda = insertar_titulo(nodo->izquierda, clave, nombre, universidad, anioObtencion);
    else if (clave > nodo->titulo.id)
        nodo->derecha = insertar_titulo(nodo->derecha, clave, nombre, universidad, anioObtencion);
    else
        return nodo;

    nodo->altura = 1 + max(altura(nodo->izquierda), altura(nodo->derecha));

    int balanceo = balance(nodo);

    if (balanceo > 1 && clave < nodo->izquierda->titulo.id)
        return rotacionDerecha(nodo);

    if (balanceo < -1 && clave > nodo->derecha->titulo.id)
        return rotacionIzquierda(nodo);

    if (balanceo > 1 && clave > nodo->izquierda->titulo.id) {
        nodo->izquierda = rotacionIzquierda(nodo->izquierda);
        return rotacionDerecha(nodo);
    }

    if (balanceo < -1 && clave < nodo->derecha->titulo.id) {
        nodo->derecha = rotacionDerecha(nodo->derecha);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}
/******************************************/

//Busca un titulo en un arbol de titulos y retorna.
Nodo_titulos* buscarTitulo(Nodo_titulos *nodo, int idTitulo){
    if(nodo == NULL){
        return NULL;
    }
    if(nodo->titulo.id == idTitulo){
        return nodo;
    }
    if(idTitulo < nodo->titulo.id){
        return buscarTitulo(nodo->izquierda, idTitulo);
    }
    return buscarTitulo(nodo->derecha, idTitulo);
}

//Crea un método para crear un titulo universitario y agregarlo al arbol de titulos de un docente de una universidad.
void agregarTitulo(Universidad *Universidad){
    int idDocente, idTitulo;
    Nodo_docente *nodoDocente = Universidad->listaDocentes;
    Nodo_titulos *nodoTitulos;
    printf("Ingrese el id del docente:\n");
    scanf("%d", &idDocente);
    fflush(stdin);
    while(nodoDocente != NULL){
        if(nodoDocente->docente.id == idDocente){
            printf("Ingrese el id del titulo:\n");
            scanf("%d", &idTitulo);
            fflush(stdin);
            // Verifica si el titulo ya existe.
            if(buscarTitulo(nodoDocente->docente.arbolTitulos, idTitulo) != NULL){
                printf("El titulo ya existe.\n");
                return;
            }
            nodoTitulos = (Nodo_titulos*)malloc(sizeof(Nodo_titulos)); // Asignación de memoria
            nodoTitulos->titulo.id = idTitulo; // Asigna el id del título

            printf("Ingrese el nombre del titulo:\n");
            fgets(nodoTitulos->titulo.nombre, 50, stdin);
            nodoTitulos->titulo.nombre[strcspn(nodoTitulos->titulo.nombre, "\n")] = '\0'; // Elimina el carácter de nueva línea

            printf("Ingrese el nombre de la universidad:\n");
            fgets(nodoTitulos->titulo.universidad, 50, stdin);
            nodoTitulos->titulo.universidad[strcspn(nodoTitulos->titulo.universidad, "\n")] = '\0'; // Elimina el carácter de nueva línea

            printf("Ingrese el dia de obtencion:\n");
            scanf("%d", &nodoTitulos->titulo.anioObtencion.dia);

            printf("Ingrese el mes de obtencion:\n");
            scanf("%d", &nodoTitulos->titulo.anioObtencion.mes);

            printf("Ingrese el anio de obtencion:\n");
            scanf("%d", &nodoTitulos->titulo.anioObtencion.anio);

            nodoTitulos = insertar_titulo(nodoDocente->docente.arbolTitulos, idTitulo, nodoTitulos->titulo.nombre, nodoTitulos->titulo.universidad, nodoTitulos->titulo.anioObtencion);
            nodoDocente->docente.arbolTitulos = nodoTitulos;
            printf("Titulo agregado correctamente.\n");
            return;

        }
        nodoDocente = nodoDocente->siguiente;
    }
    printf("No se encontro el docente.\n");
}


//Método para mostrar la información de un titulo.
void mostrarTitulo(Titulo titulo){
    printf("%-5d", titulo.id);
    printf("%-50s", titulo.nombre);
    printf("%-50s", titulo.universidad);
    printf("%02d/%02d/%04d\n", titulo.anioObtencion.dia, titulo.anioObtencion.mes, titulo.anioObtencion.anio);
}


//Crea un método para mostrar los id de los titulos en forma de arbol binario.
void mostrarArbolTitulosID(Nodo_titulos *nodo){
    if(nodo != NULL){
        mostrarArbolTitulosID(nodo->izquierda);
        printf("%d ", nodo->titulo.id);
        mostrarArbolTitulosID(nodo->derecha);
    }
}

//Muestra los titulos de un docente.
void mostrarTitulos(Nodo_titulos *nodo) {
    if (nodo != NULL) {
        mostrarTitulos(nodo->izquierda);
        mostrarTitulo(nodo->titulo);
        mostrarTitulos(nodo->derecha);
    }
}

//Imprime la informacion de un docente.
void imprimirDocente(Docente docente){
    printf("\n\n------------- Información -------------------\n\n");
    printf("Id: %d\n", docente.id);
    printf("Nombre: %s ", docente.nombre);
    printf("Apellido: %s ", docente.apellido);
    printf("Edad: %d\n", docente.edad);
    printf("Telefono: %s ", docente.telefono);
    printf("Ciudad: %s\n", docente.ciudad);
    printf("\n--------------- Titulos ---------------------\n");
    //Recorre el arbol de titulos y muestra la informacion de cada titulo.
    mostrarTitulos(docente.arbolTitulos);
    printf("---------------------------------------------\n");
}

//Crea un método para buscar un docente segun id en una universidad y retornar el docente.
Docente buscarDocente(Universidad *universidad){
    Nodo_docente *nodoActual = universidad->listaDocentes;
    int opcion;
    printf("\nIngrese la opcion de busqueda:\n");
    printf("1. Por id.\n");
    printf("2. Por nombre.\n");
    printf("Cualquier otro numero para salir.\n");
    scanf("%d", &opcion);
    fflush(stdin);
    switch (opcion)
    {
    case 1:
        int id;
        printf("Ingrese el id del docente:\n");
        scanf("%d", &id);
        fflush(stdin);
        while(nodoActual != NULL){
            if(nodoActual->docente.id == id){
                imprimirDocente(nodoActual->docente);            
            }
            nodoActual = nodoActual->siguiente;
        }
        break;
    case 2:
        char nombre[50];
        printf("Ingrese el nombre del docente:\n");
        fgets(nombre, 50, stdin);
        nombre[strcspn(nombre, "\n")] = '\0';
        fflush(stdin);
        while(nodoActual != NULL){
            if(strcmp(nodoActual->docente.nombre, nombre) == 0){
                imprimirDocente(nodoActual->docente);           
            }
            nodoActual = nodoActual->siguiente;
        }
        break;
    default:
        break;
    }
}
//Crea un metodo que busca a un docente por id.
Nodo_docente *buscarDocentePorId(Universidad *universidad, int id){
    Nodo_docente *nodoActual = universidad->listaDocentes;
    while(nodoActual != NULL){
        if(nodoActual->docente.id == id){
            return nodoActual;
        }
        nodoActual = nodoActual->siguiente;
    }
    return NULL;
}

//Crea un método para agregar un docente en orden segun id en una universidad.
void agregarDocente(Universidad *universidad){
    Nodo_docente *nodoActual = universidad->listaDocentes;
    Nodo_docente *nodoAnterior = NULL;
    Nodo_docente *nodoNuevo = (Nodo_docente*)malloc(sizeof(Nodo_docente));
    printf("Ingrese el id del docente:\n");
    scanf("%d", &nodoNuevo->docente.id);
    fflush(stdin);
    if(buscarDocentePorId(universidad, nodoNuevo->docente.id) != NULL){
        printf("El id del docente ya existe.\n");
        return;
    }
    printf("Ingrese el nombre del docente:\n");
    fgets(nodoNuevo->docente.nombre, 50, stdin);
    nodoNuevo->docente.nombre[strcspn(nodoNuevo->docente.nombre, "\n")] = '\0';
    printf("Ingrese el apellido del docente:\n");
    fgets(nodoNuevo->docente.apellido, 50, stdin);
    nodoNuevo->docente.apellido[strcspn(nodoNuevo->docente.apellido, "\n")] = '\0';
    printf("Ingrese la edad del docente:\n");
    scanf("%d", &nodoNuevo->docente.edad);
    fflush(stdin);
    printf("Ingrese el telefono del docente:\n");
    fgets(nodoNuevo->docente.telefono, 50, stdin);
    nodoNuevo->docente.telefono[strcspn(nodoNuevo->docente.telefono, "\n")] = '\0';
    printf("Ingrese la ciudad del docente:\n");
    fgets(nodoNuevo->docente.ciudad, 50, stdin);
    nodoNuevo->docente.ciudad[strcspn(nodoNuevo->docente.ciudad, "\n")] = '\0';
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
        printf("%d", nodoActual->docente.id);
        printf("->");
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
    //Agrega un titulo al docente 1
    Nodo_titulos *titulo1 = (Nodo_titulos*)malloc(sizeof(Nodo_titulos));
    titulo1->titulo.id = 10;
    strcpy(titulo1->titulo.nombre, "Licenciatura en Sistemas");
    strcpy(titulo1->titulo.universidad, "UMSS");
    titulo1->titulo.anioObtencion.dia = 1;
    titulo1->titulo.anioObtencion.mes = 1;
    titulo1->titulo.anioObtencion.anio = 2010;
    //Agrega otro titulo al docente 1
    Nodo_titulos *titulo2 = (Nodo_titulos*)malloc(sizeof(Nodo_titulos));
    titulo2->titulo.id = 20;
    strcpy(titulo2->titulo.nombre, "Ingenieria en Sistemas");
    strcpy(titulo2->titulo.universidad, "San Simon");
    titulo2->titulo.anioObtencion.dia = 1;
    titulo2->titulo.anioObtencion.mes = 1;
    titulo2->titulo.anioObtencion.anio = 2000;
    //Agrega otro titulo al docente 1
    Nodo_titulos *titulo3 = (Nodo_titulos*)malloc(sizeof(Nodo_titulos));
    titulo3->titulo.id = 30;
    strcpy(titulo3->titulo.nombre, "Maestria en Sistemas");
    strcpy(titulo3->titulo.universidad, "Universitat de Barcelona");
    titulo3->titulo.anioObtencion.dia = 1;
    titulo3->titulo.anioObtencion.mes = 1;
    titulo3->titulo.anioObtencion.anio = 2015;
    titulo2->izquierda = titulo1;
    titulo2->derecha = titulo3;
    docente1->docente.arbolTitulos = titulo2;

    //Docente 2
    Nodo_docente *docente2 = (Nodo_docente*)malloc(sizeof(Nodo_docente));
    docente2->docente.id = 10;
    strcpy(docente2->docente.nombre, "Maria");
    strcpy(docente2->docente.apellido, "Lopez");
    docente2->docente.edad = 25;
    strcpy(docente2->docente.telefono, "123456");
    strcpy(docente2->docente.ciudad, "Cochabamba");
    //Agregar un titulo al docente 2
    Nodo_titulos *titulo4 = (Nodo_titulos*)malloc(sizeof(Nodo_titulos));
    titulo4->titulo.id = 10;
    strcpy(titulo4->titulo.nombre, "Licenciatura en Sistemas");
    strcpy(titulo4->titulo.universidad, "UMSS");
    titulo4->titulo.anioObtencion.dia = 1;
    titulo4->titulo.anioObtencion.mes = 1;
    titulo4->titulo.anioObtencion.anio = 2010;
    //Agregar otro titulo al docente 2
    Nodo_titulos *titulo5 = (Nodo_titulos*)malloc(sizeof(Nodo_titulos));
    titulo5->titulo.id = 20;
    strcpy(titulo5->titulo.nombre, "Ingenieria en Sistemas");
    strcpy(titulo5->titulo.universidad, "San Simon");
    titulo5->titulo.anioObtencion.dia = 1;
    titulo5->titulo.anioObtencion.mes = 1;
    titulo5->titulo.anioObtencion.anio = 2000;
    //Agregar otro titulo al docente 2
    Nodo_titulos *titulo6 = (Nodo_titulos*)malloc(sizeof(Nodo_titulos));
    titulo6->titulo.id = 30;
    strcpy(titulo6->titulo.nombre, "Maestria en Sistemas");
    strcpy(titulo6->titulo.universidad, "Universitat de Barcelona");
    titulo6->titulo.anioObtencion.dia = 1;
    titulo6->titulo.anioObtencion.mes = 1;
    titulo6->titulo.anioObtencion.anio = 2015;
    titulo5->izquierda = titulo4;
    titulo5->derecha = titulo6;
    docente2->docente.arbolTitulos = titulo5;

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
    //Agrega un titulo al docente 3
    Nodo_titulos *titulo7 = (Nodo_titulos*)malloc(sizeof(Nodo_titulos));
    titulo7->titulo.id = 10;
    strcpy(titulo7->titulo.nombre, "Licenciatura en Sistemas");
    strcpy(titulo7->titulo.universidad, "UMSS");
    titulo7->titulo.anioObtencion.dia = 1;
    titulo7->titulo.anioObtencion.mes = 1;
    titulo7->titulo.anioObtencion.anio = 2010;
    //Agregar otro titulo al docente 3
    Nodo_titulos *titulo8 = (Nodo_titulos*)malloc(sizeof(Nodo_titulos));
    titulo8->titulo.id = 20;
    strcpy(titulo8->titulo.nombre, "Ingenieria en Sistemas");
    strcpy(titulo8->titulo.universidad, "San Simon");
    titulo8->titulo.anioObtencion.dia = 1;
    titulo8->titulo.anioObtencion.mes = 1;
    titulo8->titulo.anioObtencion.anio = 2000;
    //Agregar otro titulo al docente 3
    Nodo_titulos *titulo9 = (Nodo_titulos*)malloc(sizeof(Nodo_titulos));
    titulo9->titulo.id = 30;
    strcpy(titulo9->titulo.nombre, "Maestria en Sistemas");
    strcpy(titulo9->titulo.universidad, "Universitat de Barcelona");
    titulo9->titulo.anioObtencion.dia = 1;
    titulo9->titulo.anioObtencion.mes = 1;
    titulo9->titulo.anioObtencion.anio = 2015;
    //Agrega otro titulo al docente 3
    Nodo_titulos *titulo10 = (Nodo_titulos*)malloc(sizeof(Nodo_titulos));
    titulo10->titulo.id = 25;
    strcpy(titulo10->titulo.nombre, "Doctorado en Sistemas");
    strcpy(titulo10->titulo.universidad, "Universitat de Barcelona");
    titulo10->titulo.anioObtencion.dia = 1;
    titulo10->titulo.anioObtencion.mes = 1;
    titulo10->titulo.anioObtencion.anio = 2017;
    titulo9->izquierda = titulo10;
    titulo8->izquierda = titulo7;
    titulo8->derecha = titulo9;
    docente3->docente.arbolTitulos = titulo8;
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
        printf("3. Eliminar docente.\n");
        printf("4. Agregar título.\n");
        printf("5. Buscar título.\n");
        printf("6. Eliminar título.\n");
        printf("7. Imprimir lista de Docentes.\n");
        printf("8. Imprimir arbol de títulos de un medico.\n");
        printf("9. Imprimir los datos completos de cada titulo de un docente.\n");
        printf("10. SALIR.\n");
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
            case 4:
                agregarTitulo(universidad);
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            case 10:
                printf("Adios.\n");
                break;
            default:
                printf("Opcion invalida.\n");
                break;
        };
    }while(opcion != 10);
    return 0;
}