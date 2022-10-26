#include "ft_printf.h"

static t_args	set_for_mandatory(t_args args)
{
	args.field_width = args.len_str;
	return (args);
}

static bool	is_cspu_types(t_args args)
{
	return (args.type == 'c' || args.type == 's' || \
			args.type == 'p' || args.type == 'u');
}

static t_args	set_field_width_cspu(t_args args)
{
	if (args.type == 'c')
		args.field_width = args.width;
	else if (args.type == 's')
	{
		if (args.precision && args.precision < args.len_str)
			args.len_str = args.precision;
		args.field_width = ft_max(args.width, args.len_str);
	}
	else if (args.type == 'p' || args.type == 'u')
		args.field_width = ft_max(args.width, args.len_str);
	args.len_flagged_str = args.len_str;
	return (args);
}

static t_args	set_field_width_dix2(t_args args)
{
	size_t	add_flag;

	if (args.type == 'x' || args.type == 'X')
		add_flag = (2 * args.sharp);
	else
		add_flag = args.plus;
	args.len_flagged_str = args.len_str + add_flag;
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
	if ((!args.width && !args.precision) || args.type == '%')
		return (set_for_mandatory(args));
	if (is_cspu_types(args))
		return (set_field_width_cspu(args));
	return (set_field_width_dix2(args));
}
