#include "ft_printf.h"

static size_t	count_length(size_t num, size_t now)
{
	if (!num)
		return (now);
	return (count_length(num / 16, now + 1));
}

static char	*set_to_list(size_t num, size_t len, bool is_upper)
{
	char	*res;
	size_t	i;
	char	hex;

	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		hex = HEX[num % 16];
		if (is_upper)
			hex = ft_toupper(hex);
		res[len - i - 1] = hex;
		num /= 16;
		i++;
	}
	res[len] = '\0';
	return (res);
}

t_args	xtoa_for_printf(unsigned int n, t_args args, bool is_upper)
{
	size_t	num;
	size_t	len;

	num = n;
	len = count_length(num, 0);
	if (n == 0)
		len = 1;
	args.dup_str = set_to_list(num, len, is_upper);
	if (args.dup_str == NULL)
		args.error = ERROR_MALLOC;
	args.len_str = len;
	return (args);
}
