/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_error_cleanup.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/13 13:48:17 by aholster       #+#    #+#                */
/*   Updated: 2019/10/13 13:49:08 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_error_cleanup(t_fstack *const restrict afstack)
{
	perror("ft_ls");
	ft_fstack_del(afstack);
	exit(-1);
}
