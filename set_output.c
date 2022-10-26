#include "ft_printf.h"

static	t_args	copy_str_for_mandatory(t_args args)
{
	size_t	i;

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

static t_args	set_sign_or_0x(t_args args)
{
	if (args.plus && (args.type == 'd' || args.type == 'i'))
	{
		if (args.is_negative_num)
			return (fill_n_with_c(args, 1, '-'));
		else
			return (fill_n_with_c(args, 1, '+'));
	}
	else if (args.sharp && (args.type == 'x' || args.type == 'X'))
	{
		args = fill_n_with_c(args, 1, '0');
		args = fill_n_with_c(args, 1, 'x');
	}
	return (args);
}

// 26 lines
t_args	set_output(t_args args)
{
	size_t	len_zero;
	size_t	len_space;

	if ((!args.width && !args.precision) || args.type == '%')
		return (copy_str_for_mandatory(args));
	len_zero = 0;
	if (!args.precision)
	{
		if (args.zero && args.width > args.len_flagged_str)
			len_zero = args.width - args.len_flagged_str;
	}
	else
	{
		if (args.precision > args.len_str)
			len_zero = args.precision - args.len_str;
	}
	len_space = args.field_width - args.len_flagged_str - len_zero;
	if (!args.minus)
		args = fill_n_with_c(args, len_space, ' ');
	args.len_zero = len_zero;
	args = set_sign_or_0x(args);
	args = fill_n_with_c(args, args.len_zero, '0');
	args = copy_str_for_mandatory(args);
	if (args.minus)
		args = fill_n_with_c(args, len_space, ' ');
	return (args);
}
