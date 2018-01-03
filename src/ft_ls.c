/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 14:21:17 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/01/03 20:36:09 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_usage(char *p_name, char tmp)
{
	ft_printf("%s: illegal option -- %c\n", p_name, tmp);
	ft_printf("usage: ft_ls [-Ralrt1] [file ...]\n");
	exit(errno);
}

static char	ft_get_flags(char *fl, uint64_t *flags)
{
	while (*fl)
	{
		if (*fl == 'l')
			*flags |= FT_LFRMT;
		else if (*fl == 'R')
			*flags |= FT_RECURS;
		else if (*fl == 'a')
			*flags |= FT_ALL;
		else if (*fl == 'r')
			*flags |= FT_REV;
		else if (*fl == 't')
			*flags |= FT_TIME_M;
		else
		{
			errno = EIO;
			return (*fl);
		}
		fl++;
	}
	return (0);
}

/*void	ft_print_info(struct dirent f_info, uint64_t flags)
{

}

void	ft_ls(char	*path, int show_path)
{

}
*/
int	main(int ac, char **av)
{
	int				i;
//	DIR				*dir;
//	struct dirent	*dp;
	uint64_t		flags;
	char			tmp;

	i = 1;
	flags = 0;
	if (ac > 1 && *av[1] == '-' && i++)
		(tmp = ft_get_flags(av[1] + 1, &flags)) ? ft_usage(av[0], tmp) : 0;
/*	while (i < ac)
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
		}*/
}
