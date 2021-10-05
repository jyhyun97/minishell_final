NAME = minishell
CC = gcc
LDFLAGS = "-L/opt/homebrew/opt/readline/lib"
CPPFLAGS= "-I/opt/homebrew/opt/readline/include"
SRCS = tokenizer_envp_convert.c\
		tokenizer_envp_list.c\
		tokenizer_parser.c\
		tokenizer_trim.c\
		tokenizer_divide.c\
		lexicalize_token.c\
		main.c\
		signal.c

#gcc *.c -lreadline -lft -L./libft -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include
OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	$(CC) -g -lreadline -lft -L./libft -o $(NAME) $(OBJS) 

all: $(NAME)

clean :
		rm -rf $(OBJS)

fclean : clean
		rm -rf $(OBJS)

re : fclean $(NAME)

PHONY : all clean fclean re
