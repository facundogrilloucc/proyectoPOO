#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int convertirAEntero(string entrada);
long convertirALong(string entrada);
float convertirAFloat(string entrada);

// Clases de excepciones (ArgumentoInvalido y Memoria)
class Excepcion
{
protected:
    string mensaje;
public:
    Excepcion();
    Excepcion(string msg);
    virtual string error() const;
    virtual ~Excepcion();
};

class ExcepcionArgumentoInvalido : public Excepcion
{
public:
    ExcepcionArgumentoInvalido();
    ExcepcionArgumentoInvalido(string msg);
};

class ExcepcionMemoria : public Excepcion
{
public:
    ExcepcionMemoria();
    ExcepcionMemoria(string msg);
};

// Clase persona (herencia para cliente y personal)
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

// Estructuras para archivos

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

//Clase Transacciones

class transacciones {
    protected:
        archivo_transacciones* _transacciones;
        int totalTransacciones;
        int capacidadTransacciones;
    public: 
        transacciones();
        ~transacciones();
        void mostrar_transaccion_cliente(string numCliente);
        void mostrar_transacciones();
        void transacciones_anio();
        void transacciones_mes();
        void cargarTransaccionesDesdeArchivo();
        void guardarTransaccionesEnArchivo();
};

class caja_de_ahorro : public transacciones{
    private:
        float saldodolares;
        float saldopesos;
    public:
        caja_de_ahorro();
        void setSaldoDolares(float);
        float getSaldoDolares();
        void setSaldoPesos(float);
        float getSaldoPesos();

        void mostrar_saldo();
        void calcular_saldo_cliente(string numCliente);
        void registrar_transaccion(); 
};

class cliente : public persona
{
private:
    string tipo_cliente;
    string estado_cliente;
    string numero_cliente;
    caja_de_ahorro cuenta;
public:
    cliente();
    cliente(string, string, string, string, string, string);
    void setTipoCliente(string);
    string getTipoCliente();
    void setEstadoCliente(string);
    string getEstadoCliente();
    void setNumeroCliente(string);
    string getNumeroCliente();
    
    // Acceso a la cuenta del cliente
    caja_de_ahorro& getCuenta();

    void mostrar_datos();
    void mostrar_info_tarjeta_credito();
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
    personal pr; 
    
    cliente* clientes;
    int totalClientes;
    int capacidad;
    
public:
    banco();
    banco(string, personal);
    ~banco();
    
    void setNombreBanco(string);
    string getNombreBanco();
    void setPersonal(personal);
    personal getPersonal();
    void mostrar_datos();
    
    void cargarDesdeArchivo();
    void guardarEnArchivo();
    
    void mostrarListaClientes();
    void mostrarDetallesCliente(string numCliente);
    void cambiarEstadoCliente(string numCliente);
    
    // Acceso a la cuenta de un cliente específico
    caja_de_ahorro* getCuentaCliente(string numCliente);
};
