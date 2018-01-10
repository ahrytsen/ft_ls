/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 14:04:50 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/01/10 16:49:44 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*ft_newnod(char *path, struct stat *st)
{
	t_file	*newnod;

	if (!(newnod = (t_file*)ft_memalloc(sizeof(t_file))))
		return (NULL);
	newnod->path = path;
	st ? ft_memcpy(&(newnod->st), st, sizeof(struct stat)) : 0;
	return (newnod);
}

void	ft_bufadd(t_file **files, t_file *new)
{
	if (new && files)
	{
		new->next = *files;
		new->m_w = *files ? (*files)->m_w : ft_memalloc(sizeof(t_wf));
		new->m_w->count++;
		*files = new;
	}
}

void	ft_print_node(t_file *node, uint64_t *flags)
{
	char	*l_path;

	l_path = (node->mod[0] == 'l') ? ft_memalloc(sizeof(char) * 3072) : NULL;
	if (*flags & FT_LFRMT)
	{
		(*flags & FT_SUPROWNER)
			? ft_printf("%s %*s  %-*s  %*s %s ", node->mod, node->m_w->links_w,
						node->links, node->m_w->group_w, node->group,
						node->m_w->size_w, node->size, node->date)
			: ft_printf("%s %*s %-*s  %-*s  %*s %s ", node->mod,
						node->m_w->links_w, node->links, node->m_w->owner_w,
						node->owner, node->m_w->group_w, node->group,
						node->m_w->size_w, node->size, node->date);
		ft_printf("%s", node->name ? node->name : node->path);
		(l_path && readlink(node->path, l_path, 1023) > 0)
			? ft_printf(" -> %s\n", l_path) : ft_printf("\n");
	}
	else
		ft_printf("%s\n", node->name ? node->name : node->path);
	free(l_path);
}

void	ft_del_node(t_file *node)
{
	free(node->name);
	free(node->path);
	free(node->links);
	free(node->owner);
	free(node->group);
	free(node->size);
	(!node->next) ? free(node->m_w) : 0;
	free(node);
}
