#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/30 18:43:03 by ahrytsen          #+#    #+#              #
#    Updated: 2018/01/14 22:31:30 by ahrytsen         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	ft_ls
DIRSRC		=	./src/
DIROBJ		=	./obj/
INCLUDE		=	-I./includes/ -I./libftprintf/
SUB_MAKE	=	./libftprintf/
INC_LIB		=	-L./libftprintf -lftprintf
SRC			=	ft_ls.c ft_ls_buf.c ft_ls_sort.c ft_ls_helpers.c ft_ls_xattr.c \
				ft_ls_sort_helper.c
HDR			=	includes/ft_ls.h

OBJ			=	$(addprefix $(DIROBJ), $(SRC:.c=.o))

ifdef FLAGS
	ifeq ($(FLAGS), no)
CFLAGS		=
	endif
	ifeq ($(FLAGS), debug)
CFLAGS		=	-Wall -Wextra -Werror -ansi -pedantic -g
	endif
else
CFLAGS		=	-Wall -Wextra -Werror
endif

CC			=	gcc
RM			=	rm -f
ECHO		=	echo


$(NAME)	:		$(OBJ)
ifdef SUB_MAKE
				@$(MAKE) -C $(SUB_MAKE) -j3
endif
				@$(CC) $(INCLUDE) $(INC_LIB) $(CFLAGS) -Ofast -o $(NAME) $(OBJ)
				@$(ECHO) "\033[31m> \033[32mft_ls: Compiled\033[0m"

clean	:
				@$(RM) $(OBJ)
ifdef SUB_MAKE
				@$(MAKE) -C $(SUB_MAKE) clean
endif
				@$(ECHO) "\033[31m> \033[33mft_ls: Directory cleaned\033[0m"

all		:		$(NAME)

fclean	:		clean
ifdef SUB_MAKE
				@$(MAKE) -C $(SUB_MAKE) fclean
endif
				-@$(RM) $(NAME)
				@$(ECHO) "\033[31m> \033[33mft_ls: Remove executable\033[0m"

re		:		fclean all

.PHONY	:		all clean re

$(OBJ)	:		$(DIROBJ)%.o : $(DIRSRC)%.c $(HDR)
				@$(CC) $(INCLUDE) $(CFLAGS) -Ofast -o $@ -c $<
