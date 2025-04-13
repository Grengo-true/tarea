Este sistema permite a los usuarios a gestionar los pacientes por ID y prioridad en un hospital. El usuario puede registrar un ID con su problema, asignarle una prioridad, ver la lista de pacientes pendientes y mas. Esto esta diseñado para mejorar el manejo de tiempo de manera que se pueda tratar mas eficientemente a los pacientes.

Como compilar y ejecutar:

Requisitos:

- Tener instalado Visual Studio Code.
- Instalar la extensión C/C++ (Microsoft).
- Tener instalado un compilador de C (como gcc). Si estás en Windows, se recomienda instalar MinGW o utilizar el entorno WSL.

Pasos a seguir:
- Inicia Visual Studio Code
- Selecciona Archivo > Abrir carpeta, y elige la carpeta en donde descomprimiste el zip.
- Abre programa.c
- Ve a Terminal > Nueva terminal
- En la terminal, escribe lo siguiente "gcc programa.c tda/*.c"
- En la terminal, escribe lo siguiente "./a.exe

Funciones:

- Registra un ID junto con su problema (Prioridad bajo por defecto).
- Asigna y modifica la prioridad de un paciente.
- Ver la lista de espera actual.
- Liberar al paciente con la mas alta prioridad.
- Buscar paciente por ID

Problemas conocidos:
- Se puede registrar a 2 pacientes por el mismo ID, lo que puede causar problemas en el funcionamiento del sistema.

Ejemplo de uso:

Si quieres registrar un paciente:
- Registrar nuevo ticket
- Ingrese ID del ticket
- Ingrese descripción del problema

Si quieres cambiar la prioridad de un ticket:
- Asignar prioridad a ticket
- Ingrese ID del ticket
- Ingrese nueva prioridad (Alto, Medio, Bajo)

Si quieres ver la lista de tickets pendientes:
- Mostrar lista de tickets pendientes

Si quieres procesar el siguiente ticket:
- Procesar siguiente ticket

Si quieres buscar un ticket por ID:
- Buscar ticket por ID
- Ingrese ID del ticket a buscar

Créditos:
Bruno Pérez 
