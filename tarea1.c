#include "tdas/list.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>

// STRUCT =======================================
typedef struct
{
  char descripcion[200];
  char hora[30];
  char categoria[30]
} Tarea; // TAREA

typedef struct
{
  char nombre[30];
  List *Tarea;
} Categoria; // CATEGORIA
// STRUCT =======================================

// FUNCIONES PROT =======================================
void mostrarMenuPrincipal();
char* leerNombre(); // Lee un string y lo capitaliza
void registrar_categorias(List *); // 1
void eliminar_categorias(List *); // 2
void mostrar_categorias(List *); // 3
void registrar_tareas(List *); // 4
void atender_siguente_tarea(List *); // 5
void mostrar_general(List *); // 6
void filtrado_categoria(List *); // 7
void salir(); // 8
// FUNCIONES PROT =======================================

// MAIN =======================================
int main() {
  char opcion;
  List *Lista_cat = list_create(); // Lista para almacenar categorías

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el newline anterior

    switch (opcion) 
    {
    case '1':
      registrar_categorias(Lista_cat);
    case '2':
      eliminar_categorias(Lista_cat);
    case '3':
      mostrar_categorias(Lista_cat);
    case '4':
      registrar_tareas(Lista_cat);
    case '5':
      atender_siguente_tarea(Lista_cat);
    case '6':
      mostrar_general(Lista_cat);
    case '7':
      filtrado_categoria(Lista_cat);
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

char* leerNombre()
{
  char nombre[30];
  scanf(" %c", &nombre);
  if (nombre[0] == '\0') return;
  nombre[0] = toupper(nombre[0]);
  for (int i = 1 ; nombre[i] != '\0' ; i++)
  {
    nombre[i] = tolower(nombre[i]);
  }
  return nombre;
}

void registrar_categorias(List *Lista_cat) // 1
{
  char *nombre = leerNombre();
  Categoria *Cat;
  
  printf("Registrar nueva categoría\n");
  if (list_first(Lista_cat) == NULL)
  {
    strcpy(Cat->nombre, nombre);
    Lista_cat = list_popFront(Cat);
  }
  while (list_next(Lista_cat) != NULL)
  {
    if 
  }
}

void eliminar_categorias(List *Lista_cat) // 2
{
  printf("Eliminar nueva categoría\n");
}

void mostrar_categorias(List *Lista_cat) // 3
{
  printf("Categorías:\n");
}

void registrar_tarea(List *Lista_cat) // 4
{
  printf("Categorías:\n");
}

void atender_siguente_tarea(List *Lista_cat) // 5
{
  printf("Categorías:\n");
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