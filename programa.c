#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tda/list.h"
#include "tda/extra.h"

typedef enum {
    BAJO = 0,
    MEDIO = 1,
    ALTO = 2
} Prioridad;

typedef struct {
    char* id;
    char* descripcion;
    Prioridad prioridad;
    time_t hora_registro;
} Ticket;

Ticket* crearTicket(const char* id, const char* descripcion) {
    Ticket* nuevoTicket = (Ticket*)malloc(sizeof(Ticket));
    if (nuevoTicket == NULL) return NULL;
    nuevoTicket->id = strdup(id);
    nuevoTicket->descripcion = strdup(descripcion);
    nuevoTicket->prioridad = BAJO; 
    nuevoTicket->hora_registro = time(NULL); 
    
    return nuevoTicket;
}

void liberarTicket(Ticket* ticket) {
    if (ticket == NULL) return;
    free(ticket->id);
    free(ticket->descripcion);
    free(ticket);
}

int compararTickets(void* ticket1, void* ticket2) {
    Ticket* t1 = (Ticket*)ticket1;
    Ticket* t2 = (Ticket*)ticket2;
    if (t1->prioridad > t2->prioridad) return 1;
    if (t1->prioridad < t2->prioridad) return 0;
    return (t1->hora_registro <= t2->hora_registro);
}

Prioridad stringAPrioridad(const char* str) {
    if (strcmp(str, "Alto") == 0) return ALTO;
    if (strcmp(str, "Medio") == 0) return MEDIO;
    return BAJO;
}

const char* prioridadAString(Prioridad p) {
    switch (p) {
        case ALTO: return "Alto";
        case MEDIO: return "Medio";
        case BAJO: return "Bajo";
        default: return "Desconocido";
    }
}

Ticket* buscarTicketPorID(List* listaTickets, const char* id) {
    Ticket* ticket = list_first(listaTickets);
    while (ticket != NULL) {
        if (strcmp(ticket->id, id) == 0) 
        {
            return ticket;
        }
        ticket = list_next(listaTickets);
    }
    return NULL;
}

void mostrarDetallesTicket(Ticket* ticket) {
    if (ticket == NULL) 
    {
        printf("Ticket no encontrado\n");
        return;
    }
    
    char buffer[100];
    struct tm* tm_info = localtime(&ticket->hora_registro);
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", tm_info);
    printf("ID: %s\n", ticket->id);
    printf("Descripción: %s\n", ticket->descripcion);
    printf("Prioridad: %s\n", prioridadAString(ticket->prioridad));
    printf("Hora de Registro: %s\n", buffer);
}

void registrarTicket(List* listaTickets) {
    char id[100], descripcion[1024];
    printf("Ingrese ID del ticket: ");
    scanf("%s", id);
    getchar(); 
    printf("Ingrese descripción del problema: ");
    fgets(descripcion, sizeof(descripcion), stdin);
    descripcion[strcspn(descripcion, "\n")] = '\0'; 
    Ticket* nuevoTicket = crearTicket(id, descripcion);
    if (nuevoTicket == NULL) 
    {
        printf("Error al crear el ticket\n");
        return;
    }
    list_sortedInsert(listaTickets, nuevoTicket, compararTickets);
    printf("Ticket registrado correctamente con prioridad Bajo\n");
}

void asignarPrioridad(List* listaTickets) 
{
    char id[100], prioridadStr[10];
    printf("Ingrese ID del ticket: ");
    scanf("%s", id);
    printf("Ingrese nueva prioridad (Alto, Medio, Bajo): ");
    scanf("%s", prioridadStr);
    Ticket* ticket = NULL;
    Ticket* current = list_first(listaTickets);
    int found = 0;
    int position = 0;
    while (current != NULL) {
        if (strcmp(((Ticket*)current)->id, id) == 0) 
        {
            ticket = current;
            found = 1;
            break;
        }
        current = list_next(listaTickets);
        position++;
    }
    if (!found) {
        printf("Ticket con ID %s no encontrado\n", id);
        return;
    }
    Prioridad nuevaPrioridad = stringAPrioridad(prioridadStr);
    ticket->prioridad = nuevaPrioridad;
    list_popCurrent(listaTickets);
    list_sortedInsert(listaTickets, ticket, compararTickets);
    printf("Prioridad actualizada correctamente a %s\n", prioridadStr);
    
}

void mostrarTicketsPendientes(List* listaTickets) 
{
    if (list_size(listaTickets) == 0) 
    {
        printf("No hay tickets pendientes\n");
        return;
    }
    printf("Lista de tickets pendientes:\n");
    printf("--------------------------------------------------\n");
    printf("%-10s %-30s %-10s %-20s\n", "ID", "Descripción", "Prioridad", "Hora de Registro");
    printf("--------------------------------------------------\n");
    Ticket* ticket = list_first(listaTickets);
    while (ticket != NULL) 
    {
        char buffer[100];
        struct tm* tm_info = localtime(&ticket->hora_registro);
        strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", tm_info);
        printf("%-10s %-30.30s %-10s %-20s\n", ticket->id, ticket->descripcion, prioridadAString(ticket->prioridad), buffer);
        ticket = list_next(listaTickets);
    }
    printf("--------------------------------------------------\n");
}

void procesarSiguienteTicket(List* listaTickets) {
    if (list_size(listaTickets) == 0) 
    {
        printf("No hay tickets pendientes para procesar\n");
        return;
    }
    Ticket* ticket = list_popFront(listaTickets);
    printf("Procesando el siguiente ticket:\n");
    printf("--------------------------------------------------\n");
    mostrarDetallesTicket(ticket);
    printf("--------------------------------------------------\n");
    liberarTicket(ticket);
}


void buscarTicket(List* listaTickets) {
    char id[100];
    
    printf("Ingrese ID del ticket a buscar: ");
    scanf("%s", id);
    
    Ticket* ticket = buscarTicketPorID(listaTickets, id);
    
    if (ticket == NULL) 
    {
        printf("No se encontró un ticket con ID %s\n", id);
    } else 
    {
        printf("Ticket encontrado:\n");
        printf("--------------------------------------------------\n");
        mostrarDetallesTicket(ticket);
        printf("--------------------------------------------------\n");
    }
}

void limpiarTickets(List* listaTickets) {
    Ticket* ticket = list_first(listaTickets);
    while (ticket != NULL) {
        liberarTicket(ticket);
        ticket = list_first(listaTickets);
    }
    list_clean(listaTickets);
}

int main() {
    List* listaTickets = list_create();
    int opcion;
    
    do {
        limpiarPantalla();
        printf("\n=== SISTEMA DE GESTIÓN DE TICKETS DE SOPORTE ===\n");
        printf("1. Registrar nuevo ticket\n");
        printf("2. Asignar prioridad a ticket\n");
        printf("3. Mostrar lista de tickets pendientes\n");
        printf("4. Procesar siguiente ticket\n");
        printf("5. Buscar ticket por ID\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar(); 
        
        switch (opcion) {
            case 1:
                registrarTicket(listaTickets);
                break;
            case 2:
                asignarPrioridad(listaTickets);
                break;
            case 3:
                mostrarTicketsPendientes(listaTickets);
                break;
            case 4:
                procesarSiguienteTicket(listaTickets);
                break;
            case 5:
                buscarTicket(listaTickets);
                break;
            case 0:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida\n");
        }
        
        if (opcion != 0) presioneTeclaParaContinuar();
        
    } while (opcion != 0);
    
    limpiarTickets(listaTickets);
    free(listaTickets);
    
    return 0;
}