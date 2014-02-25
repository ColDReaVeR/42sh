#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hestela <hestela@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/01/28 10:07:14 by hestela           #+#    #+#              #
#    Updated: 2014/02/25 16:06:57 by msommagg         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	bin/42sh
SOURCES		=	src/main.c \
				src/edit_line.c \
				src/read.c \
				src/key.c \
				src/cpy_cut_pst.c \
				src/move.c \
				src/move2.c \
				src/move_up.c \
				src/move_down.c \
				src/history.c \
				src/env.c \
				src/env_i.c \
				src/cd.c \
				src/setenv.c \
				src/unsetenv.c \
				src/init.c \
				src/exit.c \
				src/execute.c \
				src/signal.c \
				src/suspended_pid_list.c \
				src/jobs.c \
				src/parse.c \
				src/parse_tool.c \
				src/right.c \
				src/right_d.c \
				src/left.c \
				src/left_d.c \
				src/read_for_left_d.c \
				src/pipe.c \
				src/check_quote.c \
				src/quote_list.c \
				src/ft_isempty.c \
				src/check_env.c \
				src/env_changes.c \
				src/check_permissions.c \
				src/replacements.c \
				src/replace_tilde.c \
				src/replace_variable.c \
				src/replace_alias.c \
				src/replace_star.c \
				src/replace_star_suite.c \
				src/split_args.c \
				src/echo.c \
				src/autocomp.c \
				src/autocomp_file.c \
				src/autocomp_cmd.c \
				src/autocomp_tool_1.c \
				src/autocomp_tool_2.c \
				src/autocomp_list.c \
				src/replace_script.c \
				src/check_position.c \
				src/export.c \
				src/exec_and_or.c \
				src/print_history.c \
				src/alias.c

HEADERS		=	inc/
OBJECTS		=	$(subst src,obj,$(subst .c,.o,$(SOURCES)))
LIBSDIR		=	-L./lib
LIBRARY		=	-lft
LIBNAME		=	lib/libft.a
WFLAGS		=	-g3 -Werror -Wall -Wextra

export			WFLAGS

.SILENT		:

all			:	$(NAME)

$(NAME)		:	$(LIBNAME) $(OBJECTS)
	printf "\e[32m----------------------------------\e[36m\n"
	gcc $(WFLAGS) $(OBJECTS) $(LIBSDIR) $(LIBRARY) -L/usr/lib -ltermcap -o $(NAME)
	printf "\e[32m[✔]\e[36m $@"
	printf "\n\e[32m----------------------------------\e[36m\n"

$(LIBNAME)	:	./libft
	make -C ./libft
	mv ./libft/libft.a ./lib
	cp ./libft/libft.h ./inc

obj/%.o		:	src/%.c
	printf "\e[32m[✔]\e[36m $@ \n"
	gcc $(WFLAGS) -I $(HEADERS) -c -o $@ $^

clean		:
	rm -rf $(OBJECTS)
	make -C ./libft clean
	printf "\e[31m----------------------------------\n"
	printf "[✔]\e[36m $(NAME): Objects deleted\n"
	printf "\e[31m----------------------------------\e[36m\n"

fclean		:	clean
	rm -rf $(NAME)
	rm -rf $(LIBNAME)
	rm -rf ./inc/libft.h
	printf "\e[31m----------------------------------\n"
	printf "[✔]\e[36m $(NAME): Objects deleted\n"
	printf "\e[31m----------------------------------\e[36m\n"

re			:	fclean all

.PHONY		:	re fclean clean all
