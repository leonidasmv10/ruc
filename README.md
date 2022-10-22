# [RUC](https://github.com/devgrids/ruc)

## Resumen
Programa que guarda y actualiza los RUCs de la RENIEC a una base de datos(mysql). 

## Introducción
Este programa tiene una simple depencia: [cmake](http://www.cmake.org/download/), que se utiliza para generar makefiles o archivos de proyecto específicos de la plataforma.

Comience por clonar este repositorio, asegurándose de pasar el indicador `--recursive` para capturar todas las dependencias.

```bash
git clone https://github.com/devgrids/ruc
cd ruc
git submodule update --init --recursive
```
o simplemente:
```bash
git clone --recursive https://github.com/devgrids/ruc
cd ruc
```
Ahora configure vcpkg, una biblioteca de Microsoft que le permite agregar dependencias de bibliotecas externas de una manera muy simple.

```bash
.\vcpkg\bootstrap-vcpkg.bat
```
Instalamos las dependencias con los siguientes comandos:

```bash
.\vcpkg\vcpkg install glew:x64-windows
.\vcpkg\vcpkg install glfw3:x64-windows
.\vcpkg\vcpkg install spdlog:x64-windows
.\vcpkg\vcpkg install imgui[core,glfw-binding,opengl3-binding,docking-experimental]:x64-windows
.\vcpkg\vcpkg install libzippp:x64-windows
.\vcpkg\vcpkg install curl[http2]:x64-windows
```

## Construir

Para construir el proyecto hay dos opciones:
* CMake GUI
* Consola

Si opta por usar la consola, asegúrese de que los bins de cmake estén configurados en las variables de entorno de su SO y ejecutar el siguiente comando:

```bash
cmake -G "Visual Studio 17 2022" -B "build"
```
## Compilar

Antes de compilar, debe de tener un servidor phpmyadmin, y si en caso no lo tenga, puede hacerlo de manera local usando [xampp]( https://www.afterdawn.com/software/network/servers/xampp_for_windows.cfm/v7_0_15), aseguresé de usar una versión con cotejamiento latin1_swedish_ci u similar, ya que sino tendrá errores con las ñ y tildes.

Una vez instalado el xampp, crea una base de datos e importa el archivo [empresas.sql](https://github.com/devgrids/ruc/blob/main/files/empresas.sql) que se encuentra en la carpeta files del proyecto, de esta manera tiene la tabla creada y listo para compilar.
