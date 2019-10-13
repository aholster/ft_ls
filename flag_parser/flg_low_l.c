/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flg_low_l.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/11 03:46:45 by aholster       #+#    #+#                */
/*   Updated: 2019/10/13 10:12:18 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_flag.h"

void	flg_low_l(t_flags *const restrict aflags)
{
	(*aflags) |= flg_l;
}
