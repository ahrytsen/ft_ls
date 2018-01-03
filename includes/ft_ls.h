/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 19:10:30 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/01/03 15:43:16 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <dirent.h>
# include <stdio.h>
# include <sys/errno.h>

# define FT_LFRMT 0x1
# define FT_RECURS 0x2
# define FT_ALL 0x4
# define FT_REV 0x8
# define FT_TIME_M 0x10

#endif
