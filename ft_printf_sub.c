#include "ft_printf.h"

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

t_args	set_width(t_args args)
{
	args.width = args.len_str;
	return (args);
}

t_args	copy_correct_width(t_args args)
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
	return (args);
}

void	init_t_args(t_args *args, const char *format)
{
	args->fmt = format;
	args->head = format;
	args->is_format_specifier = false;
	args->bonus_flag = '\0';
	args->width = 0;
	args->precision = 0;
	args->type = '\0';
	args->dup_str = NULL;
	args->len_str = 0;
	args->len_output = 0;
	args->error = 0;
	args->output = (char *)malloc(sizeof(char) * 200 + 1);
	// args->output = (char *)malloc(sizeof(char) * (size_t)INT_MAX + 1);
	if (args->output == NULL)
		args->error = ERROR_MALLOC;
	args->output[0] = '\0';
}

void	put_output(t_args args)
{
	write(STDOUT, args.output, args.len_output);
}
