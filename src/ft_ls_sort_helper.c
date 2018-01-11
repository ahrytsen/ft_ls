/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_sort_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 15:55:37 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/01/11 16:00:30 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*ft_ls_size_sort(t_file *root)
{
	t_file	*n_r;
	t_file	*node;
	t_file	*cur;

	n_r = NULL;
	while (root != NULL)
	{
		node = root;
		root = root->next;
		if (!n_r || node->st.st_size < n_r->st.st_size)
		{
			node->next = n_r;
			n_r = node;
		}
		else
		{
			cur = n_r;
			while (cur->next && node->st.st_size >= cur->next->st.st_size)
				cur = cur->next;
			node->next = cur->next;
			cur->next = node;
		}
	}
	return (n_r);
}
