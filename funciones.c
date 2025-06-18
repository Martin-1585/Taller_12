#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"

struct Books libros[MAX_BOOKS];

//Funciones de lectura 
void caratula(char *message){
    printf("\t\x1B[34m**************************\x1B[0m\n");
    printf("\t\x1B[35m%s\x1B[0m\n", message);
    printf("\t\x1B[34m**************************\x1B[0m\n");
}

int ingreo_numeroentero(char *message, char *validation, char *limit, int min, int max){
    int valido, value;
    do{
        printf("%s (%d - %d): ",message, min, max);
        valido = scanf("%d", &value);
        if (valido != 1 || value <= min){
            printf("\x1B[31m%s\x1B[0m\n", validation);
            while(getchar() != '\n');
        }else if (value > max){
            printf("\x1B[33m%s\x1B[0m\n", limit);
            while(getchar() != '\n');
        }else{}
    } while (valido != 1 || value <= min || value > max);
    return value;
}

int ingreso_datosstr(char *message, char *validation, char *limit, int position, int min, int max){
    int valido, value;
    do{
        printf("%s %d (entre %d - %d): ",message, position, min, max);
        valido = scanf("%d", &value);
        if (valido != 1 || value < min){
            printf("\x1B[31m%s\x1B[0m\n", validation);
            while(getchar() != '\n');
        }else if (value > max){
            printf("\x1B[33m%s\x1B[0m\n", limit);
            while(getchar() != '\n');
        } else{}
    } while (valido != 1 || value < min || value > max);
    return value;
}

void ingreso_nombre(char *message, char *validation, char info[], int position){
    do{
        printf("%s %d: ", message, position);
        fgets(info, MAX_NAME, stdin);
        info[strcspn(info, "\n")] = '\0';
        if (!nombre_valido(info)){
            printf("\x1B[31m%s\x1B[0m\n", validation);
        }
    } while (!nombre_valido(info));
}

int ingreso_codigo(char *meessage, char *repeat, char *validation, char *limit, int position, int min, int max){
    int valido, value;
    do{
        printf("%s %d (numero de 3 digitos): ", meessage, position + 1);
        valido = scanf("%d", &value);
        if (codigo_repetido(position, value)){
            printf("\x1B[33m%s\x1B[0m\n", repeat);
            while(getchar() != '\n');
        } else if (valido != 1 || value <= min){
            printf("\x1B[31m%s\x1B[0m\n", validation);
            while(getchar() != '\n');
        } else if (value > max){
            printf("\x1B[33m%s\x1B[0m\n", limit);
            while(getchar() != '\n');
        } else {}
    } while (codigo_repetido(position, value) || valido != 1 || value <= min || value > max);
    return value;
}

int nombre_valido(const char *name){
    for (int i = 0; name[i] != '\0'; i++){
        if (!isalpha((unsigned char)name[i]) && name[i] != ' '){
            return 0;
        }
    }
    return 1;
}

int codigo_repetido(int amount, int new_id){
    for (int i = 0; i < amount; i++){
        if (libros[i].id == new_id){
            return 1;
        }
    }
    return 0;
}

void menu(){
    printf("\t\t\x1B[33mMENU DE ACCIONES\x1B[0m\n");
    printf("1. Mostrar la informacion completa de los libros\n");
    printf("2. Busqueda de libro\n");
    printf("3. Rentar libro \n");
    printf("4. Devolver libro\n");
    printf("5. Eliminar libro\n");
    printf("6. SALIR\n");
}

int ingreso_numeroopcion(char *message, int min, int max){
    int value;
    printf("\n%s", message);
    while(scanf("%d", &value) != 1 || value < min || value > max){
        printf("\x1B[31mOPCION NO VALIDO, INGRESE NUEVAMENTE\x1B[0m\n");
        while(getchar()  != '\n');
        printf("%s", message);
    }
    return value;
}

void leer_busqueda(char consult[]){
    do{
        printf("Ingrese el titulo del libro a buscar: ");
        fgets(consult, MAX_NAME, stdin);
        consult[strcspn(consult, "\n")] = '\0';
        if (!nombre_valido(consult)){
            printf("\x1B[31mTitulo no valido, ingrese nuevamente\x1B[0m\n");
        }
    } while (!nombre_valido(consult));
}

//Funciones del taller
void imprimir_informacion(int amount){
    printf("\n\x1B[33m%-10s | %-20s | %-20s | %-20s | %-20s\x1B[0m\n", "ID", "Titulo", "Autor", "Anio", "Estado");
    printf("------------------------------------------------------------------------------------\n");    
    for (int i = 0; i < amount; i++){
        if (libros[i].id != 0){
            printf("%-10d | %-20s | %-20s | %-20d | %-20s\n", libros[i].id, libros[i].title, libros[i].author, libros[i].publication, libros[i].state);
        }        
    }
    printf("\n");
}

void busqueda_libro(int amount){
    int id, found = 0, option;
    char search[MAX_NAME];
    printf("\x1B[33m%-10s | %-20s\x1B[0m\n", "ID", "Titulo");
    printf("------------------------------\n");
    for (int i = 0; i < amount; i++){
        if (libros[i].id != 0){
            printf("%-10d | %-20s\n", libros[i].id, libros[i].title);
        }
    }
    printf("\n");
    printf("\t\t\x1B[33mMANERAS DE BUSQUEDA\x1B[0m\n\n");
    printf("1. ID\n");
    printf("2. TItulo\n");
    option = ingreso_numeroopcion("Seleccione una opcion de busqueda: ", 1, 2);
    getchar();
    switch (option){
    case 1:
        id = ingreo_numeroentero("Ingrese el ID del libro", "Dato no valido, ingrese nuevamente", "Supero el limite, ingrese nuevamente", 100, 999);
        for (int i = 0; i < amount; i++){
            if (libros[i].id == id){
                found = 1;
                printf("\t\x1B[33mLIBRO ENCONTRADO\x1B[0m\n");
                printf("ID: %d\n", libros[i].id);
                printf("Titulo: %s\n", libros[i].title);
                printf("Autor: %s\n", libros[i].author);
                printf("Anio de publicacion: %d\n", libros[i].publication);
                printf("Estado: %s\n", libros[i].state);
                break;
            }
        }

        if (!found){
            printf("Libro no registrado\n");
        }
        break;
    case 2:
        leer_busqueda(search);
        for (int i = 0; i < amount; i++){
            if (strcasecmp(libros[i].title, search) == 0){
                found = 1;
                printf("\t\x1B[33mLIBRO ENCONTRADO\x1B[0m\n");
                printf("ID: %d\n", libros[i].id);
                printf("Titulo: %s\n", libros[i].title);
                printf("Autor: %s\n", libros[i].author);
                printf("Anio de publicacion: %d\n", libros[i].publication);
                printf("Estado: %s\n", libros[i].state);
                break;
            }
        }

        if (!found){
            printf("Libro no registrado\n");
        }
        break;
    default:
        break;
    }

}

void cambiar_prestado(int amount){
    int id_search, found = 0;

    printf("\x1B[33m%-10s | %-20s\x1B[0m\n", "ID", "Titulo");
    printf("------------------------------\n");
    for (int i = 0; i < amount; i++){
        if (libros[i].id != 0){
            printf("%-10d | %-20s\n", libros[i].id, libros[i].title);
        }
    }
    id_search = ingreo_numeroentero("Ingrese el ID del libro que desea tomar", "Dato no valido, ingrese nuevamente", "Supero el limite, ingrese nuevamente", 100, 999);

    for (int i = 0; i < amount; i++){
        if (libros[i].id == id_search){
            found = 1;
            if (strcmp(libros[i].state, "Disponible") == 0){
                strcpy(libros[i].state, "Prestado");
                printf("\t\x1B[33mLIBRO ACTUALIZADO\x1B[0m\n");
                printf("ID: %d\n", libros[i].id);
                printf("Titulo: %s\n", libros[i].title);
                printf("Autor: %s\n", libros[i].author);
                printf("Anio de publicacion: %d\n", libros[i].publication);
                printf("Estado: %s\n", libros[i].state);
                break;
            } else {
                printf("\x1B[33mEl ID ingresado pertenece a un libro prestado\x1B[0m\n\n");
            } 
        }
    }

    if (!found){
        printf("Libro no registrado\n");
    }
}

void cambiar_disponible(int amount){
    int id_search, found = 0;

    printf("\x1B[33m%-10s | %-20s\x1B[0m\n", "ID", "Titulo");
    printf("------------------------------\n");
    for (int i = 0; i < amount; i++){
        if (libros[i].id != 0){
            printf("%-10d | %-20s\n", libros[i].id, libros[i].title);
        }
    }
    id_search = ingreo_numeroentero("Ingrese el ID del libro que desea regresar", "Dato no valido, ingrese nuevamente", "Supero el limite, ingrese nuevamente", 100, 999);

    for (int i = 0; i < amount; i++){
        if (libros[i].id == id_search){
            found = 1;
            if (strcmp(libros[i].state, "Prestado") == 0){
                strcpy(libros[i].state, "Disponible");
                printf("\t\x1B[33mLIBRO ACTUALIZADO\x1B[0m\n");
                printf("ID: %d\n", libros[i].id);
                printf("Titulo: %s\n", libros[i].title);
                printf("Autor: %s\n", libros[i].author);
                printf("Anio de publicacion: %d\n", libros[i].publication);
                printf("Estado: %s\n", libros[i].state);
                break;
            } else {
                printf("\x1B[33mEl ID ingresado pertenece a un libro disponible\x1B[0m\n\n");
            } 
        }
    }

    if (!found){
        printf("Libro no registrado\n");
    }
}

void eliminar_libro(){
    libros -> id = 0;
    for (int i = 0; i < MAX_NAME; i++){
        libros -> title[i] = '\0';
    }
    for (int i = 0; i < MAX_AUTHOR; i++){
        libros -> author[i] = '\0';
    }
    libros -> publication = 0;

    for (int i = 0; i < MAX_STATE; i++){
        libros -> state[i] = '\0';
    }
    
}

void busqueda_eliminar(int amount){
    int id_search, found = 0;
    printf("\x1B[33m%-10s | %-20s\x1B[0m\n", "ID", "Titulo");
    printf("------------------------------\n");
    for (int i = 0; i < amount; i++){
        if (libros[i].id != 0){
            printf("%-10d | %-20s\n", libros[i].id, libros[i].title);
        }
    }

    id_search = ingreo_numeroentero("Ingrese el ID del libro a eliminar", "Dato no valido, ingrese nuevamente", "Supero el limite, ingrese nuevamente", 100, 999);

    for (int i = 0; i < amount; i++){
        if (libros[i].id == id_search){
            found = 1;
            if (strcmp(libros[i].state, "Prestado") == 0){
                printf("\x1B[33mLibro prestado no se puede eliminar\x1B[0m\n");
                break;
            }
            eliminar_libro(&libros[i]);
            printf("Libro eliminado\n");
            break;
        }
    }

    if (!found){
        printf("Libro no registrado\n");
    }
}