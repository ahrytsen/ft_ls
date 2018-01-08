/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 18:13:22 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/01/08 20:58:10 by ahrytsen         ###   ########.fr       */
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
		if (!n_r || node->st.st_mtimespec.tv_sec < n_r->st.st_mtimespec.tv_sec)
		{
			node->next = n_r;
			n_r = node;
		}
		else
		{
			cur = n_r;
			while (cur->next && node->st.st_mtimespec.tv_sec
				>= cur->next->st.st_mtimespec.tv_sec)
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
	struct paswd	*pwd;
	struct groop	*gr;
	size_t			tmp;

	while (root)
	{
		pwd = getpwuid(root->st.st_uid);
		gr = getgrgid(root->st.st_gid);
		root->owner = pwd ? ft_strdup(pwd->pw_name) : ft_ltoa(root->st.st_uid);
		root->group = gr ? ft_strdup(gr->gr_name) : ft_ltoa(root->st.st_gid);
		root->links = ft_ultoa(root->st.st_nlink, 10, 0);
		root->size = ft_ultoa_base(root->st.st_size, 10, 0);

		root = root->next;
	}
}

t_file			*ft_ls_sort(t_file *root, uint64_t *flags)
{
	if (!(*flags & FT_USORT))
	{
		root = ft_ls_path_sort(root);
		(*flags & FT_TMSORT) ? root = ft_ls_mtime_sort(root) : 0;
	}
	ft_grep_frmt(root, flags);
	return (root);
}
