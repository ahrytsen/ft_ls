/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 14:21:17 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/01/05 15:30:48 by ahrytsen         ###   ########.fr       */
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

void	ft_print_info(struct dirent f_info, uint64_t *flags)
{

}

void	ft_ls(char	*path, uint64_t *flags)
{
	struct stat		st;
	DIR				*dir;
	struct dirent	*dp;
	t_lis			*d_entr;

	d_entr = NULL;
	(flags & FT_IS_FIRST) ? 0 : ft_printf("\n");
	(flags & FT_SHOW_PATH) ? ft_printf("%s:\n", path) : 0;
	if (!(dir = opendir(path)))
		ft_printf("ft_ls: %s\n", strerror(errno));
	else
	{
		while ((dp = readdir(dir)))
			dp->d_name[0] != '.' && !ft_strchr(flags, 'a')
				? ft_printf("%s\n", dp->d_name) : 0;
		i++;
		closedir(dir);
	}
}

int	main(int ac, char **av)
{
	int			i;
	struct stat	tmp_st;
	t_file		*args;
	uint64_t	flags;

	i = 1;
	flags = 0;
	args = NULL;
	if (ac > 1 && *av[1] == '-' && i++)
		(j = ft_get_flags(av[1] + 1, &flags)) ? ft_usage(av[0], j) : 0;
	ft_sort_params(av + i, ac - i);
	(i == ac) ? ft_ls(".", &flags) : 0;
	while (args && i < ac)
	{
		if (((flags & FT_LFRMT) ? lstat(av[i++], &(args->st))
			 : stat(av[i++], &(args->st))) < 0)
			ft_printf("ft_ls: %s\n", strerror(errno));
		else
			j++;
	}
	i = (flags & FT_REV) ? j : 0;
	(flags & FT_REV) ? 0 : j = 0;
	while ()
}
