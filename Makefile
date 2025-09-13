NAME = cub3d

# Source files (add your .c files here as you create them)
SRCS_LIST = main.c

# Directories
SRCS_DIRECTORY = src/
OBJECTS_DIRECTORY = objects/
LIBFT_DIRECTORY = libraries/libft/
MLX_DIRECTORY = libraries/minilibx-linux/

# Library files
LIBFT = $(LIBFT_DIRECTORY)libft.a
MLX = $(MLX_DIRECTORY)libmlx_Linux.a

# Headers
HEADER_LIST = cub3d.h
HEADER_DIRECTORY = include/
HEADERS = $(addprefix $(HEADER_DIRECTORY), $(HEADER_LIST))

# Source and object files
SRC = $(addprefix $(SRCS_DIRECTORY), $(SRCS_LIST))
OBJECT_LIST = $(SRCS_LIST:.c=.o)
OBJECTS = $(addprefix $(OBJECTS_DIRECTORY), $(OBJECT_LIST))

# Compiler and flags
CC = cc
CFLAGS = -Wall -Werror -Wextra -g

# Libraries and includes
LIBS = -L$(LIBFT_DIRECTORY) -lft -L$(MLX_DIRECTORY) -lmlx_Linux -lXext -lX11 -lm
INCLUDES = -I$(HEADER_DIRECTORY) -I$(LIBFT_DIRECTORY)include/ -I$(MLX_DIRECTORY)

# COLORS
RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
RESET   = \033[0m

$(NAME): $(LIBFT) $(MLX) $(OBJECTS_DIRECTORY) $(OBJECTS)
	@if $(CC) $(CFLAGS) $(OBJECTS) $(INCLUDES) $(LIBS) -o $(NAME); \
	then \
		$(MAKE) -s norm; \
		echo "[" "$(GREEN)OK$(RESET)" "] | $(NAME) created!"; \
	else \
		echo "[" "$(RED)Error$(RESET)" "] | An error occurred while creating $(NAME)."; \
		make clean > /dev/null 2>&1; \
		echo "[" "$(RED)Error$(RESET)" "] | All objects cleaned."; \
	fi

$(OBJECTS_DIRECTORY):
	@echo "[" "$(YELLOW)..$(RESET)" "] | Creating objects directory..."
	@mkdir -p $(OBJECTS_DIRECTORY)
	@echo "[" "$(GREEN)OK$(RESET)" "] | Objects directory ready!"

$(OBJECTS_DIRECTORY)%.o : $(SRCS_DIRECTORY)%.c
	@echo "[" "$(YELLOW)..$(RESET)" "] | Compiling $<..."
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT):
	@echo "[" "$(YELLOW)..$(RESET)" "] | Compiling libft..."
	@make -sC $(LIBFT_DIRECTORY) > /dev/null 2>&1
	@echo "[" "$(GREEN)OK$(RESET)" "] | Libft ready!"

$(MLX):
	@echo "[" "$(YELLOW)..$(RESET)" "] | Compiling minilibx..."
	@make -sC $(MLX_DIRECTORY) > /dev/null 2>&1
	@echo "[" "$(GREEN)OK$(RESET)" "] | Minilibx ready!"

clean:
	@echo "[" "$(YELLOW)..$(RESET)" "] | Removing object files..."
	@rm -rf $(OBJECTS_DIRECTORY)
	@make -sC $(LIBFT_DIRECTORY) clean > /dev/null 2>&1
	@make -sC $(MLX_DIRECTORY) clean > /dev/null 2>&1
	@echo "[" "$(GREEN)OK$(RESET)" "] | Object files removed."

fclean: clean
	@echo "[" "$(YELLOW)..$(RESET)" "] | Removing binary files..."
	@rm -rf .norminette.log
	@rm -rf $(NAME)
	@make -sC $(LIBFT_DIRECTORY) fclean > /dev/null 2>&1
	@make -sC $(MLX_DIRECTORY) clean > /dev/null 2>&1
	@echo "[" "$(GREEN)OK$(RESET)" "] | Binary file removed."

norm:
	@echo "[" "$(YELLOW)..$(RESET)" "] | Norminetting..."
	@for lib in libraries/*/; do \
		if [ "$$lib" != "libraries/minilibx-linux/" ]; then \
			norminette $$lib >> .norminette.log 2>&1; \
		fi; \
	done
	@norminette $(SRCS_DIRECTORY) $(HEADER_DIRECTORY) >> .norminette.log 2>&1
	@if grep -q "Error!" .norminette.log; then \
		echo "[" "$(RED)!!$(RESET)" "] | Norminette found errors."; \
		grep "Error!" .norminette.log | awk '{print "[ " "$(RED)!!$(RESET)" " ] | " $$0}'; \
	else \
		echo "[" "$(GREEN)OK$(RESET)" "] | Norminette passed!"; \
	fi

re: fclean
	clear && make -s

run: $(NAME)
	./$(NAME)

# Professional targets
all: $(NAME)

help:
	@echo "Available targets:"
	@echo "  all        - Build the project (default)"
	@echo "  clean      - Remove object files"
	@echo "  fclean     - Remove all generated files"
	@echo "  re         - Rebuild the project"
	@echo "  run        - Build and run cub3d"
	@echo "  norm       - Check code style with norminette"
	@echo "  help       - Show this help message"

.PHONY: all clean fclean re run norm help
