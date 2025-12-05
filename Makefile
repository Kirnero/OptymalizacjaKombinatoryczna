# To compile project, type "make all"

# To delete compiled files type "make clean_compiled" or "make clean" to also delete object files
# Generally, "make clean" to make directories look better and less cluttered
# To execute compiled thingy, type "./all" in terminal, you should know that

# Only one file should have main() function



#################### Configurables ####################



# Here type in your directories, so that there is no include.misc.h to type, too long for me
INCLUDE_DIR = include
OBJECT_DIR = obj
SOURCE_DIR = src

# Here list all .h files to include
# Each .h has to have .c in SOURCE_DIR
_DEPS = misc.h calculations.h greed.h
_OBJ = $(_DEPS:.h=.o) main.o

# This is in C, so gcc it is
CC=gcc
CFLAGS = -I$(INCLUDE_DIR) -lgsl -lgslcblas -lm -Wall -Wextra



#################### Make for actual project ####################



#Don't know, don't ask, don't touch
DEPS = $(patsubst %,$(INCLUDE_DIR)/%,$(_DEPS))

$(OBJECT_DIR):
	mkdir -p $(OBJECT_DIR)

OBJ = $(patsubst %,$(OBJECT_DIR)/%,$(_OBJ))

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c $(DEPS) | $(OBJECT_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o main $^ $(CFLAGS)

image:
	dot -Tpng graph_visual/graph.dot -o graph_visual/graph.png


# Cleaning up files
.PHONY: clean
clean:
	make clean_compiled
	make clean_objects
clean_objects:
	rm -f $(OBJECT_DIR)/*.o
clean_compiled:
	rm -f logic gui both game