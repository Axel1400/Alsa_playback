CC ?= gcc 
CXX ?= g++
CPP ?= g++


APP_NAME_INPUT = main
OBJ_FILES_INPUT = main.o

APP_NAME_PLAYBACK = playback
OBJ_FILES_PLAYBACK = playback.o

LIBS = -lasound

all: $(APP_NAME_INPUT) $(APP_NAME_PLAYBACK)
$(APP_NAME_INPUT): $(OBJ_FILES_INPUT)
	$(CC) -o $@ $^ $(LIBS)

$(APP_NAME_PLAYBACK): $(OBJ_FILES_PLAYBACK)
	$(CC) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) -o $@ -c $^ -g


clean:
	rm *.o $(APP_NAME_INPUT)
fresh:
	make clean
	make all