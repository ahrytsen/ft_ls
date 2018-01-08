/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 14:04:50 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/01/08 17:32:37 by ahrytsen         ###   ########.fr       */
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
/*
void	ft_print_node(t_file *files, uint64_t *flags)
{

}*/
