# Sistema de Gestión Bancaria - Proyecto POO

## 📋 Descripción del Proyecto

Sistema bancario desarrollado en C++ que implementa la gestión de clientes, cuentas de caja de ahorro (en pesos y dólares), transacciones bancarias, y control de acceso a tarjetas de crédito según el tipo de cliente.

---

## 🏗️ Arquitectura del Sistema

### Diagrama de Clases

```
Excepcion (Clase Base Abstracta)
├── ExcepcionArgumentoInvalido
└── ExcepcionMemoria

persona (Clase Base)
├── cliente
│   └── caja_de_ahorro (Composición)
│       └── transacciones (Herencia)
└── personal

banco
├── personal (Composición)
└── cliente* (Agregación dinámica)
```

---

## 📦 Clases Principales y su Justificación

### 1. **Clase `Excepcion` (Jerarquía de Excepciones)**

**Propósito:** Manejo robusto de errores siguiendo el principio de excepciones personalizadas en C++.

**Diseño:**
- **Clase base abstracta** con método virtual `error()`
- **Herencia:** `ExcepcionArgumentoInvalido` y `ExcepcionMemoria`

**Implementación:**
```cpp
class Excepcion {
protected:
    string mensaje;
public:
    virtual string error() const;  // Método virtual para polimorfismo
    virtual ~Excepcion();          // Destructor virtual
};
```

**¿Por qué?**
- Permite capturar excepciones específicas con `catch`
- Facilita el debugging mostrando mensajes personalizados
- Evita uso de `std::exception` genérico
- Implementa polimorfismo: `catch (const Excepcion& e)` captura cualquier derivada

**Uso en el código:**
- `ExcepcionArgumentoInvalido`: Para validaciones de entrada (DNI no numérico, monto inválido, etc.)
- `ExcepcionMemoria`: Para fallos en asignación dinámica de memoria

---

### 2. **Clase `persona` (Clase Base Abstracta)**

**Propósito:** Representar atributos comunes entre clientes y personal del banco.

**Diseño:**
- **Clase base** para `cliente` y `personal`
- Encapsulación total: atributos privados con setters/getters
- Método virtual `mostrar_datos()` para polimorfismo

**Atributos:**
```cpp
private:
    string dni;
    string nombre;
    string anio_ingreso;
```

**¿Por qué herencia?**
- **DRY (Don't Repeat Yourself):** Evita duplicar código de DNI, nombre, año ingreso
- **Polimorfismo:** `persona* p = &cliente` permite tratar clientes y personal de forma uniforme
- **Extensibilidad:** Facilita agregar otros tipos de personas (gerentes, cajeros, etc.)

**Método virtual:**
```cpp
virtual void mostrar_datos();  // Cada clase derivada puede sobrescribirlo
```

---

### 3. **Clase `cliente` (Hereda de `persona`)**

**Propósito:** Representar a los clientes del banco con sus características específicas.

**Atributos propios:**
```cpp
private:
    string tipo_cliente;      // PLATA, ORO, PLATINO
    string estado_cliente;    // ACTIVO, BAJA
    string numero_cliente;
    caja_de_ahorro cuenta;    // COMPOSICIÓN: cada cliente TIENE una cuenta
```

**¿Por qué composición con `caja_de_ahorro`?**
- **Relación "tiene-un":** Un cliente TIENE una cuenta de caja de ahorro
- **Ciclo de vida:** La cuenta nace y muere con el cliente
- **Encapsulamiento:** La cuenta es parte integral del cliente
- **Realismo:** En la vida real, no hay cuentas sin dueño

**Métodos específicos:**

#### `mostrar_info_tarjeta_credito()`
```cpp
void cliente::mostrar_info_tarjeta_credito() {
    if (tipo_cliente == "PLATA")
        cout << "No tiene acceso a tarjeta de credito." << endl;
    else if (tipo_cliente == "ORO")
        cout << "Tarjeta Credix - Limite: $250,000" << endl;
    else if (tipo_cliente == "PLATINO")
        cout << "Tarjeta Premium - Limite: $500,000" << endl;
}
```
**Justificación:** Implementa la regla de negocio de acceso a tarjetas según consignas.

#### `getCuenta()`
```cpp
caja_de_ahorro& cliente::getCuenta() {
    return cuenta;  // Retorna referencia para modificar la cuenta
}
```
**Justificación:** Permite acceso controlado a la cuenta del cliente desde el banco.

---

### 4. **Clase `personal` (Hereda de `persona`)**

**Propósito:** Representar al personal del banco.

**Atributos propios:**
```cpp
private:
    string area_trabajo;  // Área donde trabaja (atención, caja, gerencia, etc.)
```

**¿Por qué mantener esta clase si no se usa activamente?**
- **Cumplimiento de consignas:** El enunciado menciona "personal del banco"
- **Modelado del dominio:** Un banco tiene personal, aunque el sistema actual no gestione sus operaciones
- **Extensibilidad futura:** Facilita agregar funcionalidades (control de acceso, auditoría, etc.)
- **Diseño completo:** Representa el modelo conceptual del banco

---

### 5. **Clase `transacciones` (Clase Base)**

**Propósito:** Gestionar todas las transacciones bancarias (depósitos y extracciones).

**Diseño:**
- **Clase base** para `caja_de_ahorro`
- Atributos `protected` para herencia
- Gestión de arreglo dinámico con redimensionamiento

**Atributos:**
```cpp
protected:
    archivo_transacciones* _transacciones;  // Arreglo dinámico
    int totalTransacciones;
    int capacidadTransacciones;
```

**¿Por qué `protected`?**
- Permite que `caja_de_ahorro` acceda directamente al arreglo
- Facilita la herencia sin romper encapsulamiento
- `caja_de_ahorro` puede extender funcionalidad (validación de saldo)

**Métodos principales:**

#### `cargarTransaccionesDesdeArchivo()`
```cpp
void transacciones::cargarTransaccionesDesdeArchivo() {
    // Libera memoria previa
    // Lee archivo línea por línea (7 líneas = 1 transacción)
    // Valida campos numéricos con convertirALong/Entero
    // Redimensiona arreglo dinámicamente (patrón de duplicación)
}
```
**Justificación:**
- **Persistencia:** Lee del archivo `transacciones.txt`
- **Validación temprana:** Detecta errores de formato al cargar
- **Memoria dinámica:** Crece según necesidad (10, 20, 40, 80...)

#### `guardarTransaccionesEnArchivo()`
```cpp
void transacciones::guardarTransaccionesEnArchivo() {
    // Escribe todas las transacciones del arreglo al archivo
    // Formato: 7 líneas por transacción
}
```
**Justificación:** Persiste cambios en disco de forma consistente.

#### Métodos de consulta
- `mostrar_transacciones()`: Lista todas las transacciones
- `mostrar_transaccion_cliente(string numCliente)`: Filtra por número de cliente (recibe el número como parámetro)
- `transacciones_anio()`: Filtra por año
- `transacciones_mes()`: Filtra por mes y año

**Justificación:** Cumplen con los requisitos de informes de las consignas.

---

### 6. **Clase `caja_de_ahorro` (Hereda de `transacciones`)**

**Propósito:** Extender `transacciones` con funcionalidad específica de cuentas bancarias.

**Diseño:**
- **Herencia:** Reutiliza toda la gestión de transacciones
- **Extensión:** Agrega cálculo de saldo y validación

**Atributos propios:**
```cpp
private:
    float saldodolares;
    float saldopesos;
```

**¿Por qué herencia de `transacciones`?**
- **Relación "es-un":** Una caja de ahorro ES UN tipo especial de gestor de transacciones
- **Reutilización:** Aprovecha `cargarTransaccionesDesdeArchivo()`, `mostrar_transacciones()`, etc.
- **Extensión:** Añade lógica de negocio (validación de saldo) sin modificar la clase base
- **Principio Open/Closed:** `transacciones` está cerrada a modificaciones, abierta a extensión

**Métodos clave:**

#### `calcular_saldo_cliente(string numCliente)`
```cpp
void caja_de_ahorro::calcular_saldo_cliente(string numCliente) {
    setSaldoDolares(0.0);
    setSaldoPesos(0.0);
    
    cargarTransaccionesDesdeArchivo();  // Heredado
    
    // Itera transacciones del cliente
    for (int i = 0; i < totalTransacciones; i++) {
        if (_transacciones[i].NumCliente == numCliente) {
            float monto = convertirAFloat(_transacciones[i].Monto);
            
            if (TipoMoneda == "USD") {
                if (TipoTransaccion == "DEPOSITO")
                    setSaldoDolares(getSaldoDolares() + monto);
                else if (TipoTransaccion == "EXTRACCION")
                    setSaldoDolares(getSaldoDolares() - monto);
            }
            // Similar para ARS...
        }
    }
}
```
**Justificación:**
- **Cálculo dinámico:** Suma/resta todas las transacciones históricas
- **Separación por moneda:** Mantiene saldos independientes en USD y ARS
- **Sin persistencia de saldo:** El saldo se calcula en tiempo real desde transacciones

#### `registrar_transaccion()`
```cpp
void caja_de_ahorro::registrar_transaccion() {
    // Pide datos al usuario (con abreviaturas E/D, U/A)
    // Expande abreviaturas a EXTRACCION/DEPOSITO, USD/ARS
    
    if (TipoTransaccion == "EXTRACCION") {
        calcular_saldo_cliente(numCliente);  // Calcula saldo actual
        
        float montoFloat = convertirAFloat(monto);
        
        // VALIDACIÓN DE SALDO
        if (moneda == "USD" && getSaldoDolares() < montoFloat)
            throw ExcepcionArgumentoInvalido("Saldo insuficiente en USD");
        if (moneda == "ARS" && getSaldoPesos() < montoFloat)
            throw ExcepcionArgumentoInvalido("Saldo insuficiente en ARS");
    }
    
    // Valida campos numéricos
    // Carga, anexa, guarda
    // Muestra saldo actualizado
}
```
**Justificación:**
- **Validación de saldo:** Previene extracciones con fondos insuficientes (regla de negocio crítica)
- **UX mejorada:** Acepta abreviaturas (E/D, U/A) para rapidez
- **Validación de entrada:** Usa funciones de conversión que lanzan excepciones
- **Feedback inmediato:** Muestra saldo actualizado después de registrar

---

### 7. **Clase `banco` (Composición y Agregación)**

**Propósito:** Gestionar la colección de clientes y coordinar operaciones del banco.

**Diseño:**
- **Composición con `personal`:** El banco TIENE personal
- **Agregación con `cliente*`:** El banco gestiona clientes (arreglo dinámico)

**Atributos:**
```cpp
private:
    string nombre_banco;
    personal pr;              // Composición: parte integral del banco
    
    cliente* clientes;        // Agregación: arreglo dinámico
    int totalClientes;
    int capacidad;
```

**¿Por qué estas relaciones?**

#### Composición con `personal`:
- **Ciclo de vida compartido:** Un banco siempre tiene personal
- **Parte integral:** No tiene sentido un banco sin personal
- **Representa el dominio:** Aunque no se use activamente, modela la realidad

#### Agregación con `cliente*`:
- **Independencia:** Los clientes existen independientemente del banco
- **Memoria dinámica:** Número variable de clientes (crece según necesidad)
- **Gestión de recursos:** El banco es responsable de crear/destruir el arreglo

**Métodos principales:**

#### `cargarDesdeArchivo()`
```cpp
void banco::cargarDesdeArchivo() {
    ifstream archivo("Tabla de clientes.txt");
    
    while (true) {
        // Lee 6 líneas = 1 cliente
        getline(archivo, nombre);
        getline(archivo, dni);
        // ...
        
        // Valida campos numéricos
        convertirALong(dni);
        convertirAEntero(ingreso);
        
        // Redimensiona si es necesario (patrón de duplicación)
        if (totalClientes >= capacidad) {
            capacidad *= 2;
            cliente* nuevos = new cliente[capacidad];
            // Copia clientes existentes
            delete[] clientes;
            clientes = nuevos;
        }
        
        // Usa setters para asignar valores
        clientes[totalClientes].setNombre(nombre);
        // ...
        totalClientes++;
    }
}
```
**Justificación:**
- **Persistencia:** Carga datos desde archivo de texto
- **Validación:** Detecta errores de formato al inicio
- **Memoria dinámica eficiente:** Duplica capacidad cuando se llena (O(log n) redimensionamientos)
- **Encapsulamiento:** Usa setters en lugar de acceso directo

#### `getCuentaCliente(string numCliente)`
```cpp
caja_de_ahorro* banco::getCuentaCliente(string numCliente) {
    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].getNumeroCliente() == numCliente) {
            return &clientes[i].getCuenta();  // Retorna puntero a la cuenta
        }
    }
    return nullptr;  // Cliente no encontrado
}
```
**Justificación:**
- **Acceso controlado:** El banco media el acceso a las cuentas
- **Búsqueda por número:** Identifica cliente de forma única
- **Retorna puntero:** Permite modificar la cuenta desde el menú principal
- **Seguridad:** Retorna `nullptr` si el cliente no existe

#### `cambiarEstadoCliente(string numCliente)`
```cpp
void banco::cambiarEstadoCliente(string numCliente) {
    // Busca cliente
    // Alterna estado: ACTIVO <-> BAJA
    // Guarda cambios en archivo
}
```
**Justificación:** Implementa la funcionalidad de dar de baja clientes (consigna).

---

## 🔧 Funciones Utilitarias

### Funciones de Conversión con Validación

```cpp
int convertirAEntero(string entrada);
long convertirALong(string entrada);
float convertirAFloat(string entrada);
```

**Implementación:**
```cpp
int convertirAEntero(string entrada) {
    try {
        return stoi(entrada);
    }
    catch (const invalid_argument&) {
        throw ExcepcionArgumentoInvalido("Entrada no es un numero valido: " + entrada);
    }
    catch (const out_of_range&) {
        throw ExcepcionArgumentoInvalido("Numero fuera de rango: " + entrada);
    }
}
```

**¿Por qué estas funciones?**
- **Centralización:** Un único punto de validación de conversiones
- **Consistencia:** Todas las conversiones usan el mismo patrón
- **Excepciones unificadas:** Captura `std::invalid_argument` y `std::out_of_range`, lanza `ExcepcionArgumentoInvalido`
- **Debugging facilitado:** Mensaje de error incluye el valor problemático

**Uso en el código:**
```cpp
convertirALong(dni);          // Valida que DNI sea numérico
convertirAEntero(anio);       // Valida que año sea entero
convertirAFloat(monto);       // Valida que monto sea decimal
```

---

## 📊 Estructuras de Datos

### `archivo_clientes`
```cpp
struct archivo_clientes {
    string Nombre;
    string DNI;
    string Tipo;
    string Ingreso;
    string Estado;
    string NumCliente;
};
```
**Justificación:** Representa el formato del archivo de texto (6 líneas por cliente).

### `archivo_transacciones`
```cpp
struct archivo_transacciones {
    string NumCliente;
    string anio;
    string mes;
    string dia;
    string TipoTransaccion;  // DEPOSITO, EXTRACCION
    string TipoMoneda;       // USD, ARS
    string Monto;
};
```
**Justificación:** 
- Representa el formato del archivo de texto (7 líneas por transacción)
- Todo como `string` para facilitar lectura/escritura de archivos
- Conversión a numérico solo cuando es necesario calcular

---

## 🎯 Decisiones de Diseño Clave

### 1. **¿Por qué TODO como `string` en las estructuras?**

**Ventaja:**
- Facilita lectura/escritura de archivos de texto
- Evita problemas de conversión al persistir
- Validación flexible (se valida al usar, no al cargar)

**Desventaja:**
- Conversiones repetidas (mitigado con funciones utilitarias)

**Decisión:** Priorizar persistencia simple sobre eficiencia en memoria.

---

### 2. **¿Por qué arreglos dinámicos en lugar de `std::vector`?**

**Justificación:**
- Requisito académico: demostrar manejo manual de memoria
- Muestra comprensión de:
  - Punteros
  - `new` / `delete`
  - Redimensionamiento manual
  - Gestión de recursos (RAII)

**Implementación del patrón de duplicación:**
```cpp
if (totalElementos >= capacidad) {
    capacidad *= 2;  // Duplica capacidad
    Tipo* nuevos = new Tipo[capacidad];
    for (int i = 0; i < totalElementos; i++)
        nuevos[i] = existentes[i];  // Copia
    delete[] existentes;
    existentes = nuevos;
}
```

---

### 3. **¿Por qué NO hay saldo persistido, solo transacciones?**

**Decisión:** El saldo se calcula en tiempo real desde el historial de transacciones.

**Ventajas:**
- **Integridad:** Imposible tener saldo inconsistente con transacciones
- **Auditoría:** Todas las operaciones están registradas
- **Simplicidad:** Un solo archivo maestro (transacciones)

**Desventaja:**
- Cálculo repetido (mitigado: solo se calcula cuando se necesita)

---

### 4. **¿Por qué abreviaturas en input (E/D, U/A)?**

**Implementación:**
```cpp
if (input == "E" || input == "e")
    tipo = "EXTRACCION";
else if (input == "D" || input == "d")
    tipo = "DEPOSITO";
else
    throw ExcepcionArgumentoInvalido("Tipo invalido");
```

**Justificación:**
- **UX mejorada:** Usuario escribe menos
- **Validación estricta:** Solo acepta valores esperados
- **Almacenamiento completo:** Archivo tiene palabras completas (legibilidad)

---

### 5. **¿Por qué `protected` en `transacciones`?**

```cpp
class transacciones {
protected:  // No private
    archivo_transacciones* _transacciones;
    int totalTransacciones;
    int capacidadTransacciones;
};
```

**Justificación:**
- Permite que `caja_de_ahorro` acceda directamente al arreglo
- Necesario para `calcular_saldo_cliente()` que itera `_transacciones`
- Facilita la herencia sin romper encapsulamiento público

---

## 🚀 Flujo de Operaciones

### Registrar una Transacción

1. Usuario elige opción 4 en el menú
2. Sistema pide número de cliente, tipo (E/D), moneda (U/A), monto, fecha
3. Sistema expande abreviaturas (E→EXTRACCION, U→USD)
4. **Si es EXTRACCION:**
   - Calcula saldo actual del cliente
   - Valida fondos suficientes
   - Lanza excepción si saldo insuficiente
5. Valida campos numéricos (lanza excepción si inválidos)
6. Carga todas las transacciones del archivo
7. Agrega nueva transacción al arreglo (redimensiona si es necesario)
8. Guarda todo el arreglo al archivo
9. Calcula y muestra saldo actualizado

### Consultar Saldo

1. Usuario elige opción 5 y proporciona número de cliente
2. Sistema busca cliente en el banco
3. Obtiene referencia a la cuenta del cliente
4. Cuenta calcula saldo:
   - Resetea saldos a 0
   - Carga todas las transacciones
   - Filtra por número de cliente
   - Suma DEPOSITOS, resta EXTRACCIONES
   - Mantiene saldos separados (USD/ARS)
5. Muestra saldo en pantalla

---

## 📁 Estructura de Archivos

### `Tabla de clientes.txt`
```
Formato: 6 líneas por cliente
Línea 1: Nombre
Línea 2: DNI
Línea 3: Tipo (PLATA/ORO/PLATINO)
Línea 4: Año Ingreso
Línea 5: Estado (ACTIVO/BAJA)
Línea 6: Número Cliente
```

### `transacciones.txt`
```
Formato: 7 líneas por transacción
Línea 1: Número Cliente
Línea 2: Año
Línea 3: Mes
Línea 4: Día
Línea 5: Tipo Transacción (DEPOSITO/EXTRACCION)
Línea 6: Tipo Moneda (USD/ARS)
Línea 7: Monto
```

---

## ✅ Cumplimiento de Consignas

### Requisitos Funcionales

| Requisito | Implementación | Clase/Método |
|-----------|----------------|--------------|
| Mantener lista de clientes | ✅ | `banco::clientes` (arreglo dinámico) |
| Cambiar estado ACTIVO/BAJA | ✅ | `banco::cambiarEstadoCliente()` |
| Registrar datos de clientes | ✅ | `cliente` con setters/getters |
| Guardar clientes en archivo | ✅ | `banco::guardarEnArchivo()` |
| Transacciones en Caja de Ahorro | ✅ | `caja_de_ahorro` (hereda de `transacciones`) |
| Depósitos y Extracciones | ✅ | `caja_de_ahorro::registrar_transaccion()` |
| Validación de saldo | ✅ | Validación en `registrar_transaccion()` antes de EXTRACCION |
| Tarjetas de crédito por tipo | ✅ | `cliente::mostrar_info_tarjeta_credito()` |
| - PLATA: Sin acceso | ✅ | Condicional en método |
| - ORO: Credix $250K | ✅ | Condicional en método |
| - PLATINO: Premium $500K | ✅ | Condicional en método |
| Detalle de cliente | ✅ | `banco::mostrarDetallesCliente()` |
| Listado de clientes | ✅ | `banco::mostrarListaClientes()` |
| Listado de transacciones | ✅ | `transacciones::mostrar_transacciones()` |
| Transacciones por cliente | ✅ | `transacciones::mostrar_transaccion_cliente(string numCliente)` |
| Informes por mes | ✅ | `transacciones::transacciones_mes()` |
| Informes por año | ✅ | `transacciones::transacciones_anio()` |

### Requisitos Técnicos (POO)

| Concepto | Implementación | Ubicación |
|----------|----------------|-----------|
| **Herencia** | ✅ | `persona` → `cliente`, `personal` |
| | ✅ | `transacciones` → `caja_de_ahorro` |
| | ✅ | `Excepcion` → `ExcepcionArgumentoInvalido`, `ExcepcionMemoria` |
| **Composición** | ✅ | `cliente` TIENE `caja_de_ahorro` |
| | ✅ | `banco` TIENE `personal` |
| **Agregación** | ✅ | `banco` gestiona `cliente*` |
| | ✅ | `transacciones` gestiona `archivo_transacciones*` |
| **Polimorfismo** | ✅ | Método virtual `persona::mostrar_datos()` |
| | ✅ | Jerarquía de excepciones con `virtual error()` |
| **Encapsulamiento** | ✅ | Todos los atributos privados/protected |
| | ✅ | Acceso solo mediante setters/getters |
| **Abstracción** | ✅ | Clases base (`persona`, `Excepcion`) |
| **Manejo de excepciones** | ✅ | Try-catch en `main`, throw en validaciones |
| **Memoria dinámica** | ✅ | Arreglos dinámicos con `new`/`delete` |
| | ✅ | Destructores para liberar memoria |
| **Archivos de texto** | ✅ | `ifstream`/`ofstream` con formato línea por línea |

---

## 🛠️ Compilación y Ejecución

### Método 1: Scripts de Ejecución Automática (Recomendado)

#### En Linux/Mac
```bash
./run.sh
```
Este script:
- Compila automáticamente el proyecto
- Ejecuta el programa si la compilación es exitosa
- Muestra un encabezado de bienvenida
- Pausa la terminal al finalizar

#### En Windows
Doble clic en `run.bat` o desde CMD:
```cmd
run.bat
```
Este script:
- Compila automáticamente el proyecto
- Ejecuta el programa si la compilación es exitosa
- Muestra un encabezado de bienvenida
- Pausa la terminal al finalizar

---

### Método 2: Compilación Manual

#### Compilar
```bash
g++ -std=c++11 main.cpp proyecto.cpp -o app
```

#### Ejecutar
**Linux/Mac:**
```bash
./app
```

**Windows:**
```cmd
app.exe
```

---

### Requisitos
- Compilador compatible con C++11 (`g++`, `clang++`, MinGW en Windows)
- Archivos de datos en el mismo directorio:
  - `Tabla de clientes.txt`
  - `transacciones.txt`

---

## 🧪 Ejemplo de Uso

### Registrar Transacción
```
Ingrese numero de cliente: 1001
Tipo de transaccion (E=Extraccion / D=Deposito): D
Tipo de moneda (U=USD / A=ARS): U
Monto: 5000
Ingrese anio (YYYY): 2025
Ingrese mes (MM o numero): 11
Ingrese dia (DD): 10

Transaccion registrada correctamente.
Saldo actualizado del cliente #1001:
Saldo en USD: 5000 | Saldo en ARS: 0
```

### Consultar Saldo
```
Ingrese numero de cliente para consultar saldo: 1001

===== SALDO CLIENTE #1001 =====
Saldo en USD: 5000 | Saldo en ARS: 0
```

### Intento de Extracción sin Fondos
```
Tipo de transaccion (E=Extraccion / D=Deposito): E
Tipo de moneda (U=USD / A=ARS): U
Monto: 10000

Error al registrar transaccion: Saldo insuficiente en USD. Saldo actual: 5000
```

---

## 📚 Conceptos de POO Aplicados

### 1. **Herencia**
- `cliente` y `personal` heredan de `persona` (reutilización de código)
- `caja_de_ahorro` hereda de `transacciones` (extensión de funcionalidad)

### 2. **Polimorfismo**
- `virtual void mostrar_datos()` permite llamar a la versión correcta según el tipo real
- `virtual string error()` en excepciones

### 3. **Encapsulamiento**
- Atributos privados/protected
- Acceso controlado mediante métodos públicos

### 4. **Composición**
- `cliente` TIENE `caja_de_ahorro` (fuerte)
- `banco` TIENE `personal` (fuerte)

### 5. **Agregación**
- `banco` gestiona `cliente*` (débil, clientes pueden existir independientemente)

### 6. **Abstracción**
- Clases base definen interfaz común
- Detalles de implementación ocultos

---

## 🎓 Conclusión

Este proyecto demuestra una implementación completa de un sistema bancario utilizando principios sólidos de Programación Orientada a Objetos en C++. Cada decisión de diseño está justificada por requisitos funcionales o principios de ingeniería de software.

**Fortalezas del diseño:**
- ✅ Separación clara de responsabilidades
- ✅ Reutilización de código mediante herencia
- ✅ Encapsulamiento estricto
- ✅ Manejo robusto de errores
- ✅ Persistencia mediante archivos de texto
- ✅ Validación exhaustiva de datos
- ✅ Código mantenible y extensible

**Autores:** Augusto Garcia, Facundo Grillo y Gonzalo Marin
**Fecha:** Octubre - Noviembre 2025  
**Curso:** Programación Orientada a Objetos
