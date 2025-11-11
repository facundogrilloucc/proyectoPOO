# 🚀 INSTRUCCIONES RÁPIDAS DE EJECUCIÓN

## Linux / Mac

### Opción 1: Script run.sh (MÁS FÁCIL) ⭐
```bash
./run.sh
```
O **doble clic** en `run.sh` desde el explorador de archivos

**Ventajas:**
- ✅ Funciona desde terminal (ejecuta directamente)
- ✅ Funciona con doble clic (abre nueva terminal automáticamente)
- ✅ Detecta automáticamente el emulador de terminal disponible
- ✅ No requiere configuración adicional

### Opción 2: Lanzador Gráfico
**Doble clic** en `SistemaBancario.desktop`

**Si pide confiar:**
```bash
gio set SistemaBancario.desktop metadata::trusted true
chmod +x SistemaBancario.desktop
```

## Windows

### Opción 1: Doble clic (más fácil)
1. Busca el archivo `programa.bat`
2. Haz doble clic

### Opción 2: CMD/PowerShell
```cmd
programa.bat
```

---

## ⚠️ Notas Importantes

- **Asegúrate de tener g++ instalado:**
  - Linux: `sudo apt install g++` (Ubuntu/Debian) o `sudo dnf install gcc-c++` (Fedora)
  - Mac: Instala Xcode Command Line Tools: `xcode-select --install`
  - Windows: Instala MinGW o usa MSYS2

- **Los archivos de datos deben estar en la misma carpeta:**
  - `Tabla de clientes.txt`
  - `transacciones.txt`

- **Si tienes errores de compilación**, verifica que estés usando C++11 o superior

---

## 📂 Archivos del Proyecto

```
proyectoPOO/
├── main.cpp                    # Programa principal
├── proyecto.cpp                # Implementación de clases
├── proyecto.h                  # Declaraciones de clases
├── Tabla de clientes.txt       # Datos de clientes
├── transacciones.txt           # Datos de transacciones
├── README.md                   # Documentación completa
├── INSTRUCCIONES.md            # Este archivo
├── run.sh                      # Script Linux/Mac
├── run.bat                     # Script Windows
└── SistemaBancario.desktop     # Lanzador Linux
```

---

## 🐛 Solución de Problemas

### "Permission denied" en Linux/Mac
```bash
chmod +x run.sh
chmod +x SistemaBancario.desktop
```

### "g++ not found" en Windows
- Instala MinGW desde: https://www.mingw-w64.org/
- O usa MSYS2: https://www.msys2.org/
- Agrega g++ al PATH del sistema

### El programa no encuentra los archivos .txt
- Asegúrate de ejecutar desde la carpeta del proyecto
- Los archivos .txt deben estar en el mismo directorio que los ejecutables

---

Para más información detallada, consulta `README.md`

