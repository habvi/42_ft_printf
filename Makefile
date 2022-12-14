SRCS		=	ft_printf.c \
				handle_info.c \
				parse_format.c \
				convert_to_str.c \
				convert_to_str2.c \
				strdup_for_printf.c \
				itoa_utoa_for_printf.c\
				ptoa_xtoa_for_printf.c \
				set_field.c \
				set_output.c \
				utils.c

OBJS		= 	$(SRCS:.c=.o)

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar rcs

NAME		= libftprintf.a

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

bonus: all

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
