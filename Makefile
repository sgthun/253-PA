#Demo:
#	g++ *.cpp -I. -Wall -o demo
CC = g++
DEBUG = -g
CC_FLAGS = -Wall -c $(DEBUG)
LD_FLAGS = -Wall -o
OBJS = main.o WordCounts.o Word.o
INCLUDE = -I.
EXE = PA2
P1: $(OBJS)
	$(CC) $(OBJS) $(INCLUDE) $(LD_FLAGS) $(EXE)
main.o: main.cpp WordCounts.h
	$(CC) main.cpp $(INCLUDE) $(CC_FLAGS)
WordCounts.o: WordCounts.cpp WordCounts.h Word.h
	$(CC) WordCounts.cpp $(INCLUDE) $(CC_FLAGS)
Word.o: Word.cpp Word.h
	$(CC) Word.cpp $(INCLUDE) $(CC_FLAGS)
clean:
	rm *.o $(EXE)
