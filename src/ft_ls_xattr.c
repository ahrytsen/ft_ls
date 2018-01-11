/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_xattr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:08:44 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/01/11 21:29:31 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_xattr(t_file *node)
{
	char	tmp[2048];
	char	*p;
	int		size;

	p = tmp;
	ft_bzero(tmp, 2048);
	listxattr(node->path, tmp, 1023, XATTR_NOFOLLOW);
	while (*p)
	{
		size = getxattr(node->path, p, NULL, 0, 0, XATTR_NOFOLLOW);
		ft_printf("\t%s\t%4d\n", p, size);
		p += ft_strlen(p) + 1;
	}
}

void	ft_print_acl(t_file *node)
{
	ft_printf("lol%p\n", node);
}
