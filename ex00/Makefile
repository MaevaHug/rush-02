# Compiler and flags
CC         = cc
CFLAGS     = -Wall -Wextra -Werror
SANITIZE   = -fsanitize=address -g

# Name of the executable
EXECUTABLE = rush-02

# Directories
SRC_DIR    = src
OBJ_DIR    = obj
INC_DIR    = include

# Source files
SRC        = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJ        = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Commands
REMOVE	 = rm -rf
MKDIR	 = mkdir -p

# Compilation rules
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	$(MKDIR) $@

clean:
	$(REMOVE) $(OBJ_DIR)

fclean: clean
	$(REMOVE) $(EXECUTABLE)

re: fclean all

sanitize: CFLAGS += $(SANITIZE)
sanitize: re

.PHONY: all clean fclean re sanitize
