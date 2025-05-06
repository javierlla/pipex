# 🧪 Pipex

**Pipex** es un proyecto que simula el comportamiento de la shell al ejecutar un encadenamiento de comandos usando **pipes**. Este proyecto pone en práctica conceptos de programación de bajo nivel como duplicación de descriptores de archivo, ejecución de programas con `execve`, y la gestión de procesos con `fork`.

---

## 📌 Objetivo

Reproducir el comportamiento de la shell para un comando como:

```bash
< infile cmd1 | cmd2 > outfile

El programa ejecutará:

./pipex infile "cmd1" "cmd2" outfile

Lo que debe ser equivalente a:

< infile cmd1 | cmd2 > outfile

🛠️ Compilación

make

Esto generará un ejecutable llamado pipex.
🚀 Uso

./pipex infile "cmd1" "cmd2" outfile

Ejemplo:

./pipex input.txt "grep hello" "wc -l" output.txt

Esto debe tener el mismo efecto que:

< input.txt grep hello | wc -l > output.txt

⚙️ Funcionalidades

    Lectura desde un archivo de entrada.

    Ejecución de dos comandos usando una pipe intermedia.

    Redirección de la salida al archivo de salida.

    Resolución del path de los comandos.

    Manejo robusto de errores.

🔄 Flujo del programa

    Abrir infile y outfile.

    Crear un pipe con pipe().

    Crear dos procesos hijos:

        El primero ejecuta cmd1, redirigiendo su entrada desde infile y su salida al pipe.

        El segundo ejecuta cmd2, tomando su entrada del pipe y escribiendo en outfile.

    Cerrar todos los descriptores correctamente.

    Esperar a que los procesos finalicen con waitpid.

🧪 Funciones permitidas

    open, close, read, write, malloc, free

    access, dup, dup2, execve, pipe, fork, wait, waitpid

    strerror, perror, exit

❗ Manejo de errores

Se deben gestionar errores como:

    Archivos no accesibles.

    Comandos inválidos.

    Número incorrecto de argumentos.

    Fallos de execve, fork, dup2, etc.

Los errores deben ser claros y mostrarse por stderr.
