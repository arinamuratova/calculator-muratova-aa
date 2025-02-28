CC = gcc
CFLAGS = -Wall -Wextra

SRC = src/main.c 
OBJ = $(SRC:.c=.o)
OUT = app.exe

all: $(OUT)

$(OUT): $(OBJ)
 $(CC) $(CFLAGS) -o $(OUT) $(OBJ)

clean:
 rm -f $(OBJ) $(OUT)

