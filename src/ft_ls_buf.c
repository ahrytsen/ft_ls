/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 14:04:50 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/01/05 14:26:31 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_file	*ft_newnod(void)
{
	t_file	*newnod;

	if (!(newnod = (t_file*)ft_memalloc(sizeof(t_file))))
		return (NULL);
	return (newnod);
}

static void		ft_bufadd(t_file **files, t_file *new)
{
	if (new && files)
	{
		new->next = *alst;
		*alst = new;
	}
}
