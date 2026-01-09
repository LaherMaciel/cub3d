NAME = cub3d

# Source files organized by directories
MAIN_C = main.c

DRAWING_C = drawing2d.c draw_loop.c draw_helpers.c

INITS_C = inits.c get_map.c

LOOPS_AND_HOOKS_C = loop.c

MOVEMENT_C = movement.c movement_helpers.c move_to_x.c

PARSING_C = parsing.c parse_map.c parse_utils.c parsing_config.c parsing_colors.c parsing_textures.c parsing_validate_map.c parsing_validate_helpers.c

FREE_C = memory_cleanup.c

RAYTRACING_C = raytracing.c raytracing_helpers.c

UTILS_C = utils.c textures.c

WINDOW_C = window_init.c window_management.c

# Header files
HEADER_LIST = cub3d.h
HEADER_DIRECTORY = include/
HEADERS = $(addprefix $(HEADER_DIRECTORY), $(HEADER_LIST))

# Source directories
SRCS_DIRECTORY = src/
DRAWING_DIRECTORY = src/drawing/
INITS_DIRECTORY = src/inits/
LOOPS_AND_HOOKS_DIRECTORY = src/loop_and_hooks/
MOVEMENT_DIRECTORY = src/movement/
PARSING_DIRECTORY = src/parsing/
RAYTRACING_DIRECTORY = src/raytracing/
FREE_DIRECTORY = src/free/
UTILS_DIRECTORY = src/utils/
WINDOW_DIRECTORY = src/window/
OBJECTS_DIRECTORY = objects/
LIBFT_DIRECTORY = libraries/libft/
MLX_DIRECTORY = libraries/minilibx-linux/

# Source files with full paths
MAIN_LIST = $(MAIN_C)
MAIN = $(addprefix $(SRCS_DIRECTORY), $(MAIN_LIST))

DRAWING_LIST = $(DRAWING_C)
DRAWING = $(addprefix $(DRAWING_DIRECTORY), $(DRAWING_LIST))

INITS_LIST = $(INITS_C)
INITS = $(addprefix $(INITS_DIRECTORY), $(INITS_LIST))

LOOPS_AND_HOOKS_LIST = $(LOOPS_AND_HOOKS_C)
LOOPS_AND_HOOKS = $(addprefix $(LOOPS_AND_HOOKS_DIRECTORY), $(LOOPS_AND_HOOKS_LIST))

MOVEMENT_LIST = $(MOVEMENT_C)
MOVEMENT = $(addprefix $(MOVEMENT_DIRECTORY), $(MOVEMENT_LIST))

PARSING_LIST = $(PARSING_C)
PARSING = $(addprefix $(PARSING_DIRECTORY), $(PARSING_LIST))

FREE_LIST = $(FREE_C)
FREE = $(addprefix $(FREE_DIRECTORY), $(FREE_LIST))

RAYTRACING_LIST = $(RAYTRACING_C)
RAYTRACING = $(addprefix $(RAYTRACING_DIRECTORY), $(RAYTRACING_LIST))

UTILS_LIST = $(UTILS_C)
UTILS = $(addprefix $(UTILS_DIRECTORY), $(UTILS_LIST))

WINDOW_LIST = $(WINDOW_C)
WINDOW = $(addprefix $(WINDOW_DIRECTORY), $(WINDOW_LIST))

# All source files
SRCS_LIST = $(MAIN) $(DRAWING) $(INITS) $(MOVEMENT) $(PARSING) $(RAYTRACING) $(FREE) $(UTILS) $(WINDOW) $(LOOPS_AND_HOOKS)

# Object files
OBJECT_LIST = $(notdir $(SRCS_LIST:.c=.o))
OBJECTS = $(addprefix $(OBJECTS_DIRECTORY), $(OBJECT_LIST))

# Library files
LIBFT = $(LIBFT_DIRECTORY)libft.a
MLX = $(MLX_DIRECTORY)libmlx.a

# Compiler settings
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
INCLUDES = -I$(HEADER_DIRECTORY) -I$(LIBFT_DIRECTORY)include/ -I$(MLX_DIRECTORY)
LIBS = -L$(LIBFT_DIRECTORY) -lft $(MLX) -lX11 -lXext -lm -lz

# Colors
RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
BLUE    = \033[0;34m
RESET   = \033[0m

# Main target
$(NAME): $(LIBFT) $(MLX) $(OBJECTS)
	@if [ ! -f $(MLX) ]; then \
		echo "[" "$(YELLOW)..$(RESET)" "] | Compiling minilibx..."; \
		echo "[" "$(GREEN)OK$(RESET)" "] | Minilibx ready!"; \
	else \
		echo "[" "$(GREEN)OK$(RESET)" "] | Minilibx already compiled!"; \
	fi
	@if [ -f $(LIBFT) ]; then \
		LIBFT_TIME=$$(stat -c %Y $(LIBFT) 2>/dev/null || stat -f %m $(LIBFT) 2>/dev/null || echo 0); \
		CURRENT_TIME=$$(date +%s 2>/dev/null || echo 0); \
		if [ $$LIBFT_TIME -gt 0 ] && [ $$CURRENT_TIME -gt 0 ] && [ $$((CURRENT_TIME - LIBFT_TIME)) -gt 3 ]; then \
			echo "[" "$(GREEN)OK$(RESET)" "] | Libft already compiled!"; \
		fi \
	fi
	@echo "[" "$(YELLOW)..$(RESET)" "] | Compiling files..."
	@if [ ! -d $(OBJECTS_DIRECTORY) ] || [ -z "$$(find $(OBJECTS_DIRECTORY) -name '*.o' 2>/dev/null | head -1)" ]; then \
		echo "[" "$(YELLOW)..$(RESET)" "] | Creating objects directory structure..."; \
		mkdir -p $(OBJECTS_DIRECTORY)$(DRAWING_DIRECTORY) $(OBJECTS_DIRECTORY)$(INITS_DIRECTORY) $(OBJECTS_DIRECTORY)$(MOVEMENT_DIRECTORY) $(OBJECTS_DIRECTORY)$(PARSING_DIRECTORY) $(OBJECTS_DIRECTORY)$(RAYTRACING_DIRECTORY) $(OBJECTS_DIRECTORY)$(FREE_DIRECTORY) $(OBJECTS_DIRECTORY)$(UTILS_DIRECTORY) $(OBJECTS_DIRECTORY)$(WINDOW_DIRECTORY) $(OBJECTS_DIRECTORY)$(LOOPS_AND_HOOKS_DIRECTORY); \
		echo "[" "$(GREEN)OK$(RESET)" "] | Objects directory structure ready!"; \
	fi
	@if $(CC) $(CFLAGS) $(OBJECTS) $(INCLUDES) $(LIBS) -o $(NAME); then \
		echo "[" "$(GREEN)OK$(RESET)" "] | Compilation successful!"; \
		make norm -s; \
		echo "[" "$(GREEN)OK$(RESET)" "] | $(NAME) created successfully!"; \
	else \
		echo "[" "$(RED)Error$(RESET)" "] | An error occurred while creating $(NAME)."; \
		make clean > /dev/null 2>&1; \
		echo "[" "$(RED)Error$(RESET)" "] | All objects cleaned."; \
	fi

# Create objects directory structure
$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@mkdir -p $(OBJECTS_DIRECTORY)$(DRAWING_DIRECTORY)
	@mkdir -p $(OBJECTS_DIRECTORY)$(INITS_DIRECTORY)
	@mkdir -p $(OBJECTS_DIRECTORY)$(MOVEMENT_DIRECTORY)
	@mkdir -p $(OBJECTS_DIRECTORY)$(PARSING_DIRECTORY)
	@mkdir -p $(OBJECTS_DIRECTORY)$(RAYTRACING_DIRECTORY)
	@mkdir -p $(OBJECTS_DIRECTORY)$(FREE_DIRECTORY)
	@mkdir -p $(OBJECTS_DIRECTORY)$(UTILS_DIRECTORY)
	@mkdir -p $(OBJECTS_DIRECTORY)$(WINDOW_DIRECTORY)
	@mkdir -p $(OBJECTS_DIRECTORY)$(LOOPS_AND_HOOKS_DIRECTORY)

# Compile object files
$(OBJECTS_DIRECTORY)%.o : $(SRCS_DIRECTORY)%.c $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(OBJECTS_DIRECTORY)%.o : $(DRAWING_DIRECTORY)%.c $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(OBJECTS_DIRECTORY)%.o : $(INITS_DIRECTORY)%.c $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(OBJECTS_DIRECTORY)%.o : $(MOVEMENT_DIRECTORY)%.c $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(OBJECTS_DIRECTORY)%.o : $(PARSING_DIRECTORY)%.c $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(OBJECTS_DIRECTORY)%.o : $(RAYTRACING_DIRECTORY)%.c $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(OBJECTS_DIRECTORY)%.o : $(FREE_DIRECTORY)%.c $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(OBJECTS_DIRECTORY)%.o : $(UTILS_DIRECTORY)%.c $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(OBJECTS_DIRECTORY)%.o : $(WINDOW_DIRECTORY)%.c $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(OBJECTS_DIRECTORY)%.o : $(LOOPS_AND_HOOKS_DIRECTORY)%.c $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT):
	@if [ ! -f $(LIBFT) ]; then \
		echo "[" "$(YELLOW)..$(RESET)" "] | Compiling libft..."; \
		make -sC $(LIBFT_DIRECTORY) > /dev/null 2>&1; \
		echo "[" "$(GREEN)OK$(RESET)" "] | Libft ready!"; \
	fi


$(MLX):
	@if [ ! -f $(MLX) ]; then \
		cd $(MLX_DIRECTORY) && bash configure > /dev/null 2>&1 || ( \
			mkdir -p obj; \
			for file in *.c; do clang -O3 -I/usr/include -c "$$file" -o "obj/$${file%.c}.o" > /dev/null 2>&1 || true; done; \
			ar -r libmlx.a obj/*.o > /dev/null 2>&1 || true; \
			ranlib libmlx.a > /dev/null 2>&1 || true; \
		); \
	fi

all: $(NAME)

# Clean targets
clean:
	@echo "[" "$(YELLOW)..$(RESET)" "] | Removing object files..."
	@rm -rf $(OBJECTS_DIRECTORY)
	@make -sC $(LIBFT_DIRECTORY) clean > /dev/null 2>&1
	@rm -rf $(MLX_DIRECTORY)obj/
	@echo "[" "$(YELLOW)..$(RESET)" "] | Updating Project analytics..."
	@./project_extras/scripts/update_analytics.sh
	@echo "[" "$(GREEN)OK$(RESET)" "] | Analytics updated!"
	@echo "[" "$(GREEN)OK$(RESET)" "] | Object files removed."

fclean: clean
	@echo "[" "$(YELLOW)..$(RESET)" "] | Removing $(NAME)..."
	@rm -rf $(NAME)
	@make -sC $(LIBFT_DIRECTORY) fclean > /dev/null 2>&1
	@echo "[" "$(GREEN)OK$(RESET)" "] | $(NAME) removed."

clean_mlx:
	@echo "[" "$(YELLOW)..$(RESET)" "] | Removing minilibx..."
	@rm -rf $(MLX_DIRECTORY)obj/
	@rm -rf $(MLX_DIRECTORY)libmlx.a
	@echo "[" "$(GREEN)OK$(RESET)" "] | Minilibx removed."

# Norminette check
norm:
	@echo "[" "$(YELLOW)..$(RESET)" "] | Running norminette..."
	@rm -f .norminette.log
	@for lib in libraries/*/; do \
		case "$$lib" in \
			*minilibx*) ;; \
			*) norminette $$lib >> .norminette.log 2>&1 || true ;; \
		esac; \
	done
	@norminette $(SRCS_DIRECTORY) $(HEADER_DIRECTORY) >> .norminette.log 2>&1 || true
	@if grep -q "Error!" .norminette.log; then \
		echo "[" "$(RED)!!$(RESET)" "] | Norminette found errors:"; \
		grep "Error!" .norminette.log | awk '{print "[ " "$(RED)!!$(RESET)" " ] | " $$0}'; \
	else \
		echo "[" "$(GREEN)OK$(RESET)" "] | Norminette passed!"; \
	fi

# Rebuild target
re: fclean
	@echo "[" "$(YELLOW)..$(RESET)" "] | Rebuilding $(NAME)..."
	@make -s

run: $(NAME)
	./$(NAME)

submit:
	@echo "[" "$(YELLOW)..$(RESET)" "] | Preparing project for submission..."
	@echo "[" "$(YELLOW)..$(RESET)" "] | Removing none mandatory files..."
	@./project_extras/scripts/prepare_submission.sh
	@echo "[" "$(GREEN)OK$(RESET)" "] | None mandatory files removed!"
	@echo "[" "$(GREEN)OK$(RESET)" "] | Project prepared for submission!"

# Help target
help:
	@echo "Available targets:"
	@echo "  $(NAME)     - Build the $(NAME) executable"
	@echo "  clean       - Remove object files"
	@echo "  fclean      - Remove object files and executable"
	@echo "  re          - Rebuild everything"
	@echo "  run         - Build and run cub3d"
	@echo "  norm        - Run norminette check"
	@echo "  submit      - Prepare project for submission"
	@echo "  help        - Show this help message"

.PHONY: all clean fclean re run norm submit help $(MLX)