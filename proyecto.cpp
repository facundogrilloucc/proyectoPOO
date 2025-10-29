#include <iostream>
using namespace std;

class persona
{
private:
    long dni;
    string nombre;
    int anio_ingreso;

public:
    persona();
    persona(long, string, int);
    void setDNI(long);
    long getDNI();
    void setNombre(string);
    string getNombre();
    void setAnioIngreso(int);
    int getAnioIngreso();
    virtual void mostrar_datos();
};

void verificar_tarjeta(cliente cl)
{
    if (cl.getTipoCliente() == "Plata")
    {
        cout << "Los cliente Plata no tienen acceso a tarjeta de credito." << endl;
    }
    else if (cl.getTipoCliente() == "Oro")
    {
        cout << "Los clientes Oro tienen acceso a tarjeta de credito con un limite de $250.000." << endl;
    }
    else if (cl.getTipoCliente() == "Platino")
    {
        cout << "Los clientes Platino tienen acceso a tarjeta de credito con un limite de $500.000." << endl;
    }
    else
    {
        cout << "Tipo de cliente no reconocido." << endl;
    }
}

class archivo_clientes
{
private:
    string nombre_archivo;
public:
    archivo_clientes();
    archivo_clientes(string);
    void setNombreArchivo(string);
    string getNombreArchivo();
    void abrir_archivo();
    void cerrar_archivo();
    void escribir_datos();
    void leer_datos();
};

class archivo_transacciones
{
private:
    string nombre_archivo;
public:
    archivo_transacciones();
    archivo_transacciones(string);
    void setNombreArchivo(string);
    string getNombreArchivo();
    void abrir_archivo();
    void cerrar_archivo();
    void escribir_datos();
    void leer_datos();
};

class transacciones
{
private:
    string tipo_transaccion;
    double monto;
    archivo_transacciones archivo;
public:
    transacciones();
    transacciones(string, double);
    void setTipoTransaccion(string);
    string getTipoTransaccion();
    void setMonto(double);
    double getMonto();
    void setArchivo(archivo_transacciones);
    archivo_transacciones getArchivo();
    void registrar_transaccion();
    void mostrar_datos();
};

class cliente : public persona
{
private:
    string tipo_cliente;
    string estado_cliente;
    long numero_cliente;
public:
    cliente();
    cliente(long, string, int, string, string , long);
    void setTipoCliente(string);
    string getTipoCliente();
    void setEstadoCliente(string);
    string getEstadoCliente();
    void setNumeroCliente(long);
    long getNumeroCliente();
    void mostrar_datos();
};

class personal : public persona
{
private:
    string area_trabajo;

public:
    personal();
    personal(long, string, int, string);
    void setAreaTrabajo(string);
    string getAreaTrabajo();
    void mostrar_datos();
};

class banco
{
private:
    string nombre_banco;
    archivo_clientes lista_clientes;
    cliente cl;
    personal pr;
public:
    banco();
    banco(string, archivo_clientes, cliente, personal);
    void setNombreBanco(string);
    string getNombreBanco();
    void setArchivoClientes(archivo_clientes);
    archivo_clientes getArchivoClientes();
    void setCliente(cliente);
    cliente getCliente();
    void setPersonal(personal);
    personal getPersonal();
    void mostrar_datos();
};

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

archivo_clientes::archivo_clientes() {}
archivo_clientes::archivo_clientes(string _nombre_archivo)
{
    nombre_archivo = _nombre_archivo;
}

void archivo_clientes::setNombreArchivo(string _nombre_archivo)
{
    nombre_archivo = _nombre_archivo;
}

string archivo_clientes::getNombreArchivo()
{
    return nombre_archivo;
}

