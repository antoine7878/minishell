# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ale-tell <ale-tell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 20:57:01 by ale-tell          #+#    #+#              #
#    Updated: 2024/12/18 11:01:16 by ale-tell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CDIR = ./src
HDIR = include
CFLAGS = -g3 -Wall -Wextra -Werror -I$(HDIR)

SRC =	$(CDIR)/ft_atoi.c \
		$(CDIR)/ft_bzero.c \
		$(CDIR)/ft_isalnum.c \
		$(CDIR)/ft_isalpha.c \
		$(CDIR)/ft_isascii.c \
		$(CDIR)/ft_isdigit.c \
		$(CDIR)/ft_isspace.c \
		$(CDIR)/ft_isprint.c \
		$(CDIR)/ft_itoa.c \
		$(CDIR)/ft_memchr.c \
		$(CDIR)/ft_memcmp.c \
		$(CDIR)/ft_memcpy.c \
		$(CDIR)/ft_memmove.c \
		$(CDIR)/ft_memset.c \
		$(CDIR)/ft_putchar_fd.c \
		$(CDIR)/ft_putendl_fd.c \
		$(CDIR)/ft_putnbr_fd.c \
		$(CDIR)/ft_putstr_fd.c \
		$(CDIR)/ft_split.c \
		$(CDIR)/ft_print_split.c \
		$(CDIR)/ft_join_split.c \
		$(CDIR)/ft_len_split.c \
		$(CDIR)/ft_replace.c \
		$(CDIR)/ft_strchr.c \
		$(CDIR)/ft_strdup.c \
		$(CDIR)/ft_striteri.c \
		$(CDIR)/ft_strjoin.c \
		$(CDIR)/ft_freejoin.c \
		$(CDIR)/ft_strlcat.c \
		$(CDIR)/ft_strlcpy.c \
		$(CDIR)/ft_strlen.c \
		$(CDIR)/ft_strmapi.c \
		$(CDIR)/ft_strncmp.c \
		$(CDIR)/ft_stricmp.c \
		$(CDIR)/ft_strcmp.c \
		$(CDIR)/ft_wildcmp.c \
		$(CDIR)/ft_strnstr.c \
		$(CDIR)/ft_strstr.c \
		$(CDIR)/ft_strrchr.c \
		$(CDIR)/ft_strtrim.c \
		$(CDIR)/ft_substr.c \
		$(CDIR)/ft_tolower.c \
		$(CDIR)/ft_toupper.c \
		$(CDIR)/ft_lstnew.c \
		$(CDIR)/ft_lstadd_front.c \
		$(CDIR)/ft_lstsize.c \
		$(CDIR)/ft_get_word.c \
		$(CDIR)/ft_lstlast.c \
		$(CDIR)/ft_lstadd_back.c \
		$(CDIR)/ft_lstdelone.c \
		$(CDIR)/ft_lstclear.c \
		$(CDIR)/ft_lstiter.c \
		$(CDIR)/ft_lstmap.c \
		$(CDIR)/get_next_line.c \
		$(CDIR)/ft_tabtlst.c \
		$(CDIR)/ft_printlst.c \
		$(CDIR)/ft_splitlst.c \
		$(CDIR)/ft_joinlst.c \
		$(CDIR)/ft_lstremove_if.c \
		$(CDIR)/ft_close.c \
		$(CDIR)/ft_strcat.c \
		$(CDIR)/ft_arglen.c \
		$(CDIR)/ft_strinsert.c \
		$(CDIR)/ft_strjointab.c \
		$(CDIR)/ft_sort_strs.c \

SRC +=	$(CDIR)/ft_math/ft_max.c \
		$(CDIR)/ft_math/ft_min.c \
		$(CDIR)/ft_math/ft_abs.c \
		$(CDIR)/ft_find.c \
		$(CDIR)/ft_striter.c \
		$(CDIR)/ft_any.c \
		$(CDIR)/ft_sort.c \
		$(CDIR)/ft_swap.c \

SRC +=	$(CDIR)/ft_printf/conv_utils.c \
		$(CDIR)/ft_printf/ft_printf.c \
		$(CDIR)/ft_printf/ft_put.c \
		$(CDIR)/ft_printf/nbrlen.c \
		$(CDIR)/ft_printf/parse_arg.c \
		$(CDIR)/ft_printf/print_convs.c \

SRC +=	$(CDIR)/collector/collector.c \
		$(CDIR)/collector/galloc.c \
		$(CDIR)/collector/gcalloc.c \
		$(CDIR)/collector/gfree.c \
		$(CDIR)/collector/gfree_all.c

ODIR = obj

ODIRS = $(ODIR)/ft_printf \
		$(ODIR)/get_next_line \
		$(ODIR)/ft_math \
		$(ODIR)/collector

OBJ = $(patsubst $(CDIR)/%.c, $(ODIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $^

$(ODIR)/%.o: $(CDIR)/%.c | $(ODIR) $(ODIRS)
	$(CC) $(CFLAGS) -c $< -o $@

$(ODIRS):
	mkdir -p $@ $(ODIRS)

$(ODIR):
	mkdir -p $@ $(ODIR)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
