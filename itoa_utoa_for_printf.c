#include "ft_printf.h"

static size_t	count_length(size_t num, size_t now)
{
	if (!num)
		return (now);
	return (count_length(num / 10, now + 1));
}

static char	*set_to_list(size_t num, size_t len)
{
	char	*res;
	size_t	i;

	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[len - i - 1] = num % 10 + '0';
		num /= 10;
		i++;
	}
	res[len] = '\0';
	return (res);
}

t_args	itoa_for_printf(int n, t_args args)
{
	size_t	num;
	size_t	len;

	if (n < 0)
	{
		args.is_negative_num = true;
		if (n == INT_MIN)
			num = (size_t)(-(n + 1)) + 1;
		else
			num = -n;
	}
	else
		num = n;
	len = count_length(num, 0) + (n == 0);
	args.dup_str = set_to_list(num, len);
	if (args.dup_str == NULL)
		args.error = ERROR_MALLOC;
	args.len_str = len;
	return (args);
}

t_args	utoa_for_printf(unsigned int n, t_args args)
{
	size_t	num;
	size_t	len;

	num = n;
	len = count_length(num, 0) + (n == 0);
	args.dup_str = set_to_list(num, len);
	if (args.dup_str == NULL)
		args.error = ERROR_MALLOC;
	args.len_str = len;
	return (args);
}
