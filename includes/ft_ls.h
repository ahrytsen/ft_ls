/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 19:10:30 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/01/06 20:12:14 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <dirent.h>
# include <stdio.h>
# include <sys/errno.h>
# include <sys/stat.h>

# define FT_LFRMT 0x1
# define FT_RECURS 0x2
# define FT_ALL 0x4
# define FT_REV 0x8
# define FT_TIME_M 0x10
# define FT_SHOW_PATH 0x20
# define FT_IS_FIRST 0x40

typedef struct	s_file
{
	char			*name;
	char			*path;
	struct stat		st;
	struct s_file	*next;
}				t_file;

void			ft_ls(char *path, uint64_t *flags);
t_file			*ft_newnod(char *path, struct stat *st);
void			ft_bufadd(t_file **files, t_file *new);

#endif
