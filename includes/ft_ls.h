/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 19:10:30 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/01/08 21:21:09 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <time.h>
# include <dirent.h>
# include <stdio.h>
# include <sys/errno.h>
# include <sys/stat.h>

# define FT_LFRMT 0x1
# define FT_RECURS 0x2
# define FT_ALL 0x4
# define FT_REV 0x8
# define FT_TMSORT 0x10
# define FT_SHOW_PATH 0x20
# define FT_IS_FIRST 0x40
# define FT_USORT 0x80

typedef struct	s_wf
{
	size_t		total;
	size_t		count;
	uint16_t	links_w;
	uint16_t	owner_w;
	uint16_t	group_w;
	uint16_t	size_w;
	uint16_t	name_w;
	uint8_t		columns;
}				t_wf;

typedef struct	s_file
{
	uint16_t		w_prnt;
	char			*name;
	t_wf			*m_w;
	char			*path;
	struct stat		st;
	struct s_file	*next;
	char			mod[11];
	char			*links;
	char			*owner;
	char			*group;
	char			*size;
}				t_file;

void			ft_ls(char *path, uint64_t *flags);
t_file			*ft_newnod(char *path, struct stat *st);
void			ft_bufadd(t_file **files, t_file *new);
t_file			*ft_ls_sort(t_file *root, uint64_t *flags);
void			ft_get_mod(t_mode m, char *mod);

#endif
