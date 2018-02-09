#Demo:
#	g++ *.cpp -I. -Wall -o demo
CC = g++ -std=c++11
DEBUG = -g
CC_FLAGS = -Wall -O2 -c $(DEBUG)
LD_FLAGS = -Wall -o
OBJS = main.o WordCounts.o Word.o ParseBox.o Stemmer.o Replace.o Collection.o
INCLUDE = -I.
EXE = PA8
all: $(OBJS)
	$(CC) $(OBJS) $(INCLUDE) $(LD_FLAGS) $(EXE)
main.o: main.cpp WordCounts.h Replace.h
	$(CC) main.cpp $(INCLUDE) $(CC_FLAGS)
WordCounts.o: WordCounts.cpp WordCounts.h Word.h Stemmer.h Replace.h
	$(CC) WordCounts.cpp $(INCLUDE) $(CC_FLAGS)
Word.o: Word.cpp Word.h
	$(CC) Word.cpp $(INCLUDE) $(CC_FLAGS)
ParseBox.o: ParseBox.cpp Word.cpp Word.h
	$(CC) ParseBox.cpp $(INCLUDE) $(CC_FLAGS)
Stemmer.o: Stemmer.cpp Stemmer.h
	$(CC) Stemmer.cpp $(INCLUDE) $(CC_FLAGS)
Replace.o: Replace.cpp Replace.h
	$(CC) Replace.cpp $(INCLUDE) $(CC_FLAGS)
Collection.o: Collection.cpp Collection.h
	$(CC) Collection.cpp $(INCLUDE) $(CC_FLAGS)
clean:
	rm *.o $(EXE)
