#include "ft_printf.h"

static bool	is_overflow(size_t num, int c)
{
	size_t	ov_div;
	size_t	ov_mod;

	ov_div = INT_MAX / 10;
	ov_mod = INT_MAX % 10;
	if (num >= ov_div)
		return (true);
	if (num == ov_div && (size_t)c - '0' >= ov_mod)
		return (true);
	return (false);
}

static void	atoi_for_printf(t_info *info, size_t kind)
{
	size_t	*num;

	if (kind == WIDTH)
		num = &info->width;
	else
		num = &info->precision;
	if (is_overflow(*num, *info->fmt))
	{
		if (kind == WIDTH)
			info->error = ERROR_OVERFLOW;
		else
			*num = INT_MAX;
		return ;
	}
	*num = *num * 10 + *info->fmt - '0';
}

void	set_format_flags(t_info *info)
{
	const char	c = *info->fmt;

	if (info->dot)
	{
		atoi_for_printf(info, PRECISION);
		info->fmt++;
		return ;
	}
	if (c == '-')
		info->minus = true;
	else if (c == '+')
		info->plus = true;
	else if (c == '#')
		info->hash = true;
	else if (c == '0' && !ft_isdigit(*(info->fmt - 1)))
		info->zero = true;
	else if (c == '.')
		info->dot = true;
	else if (c == ' ')
		info->space = true;
	else if (ft_isdigit(c))
		atoi_for_printf(info, WIDTH);
	info->fmt++;
}

void	check_ignored_flags(t_info *info)
{
	if (info->minus && info->zero)
		info->zero = false;
	if (info->plus && info->space)
		info->space = false;
}
