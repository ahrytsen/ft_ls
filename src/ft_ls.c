/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 14:21:17 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/01/09 21:57:49 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static char	ft_get_flags(char *fl, uint64_t *flags)
{
	while (*++fl)
		if (*fl == 'l')
			*flags = (*flags | FT_LFRMT) & ~FT_COLUMNS;
		else if (*fl == 'R' || *fl == 'a')
			*flags |= (*fl == 'R') ? FT_RECURS : FT_ALL;
		else if (*fl == 'r' || *fl == 't')
			*flags |= (*fl == 'r') ? FT_REV : FT_TSORT;
		else if (*fl == 'u')
			*flags = (*flags & ~FT_TCSORT) | FT_TASORT;
		else if (*fl == 'U')
			*flags = (*flags & ~FT_TASORT) | FT_TCSORT;
		else if (*fl == 'f')
			*flags |= FT_USORT | FT_ALL;
		else if (*fl == '1')
			*flags &= ~FT_COLUMNS;
		else if (*fl == 'g' || *fl == 'd')
			*flags |= (*fl == 'g') ? FT_SUPROWNER : FT_DIRASREG;
		else if (*fl == 'G')
			*flags |= FT_COLOR;
		else
			return (*fl);
	return (0);
}

static void	ft_flags(char **av, int *i, int *ac, uint64_t *flags)
{
	char	c;

	while (*ac > *i && av[*i][0] == '-' && av[*i][1])
	{
		if ((c = ft_get_flags(av[*i], flags)))
		{
			if (!ft_strcmp("--", av[*i]))
				c = 0;
			(*i)++;
			break ;
		}
		(*i)++;
	}
	if (c)
	{
		ft_putstr_fd(*av, 2);
		ft_putstr_fd(": illegal option -- ", 2);
		ft_putchar_fd(c, 2);
		ft_putstr_fd("\nusage: ft_ls [-Ralrt1] [file ...]\n", 2);
		exit(1);
	}
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
		(!mod && S_ISDIR(args->st.st_mode) && !(*flags & FT_DIRASREG)
		&& (!args->name || (ft_strcmp("..", args->name)
							&& ft_strcmp(".", args->name))))
			? ft_ls(ft_strdup(args->path), flags) : 0;
		ft_del_node(args);
	}
	else if (mod == 2 || !(args->st.st_mode & S_IFDIR)
			|| (*flags & FT_DIRASREG))
	{
		ft_print_node(args, flags);
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
	*flags & FT_LFRMT && files ? ft_printf("total %d\n", files->m_w->total) : 0;
	ft_proc_args(files, flags, 2);
	ft_proc_args(files, flags, ((*flags & FT_RECURS) ? 0 : -1));
	free(path);
}

int			main(int ac, char **av)
{
	int			i;
	struct stat	tmp_st;
	t_file		*args;
	uint64_t	flags;

	i = 1;
	flags = FT_IS_FIRST | FT_COLUMNS;
	args = NULL;
	ft_flags(av, &i, &ac, &flags);
	ft_sort_params(av + i, ac - i);
	(i == ac) ? ft_bufadd(&args, ft_newnod(ft_strdup("."), NULL)) : 0;
	if (i == ac)
		stat(".", &(args->st)) < 0 ? perror(".") : 0;
	(ac - i > 1) ? flags |= FT_SHOW_PATH : 0;
	while (i < ac)
		if (((flags & FT_LFRMT || stat(av[i], &tmp_st) < 0)
			? lstat(av[i++], &tmp_st)
			: stat(av[i++], &tmp_st)) < 0 && write(2, "ls: ", 4))
			av[i - 1][0] ? perror(av[i -1]) : " ");
		else if (!(errno = 0))
			ft_bufadd(&args, ft_newnod(ft_strdup(av[i - 1]), &tmp_st));
	args = ft_ls_sort(args, &flags);
	ft_proc_args(args, &flags, 1);
	ft_proc_args(args, &flags, 0);
	return (errno ? 1 : 0);
}
