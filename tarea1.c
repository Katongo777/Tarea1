#include "tdas/list.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// STRUCT =======================================
typedef struct
{
  char descripcion[300];
  char hora[30];
  char categoria[30]
} Tarea; // TAREA

typedef struct
{
  char nombre[30];
  size_t pendientes;
  List *Tarea;
} Categoria; // CATEGORIA
// STRUCT =======================================

// PROTOTIPOS =======================================
void mostrarMenuPrincipal();
Categoria* buscar_categoria(List *, char *); 
char* leerNombre(char *); // Lee un string y lo capitaliza
void registrar_categorias(List *, char *); // 1
void eliminar_categorias(List *); // 2
void mostrar_categorias(List *); // 3
void registrar_tareas(List *); // 4
void leer_descripcion(char *); // Lee la descripcion de la tarea
void guardar_hora(char *);
void atender_siguente_tarea(List *); // 5
void mostrar_general(List *); // 6
void filtrado_categoria(List *);  // 7
void salir(); // 8
// PROTOTIPOS =======================================

// MAIN =======================================
int main() 
{
  char opcion;
  List *Lista_cat = list_create(); // Lista para almacenar categorías

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el newline anterior

    switch (opcion) 
    {
    case '1':
    {
      char nombre[30];
      leer_nombre(nombre); // Funcion para ingresar el nombre, capitalizarlo y guardarlo
      registrar_categorias(Lista_cat, nombre);
      break;
    }
    case '2':
      eliminar_categorias(Lista_cat);
      break;
    case '3':
      mostrar_categorias(Lista_cat);
      break;
    case '4':
      registrar_tareas(Lista_cat);
      break;
    case '5':
      atender_siguente_tarea(Lista_cat);
      break;
    case '6':
      mostrar_general(Lista_cat);
      break;
    case '7':
      filtrado_categoria(Lista_cat);
      break;
    case '8':
      puts("Saliendo del sistema de gestión hospitalaria...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '8');

  // Liberar recursos, si es necesario
  list_clean(Lista_cat);

  return 0;
}
// MAIN =======================================


// FUNCIONES =======================================
void mostrarMenuPrincipal() // Menú principal
{
  limpiarPantalla();
  puts("=========================================================");
  puts("     Sistema de Gestión de Tareas Personalizadas");
  puts("=========================================================");
  
  puts("1) Nueva Categoría");
  puts("2) Eliminar Categoría");
  puts("3) Mostrar Categorías");
  puts("4) Registrar Tarea");
  puts("5) Atender Siguiente");
  puts("6) Visualización del Tablero General");
  puts("7) Filtrado por Categoría");
  puts("8) Salir");
}

void leer_nombre(char *nombre)
{
  puts("Ingrese el nombre de la categoría: ");
  scanf("%29s", nombre);

  if (nombre[0] == '\0') return;
  
  nombre[0] = toupper(nombre[0]); // Capitalizar el nombre
  for (int i = 1 ; nombre[i] != '\0' ; i++) nombre[i] = tolower(nombre[i]);
}

Categoria* buscar_categoria(List *Lista_cat, char *nombre) // Función para buscar una categoría
{
  Categoria *actual_cat = (Categoria*)list_first(Lista_cat);

  while (actual_cat != NULL) 
  {
    if (strcmp(nombre, actual_cat->nombre) == 0) 
    {
      return actual_cat; // Se encontro la categoría
    }
    actual_cat = (Categoria*)list_next(Lista_cat);
    }

    return NULL; // Retorna NULL si es que no se encontro
}

void registrar_categorias(List *Lista_cat, char *nombre) // 1 
{
  puts("Registrar nueva categoría");
  
  Categoria *actual_cate = buscar_categoria(Lista_cat, nombre);

  if (actual_cate != NULL)
  {
    printf("¡Ya existe la categoria %s!\n", nombre);
    return;
  }

  Categoria *nueva_cate = (Categoria*)malloc(sizeof(Categoria));
  strcpy(nueva_cate->nombre, nombre); // Se guarda el nombre de la categoría
  nueva_cate->pendientes = 0; // Se inicializa la variable que cuenta las tareas pendientes de esa categoria
  nueva_cate->Tarea = list_create(); // Se crea una lista vacía donde se guardaran las tareas

  list_pushFront(Lista_cat, nueva_cate); // Se agrega la categoría a la lista de categorías

  puts("¡Categoría creada exitosamente!");
}

void eliminar_categorias(List *Lista_cat) // 2
{
  puts("Eliminar nueva categoría");
  printf("Ingrese la categoría a eliminar: ");  
  char nombre[30];
  leer_nombre(nombre);

  Categoria *actual_cate = buscar_categoria(Lista_cat, nombre);

  if (actual_cate == NULL)
  {
    puts("¡No se encontro la categoría ingresada!");
    return;
  }
  
  list_clean(actual_cate->Tarea);
  list_clean(actual_cate);

  puts("¡Categoría eliminada exitosamente!");
}

void mostrar_categorias(List *Lista_cat) // 3 s
{
  printf("Categorías:\n");
  puts("=========================================================");
  Categoria *actual_cate = list_first(Lista_cat);
  while (actual_cate != NULL)
  {
    printf("%s ----> Tareas pendientes: %zu \n", actual_cate->nombre, actual_cate->pendientes);
    actual_cate = list_next(Lista_cat);
  }
  puts("=========================================================");
}

void registrar_tarea(List *Lista_cat) // 4
{
  puts("Registrar nueva tarea");
  puts("Ingrese una de las categorías existentes (si no está, se creara la categoría)");
  mostrar_categorias(Lista_cat);

  char nombre[30];
  leer_nombre(nombre);

  Categoria *actual_cate = buscar_categoria(Lista_cat, nombre);

  Tarea *nueva_tarea = (Tarea *)malloc(sizeof(Tarea));
  strcpy(nueva_tarea->categoria, nombre); 
  leer_descripcion(nueva_tarea->descripcion); // Funcion para leer la descripción
  guardar_hora(nueva_tarea->hora); // Se usan las funciones de la librería time.h
  
  if (actual_cate == NULL) // Si no está la categoría, se creara una nueva
  {
    registrar_categorias(Lista_cat, nombre);
    actual_cate = list_first(Lista_cat); // La nueva categoría paso a ser la primera en la lista
  }

  actual_cate->pendientes++;
  list_pushBack(actual_cate->Tarea, nueva_tarea); // Se agrega al final para mantener la regla FIFO
}

void leer_descripcion(char *descripcion)
{
  scanf("%299s", descripcion);
}

void guardar_hora(char *hora) // Funciones de la librería time.h
{
  // Pedimos el tiempo al sistema operativo
  time_t tiempoActual = time(NULL);
  struct tm *infoTiempo = localtime(&tiempoActual);
    
  // strftime formatea la hora y la guarda directamente en tu variable
  strftime(hora, 30, "%H:%M:%S", infoTiempo); 
  // %H:%M:%S guardara algo como "HORA:MINUTO:SEGUNDO"
}

void atender_siguente_tarea(List *Lista_cat) // 5
{
  char nombre[30];
  leer_nombre(nombre);
  Categoria *actual_cate = buscar_categoria(Lista_cat, nombre);
  if (actual_cate->pendientes == 0)
  {
    puts("¡Libre de pendientes!");
    return;
  }

  Tarea *actual_tarea = list_first(actual_cate->Tarea);
  printf("Descripcion de la tarea: [%s] ", actual_tarea->descripcion);
  printf("| Categoría: [%s] |", actual_tarea->categoria);
  printf(" Registrada a las: [%s]", actual_tarea->hora);
  actual_cate->pendientes--;
  free(actual_tarea); // Se libera la memoria usada por esa tarea
}

void mostrar_general(List *Lista_cat) // 6
{
  printf("Categorías:\n");
}

void filtrado_categoria(List *Lista_cat) // 7
{
  printf("Categorías:\n");
}

void salir(List *Lista_cat) // 8
{
  printf("Categorías:\n");
}
// FUNCIONES =======================================