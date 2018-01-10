/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 18:13:22 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/01/10 21:30:54 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static t_file	*ft_ls_mtime_sort(t_file *root)
{
	t_file	*n_r;
	t_file	*node;
	t_file	*cur;

	n_r = NULL;
	while (root != NULL)
	{
		node = root;
		root = root->next;
		if (!n_r || node->time < n_r->time)
		{
			node->next = n_r;
			n_r = node;
		}
		else
		{
			cur = n_r;
			while (cur->next && node->time >= cur->next->time)
				cur = cur->next;
			node->next = cur->next;
			cur->next = node;
		}
	}
	return (n_r);
}

static t_file	*ft_ls_path_sort(t_file *root)
{
	t_file	*n_r;
	t_file	*node;
	t_file	*cur;

	n_r = NULL;
	while (root != NULL)
	{
		node = root;
		root = root->next;
		if (!n_r || ft_strcmp(node->path, n_r->path) > 0)
		{
			node->next = n_r;
			n_r = node;
		}
		else
		{
			cur = n_r;
			while (cur->next
				&& ft_strcmp(node->path, cur->next->path) <= 0)
				cur = cur->next;
			node->next = cur->next;
			cur->next = node;
		}
	}
	return (n_r);
}

static void		ft_grep_frmt(t_file *root, uint64_t *flags)
{
	uint16_t		tmp;

	while (root)
	{
		if ((*flags & FT_TASORT) || (*flags & FT_TCSORT))
			root->time = (*flags & FT_TASORT)
				? root->st.st_atimespec.tv_sec : root->st.st_ctimespec.tv_sec;
		else
			root->time = root->st.st_mtimespec.tv_sec;
		tmp = ft_strlen(root->name ? root->name : root->path);
		tmp > root->m_w->name_w ? root->m_w->name_w = tmp : 0;
		ft_get_mod(root->st.st_mode, root->mod);
		if (*flags & FT_LFRMT)
		{
			ft_grep_helper(root);
			acl_get_file(root->path, ACL_TYPE_EXTENDED) != 0
			  ? root->mod[10] = '+' : 0;
			if (listxattr(root->path, NULL, 0, XATTR_NOFOLLOW) > 0)
				root->mod[10] = '@';
			else
				errno = 0;
		}
		root = root->next;
	}
}

t_file			*ft_ls_sort(t_file *root, uint64_t *flags)
{
	ft_grep_frmt(root, flags);
	if (!(*flags & FT_USORT))
	{
		root = ft_ls_path_sort(root);
		(*flags & FT_TSORT) ? root = ft_ls_mtime_sort(root) : 0;
	}
	return (root);
}
