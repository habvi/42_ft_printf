#include "ft_printf.h"

static void	strlcpy_for_printf(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i + 1 < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

t_args	strdup_for_printf(t_args args, const char *src)
{
	size_t	len_s;
	char	*dst;

	len_s = ft_strlen(src);
	dst = (char *)malloc(sizeof(char) * (len_s + 1));
	if (dst == NULL)
	{
		args.error = ERROR_MALLOC;
		return (args);
	}
	strlcpy_for_printf(dst, src, len_s + 1);
	args.dup_str = dst;
	if (args.type == 'c' && !len_s)
		len_s++;
	args.len_str = len_s;
	return (args);
}
