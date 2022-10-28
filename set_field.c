#include "ft_printf.h"

static t_args	set_for_mandatory(t_args args)
{
	args.field_width = args.len_str + args.is_negative_num;
	return (args);
}

static bool	is_csp2_types(t_args args)
{
	return (args.type == 'c' || args.type == 's' || \
			args.type == 'p' || args.type == '%');
}

static t_args	set_field_width_csp2(t_args args)
{
	if (args.type == 'c')
		args.field_width = args.width;
	else if (args.type == 's')
	{
		if (args.dot && args.precision < args.len_str)
			args.len_str = args.precision;
		args.field_width = ft_max(args.width, args.len_str);
	}
	else if (args.type == 'p')
		args.field_width = ft_max(args.width, args.len_str);
	else
	{
		args.precision = 0;
		args.space = false;
		args.field_width = ft_max(args.width, args.len_str);
	}
	args.len_flagged_str = args.len_str;
	return (args);
}

static t_args	set_field_width_diux2(t_args args)
{
	size_t	add_flag;

	if (args.type == 'x' || args.type == 'X')
	{
		add_flag = (2 * args.sharp);
		if (args.sharp && args.width && is_zero_num(args))
			add_flag = 0;
	}
	else
		add_flag = (args.plus || args.is_negative_num);
	args.len_flagged_str = args.len_str + add_flag;
	if (args.dot && args.precision == 0 && is_zero_num(args))
	{
		args.len_str = 0;
		args.len_flagged_str = 0;
	}
	args.field_width = ft_max(args.width, args.len_flagged_str);
	if (args.precision > args.len_str)
	{
		args.field_width = ft_max(args.field_width, \
							ft_max(args.precision, args.len_str) + add_flag);
	}
	return (args);
}

t_args	set_field_width(t_args args)
{
	if (args.type && *(args.fmt - 2) == '%')
		return (set_for_mandatory(args));
	if (is_csp2_types(args))
		return (set_field_width_csp2(args));
	return (set_field_width_diux2(args));
}
