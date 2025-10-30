#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
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
    
    // Nuevas funciones para gestión de clientes
    void mostrarListaClientes();
    void mostrarDetallesCliente(int numCliente);
    void cambiarEstadoCliente(int numCliente);
};
