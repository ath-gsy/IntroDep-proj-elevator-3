#ifndef PERSON_H
#define PERSON_H

typedef struct _Person {
    int src;
    int dest;
} Person;

Person* createPerson(int src, int dest); //renvoie une adresse vers un objet Person



typedef struct _PersonList {
    Person *person;
    struct _PersonList *next;
} PersonList;

PersonList* insert(Person *p, PersonList *list); //adds the next in the linked list

void printList(PersonList *list);

int sizePersonList(PersonList *list);

#endif
