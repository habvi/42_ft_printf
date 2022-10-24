#include "ft_printf.h"

static size_t	count_length(size_t num, size_t now)
{
	if (!num)
		return (now);
	return (count_length(num / 16, now + 1));
}

static char	*set_to_list(size_t num, size_t start, size_t len)
{
	char	*res;
	size_t	i;

	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (start + i < len)
	{
		res[len - i - 1] = HEX[num % 16];
		num /= 16;
		i++;
	}
	res[len] = '\0';
	return (res);
}

t_args	ptoa_for_printf(unsigned long long n, t_args args)
{
	size_t	num;
	size_t	len;

	num = n;
	len = count_length(num, 0) + 2;
	if (n == 0)
		len = 3;
	args.dup_str = set_to_list(num, 2, len);
	if (args.dup_str == NULL)
	{
		args.error = ERROR_MALLOC;
		return (args);
	}
	args.dup_str[0] = '0';
	args.dup_str[1] = 'x';
	args.len_str = len;
	return (args);
}
