#include "proyecto.h"

persona::persona() {}
persona::persona(long _dni, string _nombre, int _anio_ingreso)
{
    dni = _dni;
    nombre = _nombre;
    anio_ingreso = _anio_ingreso;
}

void persona::setDNI(long _dni)
{
    dni = _dni;
}

long persona::getDNI()
{
    return dni;
}

void persona::setNombre(string _nombre)
{
    nombre = _nombre;
}

string persona::getNombre()
{
    return nombre;
}

void persona::setAnioIngreso(int _anio_ingreso)
{
    anio_ingreso = _anio_ingreso;
}

int persona::getAnioIngreso()
{
    return anio_ingreso;
}

void persona::mostrar_datos()
{
    cout << "Nombre: " << nombre << ". DNI: " << dni << ". Anio de Ingreso: " << anio_ingreso << "." << endl;
}

// Implementación de la clase cliente
cliente::cliente() {}

cliente::cliente(long _dni, string _nombre, int _anio_ingreso, string _tipo_cliente, string _estado_cliente, long _numero_cliente)
    : persona(_dni, _nombre, _anio_ingreso)
{
    tipo_cliente = _tipo_cliente;
    estado_cliente = _estado_cliente;
    numero_cliente = _numero_cliente;
}

void cliente::setTipoCliente(string _tipo_cliente)
{
    tipo_cliente = _tipo_cliente;
}

string cliente::getTipoCliente()
{
    return tipo_cliente;
}

void cliente::setEstadoCliente(string _estado_cliente)
{
    estado_cliente = _estado_cliente;
}

string cliente::getEstadoCliente()
{
    return estado_cliente;
}

void cliente::setNumeroCliente(long _numero_cliente)
{
    numero_cliente = _numero_cliente;
}

long cliente::getNumeroCliente()
{
    return numero_cliente;
}

void cliente::mostrar_datos()
{
    persona::mostrar_datos();
    cout << "Tipo de Cliente: " << tipo_cliente << ". Estado: " << estado_cliente 
         << ". Numero de Cliente: " << numero_cliente << "." << endl;
}

// Implementación de la clase personal
personal::personal() {}

personal::personal(long _dni, string _nombre, int _anio_ingreso, string _area_trabajo)
    : persona(_dni, _nombre, _anio_ingreso)
{
    area_trabajo = _area_trabajo;
}

void personal::setAreaTrabajo(string _area_trabajo)
{
    area_trabajo = _area_trabajo;
}

string personal::getAreaTrabajo()
{
    return area_trabajo;
}

void personal::mostrar_datos()
{
    persona::mostrar_datos();
    cout << "Area de Trabajo: " << area_trabajo << "." << endl;
}

// Implementación de la clase banco
banco::banco() {}

banco::banco(string _nombre_banco, archivo_clientes _lista_clientes, cliente _cl, personal _pr)
{
    nombre_banco = _nombre_banco;
    lista_clientes = _lista_clientes;
    cl = _cl;
    pr = _pr;
}

void banco::setNombreBanco(string _nombre_banco)
{
    nombre_banco = _nombre_banco;
}

string banco::getNombreBanco()
{
    return nombre_banco;
}

void banco::setArchivoClientes(archivo_clientes _lista_clientes)
{
    lista_clientes = _lista_clientes;
}

archivo_clientes banco::getArchivoClientes()
{
    return lista_clientes;
}

void banco::setCliente(cliente _cl)
{
    cl = _cl;
}

cliente banco::getCliente()
{
    return cl;
}

void banco::setPersonal(personal _pr)
{
    pr = _pr;
}

personal banco::getPersonal()
{
    return pr;
}

void banco::mostrar_datos()
{
    cout << "Nombre del Banco: " << nombre_banco << endl;
}

// Implementación de las funciones de gestión de clientes del banco

// Función para mostrar la lista de todos los clientes del archivo CSV
void banco::mostrarListaClientes()
{
    ifstream archivo("Tabla de clientes.csv");
    
    if (!archivo.is_open())
    {
        cout << "Error: No se pudo abrir el archivo 'Tabla de clientes.csv'" << endl;
        return;
    }
    
    string linea;
    int contador = 0;
    
    cout << "\n========== LISTA DE CLIENTES ==========" << endl;
    cout << "---------------------------------------" << endl;
    
// Leer la primera línea de la tabla (las secciones)
    getline(archivo, linea);
    
// Leer y mostrar cada cliente
    while (getline(archivo, linea))
    {
        stringstream ss(linea);
        string nombre, dni, tipo, ingreso, estado, numCliente;
        
        getline(ss, nombre, ';');
        getline(ss, dni, ';');
        getline(ss, tipo, ';');
        getline(ss, ingreso, ';');
        getline(ss, estado, ';');
        getline(ss, numCliente, ';');
        
        contador++;
        cout << "Cliente #" << numCliente << " - " << nombre << " | DNI: " << dni << " | Tipo: " << tipo << " | Estado: " << estado << " | Año de Ingreso: " << ingreso << endl;
    }
    
    cout << "---------------------------------------" << endl;
    cout << "Total de clientes: " << contador << endl;
    cout << "========================================\n" << endl;
    
    archivo.close();
}

// Función para mostrar todos los detalles de un cliente específico por número
void banco::mostrarDetallesCliente(int numCliente)
{
    ifstream archivo("Tabla de clientes.csv");
    
    if (!archivo.is_open())
    {
        cout << "Error: No se pudo abrir el archivo 'Tabla de clientes.csv'" << endl;
        return;
    }
    
    string linea;
    bool encontrado = false;
    
    // Leer la primera línea (encabezado)
    getline(archivo, linea);
    
    // Buscar el cliente por número
    while (getline(archivo, linea))
    {
        stringstream ss(linea);
        string nombre, dni, tipo, ingreso, estado, numClienteStr;
        
        getline(ss, nombre, ';');
        getline(ss, dni, ';');
        getline(ss, tipo, ';');
        getline(ss, ingreso, ';');
        getline(ss, estado, ';');
        getline(ss, numClienteStr, ';');
        
        if (stoi(numClienteStr) == numCliente)
        {
            encontrado = true;
            cout << "\n========== DETALLES DEL CLIENTE ==========" << endl;
            cout << "Número de Cliente: " << numClienteStr << endl;
            cout << "Nombre: " << nombre << endl;
            cout << "DNI: " << dni << endl;
            cout << "Tipo de Cliente: " << tipo << endl;
            cout << "Año de Ingreso: " << ingreso << endl;
            cout << "Estado: " << estado << endl;
            cout << "==========================================\n" << endl;
            break;
        }
    }
    
    if (!encontrado)
    {
        cout << "\nCliente #" << numCliente << " no encontrado." << endl;
    }
    
    archivo.close();
}

// Función para cambiar el estado de un cliente (ACTIVO <-> BAJA)
void banco::cambiarEstadoCliente(int numCliente)
{
    ifstream archivoEntrada("Tabla de clientes.csv");
    
    if (!archivoEntrada.is_open())
    {
        cout << "Error: No se pudo abrir el archivo 'Tabla de clientes.csv'" << endl;
        return;
    }
    
    vector<string> lineas;
    string linea;
    bool encontrado = false;
    string nuevoEstado;
    string nombreCliente;
    
    // Leer la primera línea (encabezado)
    getline(archivoEntrada, linea);
    lineas.push_back(linea);
    
    // Leer todas las líneas y modificar la correspondiente
    while (getline(archivoEntrada, linea))
    {
        stringstream ss(linea);
        string nombre, dni, tipo, ingreso, estado, numClienteStr;
        
        getline(ss, nombre, ';');
        getline(ss, dni, ';');
        getline(ss, tipo, ';');
        getline(ss, ingreso, ';');
        getline(ss, estado, ';');
        getline(ss, numClienteStr, ';');
        
        if (stoi(numClienteStr) == numCliente)
        {
            encontrado = true;
            nombreCliente = nombre;
            
            // Cambiar el estado
            if (estado == "ACTIVO")
            {
                nuevoEstado = "BAJA";
            }
            else
            {
                nuevoEstado = "ACTIVO";
            }
            
            // Reconstruir la línea con el nuevo estado
            linea = nombre + ";" + dni + ";" + tipo + ";" + ingreso + ";" + nuevoEstado + ";" + numClienteStr;
        }
        
        lineas.push_back(linea);
    }
    
    archivoEntrada.close();
    
    if (!encontrado)
    {
        cout << "\nCliente #" << numCliente << " no encontrado." << endl;
        return;
    }
    
    // Escribir todas las líneas de vuelta al archivo
    ofstream archivoSalida("Tabla de clientes.csv");
    
    if (!archivoSalida.is_open())
    {
        cout << "Error: No se pudo escribir en el archivo 'Tabla de clientes.csv'" << endl;
        return;
    }
    
    for (const string& l : lineas)
    {
        archivoSalida << l << endl;
    }
    
    archivoSalida.close();
    
    cout << "\nEstado del cliente #" << numCliente << " (" << nombreCliente << ") cambiado exitosamente a: " << nuevoEstado << endl;
}

