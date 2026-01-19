# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/31 18:07:37 by lwencesl          #+#    #+#              #
#    Updated: 2026/01/19 09:29:31 by lahermaciel      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = src/ft_atoi.c src/ft_bzero.c src/ft_calloc.c src/ft_isalnum.c src/ft_isalpha.c src/ft_isascii.c\
src/ft_isdigit.c src/ft_isprint.c src/ft_itoa.c src/ft_memchr.c src/ft_memcmp.c src/ft_memcpy.c\
src/ft_memmove.c src/ft_memset.c src/ft_putchar_fd.c src/ft_putendl_fd.c src/ft_putnbr_fd.c\
src/ft_putstr_fd.c src/ft_split.c src/ft_strchr.c src/ft_strdup.c src/ft_striteri.c src/ft_strjoin.c src/ft_strjoin2.c\
src/ft_strlcat.c src/ft_strlcpy.c src/ft_strlen.c src/ft_strmapi.c src/ft_strncmp.c src/ft_strnstr.c\
src/ft_strrchr.c src/ft_strtrim.c src/ft_substr.c src/ft_tolower.c src/ft_toupper.c src/ft_lstnew.c\
src/ft_lstadd_front.c src/ft_lstsize.c src/ft_lstlast.c src/ft_lstadd_back.c src/ft_lstdelone.c\
src/ft_lstclear.c src/ft_lstiter.c src/ft_lstmap.c src/ft_printf.c src/ft_printf_utils.c src/ft_printf_utils2.c\
src/ft_printf_fd.c src/ft_printf_fd_utils.c src/ft_printf_fd_arrays.c src/get_next_line_bonus.c src/get_next_line_utils_bonus.c\
src/ft_strcmp.c src/ft_free_array.c src/ft_arraylen.c src/ft_swap.c src/ft_rm_from_array.c\
src/ft_strcpy.c src/ft_realloc.c src/ft_realloc_and_clear.c src/ft_isspace.c src/ft_isalldigit.c

AR = ar rc
CC = cc
RM = @rm -f
CFLAGS = -g -Wall -Werror -Wextra -Iinclude

OBJ = $(notdir $(SRC:.c=.o))
OBJECTS_DIRECTORY = bin/
OBJECTS = $(addprefix $(OBJECTS_DIRECTORY), $(OBJ))

# COLORS
RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
RESET   = \033[0m

all: $(NAME)

$(NAME): $(OBJECTS_DIRECTORY) $(OBJECTS)
		@if $(AR) $(NAME) $(OBJECTS) > /dev/null 2>&1; \
		then \
			make norm -s; \
			echo "[" "$(GREEN)OK$(RESET)" "] | libft.a created!"; \
		else \
			echo "[" "$(RED)Error$(RESET)" "] | An error occurred while creating libft.a."; \
			make clean > /dev/null 2>&1; \
			echo "[" "$(RED)Error$(RESET)" "] | All objects cleaned."; \
		fi

$(OBJECTS_DIRECTORY):
	@echo "[" "$(YELLOW)..$(RESET)" "] | Creating objects..."
	@mkdir -p $(OBJECTS_DIRECTORY)
	@echo "[" "$(GREEN)OK$(RESET)" "] | Objects ready!"

$(OBJECTS_DIRECTORY)%.o: src/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "[" "$(YELLOW)..$(RESET)" "] | Removing object files...$(RESET)"
	@$(RM) $(OBJECTS)
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "[" "$(GREEN)OK$(RESET)" "] | Object files removed."

fclean: clean
	@echo "[" "$(YELLOW)..$(RESET)" "] | Removing binary files...$(RESET)"
	$(RM) $(NAME)
	@rm -rf .norminette.log
	@echo "[" "$(GREEN)OK$(RESET)" "] | Binary file removed."

re: fclean
	clear && make -s

test: $(NAME)
	@echo "[" "$(YELLOW)..$(RESET)" "] | Compiling test program..."
	@$(CC) $(CFLAGS) test_libft.c -L. -lft -o test_libft
	@echo "[" "$(GREEN)OK$(RESET)" "] | Test program compiled!"
	@echo "[" "$(YELLOW)..$(RESET)" "] | Running tests..."
	@./test_libft
	@echo "[" "$(GREEN)OK$(RESET)" "] | Tests completed!"

memtest: $(NAME)
	@echo "[" "$(YELLOW)..$(RESET)" "] | Compiling test program for memory check..."
	@$(CC) $(CFLAGS) test_libft.c -L. -lft -o test_libft
	@echo "[" "$(YELLOW)..$(RESET)" "] | Running valgrind memory check..."
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test_libft
	@echo "[" "$(GREEN)OK$(RESET)" "] | Memory check completed!"

norm:
	@echo "[" "$(YELLOW)..$(RESET)" "] | Norminetting...$(RESET)"
	@if norminette src/ include/ > .norminette.log 2>&1 ; then \
	    if grep -q "Error!" .norminette.log; then \
	        echo "[" "$(RED)!!$(RESET)" "] | Norminette found errors.$(RESET)"; \
	        grep "Error!" .norminette.log | awk '{print "[ " "$(RED)!!$(RESET)" " ] | " $$0}'; \
	    else \
	        echo "[" "$(GREEN)OK$(RESET)" "] | Norminette passed!"; \
	    fi; \
	else \
	    echo "[" "$(RED)XX$(RESET)" "] | Norminette Error!"; \
		norminette src/ include/ | awk '/Error!/ {print "[ " "$(RED)!!$(RESET)" " ] | " $$0}'; \
	fi

.PHONY: all clean fclean re test memtest norm