CC = gcc
CFLAGS = -W -Wall
TARGET = airline
OBJECTS = main.c admin.o logIn.o ticket.o
all : $(TARGET)
$(TARGET) : $(OBJECTS)
        $(CC) $(CFLAGS) -o $@ $^
clean:
        rm *.o airline
