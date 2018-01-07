/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 18:13:22 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/01/08 00:02:41 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_file	*ft_ls_mtime_sort(t_file *root)
{
	t_file	*new_root;
	t_file	*node;
	t_file	*current;

	new_root = NULL;
	while ( root != NULL )
	{
		node = root;
		root = root->next;
		if (!new_root
			|| node->st.st_mtimespec.tv_sec > new_root->st.st_mtimespec.tv_sec)
		{
			node->next = new_root;
			new_root = node;
		}
		else
		{
			current = new_root;
			while (current->next && !(node->st.st_mtimespec.tv_sec
			  > current->next->st.st_mtimespec.tv_sec))
				current = current->next;
			node->next = current->next;
			current->next = node;
		}
	}
	return (new_root);
}
