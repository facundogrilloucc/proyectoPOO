#include "proyecto.h"

// Implementación de las clases de excepciones
Excepcion::Excepcion()
{
    mensaje = "Error desconocido";
}

Excepcion::Excepcion(string msg)
{
    mensaje = msg;
}

ExcepcionArgumentoInvalido::ExcepcionArgumentoInvalido()
{
    mensaje = "Argumento inválido";
}

ExcepcionArgumentoInvalido::ExcepcionArgumentoInvalido(string msg)
{
    mensaje = msg;
}

ExcepcionMemoria::ExcepcionMemoria()
{
    mensaje = "Error de asignación de memoria";
}

ExcepcionMemoria::ExcepcionMemoria(string msg)
{
    mensaje = msg;
}

string Excepcion::error() const
{
    return mensaje;
}

Excepcion::~Excepcion() {}

// Funciones de conversión con validación
int convertirAEntero(string entrada)
{
    try
    {
        return stoi(entrada);
    }
    catch (const invalid_argument &)
    {
        throw ExcepcionArgumentoInvalido("Entrada no es un numero valido: " + entrada);
    }
    catch (const out_of_range &)
    {
        throw ExcepcionArgumentoInvalido("Numero fuera de rango: " + entrada);
    }
}

long convertirALong(string entrada)
{
    try
    {
        return stol(entrada);
    }
    catch (const invalid_argument &)
    {
        throw ExcepcionArgumentoInvalido("Entrada no es un numero valido: " + entrada);
    }
    catch (const out_of_range &)
    {
        throw ExcepcionArgumentoInvalido("Numero fuera de rango: " + entrada);
    }
}

float convertirAFloat(string entrada)
{
    try
    {
        return stof(entrada);
    }
    catch (const invalid_argument &)
    {
        throw ExcepcionArgumentoInvalido("Entrada no es un numero valido: " + entrada);
    }
    catch (const out_of_range &)
    {
        throw ExcepcionArgumentoInvalido("Numero fuera de rango: " + entrada);
    }
}

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
cliente::cliente(string _dni, string _nombre, string _anio_ingreso, string _tipo_cliente, string _estado_cliente, string _numero_cliente) : persona(_dni, _nombre, _anio_ingreso)
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
    mostrar_info_tarjeta_credito();
}

void cliente::mostrar_info_tarjeta_credito()
{
    cout << "Informacion de Tarjeta de Credito: ";

    if (tipo_cliente == "PLATA" || tipo_cliente == "Plata")
    {
        cout << "No tiene acceso a tarjeta de credito." << endl;
    }
    else if (tipo_cliente == "ORO" || tipo_cliente == "Oro")
    {
        cout << "Tarjeta Credix - Limite: $250,000" << endl;
    }
    else if (tipo_cliente == "PLATINO" || tipo_cliente == "Platino")
    {
        cout << "Tarjeta Premium - Limite: $500,000" << endl;
    }
    else
    {
        cout << "Tipo de cliente no reconocido." << endl;
    }
}

caja_de_ahorro& cliente::getCuenta()
{
    return cuenta;
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

        while (true)
        {
            // Si necesitamos más espacio, redimensionar
            if (totalClientes >= capacidad)
            {
                capacidad *= 2;
                cliente *nuevosClientes = new cliente[capacidad];

                if (nuevosClientes == nullptr)
                    throw ExcepcionMemoria("No se pudo redimensionar el arreglo de clientes");

                for (int i = 0; i < totalClientes; i++)
                {
                    nuevosClientes[i] = clientes[i];
                }

                // Liberar memoria anterior
                delete[] clientes;

                clientes = nuevosClientes;
            }

            // Leer 6 líneas del archivo (1 cliente)
            string nombre, dni, tipo, ingreso, estado, numCliente;

            if (!getline(archivo, nombre))
                break; // Línea 1: Nombre
            if (!getline(archivo, dni))
                break; // Línea 2: DNI
            if (!getline(archivo, tipo))
                break; // Línea 3: Tipo
            if (!getline(archivo, ingreso))
                break; // Línea 4: Año Ingreso
            if (!getline(archivo, estado))
                break; // Línea 5: Estado
            if (!getline(archivo, numCliente))
                break; // Línea 6: NumCliente

            // Convertir datos numericos
            convertirALong(dni);
            convertirAEntero(ingreso);
            convertirALong(numCliente);

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
    catch (const ExcepcionArgumentoInvalido &e)
    {
        cerr << "Error al cargar: " << e.error() << endl;
    }
    catch (const ExcepcionMemoria &e)
    {
        cerr << "Error de memoria: " << e.error() << endl;
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
    catch (const ExcepcionArgumentoInvalido &e)
    {
        cerr << "Error al guardar: " << e.error() << endl;
    }
}

// Implementación de las funciones de gestión de clientes del banco

// Función para mostrar la lista de todos los clientes
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
    cout << "========================================\n"
         << endl;
}

// Función para mostrar detalles del cliente según su número
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

            cout << "==========================================\n"
                 << endl;
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

// Función para obtener la cuenta de un cliente específico
caja_de_ahorro* banco::getCuentaCliente(string numCliente)
{
    for (int i = 0; i < totalClientes; i++)
    {
        if (clientes[i].getNumeroCliente() == numCliente)
        {
            return &clientes[i].getCuenta();
        }
    }
    return nullptr;  // Cliente no encontrado
}

// Implementación de la clase transacciones
transacciones::transacciones()
{
    _transacciones = nullptr;
    totalTransacciones = 0;
    capacidadTransacciones = 0;
}

transacciones::~transacciones()
{
    if (_transacciones != nullptr)
        delete[] _transacciones;
}

// Cargar todas las transacciones desde archivo
void transacciones::cargarTransaccionesDesdeArchivo()
{
    // Liberar arreglo previo si existe
    if (_transacciones != nullptr)
    {
        delete[] _transacciones;
        _transacciones = nullptr;
        totalTransacciones = 0;
        capacidadTransacciones = 0;
    }

    ifstream archivo("transacciones.txt");

    // Inicializar con capacidad base
    capacidadTransacciones = 10;
    _transacciones = new archivo_transacciones[capacidadTransacciones];
    totalTransacciones = 0;

    while (true)
    {
        archivo_transacciones at;
        if (!getline(archivo, at.NumCliente))
            break;
        if (!getline(archivo, at.anio))
            break;
        if (!getline(archivo, at.mes))
            break;
        if (!getline(archivo, at.dia))
            break;
        if (!getline(archivo, at.TipoTransaccion))
            break;
        if (!getline(archivo, at.TipoMoneda))
            break;
        if (!getline(archivo, at.Monto))
            break;

        convertirALong(at.NumCliente);
        convertirAEntero(at.anio);
        convertirAEntero(at.mes);
        convertirAEntero(at.dia);

        // Redimensionar si es necesario
        if (totalTransacciones >= capacidadTransacciones)
        {
            int nuevaCap = capacidadTransacciones * 2;
            archivo_transacciones *nuevos = new archivo_transacciones[nuevaCap];
            for (int i = 0; i < totalTransacciones; i++)
                nuevos[i] = _transacciones[i];
            delete[] _transacciones;
            _transacciones = nuevos;
            capacidadTransacciones = nuevaCap;
        }

        _transacciones[totalTransacciones++] = at;
    }

    archivo.close();
}

// Guardar todas las transacciones desde el arreglo
void transacciones::guardarTransaccionesEnArchivo()
{
    ofstream archivo("transacciones.txt");
    if (!archivo.is_open())
    {
        cerr << "No se pudo abrir 'transacciones.txt' para escritura" << endl;
        return;
    }

    for (int i = 0; i < totalTransacciones; i++)
    {
        archivo << _transacciones[i].NumCliente << endl
                << _transacciones[i].anio << endl
                << _transacciones[i].mes << endl
                << _transacciones[i].dia << endl
                << _transacciones[i].TipoTransaccion << endl
                << _transacciones[i].TipoMoneda << endl
                << _transacciones[i].Monto << endl;
    }

    archivo.close();
}

// Mostrar transacciones de un cliente
void transacciones::mostrar_transaccion_cliente(string numCliente)
{
    ifstream archivo("transacciones.txt");
    if (!archivo.is_open())
    {
        cout << "No existe el archivo 'transacciones.txt' o no se puede abrir." << endl;
        return;
    }

    bool trans = false;
    cout << "\n===== TRANSACCIONES DEL CLIENTE #" << numCliente << " =====" << endl;
    while (true)
    {
        archivo_transacciones at;
        if (!getline(archivo, at.NumCliente))
            break;
        if (!getline(archivo, at.anio))
            break;
        if (!getline(archivo, at.mes))
            break;
        if (!getline(archivo, at.dia))
            break;
        if (!getline(archivo, at.TipoTransaccion))
            break;
        if (!getline(archivo, at.TipoMoneda))
            break;
        if (!getline(archivo, at.Monto))
            break;

        if (at.NumCliente == numCliente)
        {
            trans = true;
            cout << "Cliente: " << at.NumCliente << " | Fecha: " << at.dia << "/" << at.mes << "/" << at.anio
                 << " | Tipo: " << at.TipoTransaccion << " | Moneda: " << at.TipoMoneda << " | Monto: " << at.Monto << endl;
        }
    }

    if (!trans)
        cout << "No se encontraron transacciones para el cliente " << numCliente << "." << endl;

    archivo.close();
}

// Mostrar todas las transacciones
void transacciones::mostrar_transacciones()
{
    ifstream archivo("transacciones.txt");
    if (!archivo.is_open())
    {
        cout << "No existe el archivo 'transacciones.txt' o no se puede abrir." << endl;
        return;
    }

    cout << "\n===== LISTADO DE TRANSACCIONES =====" << endl;
    while (true)
    {
        archivo_transacciones at;
        if (!getline(archivo, at.NumCliente))
            break;
        if (!getline(archivo, at.anio))
            break;
        if (!getline(archivo, at.mes))
            break;
        if (!getline(archivo, at.dia))
            break;
        if (!getline(archivo, at.TipoTransaccion))
            break;
        if (!getline(archivo, at.TipoMoneda))
            break;
        if (!getline(archivo, at.Monto))
            break;

        cout << "Cliente: " << at.NumCliente << " | Fecha: " << at.dia << "/" << at.mes << "/" << at.anio
             << " | Tipo: " << at.TipoTransaccion << " | Moneda: " << at.TipoMoneda << " | Monto: " << at.Monto << endl;
    }

    archivo.close();
}

// Informes por año
void transacciones::transacciones_anio()
{
    string anio;
    cout << "Ingrese año a filtrar (YYYY): ";
    cin >> anio;

    ifstream archivo("transacciones.txt");
    if (!archivo.is_open())
    {
        cout << "No existe el archivo 'transacciones.txt' o no se puede abrir." << endl;
        return;
    }

    bool info_anio = false;
    cout << "\n===== TRANSACCIONES AÑO " << anio << " =====" << endl;
    while (true)
    {
        archivo_transacciones at;
        if (!getline(archivo, at.NumCliente))
            break;
        if (!getline(archivo, at.anio))
            break;
        if (!getline(archivo, at.mes))
            break;
        if (!getline(archivo, at.dia))
            break;
        if (!getline(archivo, at.TipoTransaccion))
            break;
        if (!getline(archivo, at.TipoMoneda))
            break;
        if (!getline(archivo, at.Monto))
            break;

        if (at.anio == anio)
        {
            info_anio = true;
            cout << "Cliente: " << at.NumCliente << " | Fecha: " << at.dia << "/" << at.mes << "/" << at.anio
                 << " | Tipo: " << at.TipoTransaccion << " | Moneda: " << at.TipoMoneda << " | Monto: " << at.Monto << endl;
        }
    }

    if (!info_anio)
        cout << "No se encontraron transacciones para el año " << anio << "." << endl;

    archivo.close();
}

// Informes por mes (pide año y mes)
void transacciones::transacciones_mes()
{
    string anio, mes;
    cout << "Ingrese anio (YYYY): ";
    cin >> anio;
    cout << "Ingrese mes (MM o numero): ";
    cin >> mes;

    ifstream archivo("transacciones.txt");
    if (!archivo.is_open())
    {
        cout << "No existe el archivo 'transacciones.txt' o no se puede abrir." << endl;
        return;
    }

    bool info_mes = false;
    cout << "\n===== TRANSACCIONES " << mes << "/" << anio << " =====" << endl;
    while (true)
    {
        archivo_transacciones at;
        if (!getline(archivo, at.NumCliente))
            break;
        if (!getline(archivo, at.anio))
            break;
        if (!getline(archivo, at.mes))
            break;
        if (!getline(archivo, at.dia))
            break;
        if (!getline(archivo, at.TipoTransaccion))
            break;
        if (!getline(archivo, at.TipoMoneda))
            break;
        if (!getline(archivo, at.Monto))
            break;

        if (at.anio == anio && at.mes == mes)
        {
            info_mes = true;
            cout << "Cliente: " << at.NumCliente << " | Fecha: " << at.dia << "/" << at.mes << "/" << at.anio
                 << " | Tipo: " << at.TipoTransaccion << " | Moneda: " << at.TipoMoneda << " | Monto: " << at.Monto << endl;
        }
    }

    if (!info_mes)
        cout << "No se encontraron transacciones para " << mes << "/" << anio << "." << endl;

    archivo.close();
}

// Implementación de caja_de_ahorro
caja_de_ahorro::caja_de_ahorro()
{
    saldodolares = 0.0;
    saldopesos = 0.0;
}

void caja_de_ahorro::setSaldoDolares(float sd)
{
    saldodolares = sd;
}

float caja_de_ahorro::getSaldoDolares()
{
    return saldodolares;
}

void caja_de_ahorro::setSaldoPesos(float sp)
{
    saldopesos = sp;
}

float caja_de_ahorro::getSaldoPesos()
{
    return saldopesos;
}

void caja_de_ahorro::mostrar_saldo()
{
    cout << "Saldo en USD: " << saldodolares << " | Saldo en ARS: " << saldopesos << endl;
}

// Calcular saldo de un cliente basándose en sus transacciones
void caja_de_ahorro::calcular_saldo_cliente(string numCliente)
{
    // Resetear saldos
    setSaldoDolares(0.0);
    setSaldoPesos(0.0);

    // Cargar transacciones desde archivo
    cargarTransaccionesDesdeArchivo();

    // Recorrer transacciones del cliente y calcular saldos
    for (int i = 0; i < totalTransacciones; i++)
    {
        if (_transacciones[i].NumCliente == numCliente)
        {
            try
            {
                // Convertir monto a float (el monto está guardado como string)
                float monto = convertirAFloat(_transacciones[i].Monto);

                if (_transacciones[i].TipoMoneda == "USD")
                {
                    if (_transacciones[i].TipoTransaccion == "DEPOSITO")
                        setSaldoDolares(getSaldoDolares() + monto);
                    else if (_transacciones[i].TipoTransaccion == "EXTRACCION")
                        setSaldoDolares(getSaldoDolares() - monto);
                }
                else if (_transacciones[i].TipoMoneda == "ARS")
                {
                    if (_transacciones[i].TipoTransaccion == "DEPOSITO")
                        setSaldoPesos(getSaldoPesos() + monto);
                    else if (_transacciones[i].TipoTransaccion == "EXTRACCION")
                        setSaldoPesos(getSaldoPesos() - monto);
                }
            }
            catch (const ExcepcionArgumentoInvalido &e)
            {
                cerr << "Advertencia: Monto invalido en transaccion, se omite." << endl;
            }
        }
    }
}

// Registrar transacción
void caja_de_ahorro::registrar_transaccion()
{
    try
    {
        archivo_transacciones at;

        cout << "Ingrese numero de cliente: ";
        cin >> at.NumCliente;

        cout << "Tipo de transaccion (E=Extraccion / D=Deposito): ";
        cin >> at.TipoTransaccion;

        if (at.TipoTransaccion == "E" || at.TipoTransaccion == "e")
            at.TipoTransaccion = "EXTRACCION";
        else if (at.TipoTransaccion == "D" || at.TipoTransaccion == "d")
            at.TipoTransaccion = "DEPOSITO";
        else
            throw ExcepcionArgumentoInvalido("Tipo de transaccion invalido. Use 'E' para Extraccion o 'D' para Deposito.");

        cout << "Tipo de moneda (U=USD / A=ARS): ";
        cin >> at.TipoMoneda;

        if (at.TipoMoneda == "U" || at.TipoMoneda == "u")
            at.TipoMoneda = "USD";
        else if (at.TipoMoneda == "A" || at.TipoMoneda == "a")
            at.TipoMoneda = "ARS";
        else
            throw ExcepcionArgumentoInvalido("Tipo de moneda invalido. Use 'U' para USD o 'A' para ARS.");

        cout << "Monto: ";
        cin >> at.Monto;

        // Si es EXTRACCION, validar saldo suficiente
        if (at.TipoTransaccion == "EXTRACCION")
        {
            calcular_saldo_cliente(at.NumCliente);

            float montoFloat = convertirAFloat(at.Monto);

            if (at.TipoMoneda == "USD")
            {
                if (getSaldoDolares() < montoFloat)
                    throw ExcepcionArgumentoInvalido("Saldo insuficiente en USD. Saldo actual: " + to_string(getSaldoDolares()));
            }
            else if (at.TipoMoneda == "ARS")
            {
                if (getSaldoPesos() < montoFloat)
                    throw ExcepcionArgumentoInvalido("Saldo insuficiente en ARS. Saldo actual: " + to_string(getSaldoPesos()));
            }
        }

        cout << "Ingrese anio (YYYY): ";
        cin >> at.anio;
        cout << "Ingrese mes (MM o numero): ";
        cin >> at.mes;
        cout << "Ingrese dia (DD): ";
        cin >> at.dia;

        convertirALong(at.NumCliente);
        convertirAEntero(at.anio);
        convertirAEntero(at.mes);
        convertirAEntero(at.dia);
        convertirAFloat(at.Monto);

        // Cargar transacciones
        cargarTransaccionesDesdeArchivo();

        // Redimensionar si es necesario
        if (totalTransacciones >= capacidadTransacciones)
        {
            int nuevaCap = (capacidadTransacciones == 0) ? 10 : capacidadTransacciones * 2;
            archivo_transacciones *nuevos = new archivo_transacciones[nuevaCap];
            for (int i = 0; i < totalTransacciones; i++)
                nuevos[i] = _transacciones[i];
            delete[] _transacciones;
            _transacciones = nuevos;
            capacidadTransacciones = nuevaCap;
        }

        _transacciones[totalTransacciones++] = at;
        guardarTransaccionesEnArchivo();

        cout << "\nTransaccion registrada correctamente." << endl;

        // Mostrar saldo actualizado
        calcular_saldo_cliente(at.NumCliente);
        cout << "Saldo actualizado del cliente #" << at.NumCliente << ":" << endl;
        mostrar_saldo();
    }
    catch (const ExcepcionArgumentoInvalido &e)
    {
        cerr << "Error al registrar transaccion: " << e.error() << endl;
    }
}
