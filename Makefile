OBJFILES = person.o elevatorr.o test_elevator.o
TARGET = elevator_exe

all: $(TARGET)

$(TARGET): $(OBJFILES)
	gcc $(OBJFILES) -o $(TARGET) -lncurses

test_elevator.o: test_elevator.c elevator.h person.h
	gcc -c test_elevator.c -lncurses

elevator.o: elevatorr.c elevator.h
	gcc -c elevatorr.c

person.o: person.c person.h
	gcc -c person.c

run:
	./$(TARGET)

clean:
	rm -f $(OBJFILES) *~
