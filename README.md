# SIMULADOR DE PROCESADOR - POO

## Descripción
Simulador de un procesador simple implementado con Programación Orientada a Objetos en C++.
El proyecto está organizado en múltiples archivos con separación de responsabilidades.

## Estructura del Proyecto

```
assignment1/
├── Register.h              # Declaración de clases de registros
├── Register.cpp            # Implementación de registros
├── ControlUnit.h           # Declaración de la unidad de control
├── ControlUnit.cpp         # Implementación de la unidad de control
├── ALU.h                   # Declaración de la ALU
├── ALU.cpp                 # Implementación de la ALU
├── Memory.h                # Declaración de la memoria
├── Memory.cpp              # Implementación de la memoria
├── Instruction.h           # Estructura de instrucción
├── Instruction.cpp         # Implementación de instrucción
├── CPU.h                   # Declaración de la CPU
├── CPU.cpp                 # Implementación de la CPU
├── main.cpp                # Programa principal
├── Makefile                # Script de compilación
├── programa_test.txt       # Programa de prueba
├── programa_simple.txt     # Programa simple
└── README.md               # Esta documentación
```

## Arquitectura

### Registros Implementados
- **ACC (Accumulator)**: Registro acumulador para operaciones aritméticas
- **PC (Program Counter)**: Contador de programa
- **ICR (Instruction Register)**: Registro de instrucción actual
- **MAR (Memory Address Register)**: Registro de dirección de memoria
- **MDR (Memory Data Register)**: Registro de datos de memoria
- **UC (Control Unit)**: Unidad de control (estados: FETCH, DECODE, EXECUTE, HALTED, PAUSED)

### Componentes
- **ALU**: Unidad Aritmético-Lógica para operaciones
- **Memory**: Memoria principal (256 posiciones)
- **CPU**: Procesador principal que coordina todos los componentes

## Conjunto de Instrucciones

### SET - Almacenar en Memoria
```
SET D1 X NULL NULL
```
Almacena el valor X en la dirección de memoria D1.
- X puede ser un valor inmediato (número)

**Ejemplo:** `SET D0 100 NULL NULL` → Almacena 100 en D0

---

### LDR - Cargar al Acumulador
```
LDR D3 NULL NULL
```
Carga el valor de la dirección D3 al registro acumulador.

**Ejemplo:** `LDR D0 NULL NULL` → Carga el valor de D0 al acumulador

---

### ADD - Suma
Tres formas de uso:

1. **ADD D1 NULL NULL**
   - Suma el valor en D1 al contenido actual del acumulador
   - Resultado queda en el acumulador

2. **ADD D1 D3 NULL**
   - Carga D1 en el acumulador y suma D3
   - Resultado queda en el acumulador

3. **ADD D1 D3 D4**
   - Suma D1 + D3 y guarda el resultado en D4
   - No modifica el acumulador

**Ejemplos:**
```
LDR D0 NULL NULL    # ACC = D0
ADD D1 NULL NULL    # ACC = ACC + D1

ADD D0 D1 NULL      # ACC = D0 + D1

ADD D0 D1 D2        # D2 = D0 + D1
```

---

### INC - Incrementar
```
INC D3 NULL NULL
```
Incrementa en 1 el valor en la dirección D3 y lo guarda en la misma dirección.

**Ejemplo:** `INC D0 NULL NULL` → Si D0=5, ahora D0=6

---

### DEC - Decrementar
```
DEC D3 NULL NULL
```
Decrementa en 1 el valor en la dirección D3 y lo guarda en la misma dirección.

**Ejemplo:** `DEC D0 NULL NULL` → Si D0=5, ahora D0=4

---

### STR - Almacenar desde Acumulador
```
STR D3 NULL NULL
```
Almacena el valor del acumulador en la dirección D3.

**Ejemplo:** `STR D5 NULL NULL` → Guarda ACC en D5

---

### SHW - Mostrar
Muestra el contenido de registros o memoria.

**Sintaxis:**
```
SHW D2 NULL NULL    # Muestra el valor en D2
SHW ACC NULL NULL   # Muestra el acumulador
SHW ICR NULL NULL   # Muestra el registro de instrucción
SHW MAR NULL NULL   # Muestra el registro de dirección
SHW MDR NULL NULL   # Muestra el registro de datos
SHW UC NULL NULL    # Muestra el estado de la unidad de control
```

---

### PAUSE - Pausar
```
PAUSE NULL NULL NULL
```
Pausa la ejecución y muestra el estado de todos los registros y la memoria.
Presionar Enter para continuar.

---

### END - Finalizar
```
END NULL NULL NULL
```
Finaliza la ejecución del programa.

---

## Compilación

### Opción 1: Usando Makefile (Recomendado)
```bash
make all
```

### Opción 2: Compilación manual
```bash
g++ -o simulador.exe Register.cpp ControlUnit.cpp ALU.cpp Memory.cpp Instruction.cpp CPU.cpp main.cpp -std=c++11
```

### Otros comandos del Makefile
```bash
make test    # Compila y ejecuta programa_test.txt
make run     # Compila y ejecuta programa_simple.txt
make clean   # Limpia archivos compilados
make help    # Muestra ayuda
```

## Uso

### Opción 1: Con argumento de línea de comandos
```bash
./simulador instrucciones.txt
```

### Opción 2: Entrada interactiva
```bash
./simulador
# El programa pedirá el nombre del archivo
```

## Formato de Archivo de Instrucciones

- Una instrucción por línea
- Formato: `OPCODE OPERAND1 OPERAND2 OPERAND3`
- Usar `NULL` para operandos no utilizados
- Las líneas que empiezan con `#` son comentarios
- Las líneas vacías se ignoran
- Siempre terminar con `END NULL NULL NULL`

## Ejemplo de Programa

```
# Programa que suma dos números
SET D0 10 NULL NULL     # D0 = 10
SET D1 20 NULL NULL     # D1 = 20
ADD D0 D1 NULL          # ACC = D0 + D1 = 30
SHW ACC NULL NULL       # Mostrar acumulador
STR D2 NULL NULL        # D2 = ACC = 30
SHW D2 NULL NULL        # Mostrar D2
END NULL NULL NULL      # Fin
```

## Ciclo de Instrucción

El procesador ejecuta cada instrucción en tres fases:

1. **FETCH (Búsqueda)**
   - Obtiene la instrucción desde memoria usando PC
   - Actualiza MAR con la dirección

2. **DECODE (Decodificación)**
   - Interpreta el código de operación

3. **EXECUTE (Ejecución)**
   - Ejecuta la operación
   - Actualiza registros y memoria según sea necesario
   - Incrementa PC

## Memoria

- Tamaño: 256 posiciones (D0 a D255)
- Direccionamiento: D# donde # es el índice (0-255)
- Inicializada en 0

## Características Implementadas con POO

✅ Clase base `Register` con herencia para registros especializados  
✅ Encapsulación de cada componente del procesador en archivos separados  
✅ Clase `CPU` que coordina todos los componentes  
✅ Clase `Memory` independiente con validación de direcciones  
✅ Clase `ControlUnit` con manejo de estados  
✅ Clase `ALU` para operaciones aritméticas  
✅ Polimorfismo en el método `display()` de los registros  
✅ Separación de interfaz (.h) e implementación (.cpp)  
✅ Organización modular del código

## Clases del Sistema

### Register (Clase Base)
- **Atributos**: value, name
- **Métodos**: setValue(), getValue(), display(), reset()
- **Clases Derivadas**: Accumulator, ProgramCounter, InstructionRegister, MemoryAddressRegister, MemoryDataRegister

### ControlUnit
- **Responsabilidad**: Controlar el ciclo de instrucción
- **Estados**: FETCH, DECODE, EXECUTE, HALTED, PAUSED
- **Métodos**: setState(), getState(), isHalted(), isPaused(), reset()

### ALU
- **Responsabilidad**: Operaciones aritméticas
- **Métodos**: add(), increment(), decrement()

### Memory
- **Responsabilidad**: Almacenamiento de datos
- **Tamaño**: 256 posiciones
- **Métodos**: read(), write(), display()

### CPU
- **Responsabilidad**: Coordinación general del sistema
- **Componentes**: Registros, ALU, UC, Memoria
- **Métodos**: loadInstructions(), fetch(), decode(), execute(), run()

## Archivos Incluidos

- **Archivos de encabezado (.h)**: Declaraciones de clases
- **Archivos de implementación (.cpp)**: Definiciones de métodos
- **main.cpp**: Punto de entrada del programa
- **Makefile**: Automatización de compilación
- **cicloInstrucc.c++**: Versión original (monolítica) - obsoleta
- **instrucciones.txt**: Programa de ejemplo completo
- **programa_simple.txt**: Programa de ejemplo simple
- **programa_test.txt**: Programa de prueba
- **README.md**: Esta documentación

## Autor

Proyecto para el curso de Sistemas Operativos - Universidad Javeriana Cali
