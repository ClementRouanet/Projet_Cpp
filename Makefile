CC = g++
CFLAGS = -Wall -O
EXEC = nuclearalert.exe

all : $(EXEC)

nuclearalert.exe : main.o 




clean : rm -f *.o core

mrpropre : clean
  rm -f $(EXEC)
