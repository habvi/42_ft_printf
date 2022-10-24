#include "ft_printf.h"

t_args	convert_u_to_str(t_args args)
{
	const unsigned int	num = va_arg(args.args_list, unsigned int);

	return (utoa_for_printf(num, args));
}

t_args	convert_x_to_str(t_args args)
{
	const unsigned int	num = va_arg(args.args_list, unsigned int);

	return (xtoa_for_printf(num, args, false));
}

t_args	convert_upoperx_to_str(t_args args)
{
	const unsigned int	num = va_arg(args.args_list, unsigned int);

	return (xtoa_for_printf(num, args, true));
}

t_args	convert_percent_to_str(t_args args)
{
	char	s[2];

	s[0] = '%';
	s[1] = '\0';
	return (strdup_for_printf(args, s));
}
