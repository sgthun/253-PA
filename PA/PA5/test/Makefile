CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall -lgtest -lpthread
#OBJS = main.o stem.o
INCLUDE = -I. -I..

testAll: test_all.cpp
	$(CC) $(INCLUDE) $(LFLAGS) test_all.cpp ../Stemmer.o -o testAll 	
