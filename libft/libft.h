/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:42:46 by lmarchai          #+#    #+#             */
/*   Updated: 2022/11/07 14:42:46 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include<unistd.h>
# include<stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}			t_list;

void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_bzero(void *s, size_t n);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void *pointer, int value, size_t count);
void	*ft_memcpy(void *destination, const void *source, size_t size);
void	*ft_memmove(void *destination, const void *source, size_t size);
void	*ft_memchr(const void *pointer, int searchedChar, size_t size);

int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t nb);
int		ft_atoi(const char *str);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_isdigit(int i);
int		ft_isalnum(int i);
int		ft_isalpha(int i);
int		ft_isdigit(int i);
int		ft_isascii(int i);
int		ft_isprint(int i);
int		ft_memcmp( const void *pointer1, const void *pointer2, size_t size );
int		ft_lstsize(t_list *lst);

size_t	ft_strlen(const char *str);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

char	*ft_strdup(const char *s);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strcat(char *dest, char *src);
char	*ft_strncat(char *dest, const char *src, size_t nb);
char	*ft_strstr(const char *str, const char *to_find);
char	*ft_strchr(const char *str, int to_find);
char	*ft_strrchr(const char *s, int to_find);
char	*ft_strnstr(const char *str, const char *to_find, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_itoa(int n);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f) (unsigned int, char));

char	**ft_split(char const *s, char c);

t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif