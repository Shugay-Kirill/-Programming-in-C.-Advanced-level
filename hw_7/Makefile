all: prog

prog: main.o object_interaction.o traffic_control.o AI.o view.o
	gcc -o prog main.o object_interaction.o traffic_control.o AI.o view.o

main.o: main.c function.h 
	gcc -c -o main.o main.c

object_interaction.o: object_interaction.c
	gcc -c -o object_interaction.o object_interaction.c

traffic_control.o: traffic_control.c
	gcc -c -o traffic_control.o traffic_control.c

AI.o: AI.c
	gcc -c -o AI.o AI.c

view.o: view.c
	gcc -c -o view.o view.c

clean:
	del *.o
	del prog.exe