#include "ft_printf.h"

static t_args	parse_format(t_args args)
{
	args.fmt++;
	while (*args.fmt && ft_strchr(FORMAT_TYPES, *args.fmt) == NULL)
	{
		args = set_format_flags(args);
		if (args.error)
			return (args);
	}
	args.type = *args.fmt;
	args = convert_to_str(args);
	if (args.error)
		return (args);
	args.fmt++;
	args = set_field_width(args);
	return (set_output(args));
}

static t_args	format_specifier_mode(t_args args)
{
	args = parse_format(args);
	if (args.error)
		return (args);
	args.is_format_specifier = false;
	return (args);
}

static t_args	normal_char_mode(t_args args)
{
	args = clear_fmt_info(args);
	while (*args.fmt && *args.fmt != '%')
	{
		args.output[args.len_output] = *args.fmt;
		if (args.len_output == INT_MAX)
		{
			args.error = ERROR_OVERFLOW;
			return (args);
		}
		args.len_output++;
		args.fmt++;
	}
	args.output[args.len_output] = '\0';
	args.is_format_specifier = true;
	if (!args.fmt)
		args.fmt++;
	return (args);
}

static t_args	format_specifier_or_not(t_args args)
{
	while (*args.fmt)
	{
		if (args.is_format_specifier)
			args = format_specifier_mode(args);
		else
			args = normal_char_mode(args);
		if (args.error)
			return (args);
	}
	return (args);
}

int	ft_printf(const char *format, ...)
{
	t_args		args;

	va_start(args.args_list, format);
	init_t_args(&args, format);
	if (args.error == ERROR_MALLOC)
		return (ERROR);
	args = format_specifier_or_not(args);
	va_end(args.args_list);
	if (args.error)
	{
		free(args.output);
		return (ERROR);
	}
	put_output(args);
	free(args.output);
	return (args.len_output);
}
