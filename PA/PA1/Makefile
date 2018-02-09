#Demo:
#	g++ *.cpp -I. -Wall -o demo
CC = g++
CC_FLAGS = -Wall -c
LD_FLAGS = -Wall -o
OBJS = main.o Numscan.o
INCLUDE = -I.
EXE = PA1
P1: $(OBJS)
	$(CC) $(OBJS) $(INCLUDE) $(LD_FLAGS) $(EXE)
main.o: main.cpp Numscan.h
	$(CC) main.cpp $(INCLUDE) $(CC_FLAGS)
Numscan.o: Numscan.cpp Numscan.h
	$(CC) Numscan.cpp $(INCLUDE) $(CC_FLAGS)
clean:
	rm *.o $(EXE)
