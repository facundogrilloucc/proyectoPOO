#!/bin/bash
# Script unificado para ejecutar el programa en Linux/Mac
# Puede usarse directamente o abrir una nueva terminal

# Función que compila y ejecuta el programa
ejecutar_programa() {
    # Compilar el programa
    echo "Compilando el programa..."
    g++ -std=c++11 main.cpp proyecto.cpp -o app

    # Verificar si la compilación fue exitosa
    if [ $? -eq 0 ]; then
        echo "✅ Compilación exitosa"
        echo ""
        echo "=========================================="
        echo "    SISTEMA DE GESTIÓN BANCARIA"
        echo "=========================================="
        echo ""
        
        # Ejecutar el programa
        ./app
        
        # Pausar al finalizar para que no se cierre la terminal
        echo ""
        echo "Programa finalizado. Presiona Enter para cerrar..."
        read
    else
        echo "❌ Error en la compilación"
        echo "Presiona Enter para cerrar..."
        read
    fi
}

# Detectar si se está ejecutando desde una terminal interactiva
if [ -t 0 ]; then
    # Se ejecuta desde terminal interactiva - ejecutar directamente
    ejecutar_programa
else
    # Se ejecuta con doble clic - abrir nueva terminal
    # Detectar qué emulador de terminal está disponible
    SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
    
    if command -v gnome-terminal &> /dev/null; then
        gnome-terminal -- bash -c "cd '$SCRIPT_DIR' && bash '$0' terminal; exec bash"
    elif command -v konsole &> /dev/null; then
        konsole --workdir "$SCRIPT_DIR" -e bash -c "bash '$0' terminal; exec bash"
    elif command -v xterm &> /dev/null; then
        xterm -e "cd '$SCRIPT_DIR' && bash '$0' terminal; exec bash"
    elif command -v xfce4-terminal &> /dev/null; then
        xfce4-terminal --working-directory="$SCRIPT_DIR" -e "bash -c 'bash \"$0\" terminal; exec bash'"
    else
        # Si no hay terminal GUI, ejecutar en la actual (fallback)
        ejecutar_programa
    fi
    exit 0
fi

# Si se pasó el argumento "terminal", ejecutar el programa
if [ "$1" = "terminal" ]; then
    ejecutar_programa
fi
