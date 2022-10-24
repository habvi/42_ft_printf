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

	return (itoa_for_printf(num, args));
}
