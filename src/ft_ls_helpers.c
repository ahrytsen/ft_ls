/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 20:58:35 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/01/09 20:41:51 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_get_mod(mode_t m, char *mod)
{
	*mod = S_ISBLK(m) ? 'b' : '-';
	S_ISCHR(m) ? *mod = 'c' : 0;
	S_ISDIR(m) ? *mod = 'd' : 0;
	S_ISFIFO(m) ? *mod = 'p' : 0;
	S_ISLNK(m) ? *mod = 'l' : 0;
	S_ISSOCK(m) ? *mod = 's' : 0;
	*(++mod) = (m & S_IRUSR) ? 'r' : '-';
	*(++mod) = (m & S_IWUSR) ? 'w' : '-';
	*(++mod) = (m & S_IXUSR) ? 'x' : '-';
	*(++mod) = (m & S_IRGRP) ? 'r' : '-';
	*(++mod) = (m & S_IWGRP) ? 'w' : '-';
	*(++mod) = (m & S_IXGRP) ? 'x' : '-';
	*(++mod) = (m & S_IROTH) ? 'r' : '-';
	*(++mod) = (m & S_IWOTH) ? 'w' : '-';
	*(++mod) = (m & S_IXOTH) ? 'x' : '-';
	*(++mod) = ' ';
}

static void	ft_file_time(t_file *node)
{
	char	*f_time;
	time_t	cur_t;
	time_t	diff;

	f_time = ctime(&node->time);
	ft_memcpy(node->date, f_time + 4, 12);
	time(&cur_t);
	diff = 0;
	if (cur_t > node->time)
		diff = cur_t - node->time;
	else if (cur_t < node->time)
		diff = node->time - cur_t;
	diff > 15778463 ? ft_memcpy(node->date + 7, ft_strrchr(f_time, ' '), 6) : 0;
	node->date[12] == '\n' ? node->date[12] = 0 : 0;
	node->m_w->total += node->st.st_blocks;
}

void		ft_grep_helper(t_file *node)
{
	struct passwd	*pwd;
	struct group	*gr;
	uint16_t		tmp;

	node->links = ft_ultoa_base(node->st.st_nlink, 10, 0);
	pwd = getpwuid(node->st.st_uid);
	gr = getgrgid(node->st.st_gid);
	node->owner = pwd ? ft_strdup(pwd->pw_name) : ft_ltoa(node->st.st_uid);
	node->group = gr ? ft_strdup(gr->gr_name) : ft_ltoa(node->st.st_gid);
	node->size = ft_ultoa_base(node->st.st_size, 10, 0);
	(tmp = ft_strlen(node->links)) > node->m_w->links_w
		? node->m_w->links_w = tmp : 0;
	(tmp = ft_strlen(node->owner)) > node->m_w->owner_w
		? node->m_w->owner_w = tmp : 0;
	(tmp = ft_strlen(node->group)) > node->m_w->group_w
		? node->m_w->group_w = tmp : 0;
	(tmp = ft_strlen(node->size)) > node->m_w->size_w
		? node->m_w->size_w = tmp : 0;
	ft_file_time(node);
}
