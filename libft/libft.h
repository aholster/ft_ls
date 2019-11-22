/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/12 18:16:38 by aholster       #+#    #+#                */
/*   Updated: 2019/11/20 09:32:38 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_queue
{
	t_list			*head;
	t_list			*tail;
}					t_queue;

/*
** mandatory functions
*/
int					ft_atoi(char const *str);
void				ft_bzero(void *s, size_t n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
char				*ft_itoa(int n);
void				ft_lstadd(t_list **const alst, t_list *const new);
void				ft_lstdel(t_list **const alst,\
						void (*const del)(void *, size_t));
void				ft_lstdelone(t_list **const alst,\
						void(*const del)(void*, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);
void				*ft_memalloc(size_t size);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(void const *s, int c, size_t n);
int					ft_memcmp(void const *s1, void const *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_memdel(void **ap);
void				*ft_memmove(void *dst, void const *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				ft_putchar(const char c);
void				ft_putchar_fd(const char c, const int fd);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, const int fd);
void				ft_putnbr_fd(int n, const int fd);
void				ft_putnbr(int n);
void				ft_putstr(char const *s);
void				ft_putstr_fd(char const *s, const int fd);
char				*ft_strcat(char *s1, char const *s2);
char				*ft_strchr(char const *s, int c);
void				ft_strclr(char *s);
int					ft_strcmp(char const *s1, char const *s2);
int					ft_strncmp(char const *s1, char const *s2, size_t n);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
void				ft_strdel(char **as);
char				*ft_strdup(char const *s1);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, char const *src, size_t size);
size_t				ft_strlen(char const *s);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strnew(size_t size);
char				*ft_strncat(char *s1, char const *s2, size_t n);
char				*ft_strnstr(char const *haystack, char const *needle,\
size_t len);
char				*ft_strrchr(char const *s, int c);
char				**ft_strsplit(char const *s, char c);
char				*ft_strstr(char const *haystack, char const *needle);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);
int					ft_tolower(int c);
int					ft_toupper(int c);

# pragma mark advanced math

unsigned int		ft_isprime(unsigned int num);
int					ft_power(int num, unsigned int power);
int					ft_sqrt(int nb);
int					ft_factorial(int nb);

# pragma mark simple math

char				*ft_itoba(int n, unsigned int base);
unsigned int		ft_ll_len(long long n, unsigned int base);
unsigned int		ft_ull_len(unsigned long long n, const unsigned int base);
int					ft_max(int val1, int val2);
int					ft_min(int val1, int val2);
int					ft_constrain(int in, int min, int max);
long long			ft_absneg(long long num);
int					*ft_range(int min, int max);

# pragma mark lst handling

void				ft_del(void *data, size_t size);
t_list				*ft_lstaddend(t_list **const lst, t_list *const new);
unsigned int		ft_lstlen(t_list *lst);
void				ft_lsttardest(t_list **lst, t_list **target,\
						void (*del)(void *, size_t));
char				**ft_lsttostrarr(t_list *lst);
t_list				*ft_strarrtolst(char **strarr);
int					ft_lstmemtomem(char **feed, size_t *totallen,\
						t_list *lst);
int					ft_lststrtostr(char **feed, t_list *lst);

int					ft_lst_stack_push(t_list **const astack,\
						void const *content,\
						const size_t content_size);
t_list				*ft_lst_stack_pop(t_list **const astack);

int					ft_lstqueue_push(t_queue *const aqueue,\
						void const *const content,\
						const size_t content_size);
t_list				*ft_lstqueue_pop(t_queue *const aqueue);
void				ft_lstqueue_add(t_queue *const aqueue, t_list *const anode);

# pragma mark str handling

size_t				ft_strnlen(char const *s, size_t maxlen);

void				ft_putstrarr(char **strarr);
void				ft_putstrarr_fd(char **strarr, const int fd);
void				ft_strarrdel(char ***ap);
char				**ft_strarrnew(size_t size);
char				**ft_textangle(size_t x, size_t y, char c);
char				*ft_stralloc(size_t size, char c);

void				ft_putcaret(int c);
void				ft_putcaret_fd(int c, const int fd);

# pragma mark mem handling

void				ft_stock_write(unsigned char *stock, size_t bitnum);
int					ft_stock_read(const unsigned char *stock, size_t bitnum);
void				ft_putmem(char *mem, size_t len);
void				ft_putmem_fd(char *mem, size_t len, const int fd);
void				ft_putmemendl(char *mem, size_t len);
void				ft_putmemendl_fd(char *mem, size_t len, const int fd);
void				*ft_memjoin(const void *mem1, size_t size1, \
					const void *mem2, size_t size2);
void				*ft_memdup(const void *src, const size_t len);

void				ft_bitprint(const void *addr, size_t size);

# pragma mark utility

int					ft_iswhitespace(int c);
void				ft_swap(void *a, void *b);
void				ft_segdefault(void);
size_t				ft_count_if(char **tab, int (*f)(char*));
int					ft_islowercase(int c);
int					ft_iscapital(int c);

#endif
