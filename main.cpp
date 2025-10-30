#include "proyecto.h"

int main()
{
    banco miBanco;
    int opcion, numCliente;
    
    do
    {
        cout << "\n========== MENU PRINCIPAL ==========" << endl;
        cout << "1. Mostrar lista de clientes" << endl;
        cout << "2. Ver detalles de un cliente" << endl;
        cout << "3. Cambiar estado de un cliente" << endl;
        cout << "0. Salir" << endl;
        cout << "====================================" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        
        switch(opcion)
        {
            case 1:
                miBanco.mostrarListaClientes();
                break;
                
            case 2:
                cout << "\nIngrese el numero de cliente: ";
                cin >> numCliente;
                miBanco.mostrarDetallesCliente(numCliente);
                break;
                
            case 3:
                cout << "\nIngrese el numero de cliente a cambiar de estado: ";
                cin >> numCliente;
                miBanco.cambiarEstadoCliente(numCliente);
                break;
                
            case 0:
                cout << "\nSaliendo del programa..." << endl;
                break;
                
            default:
                cout << "\nOpcion invalida. Intente nuevamente." << endl;
        }
        
    } while(opcion != 0);
    
    return 0;
}
