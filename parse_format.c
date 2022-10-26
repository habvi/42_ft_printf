#include "ft_printf.h"

static bool	is_overflow(size_t num, int c)
{
	size_t	ov_div;
	size_t	ov_mod;

	ov_div = INT_MAX / 10;
	ov_mod = INT_MAX % 10;
	if (num > ov_div)
		return (true);
	if (num == ov_div && (size_t)c - '0' > ov_mod)
		return (true);
	return (false);
}

static t_args	atoi_for_printf(t_args args, size_t kind)
{
	size_t	*num;

	if (kind == WIDTH)
		num = &args.width;
	else if (kind == PRECISION)
		num = &args.precision;
	if (is_overflow(*num, *args.fmt))
	{
		args.error = ERROR_OVERFLOW;
		return (args);
	}
	*num = *num * 10 + *args.fmt - '0';
	return (args);
}

// ignore spaces
t_args	set_format_flags(t_args args)
{
	const char	c = *args.fmt;

	if (args.dot)
	{
		args = atoi_for_printf(args, PRECISION);
		args.fmt++;
		return (args);
	}
	if (c == '-')
		args.minus = true;
	else if (c == '+')
		args.plus = true;
	else if (c == '#')
		args.sharp = true;
	else if (c == '0' && !ft_isdigit(*(args.fmt - 1)))
		args.zero = true;
	else if (c == '.')
		args.dot = true;
	else if (ft_isdigit(c))
		args = atoi_for_printf(args, WIDTH);
	args.fmt++;
	return (args);
}
