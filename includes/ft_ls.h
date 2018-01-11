/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 19:10:30 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/01/11 21:38:44 by ahrytsen         ###   ########.fr       */
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
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <sys/ioctl.h>

# define FT_LFRMT 0x1
# define FT_RECURS 0x2
# define FT_ALL 0x4
# define FT_REV 0x8
# define FT_TSORT 0x10
# define FT_SHOW_PATH 0x20
# define FT_IS_FIRST 0x40
# define FT_USORT 0x80
# define FT_TASORT 0x100
# define FT_TCSORT 0x200
# define FT_COLUMNS 0x400
# define FT_COLOR 0x800
# define FT_SUPROWNER 0x1000
# define FT_DIRASREG 0x2000
# define FT_XATTR 0x4000
# define FT_ACL 0x8000
# define FT_SSORT 0x10000
# define FT_TCHSORT 0x20000

typedef struct	s_wf
{
	size_t		total;
	size_t		count;
	uint16_t	links_w;
	uint16_t	owner_w;
	uint16_t	group_w;
	uint16_t	size_w;
	uint16_t	name_w;
	uint16_t	termw;
	uint16_t	columns;
	uint16_t	rows;
}				t_wf;

typedef struct	s_file
{
	uint16_t		w_prnt;
	time_t			time;
	char			*name;
	t_wf			*m_w;
	char			*path;
	struct stat		st;
	struct s_file	*next;
	struct s_file	*prev;
	char			mod[12];
	char			*links;
	char			*owner;
	char			*group;
	char			*size;
	char			date[14];
	acl_t			acl;
}				t_file;

void			ft_ls(char *path, uint64_t *flags);
t_file			*ft_newnod(char *path, struct stat *st);
void			ft_bufadd(t_file **files, t_file *new);
t_file			*ft_ls_sort(t_file *root, uint64_t *flags);
void			ft_get_mod(mode_t m, char *mod);
void			ft_grep_helper(t_file *node);
void			ft_print_node(t_file *node, uint64_t *flags);
void			ft_print_columns(t_file *node, uint64_t *flags);
void			ft_del_node(t_file *node);
void			ft_print_xattr(t_file *node);
void			ft_print_acl(t_file *node);
t_file			*ft_ls_size_sort(t_file *root);
void			ft_color_out(char dev_t, int mod);

#endif
