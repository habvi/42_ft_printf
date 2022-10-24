SRCS		=	ft_printf.c ft_printf_sub.c \
				convert_to_str1.c convert_to_str2.c \
				strdup_for_printf.c \
				itoa_utoa_for_printf.c\
				xtoa_for_printf.c \
				ptoa_for_printf.c

OBJS		= 	$(SRCS:.c=.o)

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar rcs
# INCLUDES	= -I includes

NAME	= libftprintf.a

all: $(NAME)

$(NAME): $(OBJS) # todo
	$(MAKE) -C ./libft
	cp libft/libft.a $(NAME)
	$(CC) -c $(CFLAGS) $(SRCS)
	$(AR) $(NAME) $(OBJS)

bonus: all

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus