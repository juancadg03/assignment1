# DIAGRAMA DE CLASES - SIMULADOR DE PROCESADOR

## Jerarquía de Clases

```
Register (Clase Base)
├── Accumulator
├── ProgramCounter
├── InstructionRegister
├── MemoryAddressRegister
└── MemoryDataRegister

ControlUnit (Independiente)

ALU (Independiente)

Memory (Independiente)

Instruction (Struct)

CPU (Clase Principal)
├── Contiene: Accumulator
├── Contiene: ProgramCounter
├── Contiene: InstructionRegister
├── Contiene: MemoryAddressRegister
├── Contiene: MemoryDataRegister
├── Contiene: ControlUnit
├── Contiene: ALU
├── Contiene: Memory
└── Contiene: vector<Instruction>
```

## Relaciones entre Clases

```
┌─────────────────┐
│      CPU        │ ◄── Clase principal que coordina todo
└─────────────────┘
        │
        ├─────► Register (y derivados)
        ├─────► ControlUnit
        ├─────► ALU
        ├─────► Memory
        └─────► Instruction
```

## Flujo de Ejecución

```
main.cpp
   │
   ├─► Crea objeto CPU
   │
   ├─► CPU.loadInstructions(filename)
   │      │
   │      └─► Lee archivo y carga instrucciones
   │
   └─► CPU.run()
          │
          └─► Ciclo mientras no esté HALTED:
                 │
                 ├─► fetch()   - Obtener instrucción
                 ├─► decode()  - Decodificar
                 └─► execute() - Ejecutar
                        │
                        ├─► executeSET()
                        ├─► executeLDR()
                        ├─► executeADD()
                        ├─► executeINC()
                        ├─► executeDEC()
                        ├─► executeSTR()
                        ├─► executeSHW()
                        └─► executePAUSE()
```

## Dependencias de Archivos

```
main.cpp
  └─► #include "CPU.h"
         │
         ├─► #include "Register.h"
         ├─► #include "ControlUnit.h"
         ├─► #include "ALU.h"
         ├─► #include "Memory.h"
         └─► #include "Instruction.h"
```

## Responsabilidades de Cada Clase

### Register
- Almacenar un valor entero
- Proporcionar interfaz básica de lectura/escritura
- Servir como clase base para registros especializados

### Registros Derivados
- **Accumulator**: Almacenar resultados de operaciones
- **ProgramCounter**: Mantener el índice de la instrucción actual
- **InstructionRegister**: Guardar el código de la instrucción actual
- **MemoryAddressRegister**: Almacenar dirección de memoria a acceder
- **MemoryDataRegister**: Almacenar datos leídos/escritos de/a memoria

### ControlUnit
- Mantener el estado del procesador (FETCH, DECODE, EXECUTE, etc.)
- Controlar el flujo de ejecución
- Indicar si el procesador está detenido o pausado

### ALU (Arithmetic Logic Unit)
- Realizar operaciones aritméticas (suma, incremento, decremento)
- Operar sobre valores enteros

### Memory
- Almacenar datos en 256 posiciones
- Proporcionar operaciones de lectura/escritura
- Validar rangos de direcciones

### Instruction
- Estructura de datos para representar una instrucción
- Contiene: opcode, operand1, operand2, operand3

### CPU
- Coordinar todos los componentes
- Implementar el ciclo de instrucción (fetch-decode-execute)
- Cargar y ejecutar programas
- Ejecutar cada tipo de instrucción

## Ventajas de esta Arquitectura

1. **Modularidad**: Cada clase en su propio archivo
2. **Reutilización**: Las clases pueden usarse independientemente
3. **Mantenibilidad**: Fácil localizar y modificar código
4. **Escalabilidad**: Fácil agregar nuevas instrucciones o registros
5. **Encapsulamiento**: Cada clase oculta sus detalles internos
6. **Separación de responsabilidades**: Cada clase tiene un propósito claro
