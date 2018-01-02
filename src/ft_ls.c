/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 14:21:17 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/01/02 21:43:24 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_info(struct dirent f_info, t_flg flags)
{

}

void	ft_ls(char	*path, int show_path)
{

}

int	main(int ac, char **av)
{
	int				i;
	DIR				*dir;
	struct dirent	*dp;
	char			*flags;

	i = 0;
	flags = "";
	if (ac > 1 && *av[1] == '-')
	{
		flags = *av[1];
		i++;
	}
	while (i < ac)
	{
		if (!(dir = opendir(ac == 1 ? "." : av[i + 1])))
			perror(ac == 1 ? "." : av[i + 1]);
		while (dir && (dp = readdir(dir)))
			if (dp->d_name[0] == '.')
				ft_strchr(flags, 'a') ? ft_printf("%s\n", dp->d_name) : 0;
			else
				ft_printf("%s\n", dp->d_name);
		i++;
		dir ? closedir(dir) : 0;
	}
}
