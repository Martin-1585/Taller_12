#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
#define MAX_NAME 100
#define MAX_AUTHOR 50
#define MAX_STATE 20
#define FILE_NAME "libros.txt"
#define TMP_FILE "tmp_libros.txt"
 
struct Books {
    int id;
    char title[MAX_NAME];
    char author[MAX_AUTHOR];
    int publication;
    char state[MAX_STATE];
};
 
// Prototipos
void caratula(const char *message);
int ingreso_numeroopcion(char *msg, int min, int max);
int ingreso_entero(char *msg, int min, int max);
void ingreso_informacion(char *msg, char *buf, char *validation, int max);
int nombre_valido(const char *s);
int existe_id(int id);
void imprimir_informacion();
void agregar_libro();
void buscar_libro();
void prestar_libro();
void devolver_libro();
void editar_libro();
void eliminar_libro();
 
int main() {
    caratula("Simulador de Biblioteca");
    int option;
    do {
        printf("\t\x1B[32mMENU DE OPCIONES\x1B[0m\n");
        printf("1. Agregar libro\n");
        printf("2. Ver libros\n");
        printf("3. Buscar libro\n");
        printf("4. Prestar libro\n");
        printf("5. Devolver libro\n");
        printf("6. Editar libro\n");
        printf("7. Eliminar libro\n");
        printf("8. Salir\n");
        option = ingreso_numeroopcion("Seleccione una opcion: ", 1, 8);
        switch (option) {
            case 1:
                agregar_libro();
                break;
            case 2:
                imprimir_informacion();
                break;
            case 3:
                buscar_libro();
                break;
            case 4:
                prestar_libro();
                break;
            case 5:
                devolver_libro();
                break;
            case 6:
                editar_libro();
                break;
            case 7:
                eliminar_libro();
                break;  
        }
    } while (option != 8);
    printf("SALIENDO DEL PROGRAMA...\n");
    return 0;
}

void caratula(const char *message) {
    printf("\t\x1B[32m*******************\x1B[0m\n");
    printf("\t\x1B[33m%s\x1B[0m\n", message);
    printf("\t\x1B[32m*******************\x1B[0m\n");
}

int ingreso_numeroopcion(char *msg, int min, int max) {
    int value, valido;
    do {
        printf("%s", msg);
        valido = scanf("%d", &value);
        if (valido != 1 || value < min || value > max) {
            printf("\x1B[31mDato no valido, debe ser un número entre %d y %d\x1B[0m\n", min, max);
            while(getchar() != '\n'); 
        } 
    } while (valido != 1 || value < min || value > max);
    return value;
}

int ingreso_entero(char *msg, int min, int max) {
    int value, valid;
    do {
        printf("%s (%d-%d): ", msg, min, max);
        valid = scanf("%d", &value);
        if (valid != 1 || value < min || value > max) {
            printf("\x1B[31mDato no valido, debe ser un valor entre %d y %d\x1B[0m\n", min, max);
            while(getchar() != '\n'); // Limpiar el buffer
        }
    } while (valid != 1 || value < min || value > max);
    return value;
}

void ingreso_informacion(char *msg, char *buf, char *validation, int max){
    do {
        printf("%s: ", msg);
        fgets(buf, max, stdin);
        buf[strcspn(buf, "\n")] = '\0'; 
        if (!nombre_valido(buf))  {
            printf("\x1B[31m%s\x1B[0m\n", validation);
        }
    } while (!nombre_valido(buf));
}

int nombre_valido(const char *s) {
    for (; *s; s++)
        if (!isalpha((unsigned char)*s) && *s != ' ') {
            return 0;
        }
    return 1;
}

int existe_id(int id) {
    FILE *f;
    f = fopen(FILE_NAME, "r");
    struct Books books;
    if (!f){
        return 0; // No se puede verificar si el ID existe
    } 
    while (fscanf(f,"%d,%99[^,],%49[^,],%d,%19[^\n]\n", &books.id, books.title, books.author, &books.publication, books.state) == 5)
        if (books.id == id) {
            fclose(f);
            return 1; // ID encontrado
        }
    fclose(f);
    return 0; // ID no encontrado
}

void agregar_libro(){
    struct Books libros;
    libros.id = ingreso_entero("ID del libro", 100, 999);
    if (existe_id(libros.id)) {
        printf("\x1B[33mID ya existe\x1B[0m\n");
        return;
    }
    while (getchar() != '\n'); 
    ingreso_informacion("Ingrese el título", libros.title, "Titulo no valido, solo caracteres", MAX_NAME);
    ingreso_informacion("Ingrese el autor", libros.author, "Autor no valido, solo caracteres", MAX_AUTHOR);
    libros.publication = ingreso_entero("Anio de publicación", 1900, 2025);
    strcpy(libros.state, "Disponible"); 
    printf("Estado: %s\n", libros.state);

    FILE *file;
    file = fopen(FILE_NAME, "a");
    if(file == NULL) {
        printf("Error al abrir el archivo para agregar el libro.\n");
        return;
    } 
    fprintf(file, "%d,%s,%s,%d,%s\n", libros.id, libros.title, libros.author, libros.publication, libros.state);
    fclose(file);
    printf("\n\x1B[33mLibro agregado exitosamente\x1B[0m\n\n");
}

void imprimir_informacion(){
    FILE *file;
    file = fopen(FILE_NAME, "r");
    struct Books libros;
    if(!file) {
        printf("\x1B[33mNo hay libros registrados\x1B[0m\n");
        return;
    }
    printf("\x1B[33m%-5s | %-20s | %-20s | %-5s | %-10s\x1B[0m\n", "ID", "Título", "Autor", "Año", "Estado");
    printf("---------------------------------------------------------------------\n");
    while (fscanf(file, "%d,%99[^,],%49[^,],%d,%19[^\n]\n", &libros.id, libros.title, libros.author, &libros.publication, libros.state) == 5) {
        printf("%-5d | %-20s | %-20s | %-5d | %-10s\n", libros.id, libros.title, libros.author, libros.publication, libros.state);
    }
    printf("\n");
    fclose(file);
}

void buscar_libro(){
    int id;
    struct Books libros;
    int found = 0;
    printf("\x1B[33m%-5s | %-20s\x1B[0m", "ID", "Título");
    printf("\n---------------------------\n");
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("No hay libros registrados.\n");
        return;
    }
    while (fscanf(file, "%d,%99[^,],%49[^,],%d,%19[^\n]\n", &libros.id, libros.title, libros.author, &libros.publication, libros.state) == 5) {
        printf("%-5d | %-20s\n", libros.id, libros.title);
    }
    fclose(file);

    id = ingreso_entero("ID a buscar", 100, 999);    file = fopen(FILE_NAME, "r");
    while (fscanf(file, "%d,%99[^,],%49[^,],%d,%19[^\n]\n", &libros.id, libros.title, libros.author, &libros.publication, libros.state) == 5) {
        if (libros.id == id) {
            found = 1;
            printf("\t\x1B[33mLIBRO ENCONTRADO\x1B[0m\n");
            printf("ID: %d\n", libros.id);
            printf("Título: %s\n", libros.title);
            printf("Autor: %s\n", libros.author);
            printf("Año de publicación: %d\n", libros.publication);
            printf("Estado: %s\n", libros.state);
            break;
        }
    }
    if (!found) {
        printf("Libro no registrado\n");
    }
    fclose(file);
}

void prestar_libro(){
    int id_search, found = 0;
    struct Books libros;
    
    printf("\x1B[33m%-5s | %-20s\x1B[0m\n", "ID", "Título");
    printf("------------------------------\n");
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("No hay libros registrados.\n");
        return;
    }
    while (fscanf(file, "%d,%99[^,],%49[^,],%d,%19[^\n]\n", &libros.id, libros.title, libros.author, &libros.publication, libros.state) == 5) {
        if (strcmp(libros.state, "Disponible") == 0) {
            printf("%-5d | %-20s\n", libros.id, libros.title);
        }
    }
    fclose(file);
    
    id_search = ingreso_entero("Ingrese el ID del libro a prestar", 100, 999);
    
    file = fopen(FILE_NAME, "r");
    FILE *tmp_file = fopen(TMP_FILE, "w");
    if (!file || !tmp_file) {
        printf("Error al abrir los archivos.\n");
        return;
    }
    
    while (fscanf(file, "%d,%99[^,],%49[^,],%d,%19[^\n]\n", &libros.id, libros.title, libros.author, &libros.publication, libros.state) == 5) {
        if (libros.id == id_search) {
            if (strcmp(libros.state, "Prestado") == 0){
                printf("\x1B[33mEl libro ya está prestado\x1B[0m\n\n");
                fclose(file);
                fclose(tmp_file);
                remove(TMP_FILE);
                return;
            }
            strcpy(libros.state, "Prestado");
            found = 1;
            printf("\t\x1B[33mLIBRO PRESTADO\x1B[0m\n\n");
        } 
        fprintf(tmp_file, "%d,%s,%s,%d,%s\n", libros.id, libros.title, libros.author, libros.publication, libros.state);
    }
    
    fclose(file);
    fclose(tmp_file);
    
    remove(FILE_NAME);
    rename(TMP_FILE, FILE_NAME);
    
    if (!found) {
        printf("Libro no registrado\n");
    } 
}

void devolver_libro(){
    int id_search, found = 0;
    struct Books libros;
    printf("\x1B[33m%-5s | %-20s\x1B[0m\n", "ID", "Título");
    printf("------------------------------\n");
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("No hay libros registrados.\n");
        return;
    }  
    while (fscanf(file, "%d,%99[^,],%49[^,],%d,%19[^\n]\n", &libros.id, libros.title, libros.author, &libros.publication, libros.state) == 5) {
        if (strcmp(libros.state, "Prestado") == 0) {
            printf("%-5d | %-20s\n", libros.id, libros.title);
        }
    }
    fclose(file);
    
    id_search = ingreso_entero("Ingrese el ID del libro a devolver", 100, 999);

    file = fopen(FILE_NAME, "r");
    FILE *tmp_file = fopen(TMP_FILE, "w");
    if (!file || !tmp_file) {
        printf("Error al abrir los archivos.\n");
        return;
    }

    while (fscanf(file, "%d,%99[^,],%49[^,],%d,%19[^\n]\n", &libros.id, libros.title, libros.author, &libros.publication, libros.state) == 5) {
        if (libros.id == id_search) {
            if (strcmp(libros.state,"Disponible") == 0) {
                printf("\x1B[33mEl libro está disponible\x1B[0m\n\n");
                fclose(file);
                fclose(tmp_file);
                remove(TMP_FILE);
                return;
            }
            strcpy(libros.state, "Disponible");
            found = 1;
            printf("\t\x1B[33mLIBRO DEVUELTO\x1B[0m\n\n");
        }
        fprintf(tmp_file, "%d,%s,%s,%d,%s\n", libros.id, libros.title, libros.author, libros.publication, libros.state);
    }

    fclose(file);
    fclose(tmp_file);
    remove(FILE_NAME);
    rename(TMP_FILE, FILE_NAME);
    
    if (!found) {
        printf("Libro no registrado\n");
    }
}

void editar_libro() {
    int id_search, found = 0;
    struct Books libros;

    printf("\x1B[33m%-5s | %-20s\x1B[0m\n", "ID", "Título");
    printf("------------------------------\n");
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("No hay libros registrados.\n");
        return;
    }
    while (fscanf(file, "%d,%99[^,],%49[^,],%d,%19[^\n]\n", &libros.id, libros.title, libros.author, &libros.publication, libros.state) == 5) {
        printf("%-5d | %-20s\n", libros.id, libros.title);
    }
    fclose(file);

    id_search = ingreso_entero("Ingrese el ID del libro a editar", 100, 999);

    file = fopen(FILE_NAME, "r");
    FILE *tmp_file = fopen(TMP_FILE, "w");
    if (!file || !tmp_file) {
        printf("Error al abrir los archivos.\n");
        return;
    }

    while (fscanf(file, "%d,%99[^,],%49[^,],%d,%19[^\n]\n", &libros.id, libros.title, libros.author, &libros.publication, libros.state) == 5) {
        if (libros.id == id_search) {
            if (strcmp(libros.state, "Prestado") == 0){
                printf("\x1B[33mEl ID ingresado pertenece a un libro prestado\x1B[0m\n\n");
                fclose(file);
                fclose(tmp_file);  
                remove(TMP_FILE);
                return;
            }
            found = 1;
            printf("Editando libro ID %d:\n", libros.id);
            while(getchar() != '\n');
            ingreso_informacion("Nuevo título", libros.title, "Titulo no valido, solo caracteres", MAX_NAME);
            ingreso_informacion("Nuevo autor", libros.author, "Autor no valido, solo caracteres", MAX_AUTHOR);
            libros.publication = ingreso_entero("Nuevo año de publicación", 1900, 2025);
            strcpy(libros.state, "Disponible"); // Reset state to available
            printf("Libro actualizado exitosamente.\n");
        } 
        fprintf(tmp_file, "%d,%s,%s,%d,%s\n", libros.id, libros.title, libros.author, libros.publication, libros.state);
    }

    fclose(file);
    fclose(tmp_file);
    remove(FILE_NAME);
    rename(TMP_FILE, FILE_NAME);
    
    if (!found) {
        printf("\x1B[33mLibro no registrado\x1B[0m\n");
    }
}

void eliminar_libro() {
    int id_search, found = 0;
    struct Books libros;

    printf("\x1B[33m%-5s | %-20s\x1B[0m\n", "ID", "Título");
    printf("------------------------------\n");
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("\x1B[33mNo hay libros registrados\x1B[0m\n");
        return;
    }
    while (fscanf(file, "%d,%99[^,],%49[^,],%d,%19[^\n]\n", &libros.id, libros.title, libros.author, &libros.publication, libros.state) == 5) {
        printf("%-5d | %-20s\n", libros.id, libros.title);
    }
    fclose(file);

    id_search = ingreso_entero("Ingrese el ID del libro a eliminar", 100, 999);

    file = fopen(FILE_NAME, "r");
    FILE *tmp_file = fopen(TMP_FILE, "w");
    if (!file || !tmp_file) {
        printf("Error al abrir los archivos.\n");
        return;
    }

    while (fscanf(file, "%d,%99[^,],%49[^,],%d,%19[^\n]\n", &libros.id, libros.title, libros.author, &libros.publication, libros.state) == 5) {
        if (libros.id == id_search) {
            if (strcmp(libros.state, "Prestado") == 0){
                printf("\x1B[33mID ingresado corresponde a un libro prestado\x1B[0m\n\n");
                fclose(file);
                fclose(tmp_file);
                remove(TMP_FILE);
                return; 
            }
            found = 1;
            printf("\t\x1B[33mLIBRO ELIMINADO\x1B[0m\n\n");
            continue; 
        } 
        fprintf(tmp_file, "%d,%s,%s,%d,%s\n", libros.id, libros.title, libros.author, libros.publication, libros.state);
    }

    fclose(file);
    fclose(tmp_file);
    remove(FILE_NAME);
    rename(TMP_FILE, FILE_NAME);

    if (!found) {
        printf("\x1B[33mLibro no registrado\x1B[0m\n");
    }
}   