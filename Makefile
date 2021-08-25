NAME=bsq

CC=gcc

OBJECT_NAMES=\
	main \
	files \
	functions \
	map \
	strs \

OUT_DIR=./
SRC_DIR=./

OBJECTS=$(patsubst %, $(OUT_DIR)/%.o, $(OBJECT_NAMES))
SOURCES=$(patsubst %, $(SRC_DIR)/%.c, $(OBJECT_NAMES))

CFLAGS=-Wall -Wextra -Werror
LFLAGS=-I$(SRC_DIR)

all: $(NAME)
$(NAME): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LFLAGS)

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -o $@ $^ $(CFLAGS)

clean:
	@rm -rf $(wildcard *.o)
fclean: clean
	@rm -rf $(NAME)