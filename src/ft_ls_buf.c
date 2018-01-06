/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 14:04:50 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/01/06 19:58:34 by ahrytsen         ###   ########.fr       */
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
		*files = new;
	}
}
