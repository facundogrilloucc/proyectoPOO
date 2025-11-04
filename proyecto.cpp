#include "proyecto.h"

// Implementación de la clase persona
persona::persona() {}
persona::persona(string _dni, string _nombre, string _anio_ingreso)
{
    dni = _dni;
    nombre = _nombre;
    anio_ingreso = _anio_ingreso;
}

void persona::setDNI(string _dni)
{
    dni = _dni;
}

string persona::getDNI()
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

void persona::setAnioIngreso(string _anio_ingreso)
{
    anio_ingreso = _anio_ingreso;
}

string persona::getAnioIngreso()
{
    return anio_ingreso;
}

void persona::mostrar_datos()
{
    cout << "Nombre: " << nombre << ". DNI: " << dni << ". Anio de Ingreso: " << anio_ingreso << "." << endl;
}

// Implementación de la clase cliente
cliente::cliente() {}
cliente::cliente(string _dni, string _nombre, string _anio_ingreso, string _tipo_cliente, string _estado_cliente, string _numero_cliente): persona(_dni, _nombre, _anio_ingreso)
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

void cliente::setNumeroCliente(string _numero_cliente)
{
    numero_cliente = _numero_cliente;
}

string cliente::getNumeroCliente()
{
    return numero_cliente;
}

void cliente::mostrar_datos()
{
    persona::mostrar_datos();
    cout << "Tipo de Cliente: " << tipo_cliente << ". Estado: " << estado_cliente << ". Numero de Cliente: " << numero_cliente << "." << endl;
}

// Implementación de la clase personal
personal::personal() {}
personal::personal(string _dni, string _nombre, string _anio_ingreso, string _area_trabajo) : persona(_dni, _nombre, _anio_ingreso)
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
banco::banco()
{
    capacidad = 10;
    totalClientes = 0;
    clientes = new cliente[capacidad];
    
    if (clientes == nullptr)
        throw ExcepcionMemoria("No se pudo asignar memoria para los clientes");
}


banco::~banco()
{
    // Liberar memoria del arreglo de clientes
    delete[] clientes;
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

// Función para cargar todos los clientes desde el archivo 
void banco::cargarDesdeArchivo()
{
    try
    {
        ifstream archivo("Tabla de clientes.txt");
        
        if (!archivo.is_open())
            throw ExcepcionArgumentoInvalido("No se pudo abrir el archivo");
        
        totalClientes = 0;
        
        // Leer clientes y crear objetos usando setters
        while (true)
        {
            // Si necesitamos más espacio, redimensionar
            if (totalClientes >= capacidad)
            {
                capacidad *= 2;
                cliente* nuevosClientes = new cliente[capacidad];
                
                if (nuevosClientes == nullptr)
                    throw ExcepcionMemoria("No se pudo redimensionar el arreglo de clientes");
                
                // Copiar objetos existentes
                for (int i = 0; i < totalClientes; i++)
                {
                    nuevosClientes[i] = clientes[i];
                }
                
                // Liberar memoria anterior
                delete[] clientes;
                
                // Asignar nuevo arreglo
                clientes = nuevosClientes;
            }
            
            // Leer 6 líneas del archivo (1 cliente)
            string nombre, dni, tipo, ingreso, estado, numCliente;
            
            if (!getline(archivo, nombre)) break;      // Línea 1: Nombre
            if (!getline(archivo, dni)) break;         // Línea 2: DNI
            if (!getline(archivo, tipo)) break;        // Línea 3: Tipo
            if (!getline(archivo, ingreso)) break;     // Línea 4: Año Ingreso
            if (!getline(archivo, estado)) break;      // Línea 5: Estado
            if (!getline(archivo, numCliente)) break;  // Línea 6: NumCliente
            
            // Crear objeto cliente usando SETTERS
            clientes[totalClientes].setNombre(nombre);
            clientes[totalClientes].setDNI(dni);
            clientes[totalClientes].setAnioIngreso(ingreso);
            clientes[totalClientes].setTipoCliente(tipo);
            clientes[totalClientes].setEstadoCliente(estado);
            clientes[totalClientes].setNumeroCliente(numCliente);
            
            totalClientes++;
        }
        
        archivo.close();
        cout << "Datos cargados: " << totalClientes << " clientes en memoria." << endl;
    }
    catch (const ExcepcionArgumentoInvalido& e)
    {
        cerr << "Error al cargar: " << e.what() << endl;
    }
    catch (const ExcepcionMemoria& e)
    {
        cerr << "Error de memoria: " << e.what() << endl;
    }
}

// Función para guardar todos los clientes en el archivo 
void banco::guardarEnArchivo()
{
    try
    {
        ofstream archivo("Tabla de clientes.txt");
        
        if (!archivo.is_open())
            throw ExcepcionArgumentoInvalido("No se pudo abrir el archivo para escritura");
        
        for (int i = 0; i < totalClientes; i++)
        {
            archivo << clientes[i].getNombre() << endl;
            archivo << clientes[i].getDNI() << endl;
            archivo << clientes[i].getTipoCliente() << endl;
            archivo << clientes[i].getAnioIngreso() << endl;
            archivo << clientes[i].getEstadoCliente() << endl;
            archivo << clientes[i].getNumeroCliente() << endl;
        }
        
        archivo.close();
    }
    catch (const ExcepcionArgumentoInvalido& e)
    {
        cerr << "Error al guardar: " << e.what() << endl;
    }
}

// Implementación de las funciones de gestión de clientes del banco

// Función para mostrar la lista de todos los clientes (POO con getters)
void banco::mostrarListaClientes()
{
    cout << "\n========== LISTA DE CLIENTES ==========" << endl;
    cout << "---------------------------------------" << endl;
    
    for (int i = 0; i < totalClientes; i++)
    {
        cout << "Cliente #" << clientes[i].getNumeroCliente() << " - " << clientes[i].getNombre() 
             << " | DNI: " << clientes[i].getDNI() 
             << " | Tipo: " << clientes[i].getTipoCliente() 
             << " | Estado: " << clientes[i].getEstadoCliente() 
             << " | Año de Ingreso: " << clientes[i].getAnioIngreso() << endl;
    }
    
    cout << "---------------------------------------" << endl;
    cout << "Total de clientes: " << totalClientes << endl;
    cout << "========================================\n" << endl;
}

// Función para mostrar detalles del cliente (POO - usa mostrar_datos())
void banco::mostrarDetallesCliente(string numCliente)
{
    if (numCliente.empty())
    {
        cout << "\nEl número de cliente no puede estar vacío." << endl;
        return;
    }
    
    bool encontrado = false;
    
    for (int i = 0; i < totalClientes; i++)
    {
        if (clientes[i].getNumeroCliente() == numCliente)
        {
            encontrado = true;
            cout << "\n========== DETALLES DEL CLIENTE ==========" << endl;
            cout << "Número de Cliente: " << clientes[i].getNumeroCliente() << endl;
            
            clientes[i].mostrar_datos();
            
            cout << "==========================================\n" << endl;
            break;
        }
    }
    
    if (!encontrado)
        cout << "\nCliente #" << numCliente << " no encontrado." << endl;
}

// Función para cambiar el estado de un cliente 
void banco::cambiarEstadoCliente(string numCliente)
{
    if (numCliente.empty())
    {
        cout << "\nEl número de cliente no puede estar vacío." << endl;
        return;
    }
    
    bool encontrado = false;
    
    for (int i = 0; i < totalClientes; i++)
    {
        if (clientes[i].getNumeroCliente() == numCliente)
        {
            encontrado = true;
            string nombreCliente = clientes[i].getNombre();
            string estadoActual = clientes[i].getEstadoCliente();
            
            string nuevoEstado = (estadoActual == "ACTIVO") ? "BAJA" : "ACTIVO";
            clientes[i].setEstadoCliente(nuevoEstado);
         
            guardarEnArchivo();
            
            cout << "\nEstado del cliente #" << numCliente << " (" << nombreCliente << ") cambiado exitosamente a: " << nuevoEstado << endl;
            break;
        }
    }
    
    if (!encontrado)
        cout << "\nCliente #" << numCliente << " no encontrado." << endl;
}

