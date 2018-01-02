/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 14:21:17 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/01/02 15:38:41 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "libft.h"
#include "ft_ls.h"

int	main(int ac, char **av)
{
	int				i;
	DIR				*dir;
	struct dirent	*dp;
	char			*flags;

	i = 1;
	flags = "";
	if (ac > i && *av[i] == '-')
		flags = av[i++];
	while (i <= ac)
	{
		if (!(dir = opendir(ac == 1 ? "." : av[i])))
			ft_printf("ft_ls: %s: No such file or directory\n", av[i - 1]);
		while (dir && (dp = readdir(dir)))
			dp->d_name[0] != '.' && !ft_strchr(flags, 'a')
				? ft_printf("%s\n", dp->d_name) : 0;
		i++;
		dir ? closedir(dir) : 0;
	}
}
