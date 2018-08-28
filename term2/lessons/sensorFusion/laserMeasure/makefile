CC=g++
CFLAGS=-I.
DEPS=kalmanFilter.h tracking.h measurementPackage.h
OBJ=kalmanFilter.o tracking.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $(DEPS) $(CFLAGS)

a.out: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)