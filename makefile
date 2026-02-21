ifeq ($(OS),Windows_NT)
	RM = del
	EXE = .exe
else
	RM = rm -f
	EXE =
endif

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
INCLUDE_PATH = -Iraylib/include -Lraylib/lib
LIBRARIES = $(INCLUDE_PATH) -lraylib -lopengl32 -lgdi32 -lwinmm

TARGET = game
SRC = *.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET).exe $(LIBRARIES)

run: $(TARGET)
	.\$(TARGET).exe

clean:
	del $(TARGET).exe