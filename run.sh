#!/bin/bash
# Script para ejecutar el programa en Linux/Mac

# Compilar el programa
echo "Compilando el programa..."
g++ -std=c++11 main.cpp proyecto.cpp -o app

# Verificar si la compilación fue exitosa
if [ $? -eq 0 ]; then
    echo "✅ Compilación exitosa"
    echo ""
    echo "=========================================="
    echo "    SISTEMA DE GESTIÓN BANCARIA UCC"
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
