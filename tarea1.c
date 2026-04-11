#include "tdas/list.h"
#include "tdas/extra.h"
#include "tdas/queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/*
Repositorio de GitHub
https://github.com/Katongo777/Tarea1
*/

// STRUCT =======================================
typedef struct
{
  char descripcion[300];
  char hora[30];
  char categoria[30];
} Tarea; // DATOS DE TAREA

typedef struct
{
  char nombre[30];
  size_t pendientes;
} Categoria; // DATOS DE CATEGORÍA
// STRUCT =======================================

// PROTOTIPOS =======================================
void mostrarMenuPrincipal();
void leer_nombre(char *);
Categoria* buscar_categoria(List *, char *); 
void registrar_categorias(List *, char *); // === 1 ===
void eliminar_categorias(List *, Queue *); // === 2 ===
void eliminar_tareas(Categoria *, Queue *);
void mostrar_categorias(List *); // === 3 ===
void registrar_tareas(List *, Queue *); // === 4 ===
void leer_descripcion(char *);
void guardar_hora(char *);
void mostrar_tarea(Tarea *);
void atender_siguente_tarea(List *, Queue *); // === 5 ===
void mostrar_general(Queue *); // === 6 ===
void filtrado_categoria(Queue *);  // === 7 ===
// PROTOTIPOS =======================================

// MAIN =======================================
int main() 
{
  char opcion;
  List *Lista_cat = list_create(); // Lista para almacenar categorías
  Queue *Cola_glob_tareas = queue_create(NULL); // Cola GLOBAL de tareas

  do {
    mostrarMenuPrincipal(); // Funcion que muetra todas las opciones del programa
    printf("Ingrese su opcion: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el newline anterior

    switch (opcion) 
    {
    case '1':
    {
      char nombre[30];
      leer_nombre(nombre); // Leer string entrante
      registrar_categorias(Lista_cat, nombre);
      break;
    }
    case '2':
      eliminar_categorias(Lista_cat, Cola_glob_tareas);
      break;
    case '3':
      mostrar_categorias(Lista_cat);
      break;
    case '4':
      registrar_tareas(Lista_cat, Cola_glob_tareas);
      break;
    case '5':
      atender_siguente_tarea(Lista_cat, Cola_glob_tareas);
      break;
    case '6':
      mostrar_general(Cola_glob_tareas);
      break;
    case '7':
      filtrado_categoria(Cola_glob_tareas);
      break;
    case '8':
      break;
    default:
      puts("Opción no valida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();
  } while (opcion != '8');

  // Se libera TODA la memoria usada
  queue_clean(Cola_glob_tareas);
  list_clean(Lista_cat);

  return 0;
}
// MAIN =======================================

// FUNCIONES =======================================
void mostrarMenuPrincipal() // Menú principal
{
  limpiarPantalla();
  puts("=========================================================");
  puts("     Sistema de Gestion de Tareas Personalizadas");
  puts("=========================================================");
  
  puts("1) Nueva Categoria");
  puts("2) Eliminar Categoria");
  puts("3) Mostrar Categorias");
  puts("4) Registrar Tarea");
  puts("5) Atender Siguiente");
  puts("6) Visualizacion del Tablero General");
  puts("7) Filtrado por Categoria");
  puts("8) Salir");
}

void leer_nombre(char *nombre)
{
  // Función modularizada
  /*
  Esta función lee un string (nombre) ingresado, valida si se ingreso o no texto, si hay texto la
  primera letra del string pasa a ser mayúscula y después con un ciclo se pasan las demás letras
  a minúsculas
  */
  printf("Ingrese el nombre de la categoria: ");
  scanf(" %29[^\n]", nombre); // Lee hasta que se apreté Enter y se guarda un espacio para '\0'

  if (nombre[0] == '\0') return; // Si no se ingreso texto, retorna nada
  
  nombre[0] = toupper(nombre[0]); 
  for (int i = 1 ; nombre[i] != '\0' ; i++) nombre[i] = tolower(nombre[i]); // Ciclo para capitalizar el nombre
}

Categoria* buscar_categoria(List *Lista_cat, char *nombre)
{
  // Función modularizada
  /*
  Función para buscar una categoría por su nombre en la lista de categorías,
  retornado el puntero al struct de esa categoría
  */
  Categoria *actual_cat = (Categoria*)list_first(Lista_cat);

  while (actual_cat != NULL) 
  {
    if (strcmp(nombre, actual_cat->nombre) == 0) 
    {
      return actual_cat; // Se encontro la categoría, se retorna el puntero a esa categoría
    }
    actual_cat = (Categoria*)list_next(Lista_cat);
    }

    return NULL; // Retorna NULL si es que no se encontro
}

void registrar_categorias(List *Lista_cat, char *nombre) // === 1 === 
{
  puts("===== Registrar nueva categoria =====");
  
  Categoria *actual_cate = buscar_categoria(Lista_cat, nombre); // Se busca la categoría en la lista de categorías

  if (actual_cate != NULL) // Se verifica si esa categoría está en la lista de categorías
  {
    printf("Ya existe la categoria %s\n", nombre);
    return;
  }

  /*
  Se reserva memoria en el heap para la nueva categoría (struct),
  se guarda el nombre de la categoría y se inicializa la variable 
  que cuenta las tareas pendientes de esa categoria
  */
  Categoria *nueva_cate = (Categoria*)malloc(sizeof(Categoria));
  strcpy(nueva_cate->nombre, nombre); 
  nueva_cate->pendientes = 0;

  list_pushFront(Lista_cat, nueva_cate); // Se agrega la categoría a la lista de categorías

  puts("Categoria creada exitosamente");
}

void eliminar_categorias(List *Lista_cat, Queue *Cola_glob_tareas) // === 2 ===
{
  puts("===== Eliminar nueva categoria =====");
  char nombre[30];
  leer_nombre(nombre);

  Categoria *actual_cate = buscar_categoria(Lista_cat, nombre); // Se busca si la categoría existe
  if (actual_cate == NULL) // Si no existe, retorna nada
  {
    puts("No se encontro la categoria ingresada");
    return;
  }
  
  eliminar_tareas(actual_cate, Cola_glob_tareas); // Se eliminan las tareas que pertenezcan a la categoría
  list_popCurrent(Lista_cat); // Se elimina la categoría de la lista de categorías
  free(actual_cate); // Se libera la memoria usada

  puts("Categoria eliminada exitosamente");
}

void eliminar_tareas(Categoria *actual_cate, Queue *Cola_glob_tareas)
{
  /* 
  Esta función crea una cola auxiliar, donde se pasarán los datos que no pertenezcan
  a la categoría a eliminar, los que si pertenecen se eliminarán
  */
  char nombre[30];
  strcpy(nombre, actual_cate->nombre); // Se guarda el nombre de la categoría

  Queue *Cola_aux = queue_create(NULL); // Se crea la cola auxiliar donde iran los datos que no se eliminan
  Tarea *actual_tarea = queue_front(Cola_glob_tareas); // Variable para guardar la tarea y ver si pertenece o no a la categoría

  while (queue_front(Cola_glob_tareas) != NULL) // Ciclo para recorrer la cola de tareas
  {
    actual_tarea = queue_remove(Cola_glob_tareas); // Se elimina la tarea de la cola original, pero se guardan los datos temporalmente
    if (strcmp(actual_tarea->categoria, nombre) != 0) // Si la tarea NO pertenece a la categoría se guarda en la cola auxiliar
    {
      queue_insert(Cola_aux, actual_tarea);
    }
    else // Si la tarea SI pertenece a la categoría, se libera la memoria usada
    {
      free(actual_tarea);
    }
  }
  
  while (queue_front(Cola_aux) != NULL) // Ciclo que devuelve los datos de la cola auxiliar a la cola original 
  {
    actual_tarea = queue_remove(Cola_aux);
    queue_insert(Cola_glob_tareas, actual_tarea);
  }
  queue_clean(Cola_aux); // Se libera la memoria usada por la cola auxiliar
}

void mostrar_categorias(List *Lista_cat) // === 3 ===
{
  puts("===== Categorias =====");
  if (list_first(Lista_cat) == NULL)
  {
    puts("No hay categorias creadas");
    return;
  }
  puts("=========================================================");
  Categoria *actual_cate = list_first(Lista_cat);
  while (actual_cate != NULL) // Ciclo para mostrar las categorías
  {
    printf("%s ----> Tareas pendientes: %zu \n", actual_cate->nombre, actual_cate->pendientes);
    actual_cate = list_next(Lista_cat);
  }
  puts("=========================================================");
}

void registrar_tareas(List *Lista_cat, Queue *Cola_glob_tareas) // === 4 ===
{
  puts("===== Registrar nueva tarea =====");
  puts("Ingrese una de las categorias existentes (si no esta, se creara la categoria)");
  mostrar_categorias(Lista_cat);

  char nombre[30];
  leer_nombre(nombre);

  Categoria *actual_cate = buscar_categoria(Lista_cat, nombre);

  Tarea *nueva_tarea = (Tarea *)malloc(sizeof(Tarea));
  strcpy(nueva_tarea->categoria, nombre); 
  leer_descripcion(nueva_tarea->descripcion); // Función para leer la descripción
  guardar_hora(nueva_tarea->hora); // Función para guarda la hora de ingreso
  
  if (actual_cate == NULL) // Si no existe la categoría se creará una nueva
  {
    registrar_categorias(Lista_cat, nombre);
    actual_cate = list_first(Lista_cat); // La nueva categoría paso a ser la primera en la lista
  }

  actual_cate->pendientes++; // Se suma 1 a los pendientes de esa categoría
  queue_insert(Cola_glob_tareas, nueva_tarea); // Se agrega la tarea a la lista global de tareas
}

void leer_descripcion(char *descripcion)
{
  printf("Ingrese la descripcion de la tarea: ");
  scanf(" %299[^\n]", descripcion); // Lee hasta que se apreté Enter
}

void guardar_hora(char *hora)
{
  // Librería time.h

  // Se pide el tiempo al sistema operativo
  time_t tiempoActual = time(NULL);
  struct tm *infoTiempo = localtime(&tiempoActual);
    
  // strftime formatea la hora y la guarda directamente en la variable
  strftime(hora, 30, "%H:%M:%S", infoTiempo); // %H:%M:%S guardara algo como "HORA:MINUTO:SEGUNDO"
}

void mostrar_tarea(Tarea *actual_tarea)
{
  // Función modularizada
  // Función que muestra el contenido de la tarea
  printf("| Categoria: [%s] |", actual_tarea->categoria);
  printf("Descripcion de la tarea: [%s] ", actual_tarea->descripcion);
  printf(" Registrada a las: [%s]", actual_tarea->hora);
  puts("");
}

void atender_siguente_tarea(List *Lista_cate, Queue *Cola_glob_tareas) // === 5 ===
{
  puts("===== Atender tarea =====");
  Tarea *actual_tarea = queue_front(Cola_glob_tareas); // Se guarda la primera tarea en la cola
  if (actual_tarea == NULL) // Si la cola está vacía, retorna nada
  {
    puts("Libre de pendientes");
    return;
  }

  mostrar_tarea(actual_tarea); // Se muestra la tarea a eliminar

  Categoria *actual_cate = buscar_categoria(Lista_cate, actual_tarea->categoria);
  actual_cate->pendientes--; // Se le resta 1 a la categoría que pertenece la tarea a eliminar

  queue_remove(Cola_glob_tareas); // Se elimina la tarea de la cola de tareas
  free(actual_tarea); // Se libera la memoria usada por esa tarea
}

void mostrar_general(Queue *Cola_glob_tareas) // === 6 ===
{
  /*
  Función con un ciclo parecido al de "eliminar_tareas()" solo que en
  vez de eliminar las tareas, solo las muestra
  */
  puts("===== Todas las tareas pendientes =====");
  Queue *Cola_aux = queue_create(NULL);
  Tarea *actual_tarea = queue_front(Cola_glob_tareas);
  while (queue_front(Cola_glob_tareas) != NULL)
  {
    actual_tarea = queue_remove(Cola_glob_tareas);
    queue_insert(Cola_aux, actual_tarea);
    mostrar_tarea(actual_tarea);
  }

  while (queue_front(Cola_aux) != NULL)
  {
    actual_tarea = queue_remove(Cola_aux);
    queue_insert(Cola_glob_tareas, actual_tarea);
  }
  queue_clean(Cola_aux); // Se libera la memoria usada por la cola auxiliar
}

void filtrado_categoria(Queue *Cola_glob_tareas) // === 7 ===
{
  /*
  Función con un ciclo parecido al de "eliminar_tareas()" solo que en
  vez de eliminar las tareas, solo muestra las que pertenecen a la 
  categoría
  */
  char nombre[30];
  leer_nombre(nombre);
  Queue *Cola_aux = queue_create(NULL);
  Tarea *actual_tarea = queue_front(Cola_glob_tareas);
  while (queue_front(Cola_glob_tareas) != NULL)
  {
    actual_tarea = queue_remove(Cola_glob_tareas);
    queue_insert(Cola_aux, actual_tarea);
    // Se ve si la tarea pertenece a la categoría a mostrar
    if (strcmp(nombre, actual_tarea->categoria) == 0) mostrar_tarea(actual_tarea);
  }

  while (queue_front(Cola_aux) != NULL)
  {
    actual_tarea = queue_remove(Cola_aux);
    queue_insert(Cola_glob_tareas, actual_tarea);
  }
  queue_clean(Cola_aux); // Se libera la memoria usada por la cola auxiliar
}
// FUNCIONES =======================================