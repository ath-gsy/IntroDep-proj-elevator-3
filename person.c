#include "person.h"
#include <stdlib.h>
#include <stdio.h>

Person* createPerson(int srcc, int destt)
{
    Person *p = malloc(sizeof(Person));
    //Person Person1 = {srcc, destt};

    //Person Person1;
    //Person1.src = srcc;
    //Person1.dest = destt;


    (*p).src = srcc;
    (*p).dest = destt;

    return p;
}


PersonList* insert(Person *p, PersonList *list)
{
    if(list == NULL)
    {
        PersonList *PList1 = malloc(sizeof(PersonList));
        PList1->next = NULL;
        PList1->person = p;

        return PList1;
    }

    else
    {
        PersonList *temp = list;

        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        PersonList *PList2 = malloc(sizeof(PersonList));
        PList2->next = NULL;
        PList2->person = p;

        temp->next = PList2;

        return list;
    }
}

void printList(PersonList *list)
{
    if(list == NULL)
    {
        printf("this list is empty\n");
    }
    else
    {   printf("The List is : ");

        PersonList* temp1 = list;
        Person* temp2;

        do
        {
            temp2 = temp1->person;
            printf("[src:%d  dest:%d] ; ", temp2->src, temp2->dest);
            temp1 = temp1->next;
        }while(temp1 != NULL);
        printf("\n");
    }
}


int sizePersonList(PersonList *list)
{
    int size = 0;

    while(list != NULL)
        {
            size++;

            list = list->next;
        }

    return size;
}