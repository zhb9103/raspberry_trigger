

CC = g++
CFLAGS = -I./ -Wall -g 
LDFLAGS = 
SOURCES = ./TriggerDemo.cpp ./BaseFunction.cpp ./SerialPort.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = trigger_demo

all: clean build


build: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ -lpthread


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@




.PHONY: clean
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)



-include $(OBJECTS:.o=.d)

%.d: %c
	$(CC) $(CFLAGS) -MM $< > $@.tmp
	sed 's/.*://' $@.tmp > $@
	rm -f $@.tmp


