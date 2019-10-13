/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_fstack_del.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/13 12:11:31 by aholster       #+#    #+#                */
/*   Updated: 2019/10/13 13:20:53 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_fstack_del(t_fstack *const restrict afstack)
{
	finfo_lstdel(&(afstack->ndir_stack));
	finfo_lstdel(&(afstack->dir_stack));
	ft_lstdel(&(afstack->err_list), &ft_del);
	ft_bzero(afstack, sizeof(t_fstack));
}
