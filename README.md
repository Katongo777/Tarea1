# Planificador de Tareas

## Descripción

Este sistema permite a los usuarios gestionar sus tareas pendientes agrupándolas por categorías creadas por el mismo usuario. Lo principal del sistema es que se usa el orden de llegada **FIFO** (*First In, First Out*), la primera tarea que se creó es la primera que va a ser atendida, sin importar su categoría. Este sistema está diseñado utilizando **Tipos de Datos Abstractos (TDAs)** en C, específicamente se usaron **listas** y **colas**.

---

## Requisitos

Este sistema ha sido desarrollado con el **lenguaje C** y puede ejecutarse fácilmente utilizando **Visual Studio Code** junto con una extensión para C/C++, como **C/C++ Extension Pack**, o también se puede ejecutar desde una terminal (**CMD, PowerShell, Git Bash**). Muy importante tener instalado el compilador [GCC (MinGW-w64)](https://www.mingw-w64.org/) instalado en tu sistema.

## Cómo compilar y ejecutar (Desde la Terminal)

### Pasos:
1. **Descarga y descomprime el** archivo `.zip`

2. **Abre tu terminal** y llega hasta la carpeta donde descomprimiste el archivo `.zip` (debes estar posicionado exactamente donde se encuentra el archivo `tarea1.c` y la carpeta `tdas`)

3. **Compila el código** ingresando el siguiente comando
   ```
   gcc tdas/*.c tarea1.c -o tarea1
   ```

4. Ejecuta el programa escribiendo el comando correspondiente a tu sistema operativo
- En **Windows** (**CMD** o **PowerShell**)
   ```
   .\tarea1.exe
   ```
- En **Git Bash**, **Linux** o **Mac**
   ```
   ./tarea1
   ```

## Cómo compilar y ejecutar (Desde la Visual Studio Code)

### Requisitos previos:

- Tener instalado [Visual Studio Code](https://code.visualstudio.com/)
- Instalar la extensión **C/C++** (Microsoft) dentro de Visual Studio Code

### Pasos:

1. **Descarga y descomprime el** archivo `.zip`
2. **Abre el proyecto en Visual Studio Code**
    - Inicia Visual Studio Code
    - Arriba a la izquierda selecciona `File > Open Folder` y elige la carpeta donde descomprimiste el proyecto (fijarse que debe contener el archivo `tarea1.c` y la carpeta `tdas`)
3. **Compila el código**
    - Arriba a la izquierda seleciona la terminal de Visual `Terminal > New terminal`
    - En la terminal, compila el programa con el siguiente comando
        ```
        gcc tdas/*.c tarea1.c -o tarea1
        ```
        
4. **Ejecuta el programa**
    - Una vez compilado puedes ejecutar el código en la terminal, dependiendo de tu sistema
        - En **Windows** (**CMD** o **PowerShell**)
        ```
        .\tarea1.exe
        ```
        - En **Git Bash**, **Linux** o **Mac**
        ```
        ./tarea1
        ```

---

## Funcionalidades

### Funcionando correctamente:

- Crear nuevas categorías
- Eliminar categorías (y borrar correctamente todas las tareas de esa categoría)
- Mostrar todas las categorías creadas
- Registrar tareas, asignadoles a una categoría (existente o no) y guardando la hora de registro
- Atender la siguiente tarea (elimina la tarea más antigua de la cola)
- Visualizar el tablero general de todas las tareas y su información, mostrandolas por orden de llegada
- Mostrar las tareas por una categoría específica

### Problemas conocidos:

- El sistema únicamente no tiene tildes al mostrar el texto por pantalla, por el motivo de que las letras con tildes de corrompian 

### A mejorar:

- Solucionar el problemas de las tildes
- Implementar que se puedan guardar los datos permanentemente en un archivo para no perder las tareas al cerrar el programa

---

## Ejemplo de uso

**Paso 1: Registrar una nueva tarea**

Se comienza registrando una tarea, seleccionando la **`opción 4`**
```
Opción seleccionada: 4) Registrar Tarea
Ingrese el nombre de la categoria: Universidad
Ingrese la descripcion de la tarea: Terminar la tarea de Estructura de Datos
```

El sistema registra la tarea, crea automáticamente la categoría "**Universidad**" (si es que no existía antes, **`opcion 1`** para registrar una categoría) y guarda la hora actual de registro. Esta tarea se posiciona en el primer lugar de la cola.

**Paso 2: Registrar una segunda tarea**

Se quiere agregar otra tarea con otra categoría
```
Opción seleccionada: 4) Registrar Tarea
Ingrese el nombre de la categoria: Casa
Ingrese la descripcion de la tarea: Preparar la comida para el siguiente día
```
El sistema añade esta nueva tarea a la cola. Al utilizar la regla de orden de llegada **FIFO**, esta tarea quedará posicionada detrás de la primera que fue registrada sin importar su categoría.

**Paso 3: Visualización del Tablero General**

El usuario revisa el tablero para ver todas las tareas pendientes y en orden de registro, seleccionando la **`opción 6`**
```
Opción seleccionada: 6) Visualizacion del Tablero General
```
La lista muestra las tareas, indicando su categoría, descripción y hora. Todas ordenadas de más antiguas a más recientes.

**Paso 4: Atender la Siguiente Tarea**

El usuario realiza la tarea pendiente y se saca del sistema, seleccionando la **`opción 5`**
```
Opción seleccionada: 5) Atender Siguiente
```
El sistema muestra en pantalla que la tarea que está siendo atendida, le resta un pendiente a la categoría "**Universidad**", y elimina la tarea definitivamente de la lista de espera para dar paso a la siguiente.