#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"


int main(){
    int amount, opcion; //Declaración de variables
    caratula("Simulador de biblioteca"); //Llamada a la función caratula, dentro de esta función se encuentra el mensaje de presentación del simulador
    amount = ingreo_numeroentero("Ingrese la cantidad de libros", "Cantidad no valido, ingrese nuevamente", "Cantidad supero el limite, ingrese nuevamente", 0, MAX_BOOKS); //Se asigna a la variable amount la función ingreso_numeroentero la cual es la encargada de permitir una cantidad de libros por parte del usuario
    printf("\t------------------INFORMACION DE %d LIBROS-------------------\n", amount);
    //Se utiliza un ciclo y la funcion strcpy para que cada posición del arreglo de la estructura Books posea el mensaje de "Disponible"
    for (int i = 0; i < amount; i++){
        strcpy(libros[i].state, "Disponible");
    }
    //Se utliza un ciclo for para registrar la información de la cantidad de libros ingresados por el usuario
    for (int i = 0; i < amount; i++){
        libros[i].id = ingreso_codigo("Ingrese el ID del libro", "ID ya existente, ingrese nuevamente", "ID no valido, ingrese nuevamente un numero de 3 digitos", "ID supero el limite, ingrese nuevamente un numero de 3 digitos", i, 100, 999);
        while (getchar() != '\n'); //Se utiliza esta funcion para limpiar el buffer del teclado y permitir que la función ingreso_nombre funcione de manera correcta
        ingreso_nombre("Ingrese el titulo del libro", "Titulo no valido, ingrese nuevamente solo caracteres", libros[i].title, i + 1 );
        ingreso_nombre("Ingrese el autor del libro", "Autor no valido, ingrese nuevamente solo caracteres", libros[i].author, i+1);
        libros[i].publication = ingreso_datosstr("Ingrese el anio de publicacion del libro", "Anio no valido, ingrese nuevamente un anio entre 1925 y 2025", "Anio supero el limite, ingrese nuevamente un anio entre 1925 y 2025", i + 1, 1925, 2025);
        printf("El estado del libro %d es: %s\n", i + 1, libros[i].state);
        printf("----------------------------------------------------\n");
    }
    //Se utiliza el ciclo do-while para presentar una serie de acciones que pueden ser realizadas por el usuarios mientras no se ponga la opción de salida
    do{
        menu(); //Se llama a la funcion menu(), funcion la cual contiene todas las opciones que se pueden realizar
        opcion = ingreso_numeroopcion("Seleccione una opcion: ", 1, 6); //Se llama a la función ingreso_numeroopcion para permitir al usuario ingresar una de la opciones del menu, en caso que ingrese datos no validos se posee validaciones que evita que datos no deseados sean leídos y produzcan comportamientos no deseados
        switch (opcion){
        case 1:
            imprimir_informacion(amount); //LLamado a la función de imprimir_informacion para desplegar todos los datos de la biblioteca, los argumentos con una estructura y la cantidad de libros ingresados por el usuario
            break;  
        case 2:
            busqueda_libro(amount); //Llamado a la función de busqueda_libro para desplegar los 2 maneras de busqueda, ID o título
            break;
        case 3:
            cambiar_prestado(amount); //Llamado a la función cambiar_prestado, esta es la encargada de cambiar el estado del libro seleccionado a "Prestado"
            break;
        case 4:
            cambiar_disponible(amount); //Llamado a la función cambiar_disponible, esta es la encargada de cambiar el estado del libro a "Disponible" nuevamente
            break;
        case 5:
            busqueda_eliminar(amount); //Llamado a la función eliminar libro, encargada de borrar (reiniciar) los datos del libro
            break;
        default:
            break;
        }
        
    } while (opcion != 6);
    printf("\x1B[33mSALIENDO DEL PROGRAMA...\x1B[0m"); //Mensaje de salida 
    return 0;
}
