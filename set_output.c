#include "ft_printf.h"

static t_args	fill_n_with_c(t_args args, size_t size, char c)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		args.output[args.index] = c;
		args.index++;
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
		args.output[args.index] = args.dup_str[i];
		args.index++;
		i++;
	}
	args.output[args.index] = '\0';
	return (free_dup_str(args));
}

static t_args	set_sign_0x_space(t_args args)
{
	if (args.is_negative_num)
		args = fill_n_with_c(args, 1, '-');
	else if (args.plus && (args.type == 'd' || args.type == 'i'))
		args = fill_n_with_c(args, 1, '+');
	else if (args.hash && (args.type == 'x' || args.type == 'X') \
		&& !is_zero_num(args))
	{
		args = fill_n_with_c(args, 1, '0');
		args = fill_n_with_c(args, 1, args.type);
	}
	else if (args.space && args.type != 's')
		args = fill_n_with_c(args, 1, ' ');
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

t_args	set_output(t_args args)
{
	size_t	len_space;

	args.index = 0;
	if (args.type && *(args.fmt - 2) == '%')
		return (copy_str(args, false));
	args = calc_len_zero(args);
	len_space = args.field_width - args.len_flagged_str - args.len_zero;
	if (!args.minus)
		args = fill_n_with_c(args, len_space, ' ');
	args = set_sign_0x_space(args);
	args = fill_n_with_c(args, args.len_zero, '0');
	args = copy_str(args, true);
	if (args.minus)
		args = fill_n_with_c(args, len_space, ' ');
	return (args);
}
