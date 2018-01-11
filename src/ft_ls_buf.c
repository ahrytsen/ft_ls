/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 14:04:50 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/01/11 22:24:50 by ahrytsen         ###   ########.fr       */
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

void	ft_print_columns(t_file *node, uint64_t *flags)
{
	uint16_t	i;

	while (node && !node->w_prnt)
	{
		(*flags & FT_COLOR) ? ft_color_out(node->mod[0], 0) : 0;
		ft_printf("%-*s", node->m_w->name_w + 1,
				node->name ? node->name : node->path);
		(*flags & FT_COLOR) ? ft_color_out(node->mod[0], 1) : 0;
		node->w_prnt = 1;
		i = 0;
		while (node && i < node->m_w->rows)
		{
			node = (*flags & FT_REV) ? node->next : node->prev;
			i++;
		}
	}
	ft_printf("\n");
}

void	ft_print_node(t_file *node, uint64_t *flags)
{
	char	*l_path;

	l_path = (node->mod[0] == 'l') ? ft_memalloc(sizeof(char) * 3072) : NULL;
	if (*flags & FT_LFRMT)
	{
		ft_printf("%s %*s ", node->mod, node->m_w->links_w, node->links);
		if (!(*flags & FT_SUPROWNER))
			ft_printf("%-*s  ", node->m_w->owner_w, node->owner);
		ft_printf("%-*s  ", node->m_w->group_w, node->group);
		if (node->mod[0] == 'c' || node->mod[0] == 'b')
			ft_printf(minor(node->st.st_rdev) > 255 ? "%3d, %#.8x" : "%3d, %3d",
					major(node->st.st_rdev), minor(node->st.st_rdev));
		else
			ft_printf("%*s", node->m_w->size_w, node->size);
		ft_printf(" %s ", node->date);
	}
	(*flags & FT_COLOR) ? ft_color_out(node->mod[0], 0) : 0;
	ft_printf("%s", node->name ? node->name : node->path);
	(*flags & FT_COLOR) ? ft_color_out(node->mod[0], 1) : 0;
	((*flags & FT_LFRMT) && l_path && readlink(node->path, l_path, 1023) > 0)
		? ft_printf(" -> %s\n", l_path) : ft_printf("\n");
	if (*flags & FT_LFRMT && ((*flags & FT_XATTR && node->mod[10] == '@')
							|| (*flags & FT_ACL && node->mod[10] == '+')))
		(node->mod[10] == '@') ? ft_print_xattr(node) : ft_print_acl(node);
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
	acl_free(node->acl);
	free(node);
}
