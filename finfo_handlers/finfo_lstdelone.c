/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finfo_lstdelone.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/22 16:41:14 by aholster       #+#    #+#                */
/*   Updated: 2019/10/12 17:43:24 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_finfo.h"

void	finfo_lstdelone(t_finfo *restrict *const restrict alst)
{
	free((*alst)->s_name);
	free(*alst);
	*alst = NULL;
}