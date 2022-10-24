#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>

# include <stdio.h> // erase

# define STDOUT			1
# define FORMAT_TYPES	"cspdiuxX%"
# define ERROR_MALLOC	1
# define ERROR_OVERFLOW	2
# define ERROR			-1
# define HEX			"0123456789abcdef"

typedef struct s_args
{
	va_list		args_list;
	const char	*fmt;
	const char	*head;
	bool		is_format_specifier;
	char		bonus_flag; // -, +, #, 0
	size_t		width; // [1-9][0-9]
	size_t		precision; // . [1-9][0-9]
	char		type; // c, s, p, d, i, u, x, X, %
	char		*dup_str;
	size_t		len_str;
	char		*output;
	size_t		len_output;
	size_t		error;
}	t_args;

int		ft_printf(const char *format, ...);

t_args	convert_to_str(t_args args);
t_args	set_width(t_args args);
t_args	copy_correct_width(t_args args);
void	init_t_args(t_args *args, const char *format);
void	put_output(t_args args);

t_args	convert_c_to_str(t_args args);
t_args	convert_s_to_str(t_args args);
t_args	convert_p_to_str(t_args args);
t_args	convert_di_to_str(t_args args);
t_args	convert_u_to_str(t_args args);
t_args	convert_x_to_str(t_args args);
t_args	convert_upoperx_to_str(t_args args);
t_args	convert_percent_to_str(t_args args);

t_args	strdup_for_printf(t_args args, const char *src);

t_args	itoa_for_printf(int n, t_args args);
t_args	utoa_for_printf(unsigned int n, t_args args);
t_args	xtoa_for_printf(unsigned int n, t_args args, bool is_upper);
t_args	ptoa_for_printf(unsigned long long n, t_args args);

#endif
