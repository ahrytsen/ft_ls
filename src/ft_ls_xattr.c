/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_xattr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:08:44 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/01/12 13:36:59 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_acl(t_file *node)
{
	char	*acl;
	char	*tmp;

	acl = acl_to_text(node->acl, NULL);
	tmp = ft_strchr(acl, '\n') + 1;
	ft_printf(" 0: %s", tmp);
	acl_free((void*)acl);
}

void	ft_print_xattr(t_file *node, uint64_t *flags)
{
	char	tmp[2048];
	char	*p;
	int		size;

	if (node->mod[10] == '@' && *flags & FT_XATTR)
	{
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
	if (node->acl && *flags & FT_ACL)
		ft_print_acl(node);
}
