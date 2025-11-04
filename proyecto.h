#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// Clases de excepciones personalizadas (solo 2 tipos: ArgumentoInvalido y Memoria)
class Excepcion
{
protected:
    string mensaje;
public:
    Excepcion() : mensaje("Error desconocido") {}
    Excepcion(string msg) : mensaje(msg) {}
    virtual string what() const { return mensaje; }
    virtual ~Excepcion() {}
};

class ExcepcionArgumentoInvalido : public Excepcion
{
public:
    ExcepcionArgumentoInvalido() : Excepcion("Argumento inválido") {}
    ExcepcionArgumentoInvalido(string msg) : Excepcion(msg) {}
};

class ExcepcionMemoria : public Excepcion
{
public:
    ExcepcionMemoria() : Excepcion("Error de asignación de memoria") {}
    ExcepcionMemoria(string msg) : Excepcion(msg) {}
};

class persona
{
private:
    string dni;
    string nombre;
    string anio_ingreso;

public:
    persona();
    persona(string, string, string);
    void setDNI(string);
    string getDNI();
    void setNombre(string);
    string getNombre();
    void setAnioIngreso(string);
    string getAnioIngreso();
    virtual void mostrar_datos();
};

struct archivo_clientes
{
    string Nombre;
    string DNI;
    string Tipo;
    string Ingreso;
    string Estado;
    string NumCliente;
};

class cliente : public persona
{
private:
    string tipo_cliente;
    string estado_cliente;
    string numero_cliente;
public:
    cliente();
    cliente(string, string, string, string, string, string);
    void setTipoCliente(string);
    string getTipoCliente();
    void setEstadoCliente(string);
    string getEstadoCliente();
    void setNumeroCliente(string);
    string getNumeroCliente();
    void mostrar_datos();
};

class personal : public persona
{
private:
    string area_trabajo;

public:
    personal();
    personal(string, string, string, string);
    void setAreaTrabajo(string);
    string getAreaTrabajo();
    void mostrar_datos();
};

class banco
{
private:
    string nombre_banco;
    archivo_clientes lista_clientes;
    personal pr;
    
    cliente* clientes;
    int totalClientes;
    int capacidad;
    
public:
    banco();
    banco(string, archivo_clientes, personal);
    ~banco();  // Destructor para liberar memoria
    
    void setNombreBanco(string);
    string getNombreBanco();
    void setArchivoClientes(archivo_clientes);
    archivo_clientes getArchivoClientes();
    void setPersonal(personal);
    personal getPersonal();
    void mostrar_datos();
    
    // Funciones para cargar/guardar desde archivo
    void cargarDesdeArchivo();
    void guardarEnArchivo();
    
    // Funciones de gestión de clientes (usando POO)
    void mostrarListaClientes();
    void mostrarDetallesCliente(string numCliente);
    void cambiarEstadoCliente(string numCliente);
};
