#include "ft_printf.h"

static t_args	fill_n_with_c(t_args args, size_t size, char c)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		args.output[args.len_output] = c;
		args.len_output++;
		i++;
	}
	return (args);
}

static	t_args	copy_str(t_args args, bool is_bonus)
{
	size_t	i;

	if (!is_bonus && args.is_negative_num)
		args = fill_n_with_c(args, 1, '-');
	i = 0;
	while (i < args.len_str)
	{
		args.output[args.len_output] = args.dup_str[i];
		if (args.len_output == INT_MAX)
		{
			args.error = ERROR_OVERFLOW;
			return (args);
		}
		args.len_output++;
		i++;
	}
	args.output[args.len_output] = '\0';
	free(args.dup_str);
	args.dup_str = NULL;
	return (args);
}

static t_args	set_sign_or_0x(t_args args)
{
	if (args.is_negative_num)
		return (fill_n_with_c(args, 1, '-'));
	if (args.plus && (args.type == 'd' || args.type == 'i'))
		return (fill_n_with_c(args, 1, '+'));
	if (args.sharp && (args.type == 'x' || args.type == 'X') \
		&& !is_zero_num(args))
	{
		args = fill_n_with_c(args, 1, '0');
		if (args.type == 'x')
			args = fill_n_with_c(args, 1, 'x');
		else
			args = fill_n_with_c(args, 1, 'X');
	}
	return (args);
}

static t_args	calc_len_zero(t_args args)
{
	args.len_zero = 0;
	if (!args.precision)
	{
		if (args.zero && args.width > args.len_flagged_str)
			args.len_zero = args.width - args.len_flagged_str;
	}
	else
	{
		if (args.len_str && args.precision > args.len_str)
			args.len_zero = args.precision - args.len_str;
	}
	if (args.type == 's')
		args.len_zero = 0;
	return (args);
}

t_args	set_output(t_args args) // overflow
{
	size_t	len_space;

	if (args.type && *(args.fmt - 2) == '%')
		return (copy_str(args, false));
	args = calc_len_zero(args);
	len_space = args.field_width - args.len_flagged_str - args.len_zero;
	if (args.space)
		args.minus = false;
	if (!args.minus)
	{
		if (!len_space && args.type != 's')
			len_space = (args.space && !args.is_negative_num);
		args = fill_n_with_c(args, len_space, ' ');
	}
	args = set_sign_or_0x(args);
	args = fill_n_with_c(args, args.len_zero, '0');
	args = copy_str(args, true);
	if (args.minus)
		args = fill_n_with_c(args, len_space, ' ');
	return (args);
}
