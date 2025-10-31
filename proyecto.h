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

struct archivo_clientes
{
    string Nombre;
    long DNI;
    string Tipo;
    int Ingreso;
    string Estado;
    int NumCliente;
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
    
    // Arreglos dinámicos para almacenar clientes en memoria
    string* nombres;
    string* dnis;
    string* tipos;
    string* ingresos;
    string* estados;
    string* numClientes;
    int totalClientes;
    int capacidad;
    
public:
    banco();
    banco(string, archivo_clientes, cliente, personal);
    ~banco();  // Destructor para liberar memoria
    
    void setNombreBanco(string);
    string getNombreBanco();
    void setArchivoClientes(archivo_clientes);
    archivo_clientes getArchivoClientes();
    void setCliente(cliente);
    cliente getCliente();
    void setPersonal(personal);
    personal getPersonal();
    void mostrar_datos();
    
    // Funciones para cargar/guardar desde archivo
    void cargarDesdeArchivo();
    void guardarEnArchivo();
    
    // Funciones de gestión de clientes (ahora usan arreglos en memoria)
    void mostrarListaClientes();
    void mostrarDetallesCliente(string numCliente);
    void cambiarEstadoCliente(string numCliente);
};
