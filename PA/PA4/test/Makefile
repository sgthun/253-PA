CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall -lgtest -lpthread
#OBJS =  test_main.o test_helper.o test_portAlg.o
INCLUDE = -I../

testAll: test_all.o
	$(CC) $(LFLAGS) $(INCLUDE) test_all.o ../Stemmer.o -o testAll
test_all.o: test_all.cpp
	$(CC) $(CFLAGS) $(INCLUDE) test_all.cpp
