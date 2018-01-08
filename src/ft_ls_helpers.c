/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 20:58:35 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/01/08 21:17:44 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_get_mod(t_mode m, char *mod)
{
	*mod = S_ISBLK(m) ? 'b' : '-';
	S_ISCHR(m) ? *mod = 'c' : 0;
	S_ISDIR(m) ? *mod = 'd' : 0;
	S_ISFIFO(m) ? *mod = 'p' : 0;
	S_ISLNK(m) ? *mod = 'l' : 0;
	S_ISSOCK(m) ? *mod = 's' : 0;
	*(++mod) = (m & S_IRUSR) ? 'r' : '-';
	*(++mod) = (m & S_IWUSR) ? 'w' : '-';
	*(++mod) = (m & S_IXUSR) ? 'x' : '-';
	*(++mod) = (m & S_IRGRP) ? 'r' : '-';
	*(++mod) = (m & S_IWGRP) ? 'w' : '-';
	*(++mod) = (m & S_IXGRP) ? 'x' : '-';
	*(++mod) = (m & S_IROTH) ? 'r' : '-';
	*(++mod) = (m & S_IWOTH) ? 'w' : '-';
	*(++mod) = (m & S_IXOTH) ? 'x' : '-';
}
