#include "ft_printf.h"

char	*ft_strchr(const char *s, int int_c)
{
	char	c;

	c = (char)int_c;
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

bool	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

int	ft_toupper(int c)
{
	if ('a' <= c && c <= 'z')
		c += 'A' - 'a';
	return (c);
}

size_t	ft_max(size_t x, size_t y)
{
	if (x >= y)
		return (x);
	return (y);
}

bool	is_zero_num(t_args args)
{
	return (args.len_str <= 1 && args.dup_str[0] == '0');
}
