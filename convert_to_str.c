#include "ft_printf.h"

t_args	convert_c_to_str(t_args args)
{
	const char	c = va_arg(args.args_list, int);
	char		s_null[1];
	char		s[2];

	if (c == '\0')
	{
		(void)s;
		s_null[0] = c;
		return (strdup_for_printf(args, s_null));
	}
	(void)s_null;
	s[0] = c;
	s[1] = '\0';
	return (strdup_for_printf(args, s));
}

t_args	convert_s_to_str(t_args args)
{
	const char	*s = va_arg(args.args_list, char*);

	if (s == NULL)
		s = "(null)";
	return (strdup_for_printf(args, s));
}

t_args	convert_p_to_str(t_args args)
{
	unsigned long long	addr;

	addr = va_arg(args.args_list, unsigned long long);
	return (ptoa_for_printf(addr, args));
}

t_args	convert_di_to_str(t_args args)
{
	const int	num = va_arg(args.args_list, int);

	if (num < 0)
		args.is_negative_num = true;
	return (itoa_for_printf(num, args));
}

t_args	convert_to_str(t_args args)
{
	const char	c = args.type;

	if (c == 'c')
		args = convert_c_to_str(args);
	else if (c == 's')
		args = convert_s_to_str(args);
	else if (c == 'p')
		args = convert_p_to_str(args);
	else if (c == 'd' || c == 'i')
		args = convert_di_to_str(args);
	else if (c == 'u')
		args = convert_u_to_str(args);
	else if (c == 'x')
		args = convert_x_to_str(args);
	else if (c == 'X')
		args = convert_upoperx_to_str(args);
	else if (c == '%')
		args = convert_percent_to_str(args);
	return (args);
}
