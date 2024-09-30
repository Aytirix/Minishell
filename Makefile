LIBFT_PATH 	= ./libft
LIBFT      	= $(LIBFT_PATH)/libft.a

LEXER_PATH 		= ./lexer
PARSER_PATH 	= ./parser
EXTENDER_PATH 	= ./extender
EXECUTION_PATH	= ./execution
BUILTINS_PATH 	= ./builtins

SRCS 	= main.c ${addprefix ${EXTENDER_PATH}/, env_edit.c split_for_env.c env_init.c env_build.c env_clear.c print_env.c} \
				 ${addprefix ${BUILTINS_PATH}/, signals.c cd.c echo.c env.c exit.c export.c pwd.c unset.c} \
				 ${addprefix ${LEXER_PATH}/, split.c split_utils.c split_utils2.c lexer.c lexer_init.c lexer_clean.c lexer_clear.c clean_str.c clean_utils.c clean_utils2.c} \
				 ${addprefix ${PARSER_PATH}/, parser.c redirections.c free_parser.c print_parser.c parse_utils.c} \
				 ${addprefix ${EXECUTION_PATH}/, executor.c redirections.c tools.c}
OBJS 	= ${SRCS:.c=.o}


NAME 	= minishell
DEBUG 	= 0
CC 		= cc
CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=address
LDFLAGS = -lreadline
RM 		= rm -rf
INCLUDES = -Iincludes

all : ${NAME}

${NAME} : ${LIBFT} ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT} ${LDFLAGS}

$(LIBFT):
	${MAKE} -C $(LIBFT_PATH) all

%.o: %.c
	$(CC) $(CFLAGS) -DDEBUG=$(DEBUG) -c -o $@ $< $(INCLUDES)
	
clean:
	@${MAKE} clean --silent -C ${LIBFT_PATH}
	@${RM} ${OBJS}
	@printf "MAKEFILE CLEAN\n"

fclean: clean
	@${MAKE} fclean --silent -C ${LIBFT_PATH}
	@${RM} ${NAME}
	@printf "MAKEFILE FCLEAN\n"

re: fclean all

.PHONY: all clean fclean re