# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: aholster <aholster@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/02/16 15:46:43 by aholster       #+#    #+#                 #
#    Updated: 2019/10/13 09:03:29 by aholster      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

DATE := $(shell date)

PARDIR := ./flag_parser/
PARSRC := ft_flag_parser flg_cap_r flg_low_a flg_low_l flg_low_r flg_low_t\
 flg_low_d

FINFODIR := ./finfo_handlers/
FINFOSRC := finfo_lstadd finfo_lstdel finfo_lstdelone finfo_lstiter\
 finfo_lstnew

SOURCE := main sort_params run_stacks

FILEC := $(SOURCE:%=./ft_%.c) $(PARSRC:%=$(PARDIR)%.c) $(FINFOSRC:%=$(FINFODIR)%.c)

OBJ := $(FILEC:%.c=%.o)

HEAD := ft_ls.h $(PARDIR)/ft_flag_parser.h ./incl/ft_flag.h

NAME := ft_ls

NORM := norminette $(FILEC) $(HEAD) | grep -e "Error"  -e "Warning" -B 1

GCCC = ${CC} -c
CC = gcc -g -Wall -Werror -Wextra
AR = ar rcs

all: $(NAME)

assemble: $(OBJ)
	@$(CC) -o $(NAME) $(FILEC) -L ./ft_printf/ -lftprintf -L ./libft/ -lft

$(NAME):
	@make -C ./ft_printf -j
	@make -C ./libft -j
	@echo "\033[0;33mStarting assembly of $(NAME)…\033[0;00m"
	@time make assemble
	@echo "\033[0;32m$(NAME) successfully assembled!\033[0;00m\n"

%.o: %.c
	@$(GCCC) -o $@ $<

clean:
	@make clean -C ./ft_printf
	@make clean -C ./libft
	@echo "\033[0;33mInitializing Summary Deletions...\033[0;00m"
	@rm -rf $(OBJ)
	@find "./" -type f \( -name '*~' -o -name '\#*\#' -o -name '.DS_Store' \)\
	 -exec rm -rfv {} \;
	@echo "\033[0;31m	Executed!\033[0;00m\n"

fclean: clean
	@make fclean -C ./ft_printf
	@make fclean -C ./libft
	@rm -rf $(NAME)
	@echo "\033[0;31mObituary of $(NAME): Deceased on $(shell date).\
	\033[0;00m\n"

re: fclean all

norm:
	@echo "**+++=====*=====*=====*=====*{\033[0;31mOUT\033[0;00m}\
	*=====*=====*=====*=====+++**\033[0;33m"
	@$(NORM) || TRUE 
	@echo "\033[0;00m**+++=====*=====*=====*=====*\
=====*=====*===*=====*=====+++**"

add:
	@git add $(FILEC) $(HEAD) Makefile author
	git status

push: norm
ifdef MSG
	@git commit -m "$(MSG)"
	git push
else
	@git commit
	git push
endif