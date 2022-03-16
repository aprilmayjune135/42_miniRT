/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 11:43:27 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/15 15:13:49 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_count_char(char *s, char c);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *haystack, \
						const char *needle, size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
long long int		ft_str2int(char *str, int j, int sign);
double				ft_str2double(char *str, int sign);
long long int		ft_atoi(char *str);
long long int		ft_axtoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isspace(char c);
int					ft_toupper(int c);
int					ft_tolower(int c);
long long int		ft_min(int count, ...);
long long int		ft_max(int count, ...);
double				ft_min_double(int count, ...);
double				ft_max_double(int count, ...);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s1);
char				*ft_strdup_free(char *dst, char *src, int n);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_substr_free(char *s, unsigned int start, \
						size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_free(char *s1, char *s2, int n);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
size_t				ft_count_digit(long long int n);
size_t				ft_count_digit_u(unsigned long long int n);
size_t				ft_count_digit_d(double n);
size_t				ft_count_decimal_d(double n);
double				ft_power_d(double base, int power);
double				ft_first_digit(double n);
double				ft_last_digit(double n);
long long int		ft_dtoi(double n);
char				*ft_itoa(long long int n);
char				*ft_itoa_u(unsigned long long int n);
char				*ft_xtoa(unsigned long long int n);
char				*ft_otoa(unsigned long long int n);
char				*ft_dtoa(double n, int decimal_count);
char				*ft_etoa(double n, int precision, char letter_e);
char				*ft_gtoa(double n, int precision, char letter_g);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr(char *s);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

#endif
