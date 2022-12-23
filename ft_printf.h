#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>

# define FORMAT_TYPES	"cspdiuxX%"
# define ERROR_MALLOC	1
# define ERROR_OVERFLOW	2
# define EXIT			3
# define ERROR			-1
# define HEX			"0123456789abcdef"
# define WIDTH			1
# define PRECISION		2

typedef struct s_info
{
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
}	t_info;

// ft_printf.c
int		ft_printf(const char *format, ...);

// handle_t_args.c
void	init_info(t_info *info, const char *format);
void	clear_fmt_info(t_info *info);
void	free_dup_str(t_info *info);
void	put_output(t_info *info);

// parse_format.c
void	set_format_flags(t_info *info);
void	check_ignored_flags(t_info *info);

// convert_to_str.c
void	convert_to_str(t_info *info, va_list *args_list);
// convert_to_str2.c
void	convert_u_to_str(t_info *info, va_list *args_list);
void	convert_x_to_str(t_info *info, va_list *args_list);
void	convert_upperx_to_str(t_info *info, va_list *args_list);
void	convert_percent_to_str(t_info *info);

// strdup_for_printf.c
void	strdup_for_printf(t_info *info, const char *src);

// itoa_utoa_for_printf.c
void	itoa_for_printf(int n, t_info *info);
void	utoa_for_printf(unsigned int n, t_info *info);
// ptoa_xtoa_for_printf.c
void	ptoa_for_printf(unsigned long long n, t_info *info);
void	xtoa_for_printf(unsigned int n, t_info *info, bool is_upper);

// set_field.c
void	set_field_width(t_info *info);

// set_output.c
void	set_output(t_info *info);

// utils.c
char	*ft_strchr(const char *s, int int_c);
bool	ft_isdigit(int c);
int		ft_toupper(int c);
size_t	ft_max(size_t x, size_t y);
bool	is_zero_num(t_info *info);

#endif
