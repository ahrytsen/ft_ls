/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 18:13:22 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/01/12 03:26:34 by ahrytsen         ###   ########.fr       */
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
			root->time = (*flags & FT_TASORT) ? root->st.st_atimespec.tv_sec
				: root->st.st_birthtimespec.tv_sec;
		else
			root->time = (*flags & FT_TCHSORT) ? root->st.st_ctimespec.tv_sec
				: root->st.st_mtimespec.tv_sec;
		tmp = ft_strlen(root->name ? root->name : root->path);
		tmp > root->m_w->name_w ? root->m_w->name_w = tmp : 0;
		ft_get_mod(root->st.st_mode, root->mod);
		if (*flags & FT_LFRMT)
		{
			ft_grep_helper(root);
			(root->acl = acl_get_file(root->path, ACL_TYPE_EXTENDED))
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
	t_file			*tmp;
	struct winsize	w;

	ft_grep_frmt(root, flags);
	if (!(*flags & FT_USORT))
	{
		root = ft_ls_path_sort(root);
		if ((*flags & FT_TSORT) || (*flags & FT_SSORT))
			root = (*flags & FT_SSORT) ? ft_ls_size_sort(root)
				: ft_ls_mtime_sort(root);
	}
	tmp = root;
	while (tmp && tmp->next)
	{
		tmp->next->prev = tmp;
		tmp = tmp->next;
	}
	if (root && (*flags & FT_COLUMNS))
	{
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		root->m_w->columns = (uint16_t)w.ws_col / (root->m_w->name_w + 1);
		root->m_w->rows = root->m_w->columns
			? root->m_w->count / root->m_w->columns
			+ ((root->m_w->count % root->m_w->columns > 0) ? 1 : 0)
			: root->m_w->count;
	}
	return (root);
}
