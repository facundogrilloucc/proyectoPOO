@echo off
REM Script para ejecutar el programa en Windows

echo Compilando el programa...
g++ -std=c++11 main.cpp proyecto.cpp -o app.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ✓ Compilacion exitosa
    echo.
    echo ==========================================
    echo     SISTEMA DE GESTION BANCARIA UCC
    echo ==========================================
    echo.
    
    REM Ejecutar el programa
    app.exe
    
    REM Pausar al finalizar
    echo.
    echo Programa finalizado. Presiona cualquier tecla para cerrar...
    pause > nul
) else (
    echo.
    echo X Error en la compilacion
    echo Presiona cualquier tecla para cerrar...
    pause > nul
)
