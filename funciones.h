#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_BOOKS 10
#define MAX_NAME 100
#define MAX_AUTHOR 50
#define MAX_STATE 20

//Estructura del programa
struct Books {
    int id;
    char title[MAX_NAME];
    char author[MAX_AUTHOR];
    int publication;
    char state[MAX_STATE];
} extern libros[MAX_BOOKS];

#endif 

//Lecturas
void caratula(char *message);
int nombre_valido(const char *name);
int codigo_repetido(int amount, int new_id);
void menu();
int ingreso_numeroopcion(char *message, int min, int max);
int ingreo_numeroentero(char *message, char *validation, char *limit, int min, int max);
int ingreso_datosstr(char *message, char *validation, char *limit, int position, int min, int max);
void ingreso_nombre(char *message, char *validation, char info[], int position);
int ingreso_codigo(char *meessage, char *repeat, char *validation, char *limit, int position, int min, int max);
void leer_busqueda(char consult[]);

//Funciones para el taller
void imprimir_informacion(int amount);
void busqueda_libro(int amount);
void cambiar_prestado(int amount);
void cambiar_disponible(int amount);
void eliminar_libro();
void busqueda_eliminar(int amount);