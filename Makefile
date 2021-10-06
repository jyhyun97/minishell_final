NAME = minishell
CC = gcc
# CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
LDFLAGS = -L${HOME}/.brew/opt/readline/lib
CPPFLAGS= -I${HOME}/.brew/opt/readline/include	
MAKE = make
RM				= rm -f
SRCS = 	builtin_cd_exit.c\
		builtin_echo_env_pwd.c\
		builtin_export.c\
		builtin_export2.c\
		builtin_export_util.c\
		builtin_sorted.c\
		builtin_unset.c\
		envp_list.c\
		execution_line.c\
		execution_multi_pipe.c\
		execution_util.c\
		execution_util2.c\
		lexicalize_token.c\
		lexicalize_util.c\
		lexicalize_util2.c\
		main.c\
		parse_line_util.c\
		parser.c\
		redirection.c\
		signal.c\
		tokenizer_divide.c\
		tokenizer_envp_convert.c\
		tokenizer_envp_convert_util.c\
		tokenizer_parser.c\
		tokenizer_trim.c\
		tokenizer_util.c
OBJS = $(SRCS:.c=.o)

#gcc *.c -lreadline -lft -L./libft -L$HOME/.brew/opt/readline/lib -I$HOME/.brew/opt/readline/include


all: $(NAME)


$(NAME) : ${LIBFT} ${OBJS}  
	$(CC)  ${SRCS} ${LIBFT}  -lreadline ${LDFLAGS} ${CPPFLAGS} -o ${NAME}

${LIBFT}:	
			$(MAKE) -C /libft 

clean :
		$(MAKE) -C ./libft clean
		$(RM) $(OBJS)

fclean : clean
		rm -rf $(OBJS) ${NAME}

re : fclean $(NAME)

.PHONY : all clean fclean re
