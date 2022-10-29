#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>

# define STDOUT			1
# define FORMAT_TYPES	"cspdiuxX%"
# define ERROR_MALLOC	1
# define ERROR_OVERFLOW	2
# define EXIT			3
# define ERROR			-1
# define HEX			"0123456789abcdef"
# define WIDTH			1
# define PRECISION		2

typedef struct s_args
{
	va_list		args_list;
	const char	*fmt;
	bool		is_format_specifier;
	bool		minus;
	bool		plus;
	bool		hash;
	bool		zero;
	size_t		len_zero;
	size_t		width;
	bool		dot;
	size_t		precision;
	bool		space;
	char		type;
	bool		is_negative_num;
	char		*dup_str;
	size_t		len_str;
	size_t		len_flagged_str;
	size_t		field_width;
	char		*output;
	size_t		index;
	size_t		error;
	size_t		total_len;
}	t_args;

// ft_printf.c
int		ft_printf(const char *format, ...);

// handle_t_args.c
void	init_t_args(t_args *args, const char *format);
t_args	clear_fmt_info(t_args args);
t_args	free_dup_str(t_args args);
t_args	put_output(t_args args);

// parse_format.c
t_args	set_format_flags(t_args args);
void	check_ignored_flags(t_args *args);

// convert_to_str.c
t_args	convert_to_str(t_args args);
// convert_to_str2.c
t_args	convert_u_to_str(t_args args);
t_args	convert_x_to_str(t_args args);
t_args	convert_upoperx_to_str(t_args args);
t_args	convert_percent_to_str(t_args args);

// strdup_for_printf.c
t_args	strdup_for_printf(t_args args, const char *src);

// itoa_utoa_for_printf.c
t_args	itoa_for_printf(int n, t_args args);
t_args	utoa_for_printf(unsigned int n, t_args args);
// ptoa_xtoa_for_printf.c
t_args	ptoa_for_printf(unsigned long long n, t_args args);
t_args	xtoa_for_printf(unsigned int n, t_args args, bool is_upper);

// set_field.c
t_args	set_field_width(t_args args);

// set_output.c
t_args	set_output(t_args args);

// utils.c
char	*ft_strchr(const char *s, int int_c);
bool	ft_isdigit(int c);
int		ft_toupper(int c);
size_t	ft_max(size_t x, size_t y);
bool	is_zero_num(t_args args);

#endif
