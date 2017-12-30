/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 14:21:17 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/30 19:31:51 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "../libftprintf/libft.h"

int	main(int ac, char **av)
{
	int				i;
	DIR				*dir;
	struct dirent	*dp;

	while (i < ac)
	{
		if (!(dir = opendir(av[i++])))
			ft_printf("ls: %s: No such file or directory", av[i - 1]);
		while (dir && (dp = readdir(dir)) != NULL)
			ft_printf("%s\n", ac == 1 ? "." : dp->d_name);
		closedir(dir);
	}
}
