# EEDD-Final-Project
**0. Mostrar Docentes**
Esta opción muestra la lista de los ID´S de los docentes. Se usa para verificar que los 
docentes se hayan agregado correctamente.  
**1. Agregar Docente**
Opción que añade un nuevo docente pidiéndole todos los datos (id, nombre, apellido, 
edad, teléfono, ciudad) incluyendo poder asignarle varios títulos universitarios. Si el ID del 
docente ya existe, este no se agregará.  
**2. Buscar Docente**
Permite al usuario buscar a un docente por ID o NOMBRE, si el docente existe 
entonces se mostrará en pantalla toda la información personal y los títulos que este posee.
Sino existe, regresará al menú principal.  
**3. Eliminar Docente**
Esta opción eliminará a un docente según el ID que se le pida, si el docente existe, se 
eliminará y regresará el menú principal. Si no, solo regresará al menú principal.  
**4. Agregar Titulo**
Asigna un título a un docente según un ID, si el docente no existe se regresará al 
menú principal. Si este no es el caso, entonces le pedirá todos los datos importantes del título 
universitario como: ID, NOMBRE, UNIVERSIDAD, FECHA DE OBTENCIÓN. Si el ID 
coincide con los títulos que tiene el docente, entonces no sé agregará y mostrará en pantalla 
que ya existe.  
**5. Buscar Titulo**
Permite al usuario ver si un docente tiene un título en específico. Para esto busca al 
docente por ID o NOMBRE, si existe alguna coincidencia le pedirá el ID del título que desea observar. Si los ID no coinciden ya sea con los docentes en la Universidad o que el ID del 
título no esté en el docente a buscar mostrará que no existe.  
**6. Eliminar Título**
Está opción permite al usuario eliminar un título especifico de un docente según ID. 
Si existe el docente y el título, entonces se eliminará. Si alguno de los dos no existe entonces 
se regresará al menú principal.  
**7. Imprimir Lista Docentes**
Mostrará en pantalla todos los docentes de la universidad con toda su información 
personal y los títulos que tenga.  
**8. Imprimir Árbol de Títulos de un Docente**
Se mostrará de forma gráfica el árbol de títulos que tengo un docente. Siendo un árbol 
AVL.  
**9. Imprimir los Datos Completos de Cada Título de un Docente**
Pide el ID del docente e imprime los títulos en INORDEN junto con su información 
completa.  
**10. SALIR**
Sale del programa.