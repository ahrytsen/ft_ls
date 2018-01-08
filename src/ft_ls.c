/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 14:21:17 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/01/08 19:03:42 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	ft_usage(char *p_name, char tmp)
{
	ft_putstr_fd(p_name, 2);
	ft_putstr_fd(": illegal option -- ", 2);
	ft_putchar_fd(tmp, 2);
	ft_putstr_fd("\nusage: ft_ls [-Ralrt1] [file ...]\n", 2);
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
			*flags |= FT_TMSORT;
		else if (*fl != '1')
		{
			errno = EIO;
			return (*fl);
		}
		fl++;
	}
	return (0);
}

static void	ft_proc_args(t_file *args, uint64_t *flags, int mod)
{
	t_file	*tmp;

	if (!args)
		return ;
	(*flags & FT_REV) ? 0 : ft_proc_args(args->next, flags, mod);
	tmp = args->next;
	if (mod < 1)
	{
		(!mod && S_ISDIR(args->st.st_mode)
		&& (!args->name || (ft_strcmp("..", args->name)
							&& ft_strcmp(".", args->name))))
			? ft_ls(ft_strdup(args->path), flags) : 0;
		free(args->path);
		free(args->name);
		free(args);
	}
	else if (mod == 2 || !(args->st.st_mode & S_IFDIR))
	{
		ft_printf("%s\n", args->name ? args->name : args->path);
		*flags = (*flags & ~FT_IS_FIRST) | FT_SHOW_PATH;
	}
	(*flags & FT_REV) ? ft_proc_args(tmp, flags, mod) : 0;
}

void		ft_ls(char *path, uint64_t *flags)
{
	DIR				*dir;
	struct dirent	*dp;
	t_file			*files;
	char			*tmp;

	files = NULL;
	(*flags & FT_IS_FIRST) ? *flags &= ~FT_IS_FIRST : ft_printf("\n");
	(*flags & FT_SHOW_PATH) ? ft_printf("%s:\n", path) : 0;
	if (!(dir = opendir(path)) && write(2, "ls: ", 4))
		perror(((tmp = ft_strrchr(path, '/')) ? tmp + 1 : path));
	else if ((path = ft_strextend(path, ft_strdup("/"))))
		while ((dp = readdir(dir)))
			if (dp->d_name[0] != '.' || (*flags & FT_ALL))
			{
				ft_bufadd(&files,
						ft_newnod(ft_strjoin(path, dp->d_name), NULL));
				files->name = ft_strdup(dp->d_name);
				lstat(files->path, &(files->st));
			}
	dir ? closedir(dir) : 0;
	files = ft_ls_sort(files, flags);
	ft_proc_args(files, flags, 2);
	ft_proc_args(files, flags, ((*flags & FT_RECURS) ? 0 : -1));
	free(path);
}

int			main(int ac, char **av)
{
	int			i;
	char		c;
	struct stat	tmp_st;
	t_file		*args;
	uint64_t	flags;

	i = 1;
	flags = FT_IS_FIRST;
	args = NULL;
	while (ac > i && *av[i] == '-')
		(c = ft_get_flags(av[i++] + 1, &flags)) ? ft_usage(av[0], c) : 0;
	(i == ac) ? ft_ls(ft_strdup("."), &flags) : 0;
	(ac - i > 1) ? flags |= FT_SHOW_PATH : 0;
	while (i < ac)
		if (((flags & FT_LFRMT) ? lstat(av[i++], &tmp_st)
			: stat(av[i++], &tmp_st)) < 0 && write(2, "ls: ", 4))
			perror(av[i - 1]);
		else
			ft_bufadd(&args, ft_newnod(ft_strdup(av[i - 1]), &tmp_st));
	args = ft_ls_sort(args, &flags);
	ft_proc_args(args, &flags, 1);
	ft_proc_args(args, &flags, 0);
	return (errno ? 1 : 0);
}
