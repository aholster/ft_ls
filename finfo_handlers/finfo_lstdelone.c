/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finfo_lstdelone.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/22 16:41:14 by aholster       #+#    #+#                */
/*   Updated: 2019/10/13 13:22:15 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/finfo"

void	finfo_lstdelone(t_finfo *restrict *const restrict alst)
{
	free((*alst)->s_name);
	free(*alst);
	*alst = NULL;
}
