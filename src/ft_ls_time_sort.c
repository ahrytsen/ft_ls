/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_time_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 12:51:44 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/01/06 17:00:51 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_ls_time_sort(t_file *files, uint64_t *flags)
{
	t_file	*head;
	t_file	*prev;
//	t_file	*tmp;

	head = files;
	while (files)
	{
		files = head;
		while (files->next)
		{
			if (
			{
				tmp = av[j];
				av[j] = av[j + 1];
				av[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}
