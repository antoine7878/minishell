# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/05 21:31:05 by ale-tell          #+#    #+#              #
#    Updated: 2025/01/10 11:11:33 by ale-tell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc

CDIR = ./src
ODIR = ./obj

ODIRS = obj/ast \
		obj/builtin \
		obj/env \
		obj/parse \
		obj/run \
		obj/dev

HDIR = include
TEST = 0

SRC =		$(CDIR)/minishell.c \
			$(CDIR)/utils.c \
			$(CDIR)/error.c \
			$(CDIR)/signal.c \

SRC +=		$(CDIR)/ast/get_token.c \
			$(CDIR)/ast/block.c \
			$(CDIR)/ast/exec.c \
			$(CDIR)/ast/line.c \
			$(CDIR)/ast/logic.c \
			$(CDIR)/ast/pipe.c \
			$(CDIR)/ast/redir.c \
			$(CDIR)/ast/free_ast.c \
			$(CDIR)/ast/here_doc.c \
			$(CDIR)/ast/ft_split_strm.c \
			$(CDIR)/ast/is_token.c \

SRC +=		$(CDIR)/builtin/cd.c \
			$(CDIR)/builtin/echo.c \
			$(CDIR)/builtin/env.c \
			$(CDIR)/builtin/exit.c \
			$(CDIR)/builtin/export.c \
			$(CDIR)/builtin/unset.c \
			$(CDIR)/builtin/pwd.c \

SRC +=		$(CDIR)/env/clearenv.c \
			$(CDIR)/env/ft_getenv.c \
			$(CDIR)/env/parsenv.c \
			$(CDIR)/env/printenv.c \
			$(CDIR)/env/set_env.c \
			$(CDIR)/env/path.c \
		
SRC +=		$(CDIR)/parse/mask.c \
			$(CDIR)/parse/expand_env.c \
			$(CDIR)/parse/parse_wild_utils.c \
			$(CDIR)/parse/parse_wild.c \
			$(CDIR)/parse/parser.c \
			$(CDIR)/parse/strm.c \
			$(CDIR)/parse/quotes.c \

SRC +=		$(CDIR)/run/run_ast_node.c \
			$(CDIR)/run/run_ast_node_exec.c \
			$(CDIR)/run/run_ast.c \
			$(CDIR)/run/run_utils.c \

SRC +=		$(CDIR)/dev/print_ast.c \
			$(CDIR)/dev/print_strm.c
			
LIBFT = libft/libft.a

### Compile ###
OBJ = $(patsubst $(CDIR)/%.c, $(ODIR)/%.o, $(SRC))
OBJ_BONUS = $(patsubst $(CDIR)/%.c, $(ODIR)/%.o, $(SRC_BONUS))
CFLAGS = -g3 -I$(HDIR) -Ilibft/include


all: $(NAME)

$(ODIR)/%.o: $(CDIR)/%.c | $(ODIR)
	$(CC) -D TEST=$(TEST) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $^ $(CFLAGS) -o $@ -lreadline

### libft ###
$(LIBFT):
	make -C libft all

test:
	$(MAKE) re TEST=1
	@$(MAKE) clean

stest: $(NAME)
	cd ./testScript/script && ./script.sh

vtest: $(NAME)
	# valgrind ./$(NAME)
	valgrind --trace-children=yes --leak-check=full --show-leak-kinds=all --suppressions=./valgrind_supp ./$(NAME) $(ARGS)
	# valgrind --trace-children=yes --leak-check=full --show-leak-kinds=all  ./$(NAME) $(ARGS)
	# valgrind --trace-children=yes --leak-check=full ./$(NAME) $(ARGS)
	# valgrind --trace-children=yes ./$(NAME) $(ARGS)

fd: $(NAME)
	valgrind --track-fds=yes --trace-children=yes ./$(NAME) $(ARGS)

### Setup ###
$(ODIR):
	mkdir -p $@
	mkdir -p $(ODIRS)

init: 
	mkdir -p $(HDIR) $(CDIR) $(ODIR)

add_libft:
	rm -rf ./libft
	cp -r ~/42/libft/ ./

### Clean ###
clean:
	@rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

ffclean: fclean clean
	make -C libft fclean

re: fclean all

rre: ffclean all

.PHONY: clean fclean ffclean all re rre test bonus
