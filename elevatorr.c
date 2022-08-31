#include "elevator.h"
#include <stdlib.h>
#include <stdio.h>

Elevator *create_elevator(int capacity, int currentFloor, PersonList *persons)
{
    Elevator* p = malloc(sizeof(Elevator));
    (*p).capacity = capacity;
    (*p).currentFloor = currentFloor;
    (*p).targetFloor = 0;
    (*p).persons = persons;

    return p;
}

Building *create_building(int nbFloor, Elevator *elevator, PersonList **waitingLists)
{
    Building *p = malloc(sizeof(Building));
    (*p).nbFloor = nbFloor;
    (*p).elevator = elevator;
    (*p).waitingLists = waitingLists;
}




PersonList* exitElevator(PersonList *ListElevator, int currentFloor)
{
    if(ListElevator == NULL)
    {
        return NULL;
    }
    else
    {
        //PersonList *exitPerson = NULL;
        PersonList *exitPerson = malloc(sizeof(PersonList)); //allocation de mémoire pour la PersonList à retourner
        exitPerson = NULL;

        while(ListElevator != NULL)
        {
            if(ListElevator->person->dest == currentFloor)
            {
                exitPerson = insert((ListElevator->person), exitPerson);
            }
            ListElevator = ListElevator->next;
        }

        return exitPerson;
    }
}

PersonList *newElevatorList(Elevator *e) //"removes" all the persons who leave the lift
{
    PersonList *new = malloc(sizeof(PersonList)); //the new elevator
    new = NULL;

    while(e->persons != NULL)
        {
            if(e->persons->person->dest != e->currentFloor)
            {
                new = insert(e->persons->person, new);
            }
            e->persons = e->persons->next;
        }    
    return new;
}

PersonList* enterElevator(Elevator *e, PersonList *waitingList)
{
    PersonList *newWL = malloc(sizeof(PersonList)); //the new waitingList newWL
    newWL = NULL;

    int i = (e->capacity-sizePersonList(e->persons));
    while(waitingList != NULL && i>0)
    {
        e->persons = insert(waitingList->person, e->persons);
        waitingList = waitingList->next;

        i--;
    }

    while(waitingList != NULL)
    {
        newWL = insert(waitingList->person, newWL);
        waitingList = waitingList->next;
        //printf("%d\n", i);
        //printList(newWL);
        i++;
    }

    return newWL;
}

void stepElevator(Building *b)
{    
    while(b->elevator->currentFloor != b->elevator->targetFloor)
    {
        if(b->elevator->targetFloor < b->elevator->currentFloor)
        {
            b->elevator->currentFloor -= 1;
        }
        else
        {
            b->elevator->currentFloor += 1;
        }

        PersonList* exitPerson = exitElevator(b->elevator->persons, b->elevator->currentFloor);

        b->elevator->persons = newElevatorList(b->elevator); //the elevator is now emptied of the well-arrived

        b->waitingLists[b->elevator->currentFloor] = enterElevator(b->elevator, b->waitingLists[b->elevator->currentFloor]); 

        //printf("end\n");
        //printList(b->waitingLists[b->elevator->currentFloor]);
    }
    
    

}

