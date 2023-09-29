
#ifndef LIBFT_H
# define LIBFT_H


/* ************************* */
/*         Librairies        */
/* ************************* */

# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include <unistd.h>
# include <stddef.h>
# include <stdint.h>
# include <stdarg.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

/* ************************* */
/*          Define           */
/* ************************* */

/*GNL*/

# define BUFFER_SIZE 42

/*Dprintf*/
# define HEXA_VAL "0123456789ABCDEF"
# define HEXA_VAL_MIN "0123456789abcdef"

/* ************************* */
/*          Typedefs         */
/* ************************* */

/* Linked lists */

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/* ************************* */
/*         Prototypes        */
/* ************************* */

/*Bools*/
int		ft_isalpha(int i);
int		ft_isdigit(int i);
int		ft_isalnum(int i);
int		ft_isascii(int i);
int		ft_isprint(int i);
int		ft_isprint(int i);

/*Strings*/
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t n);
char	*ft_strchr(const char *s, int c);
int		ft_strchr_int(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/*Chars*/
int		ft_toupper(int c);
int		ft_tolower(int c);

/*Display*/
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

/*GNL*/
char	*ft_get_next_line(int fd);

/*Linked lists*/
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*Memory*/
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t	n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

/*Numbers*/
int		ft_atoi(const char *str);
char	*ft_itoa(int n);

/*Printf*/
int		ft_printf(int output, const char *str, ...);
void	ft_args_pf(int output, char c, va_list ap, int *n);
void	ft_putchar_pf(int output, char c, int *n);
void	ft_putstr_pf(int output, char *str, int *n);
void	ft_putnbr_pf(int output, long long int nb, int *n, int is_unsigned);
void	ft_puthexa_pf(int output, unsigned long long int nb, int *n, int c);
void	ft_putptr_pf(int output, unsigned long int ptr, int *n);

/*Dprintf*/
char	*fill_str_with_param(char *new, va_list args, char c, int *size);
char	*fill_str_with_buff(char *new, char *buff, int *size);
char	*arg_to_content(char c, va_list args, int *size);
char	*fill_new(char	*str, va_list args, int *size);

char	*ft_intohex(char *str, unsigned long nbr, char *base_to);
char	*str_reverse(char *str);
char	*ft_itoa_hex(unsigned long nbr, char *base_to);

int		calc_char(unsigned int n);
char	*ft_itoa_u(unsigned int n);

char	*get_char(int c, int *size);
char	*get_string(char *str, int *size);
char	*get_pointer(unsigned long pntr, int *size);
char	*get_int(int nbr, int *size);
char	*get_unsigned_int(unsigned int nbr, int *size);
char	*get_hex_value_min(unsigned long nbr, int *size);
char	*get_hex_value(unsigned long nbr, int *size);

int		ft_dprintf(int i, char	*str, ...);
int		is_convert(char c);


#endif