/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finfo_lstadd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/21 19:28:11 by aholster       #+#    #+#                */
/*   Updated: 2019/10/13 13:22:13 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/finfo"

void	finfo_lstadd(t_finfo *restrict *const restrict alst,\
			t_finfo *const new)
{
	new->next = *alst;
	*alst = new;
}
