# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/08 14:06:40 by ahrytsen          #+#    #+#              #
#    Updated: 2018/01/11 20:13:05 by ahrytsen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/sh

make

ls $@ | cat -e > diff_ls
./ft_ls $@ | cat -e > diff_my
vim -d diff_ls diff_my
rm diff_ls diff_my
