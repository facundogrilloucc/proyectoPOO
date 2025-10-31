#include "proyecto.h"

int main()
{
    banco miBanco;
    int opcion;
    string numCliente;
    
    // Cargar todos los clientes del archivo al inicio
    cout << "Iniciando sistema bancario..." << endl;
    miBanco.cargarDesdeArchivo();
    
    do
    {
        try
        {
            cout << "\n========== MENU PRINCIPAL ==========" << endl;
            cout << "1. Mostrar lista de clientes" << endl;
            cout << "2. Ver detalles de un cliente" << endl;
            cout << "3. Cambiar estado de un cliente" << endl;
            cout << "0. Salir" << endl;
            cout << "====================================" << endl;
            cout << "Ingrese una opcion: ";
            
            if (!(cin >> opcion))
            {
                cin.clear(); // Limpiar el estado de error
                cin.ignore(10000, '\n'); // Ignorar la entrada incorrecta
                throw ExcepcionArgumentoInvalido("Debe ingresar un número válido");
            }
            
            switch(opcion)
            {
                case 1:
                    miBanco.mostrarListaClientes();
                    break;
                    
                case 2:
                    try
                    {
                        cout << "\nIngrese el numero de cliente: ";
                        cin >> numCliente;
                        miBanco.mostrarDetallesCliente(numCliente);
                    }
                    catch (const ExcepcionArgumentoInvalido& e)
                    {
                        cerr << "Error: " << e.what() << endl;
                    }
                    break;
                    
                case 3:
                    try
                    {
                        cout << "\nIngrese el numero de cliente a cambiar de estado: ";
                        cin >> numCliente;
                        miBanco.cambiarEstadoCliente(numCliente);
                    }
                    catch (const ExcepcionArgumentoInvalido& e)
                    {
                        cerr << "Error: " << e.what() << endl;
                    }
                    break;
                    
                case 0:
                    cout << "\nSaliendo del programa..." << endl;
                    break;
                    
                default:
                    cout << "\nOpcion invalida. Intente nuevamente." << endl;
            }
        }
        catch (const ExcepcionArgumentoInvalido& e)
        {
            cerr << "Error: " << e.what() << endl;
            opcion = -1; // Para que no salga del bucle
        }
        catch (const Excepcion& e)
        {
            cerr << "Error inesperado: " << e.what() << endl;
            opcion = -1;
        }
        
    } while(opcion != 0);
    
    return 0;
}