/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 14:21:17 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/01/05 21:45:44 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	ft_usage(char *p_name, char tmp)
{
	ft_printf("%s: illegal option -- %c\n", p_name, tmp);
	ft_printf("usage: ft_ls [-Ralrt1] [file ...]\n");
	exit(1);
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

/* void	ft_print_info(struct dirent f_info, uint64_t *flags) */
/* { */

/* } */

static void	ft_proc_args(t_file *args, uint64_t *flags, int mod)
{
	t_file	*tmp;

	if (!args)
		return ;
	(*flags & FT_REV) ? 0 : ft_proc_args(args->next, flags, mod);
	tmp = args->next;
	if (!mod)
	{
		(args->st.st_mode & S_IFDIR) ? ft_ls(ft_strdup(args->path), flags) : 0;
		free(args);
	}
	else
	{
		(mod == 3 || !(args->st.st_mode & S_IFDIR))
			? ft_printf("%s\n", args->path) : 0;
		//*flags &= ~FT_IS_FIRST;
	}
	(*flags & FT_REV) ? ft_proc_args(tmp, flags, mod) : 0;
}

void	ft_ls(char *path, uint64_t *flags)
{
	struct stat		tmp_st;
	DIR				*dir;
	struct dirent	*dp;
	t_file			*files;
	t_file			*tmp;

	files = NULL;
	(*flags & FT_IS_FIRST) ? *flags &= ~FT_IS_FIRST : ft_printf("\n");
	(*flags & FT_SHOW_PATH) ? ft_printf("%s:\n", path) : 0;
	path = ft_strextend(path, strdup("/"));
	if (!(dir = opendir(path)))
		ft_printf("ft_ls: %s\n", strerror(errno));
	else
		while ((dp = readdir(dir)))
			if (dp->d_name[0] == '.' && (*flags & FT_ALL))
				ft_bufadd(&files, ft_newnod(dp->d_name, &tmp_st));
			else if (dp->d_name[0] != '.')
				ft_bufadd(&files, ft_newnod(dp->d_name, &tmp_st));
	dir ? closedir(dir) : 0;
	ft_proc_args(files, flags, 3);
	tmp = files;
	free(path);
}

int	main(int ac, char **av)
{
	int			i;
	char		c;
	struct stat	tmp_st;
	t_file		*args;
	uint64_t	flags;

	i = 1;
	flags = FT_IS_FIRST | FT_SHOW_PATH;
	args = NULL;
	if (ac > 1 && *av[1] == '-' && i++)
		(c = ft_get_flags(av[1] + 1, &flags)) ? ft_usage(av[0], c) : 0;
	ft_sort_params(av + i, ac - i);
	(i == ac) ? ft_ls(".", &flags) : 0;
	while (i < ac)
		if (((flags & FT_LFRMT) ? lstat(av[i++], &tmp_st)
			 : stat(av[i++], &tmp_st)) < 0)
			ft_printf("ft_ls: %s: %s\n", av[i - 1], strerror(errno));
		else
			ft_bufadd(&args, ft_newnod(av[i - 1], &tmp_st));
	ft_proc_args(args, &flags, 1);
	ft_proc_args(args, &flags, 0);
	return (errno ? 1 : 0);
}
