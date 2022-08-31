#include <time.h>
#include <stdlib.h>
#include <ncurses.h>

#include "elevator.h"
#include "person.h"

#define HEIGHT 30
#define WIDTH 40
#define PERSON_WIDTH 3

/********** display functions ************/

void DisplayPersonList(WINDOW *win, PersonList *list, int level, int offset) {
  while(list != NULL) {
    // display 25 for a person going from floor 2 to floor 5
    mvwaddch(win, level, offset, '0' + list->person->src);
    mvwaddch(win, level, offset+1, '0' + list->person->dest);
    list = list->next;
    offset+= PERSON_WIDTH;
  }
}

void DisplayElevator(WINDOW *win, int nbFloor, Elevator *e, int offset) {
  //Display elevator
  // [23 24 31 30 42]
 
  int level = 3*(nbFloor - e->currentFloor); // 3 lines per level 
  mvwaddch(win, level, offset+1, '[');
  DisplayPersonList(win, e->persons, level, offset+2);
  mvwaddch(win, level, offset+2+ (PERSON_WIDTH*e->capacity), ']');
}

void DisplayBuilding(WINDOW *win, Building *b) {
  int offset = 1;

  // display wall
  // |                |
  // |[23 24 31 30 42]| 31 32
  // |                |
  int right_wall = offset + 3 + (PERSON_WIDTH*b->elevator->capacity);
  for(int i=0; i < b->nbFloor; ++i) {
    int level = 3*i+1;
    mvwaddch(win,level,  offset,'|');
    mvwaddch(win,level+1,offset,'|');
    mvwaddch(win,level,  right_wall,'|');
    mvwaddch(win,level+1,right_wall,'|');
  }
  for(int i=offset+1; i < right_wall; i++) {
    mvwaddch(win,3*(b->nbFloor)+1,i,'_');
  }

  DisplayElevator(win, b->nbFloor, b->elevator, offset);

  for(int i=0; i < b->nbFloor; i++) {
    int level = 3*(b->nbFloor - i);
    DisplayPersonList(win,b->waitingLists[i], level, right_wall + 2);
  }
}




/************ main code ***************/

int main()
{
    /*Elevator *elevator = create_elevator(5, 1 , NULL);*/

    srand(time(NULL));   // should only be called once

  // works :
    int nbFloor = 5;
    PersonList **waitingLists = malloc(nbFloor*sizeof(PersonList*));
    for(int currentFloor=0; currentFloor < nbFloor; currentFloor++)
    {
        waitingLists[currentFloor] = NULL; //waitingLists[currentFloor] est un pointeur vers une PersonList (mise à NULL ici, donc ne pointe vers rien)
        int nbPerson = 5; // 5 persons in the waiting list
        for(int j=0 ; j<nbPerson ; j++) 
        {
            int dest = rand() % (nbFloor);
            Person *p = createPerson(currentFloor, dest); //donc ici on a p un *pointeur* vers une Person
            waitingLists[currentFloor] = insert(p,waitingLists[currentFloor]); //on assigne le pointeur waitingLists[currentFloor] vers une PersonList (la première fois), ou bien on continue la linkedlist
        }
    }

    // to test :
    int capacity = 3;
    int currentFloor = 0;
    Elevator *elevator = create_elevator(capacity, currentFloor , NULL); //ok
    Building *building = create_building(nbFloor, elevator, waitingLists);




    // Initialize ncurse display
    initscr(); // initialize ncurses
    //noecho();  // do not display in window the pressed keys
    halfdelay(2);

    WINDOW *win = newwin(HEIGHT, WIDTH, 0, 0);
    keypad(win, TRUE);
    box(win, 0, 0);



    // Animation loop
    bool run=true;
    while(run) {
    // Generate people in function of input (or quit if 'q')
    int input = wgetch(win);
    if(input == 'q') {
      run = false;
    } else {
      int level = input - '0';
      if(0 <= level && level < nbFloor) {
	building->elevator->targetFloor = level;
      }
    }

    // Update state machine of elevator !!!!

    stepElevator(building);

    wclear(win);   // clear display area
    box(win, 0,0); // display border of window

    DisplayBuilding(win, building);

    wrefresh(win); // actual display function

  }
  
    endwin();






/********debug and understanding
    printf("current level (=target floor): %d\n", building->elevator->targetFloor);

    PersonList *List1 = malloc(sizeof(PersonList*));
    List1 = NULL;

    Person *p = createPerson(2, 4);
    List1 = insert(p, List1);

    printList(List1);

    Person *p2 = createPerson(4, 3);
    List1 = insert(p2, List1);

    printf("ha\n");

    printList(List1);

    Person *p3 = createPerson(1, 1);
    List1 = insert(p3, List1);

    printList(List1);

    printf("size : %d\n", sizePersonList(List1));

    Elevator *elevator1 = create_elevator(capacity, 3 , List1); //currentFloor = 3

    printf("size elevator1 : %d\n", sizePersonList(elevator1->persons));

    PersonList* exitPerson = exitElevator(elevator1->persons, elevator1->currentFloor);

    printList(exitPerson);
    printf("size exitPerson : %d\n", sizePersonList(exitPerson));

    PersonList *List2= newElevatorList(elevator1); //List2 = new elevator list after dump
    printList(List2);
    printf("size new : %d\n", sizePersonList(List2));

    elevator1->persons = List2;

    printf("the waiting list :  ");
    printList(waitingLists[elevator1->currentFloor]);

    waitingLists[elevator1->currentFloor] = enterElevator(elevator1, waitingLists[elevator1->currentFloor]); 

    printList(waitingLists[elevator1->currentFloor]);
    printList(elevator1->persons);
*/

/*
    //building->elevator->targetFloor = 2;

    printList(building->waitingLists[building->elevator->targetFloor]);
    printList(building->elevator->persons);

    stepElevator(building);

    printList(building->waitingLists[building->elevator->targetFloor]);
    printList(building->elevator->persons);

***************/

    printf("hi\n");
    return 0;
}