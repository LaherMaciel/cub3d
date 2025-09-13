/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:20:26 by lwencesl          #+#    #+#             */
/*   Updated: 2025/09/13 02:20:12 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/* ************************************************************************** */
/*                                INCLUDES                                    */
/* ************************************************************************** */

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>
# include <fcntl.h>
# include <errno.h>

/* ************************************************************************** */
/*                                CONSTANTS                                   */
/* ************************************************************************** */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/* ************************************************************************** */
/*                                COLOR CODES                                 */
/* ************************************************************************** */

# define CLEAR "\033c"
# define RED        "\033[1;31m"
# define GREEN      "\033[1;32m"
# define YELLOW     "\033[1;33m"
# define BLUE       "\033[1;34m"
# define MAGENTA    "\033[1;35m"
# define CYAN       "\033[1;36m"
# define WHITE      "\033[1;37m"
# define GRAY       "\033[1;90m"
# define ORANGE     "\033[38;5;208m"
# define PURPLE     "\033[38;5;129m"
# define PINK       "\033[38;5;205m"
# define LIME       "\033[38;5;154m"
# define TEAL       "\033[38;5;30m"
# define LAVENDER   "\033[38;5;183m"
# define GOLD       "\033[38;5;220m"
# define MAROON     "\033[38;5;88m"
# define DEFAULT_COLOR "\033[0m"
# define BOLTED_DEFAULT_COLOR "\033[1;0m"

/* ************************************************************************** */
/*                                STRUCTURES                                  */
/* ************************************************************************** */

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

/* ************************************************************************** */
/*                           CHARACTER FUNCTIONS                              */
/* ************************************************************************** */

int			ft_isalnum(int a);
int			ft_isalpha(int c);
int			ft_isascii(int a);
int			ft_isdigit(int i);
int			ft_isprint(int a);
int			ft_isspace(int c);
int			ft_tolower(int a);
int			ft_toupper(int c);

/* ************************************************************************** */
/*                           MEMORY FUNCTIONS                                 */
/* ************************************************************************** */

void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t n, size_t size);
void		*ft_memchr(void *str, int c, size_t n);
int			ft_memcmp(const void *str1, const void *str2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *str, int c, size_t n);
void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void		*ft_realloc_and_clear(void *ptr, size_t old_size, size_t new_size);

/* ************************************************************************** */
/*                           STRING FUNCTIONS                                 */
/* ************************************************************************** */

size_t		ft_strlen(const char *a);
char		*ft_strchr(const char *str, int c);
char		*ft_strrchr(const char *str, int c);
int			ft_strcmp(const char *str1, const char *str2);
int			ft_strncmp(const char *str1, const char *str2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strcpy(char *dest, char *src);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlcat(char *dest, const char *src, size_t n);
char		*ft_strdup(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoin2(char *s1, char *s2, int flag);
char		*ft_strtrim(const char *str, const char *set);
char		**ft_split(char const *str, char c);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/* ************************************************************************** */
/*                           ARRAY FUNCTIONS                                  */
/* ************************************************************************** */

size_t		ft_arraylen(char **a);
size_t		ft_arraylen_void_nullterm(void **array);
void		*ft_free_array(char **array, size_t len);
void		*ft_free_array_void(void **array, size_t len,
				void (*free_func)(void *));
void		*ft_free_array_void_nullterm(void **array,
				void (*free_func)(void *));
char		**ft_rm_from_array(char **array, size_t arraylen, size_t index);
void		ft_swap(char **a, char **b, int flag);

/* ************************************************************************** */
/*                           CONVERSION FUNCTIONS                             */
/* ************************************************************************** */

size_t		ft_atoi(const char *str);
char		*ft_itoa(int n);

/* ************************************************************************** */
/*                           OUTPUT FUNCTIONS                                 */
/* ************************************************************************** */

void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

/* ************************************************************************** */
/*                           LINKED LIST FUNCTIONS                            */
/* ************************************************************************** */

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new_node);
void		ft_lstadd_back(t_list **lst, t_list *new_node);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* ************************************************************************** */
/*                           PRINTF FUNCTIONS                                 */
/* ************************************************************************** */

int			ft_printf(const char *format, ...);
int			ft_printf_fd(int fd, const char *format, ...);
int			ft_fdputchr(int fd, char s);
int			ft_fdputstr(int fd, char *s);

/* ************************************************************************** */
/*                           GET_NEXT_LINE                                    */
/* ************************************************************************** */

char		*get_next_line(int fd);

#endif