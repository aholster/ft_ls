# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: aholster <aholster@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/02/16 15:46:43 by aholster       #+#    #+#                 #
#    Updated: 2019/11/11 21:52:08 by aholster      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

DATE := $(shell date)

LONDIR := ./file_format/
LONSRC := longformat_file generate_time\
 generate_permissions init_permissions_table\
 generate_gid_uid\
 find_longest_fields

PRODIR := ./stack_processors/
PROSRC := process_ndir_stack process_dir_stack process_files_to_txt

SORTDIR := ./stack_sorters/
SORTSRC := sortnprocess_err_queue sort_finfo_stack\
 sorter_method sorter_method_rev

PARDIR := ./flag_parser/
PARSRC := ft_flag_parser

FINFODIR := ./finfo_handlers/
FINFOSRC := finfo_lstadd finfo_lstdel finfo_lstdelone finfo_lstiter\
 finfo_lstnew finfo_stack_pop

SOURCE := main sort_params run_stacks\
 fstack_del error_cleanup

FILEC := $(SOURCE:%=./ft_%.c) $(PARSRC:%=$(PARDIR)%.c)\
 $(SORTSRC:%=$(SORTDIR)ft_%.c) $(FINFOSRC:%=$(FINFODIR)%.c)\
 $(PROSRC:%=$(PRODIR)ft_%.c) $(LONSRC:%=$(LONDIR)ft_%.c)

OBJ := $(FILEC:%.c=%.o)

HEAD := ft_ls.h ./incl/ft_flag.h ./incl/finfo.h\
 ./incl/ft_stack_sorters.h ./incl/ft_stack_processors.h\
 ./incl/ft_file_format.h

NAME := ft_ls

NORM := norminette $(FILEC) $(HEAD) | grep -e "Error"  -e "Warning" -B 1

GCCC = ${CC} -c
CC = gcc -g -Wall -Werror -Wextra
AR = ar rcs

all: $(NAME)

assemble: $(OBJ) $(HEAD)
	@$(CC) -o $(NAME) $(FILEC) -L ./ft_printf/ -lftprintf -L ./libft/ -lft

$(NAME): $(OBJ) $(HEAD)
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
#	@find "./" -type f \( -name '*~' -o -name '\#*\#' -o -name '.DS_Store' \)\
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