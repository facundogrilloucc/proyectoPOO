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
cliente::cliente(long _dni, string _nombre, int _anio_ingreso, string _tipo_cliente, string _estado_cliente, long _numero_cliente): persona(_dni, _nombre, _anio_ingreso)
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

personal::personal(long _dni, string _nombre, int _anio_ingreso, string _area_trabajo) : persona(_dni, _nombre, _anio_ingreso)
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
    // Inicializar arreglos dinámicos
    capacidad = 10;
    totalClientes = 0;
    nombres = new string[capacidad];
    dnis = new string[capacidad];
    tipos = new string[capacidad];
    ingresos = new string[capacidad];
    estados = new string[capacidad];
    numClientes = new string[capacidad];
    
    if (nombres == nullptr || dnis == nullptr || tipos == nullptr || 
        ingresos == nullptr || estados == nullptr || numClientes == nullptr)
        throw ExcepcionMemoria("No se pudo asignar memoria para los arreglos");
}

banco::banco(string _nombre_banco, archivo_clientes _lista_clientes, cliente _cl, personal _pr)
{
    nombre_banco = _nombre_banco;
    lista_clientes = _lista_clientes;
    cl = _cl;
    pr = _pr;
    
    // Inicializar arreglos dinámicos
    capacidad = 10;
    totalClientes = 0;
    nombres = new string[capacidad];
    dnis = new string[capacidad];
    tipos = new string[capacidad];
    ingresos = new string[capacidad];
    estados = new string[capacidad];
    numClientes = new string[capacidad];
    
    if (nombres == nullptr || dnis == nullptr || tipos == nullptr || 
        ingresos == nullptr || estados == nullptr || numClientes == nullptr)
        throw ExcepcionMemoria("No se pudo asignar memoria para los arreglos");
}

banco::~banco()
{
    // Liberar memoria
    delete[] nombres;
    delete[] dnis;
    delete[] tipos;
    delete[] ingresos;
    delete[] estados;
    delete[] numClientes;
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

// Función para cargar todos los clientes desde el archivo
void banco::cargarDesdeArchivo()
{
    try
    {
        ifstream archivo("Tabla de clientes.txt");
        
        if (!archivo.is_open())
            throw ExcepcionArgumentoInvalido("No se pudo abrir el archivo");
        
        totalClientes = 0;
        
        // Leer clientes (cada 6 líneas = 1 cliente)
        while (true)
        {
            // Si necesitamos más espacio, redimensionar
            if (totalClientes >= capacidad)
            {
                capacidad *= 2;
                string* nuevosNombres = new string[capacidad];
                string* nuevosDnis = new string[capacidad];
                string* nuevosTipos = new string[capacidad];
                string* nuevosIngresos = new string[capacidad];
                string* nuevosEstados = new string[capacidad];
                string* nuevosNumClientes = new string[capacidad];
                
                if (nuevosNombres == nullptr || nuevosDnis == nullptr || nuevosTipos == nullptr ||
                    nuevosIngresos == nullptr || nuevosEstados == nullptr || nuevosNumClientes == nullptr)
                    throw ExcepcionMemoria("No se pudo redimensionar");
                
                // Copiar datos existentes
                for (int i = 0; i < totalClientes; i++)
                {
                    nuevosNombres[i] = nombres[i];
                    nuevosDnis[i] = dnis[i];
                    nuevosTipos[i] = tipos[i];
                    nuevosIngresos[i] = ingresos[i];
                    nuevosEstados[i] = estados[i];
                    nuevosNumClientes[i] = numClientes[i];
                }
                
                // Liberar memoria anterior
                delete[] nombres;
                delete[] dnis;
                delete[] tipos;
                delete[] ingresos;
                delete[] estados;
                delete[] numClientes;
                
                // Asignar nuevos arreglos
                nombres = nuevosNombres;
                dnis = nuevosDnis;
                tipos = nuevosTipos;
                ingresos = nuevosIngresos;
                estados = nuevosEstados;
                numClientes = nuevosNumClientes;
            }
            
            // Leer 6 líneas (1 cliente)
            string nombre, dni, tipo, ingreso, estado, numCliente;
            
            if (!getline(archivo, nombre)) break;      // Línea 1: Nombre
            if (!getline(archivo, dni)) break;         // Línea 2: DNI
            if (!getline(archivo, tipo)) break;        // Línea 3: Tipo
            if (!getline(archivo, ingreso)) break;     // Línea 4: Año Ingreso
            if (!getline(archivo, estado)) break;      // Línea 5: Estado
            if (!getline(archivo, numCliente)) break;  // Línea 6: NumCliente
            
            // Guardar en arreglos
            nombres[totalClientes] = nombre;
            dnis[totalClientes] = dni;
            tipos[totalClientes] = tipo;
            ingresos[totalClientes] = ingreso;
            estados[totalClientes] = estado;
            numClientes[totalClientes] = numCliente;
            
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
        
        // Escribir todos los clientes (6 líneas por cliente)
        for (int i = 0; i < totalClientes; i++)
        {
            archivo << nombres[i] << endl;
            archivo << dnis[i] << endl;
            archivo << tipos[i] << endl;
            archivo << ingresos[i] << endl;
            archivo << estados[i] << endl;
            archivo << numClientes[i] << endl;
        }
        
        archivo.close();
    }
    catch (const ExcepcionArgumentoInvalido& e)
    {
        cerr << "Error al guardar: " << e.what() << endl;
    }
}

// Implementación de las funciones de gestión de clientes del banco

// Función para mostrar la lista de todos los clientes (desde memoria)
void banco::mostrarListaClientes()
{
    cout << "\n========== LISTA DE CLIENTES ==========" << endl;
    cout << "---------------------------------------" << endl;
    
    for (int i = 0; i < totalClientes; i++)
    {
        cout << "Cliente #" << numClientes[i] << " - " << nombres[i] 
             << " | DNI: " << dnis[i] 
             << " | Tipo: " << tipos[i] 
             << " | Estado: " << estados[i] 
             << " | Año de Ingreso: " << ingresos[i] << endl;
    }
    
    cout << "---------------------------------------" << endl;
    cout << "Total de clientes: " << totalClientes << endl;
    cout << "========================================\n" << endl;
}

// Función para mostrar todos los detalles de un cliente específico por número (desde memoria)
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
        if (numClientes[i] == numCliente)
        {
            encontrado = true;
            cout << "\n========== DETALLES DEL CLIENTE ==========" << endl;
            cout << "Número de Cliente: " << numClientes[i] << endl;
            cout << "Nombre: " << nombres[i] << endl;
            cout << "DNI: " << dnis[i] << endl;
            cout << "Tipo de Cliente: " << tipos[i] << endl;
            cout << "Año de Ingreso: " << ingresos[i] << endl;
            cout << "Estado: " << estados[i] << endl;
            cout << "==========================================\n" << endl;
            break;
        }
    }
    
    if (!encontrado)
        cout << "\nCliente #" << numCliente << " no encontrado." << endl;
}

// Función para cambiar el estado de un cliente (ACTIVO <-> BAJA) desde memoria
void banco::cambiarEstadoCliente(string numCliente)
{
    if (numCliente.empty())
    {
        cout << "\nEl número de cliente no puede estar vacío." << endl;
        return;
    }
    
    bool encontrado = false;
    string nuevoEstado;
    string nombreCliente;
    
    for (int i = 0; i < totalClientes; i++)
    {
        if (numClientes[i] == numCliente)
        {
            encontrado = true;
            nombreCliente = nombres[i];
            
            // Cambiar estado
            nuevoEstado = (estados[i] == "ACTIVO") ? "BAJA" : "ACTIVO";
            estados[i] = nuevoEstado;
            
            // Guardar cambios en el archivo
            guardarEnArchivo();
            
            cout << "\nEstado del cliente #" << numCliente << " (" << nombreCliente 
                 << ") cambiado exitosamente a: " << nuevoEstado << endl;
            break;
        }
    }
    
    if (!encontrado)
        cout << "\nCliente #" << numCliente << " no encontrado." << endl;
}

