#include "proyecto.h"

int main()
{
    banco miBanco;
    transaciones gestorTrans;
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
            cout << "4. Registrar transaccion" << endl;
            cout << "5. Listar transacciones por cliente" << endl;
            cout << "6. Listar todas las transacciones" << endl;
            cout << "7. Informes por año" << endl;
            cout << "8. Informes por mes" << endl;
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
                        cerr << "Error: " << e.error() << endl;
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
                        cerr << "Error: " << e.error() << endl;
                    }
                    break;

                case 4:
                    try
                    {
                        gestorTrans.registrar_transaccion();
                    }
                    catch (const Excepcion& e)
                    {
                        cerr << "Error al registrar transaccion: " << e.what() << endl;
                    }
                    break;

                case 5:
                    gestorTrans.mostrar_transaccion_cliente();
                    break;

                case 6:
                    gestorTrans.mostrar_transacciones();
                    break;

                case 7:
                    gestorTrans.transacciones_anio();
                    break;

                case 8:
                    gestorTrans.transacciones_mes();
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
            cerr << "Error: " << e.error() << endl;
            opcion = -1; // Para que no salga del bucle
        }
        catch (const Excepcion& e)
        {
            cerr << "Error inesperado: " << e.error() << endl;
            opcion = -1;
        }
        
    } while(opcion != 0);
    
    return 0;
}