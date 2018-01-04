/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 14:21:17 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/01/04 18:14:30 by ahrytsen         ###   ########.fr       */
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

void	ft_print_info(struct dirent f_info, uint64_t flags)
{

}

void	ft_ls(char	*path, uint64_t flags)
{

}

int	main(int ac, char **av)
{
	int			i;
	int			j;
	struct stat	*st;
	uint64_t	flags;
	char		tmp;

	i = 1;
	j = 0;
	flags = 0;
	if (ac > 1 && *av[1] == '-' && i++)
		(tmp = ft_get_flags(av[1] + 1, &flags)) ? ft_usage(av[0], tmp) : 0;
	ft_sort_params(av + i, ac - i);
	(i == ac) ? ft_ls(".", flags) : 0;
	st = (i < ac) ? ft_memalloc(sizeof(struct stat) * (ac - i + 1)) : NULL;
	while (i < ac)
		if (((flags & FT_LFRMT) ? lstat(av[i++], st + j)
			: stat(av[i++]), st + j) < 0)
			perror(av[i[0]]);
		else
			j++;

}
