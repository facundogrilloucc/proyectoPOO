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

struct archivo_transacciones
{
    string NumCliente;
    string anio;
    string mes;
    string dia;
    string TipoTransaccion;
    string TipoMoneda;
    string Monto;
};

class transaciones {
    private:
        archivo_transacciones transaccion;
        // Arreglo en memoria para todas las transacciones (seguimos el patrón de `banco`)
        archivo_transacciones* transacciones;
        int totalTransacciones;
        int capacidadTransacciones;
    public: 
        // Destructor para liberar memoria interna si corresponde
        ~transaciones();

        // Setters / Getters para la transaccion actual (transaccion)
        void setNumCliente(const string&);
        string getNumCliente() const;
        void setAnio(const string&);
        string getAnio() const;
        void setMes(const string&);
        string getMes() const;
        void setDia(const string&);
        string getDia() const;
        void setTipoTransaccion(const string&);
        string getTipoTransaccion() const;
        void setTipoMoneda(const string&);
        string getTipoMoneda() const;
        void setMonto(const string&);
        string getMonto() const;
    transaciones();
    transaciones(archivo_transacciones);
    void setTransaccion(const archivo_transacciones&);
    archivo_transacciones getTransaccion();
        void registrar_transaccion();
        void mostrar_transaccion_cliente();
        void mostrar_transacciones();
        void transacciones_anio();
        void transacciones_mes();
        // Nuevos métodos para cargar/guardar todas las transacciones en memoria
        void cargarTransaccionesDesdeArchivo();
        void guardarTransaccionesEnArchivo();
};

class caja_de_ahorro : public transaciones{
    private:
        float saldodolares;
        float saldopesos;
    public:
        caja_de_ahorro();
        caja_de_ahorro(archivo_transacciones, float, float);
        void setSaldoDolares(float);
        float getSaldoDolares();
        void setSaldoPesos(float);
        float getSaldoPesos();
        void mostrar_saldo();
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
