#include "ft_printf.h"

void	init_t_args(t_args *args, const char *format)
{
	args->fmt = format;
	args->is_format_specifier = false;
	args->minus = false;
	args->plus = false;
	args->hash = false;
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
	args->output = NULL;
	args->index = 0;
	args->error = 0;
	args->total_len = 0;
}

t_args	clear_fmt_info(t_args args)
{
	args.minus = false;
	args.plus = false;
	args.hash = false;
	args.zero = false;
	args.len_zero = 0;
	args.width = 0;
	args.dot = false;
	args.precision = 0;
	args.space = false;
	args.type = '\0';
	args.is_negative_num = false;
	args.dup_str = NULL;
	args.len_str = 0;
	args.len_flagged_str = 0;
	args.field_width = 0;
	return (args);
}

t_args	free_dup_str(t_args args)
{
	free(args.dup_str);
	args.dup_str = NULL;
	return (args);
}

t_args	put_output(t_args args)
{
	ssize_t	res;

	res = write(STDOUT, args.output, args.index);
	args.total_len += res;
	if (res == -1 || args.total_len >= INT_MAX)
	{
		free(args.output);
		args.error = EXIT;
		return (args);
	}
	free(args.output);
	args.output = NULL;
	return (args);
}
