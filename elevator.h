#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "person.h"

typedef struct _Elevator {
    int capacity;    // capacité maximale de la cabine
    int currentFloor;// étage courant
    int targetFloor; // destination
    PersonList *persons; // personnes dans la cabine
} Elevator;

typedef struct _Building {
    int nbFloor; // nombre d’étage des l’immeuble
    Elevator *elevator; // la cabine d’ascenseur
    PersonList **waitingLists; // array of waiting list (one per floor)
} Building;

Elevator *create_elevator(int capacity, int currentFloor, PersonList *persons); //ok
Building *create_building(int nbFloor, Elevator *elevator, PersonList **waitingLists); //ok

PersonList* exitElevator(PersonList *ListElevator, int currentFloor); //la liste de ceux qui quittent l'ascenceur
PersonList* enterElevator(Elevator *e, PersonList *waitingList);

PersonList *newElevatorList(Elevator *e); //renders the elevator emptied of the persons arrived at destination (intermediate elevator between exit and enter)

void stepElevator(Building *b);

#endif