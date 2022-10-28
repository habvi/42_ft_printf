#include "ft_printf.h"

void	put_output(t_args args)
{
	write(STDOUT, args.output, args.len_output);
}

t_args	clear_fmt_info(t_args args)
{
	args.minus = false;
	args.plus = false;
	args.sharp = false;
	args.zero = false;
	args.len_zero = 0;
	args.dot = false;
	args.space = false;
	args.type = '\0';
	// todo: necessary?
	args.width = 0;
	args.precision = 0;
	args.is_negative_num = false;
	args.len_str = 0;
	args.len_flagged_str = 0;
	args.field_width = 0;
	// args.error ?
	return (args);
}

void	init_t_args(t_args *args, const char *format)
{
	args->fmt = format;
	args->head = format;
	args->is_format_specifier = false;
	args->minus = false;
	args->plus = false;
	args->sharp = false;
	args->zero = false;
	args->len_zero = 0;
	args->width = 0;
	args->dot = false;
	args->precision = 0;
	args->space = false;
	args->type = '\0';
	args->is_negative_num = false;
	args->dup_str = NULL;
	args->len_str = 0;
	args->len_flagged_str = 0;
	args->field_width = 0;
	args->len_output = 0;
	args->error = 0;
	args->output = (char *)malloc(sizeof(char) * 10000 + 1);
	// args->output = (char *)malloc(sizeof(char) * (size_t)INT_MAX + 1);
	if (args->output == NULL)
		args->error = ERROR_MALLOC;
	args->output[0] = '\0';
}
