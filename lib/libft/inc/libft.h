/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:21:28 by narajaon          #+#    #+#             */
/*   Updated: 2018/01/26 14:20:41 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef union		u_uni
{
	unsigned int	dec;
	unsigned char	oct_4[4];
	unsigned char	oct_3[3];
	unsigned char	oct_2[2];
	unsigned char	oct_1;
}					t_uni;

void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *str, const char *to_find);
char				*ft_strnstr(const char *str, const char *to_find, size_t n);
char				*ft_strdup(const char *src);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t nb);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char *str);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int nb, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **ast, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *lst_new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_print_words_tables(char **str);
long				ft_abs(long nb);
int					ft_atoi_base(const char *str, int str_base);
void				free_tab(char **str);
void				ft_lstback(t_list **alst, void const *content,
		size_t size);
void				ft_lstadd_back(t_list **alst, t_list *new_node);
char				*ft_strtrimc(char const *s, char c);
char				*ft_strndup(const char *src, int n);
void				ft_bzero(void *s, size_t n);
size_t				ft_strlen(const char *str);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_atoi(const char *str);

int					ft_isc(char c, char to_find);
int					ft_isnu(int n, int to_find);
int					ft_islower(int c);
int					ft_isupper(int c);
int					ft_isspace(int c);
int					ft_iseven(int nb);
long				ft_abs(long nb);

int					ft_atoi_base(const char *str, int str_base);
int					ft_strcpy_ret(char *dest, const char *src);
int					ft_strncpy_ret(char *dest, const char *src, size_t n);
int					ft_itoa_base(int num, char *buff, int base);
int					ft_ltoa_base(long long int num, char *buff, int base);
int					ft_cap_ultoa_base(unsigned long long num,
		char *buff, int base);
int					ft_itoa_str(int n, char *str);
unsigned int		ft_uitoa_str(unsigned int n, char *str);
int					ft_ultoa_str(unsigned long long n, char *str);
int					ft_ultoa_base(unsigned long long num, char *buff, int base);
int					ft_ltoa_str(long int n, char *str);
int					ft_lltoa_str(long long int n, char *str);
int					nbr_size(unsigned long long int nbr);
int					ft_putuni_str(unsigned int uni, char *str);
int					ft_putstr_uni(unsigned int *uni, char *str);
int					ft_tablen(char **str);
int					get_next_line(const int fd, char **line);

void				free_str(char **to_free);
void				free_tab_str(char ***tab_str);
void				ft_print_tab(char **tab_p);
#endif
