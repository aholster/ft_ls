/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finfo_lstdelone.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/22 16:41:14 by aholster       #+#    #+#                */
/*   Updated: 2019/11/26 10:23:49 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/finfo.h"
#include "../incl/ft_file_format.h"
#include "../libft/libft.h"

void	finfo_lstdelone(t_finfo *restrict *const restrict alst)
{
	if ((*alst)->fvect != NULL)
	{
		free((*alst)->fvect->svec);
		ft_bzero((*alst)->fvect, sizeof(t_fvec));
	}
	ft_bzero((*alst), sizeof(t_finfo));
	free(*alst);
	*alst = NULL;
}
