LIBFT_PATH = ./libft
LIBFT_SRCS = ${addprefix ${LIBFT_PATH}/, ft_strcpy.c \
			free_tab.c \
			ft_free.c \
			count_words.c \
			ft_atoi.c \
			ft_atol.c \
			ft_bzero.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_strlen.c \
			ft_strlcpy.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strcmp.c \
			ft_strncmp.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strcat.c \
			ft_strlcat.c \
			ft_strnstr.c \
			ft_strdup.c \
			ft_calloc.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_strjoin.c \
			ft_strjoinf.c \
			ft_strjoinc.c \
			ft_strjoinwsep.c \
			ft_substr.c \
			ft_strtrim.c \
			ft_itoa.c \
			ft_striteri.c \
			ft_strmapi.c \
			ft_split.c \
			nbsize.c \
			ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstsize.c \
			ft_joinf.c \
			is_whitespace.c }

PRINTF_PATH = ./printf
PRINTF_SRCS = ${addprefix ${PRINTF_PATH}/, ft_printf.c \
			ft_printf_utils1.c \
			ft_printf_utils2.c}

GNL_PATH = ./gnl
GNL_SRCS = ${addprefix ${GNL_PATH}/, get_next_line.c}

SRCS = ${LIBFT_SRCS} ${PRINTF_SRCS} ${GNL_SRCS}
OBJS = ${SRCS:.c=.o}
NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
AR = ar rcs 
RM = rm -rf
INCLUDE = ./inc

%.o:%.c ${INCLUDE}    
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ${INCLUDE}

all : ${NAME}

${NAME} : ${OBJS}
	@${AR} ${NAME} ${OBJS}

clean:
	@${RM} ${OBJS} 

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re