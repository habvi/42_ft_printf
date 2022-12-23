#include "ft_printf.h"

void	init_info(t_info *info, const char *format)
{
	info->fmt = format;
	info->is_format_specifier = false;
	info->minus = false;
	info->plus = false;
	info->hash = false;
	info->zero = false;
	info->len_zero = 0;
	info->width = 0;
	info->dot = false;
	info->precision = 0;
	info->space = false;
	info->type = '\0';
	info->is_negative_num = false;
	info->dup_str = NULL;
	info->len_str = 0;
	info->len_flagged_str = 0;
	info->field_width = 0;
	info->output = NULL;
	info->index = 0;
	info->error = 0;
	info->total_len = 0;
}

void	clear_fmt_info(t_info *info)
{
	info->minus = false;
	info->plus = false;
	info->hash = false;
	info->zero = false;
	info->len_zero = 0;
	info->width = 0;
	info->dot = false;
	info->precision = 0;
	info->space = false;
	info->type = '\0';
	info->is_negative_num = false;
	info->dup_str = NULL;
	info->len_str = 0;
	info->len_flagged_str = 0;
	info->field_width = 0;
}

void	free_dup_str(t_info *info)
{
	free(info->dup_str);
	info->dup_str = NULL;
}

void	put_output(t_info *info)
{
	ssize_t	res;

	res = write(STDOUT_FILENO, info->output, info->index);
	info->total_len += res;
	if (res == -1 || info->total_len >= INT_MAX)
	{
		free(info->output);
		info->error = EXIT;
		return ;
	}
	free(info->output);
	info->output = NULL;
}
