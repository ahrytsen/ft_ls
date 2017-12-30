/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 14:21:17 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/30 18:02:20 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "libftprintf/libft.h"

int	main(int ac, char **av)
{
	int				i;
	DIR				*dir;
	struct dirent	*dp;

	i = 1;
	if (ac == 1)
	{
		dir = opendir(".");
		while ((dp = readdir(dir)) != NULL)
			ft_printf("%s\n", dp->d_name);
		closedir(dir);
	}
	while (ac-- > 1)
	{
		dir = opendir(av[i++]);
		while ((dp = readdir(dir)) != NULL)
			ft_printf("%s\n", dp->d_name);
		closedir(dir);
	}
}
