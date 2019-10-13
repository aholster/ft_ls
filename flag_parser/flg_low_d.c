/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flg_low_d.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/13 09:03:47 by aholster       #+#    #+#                */
/*   Updated: 2019/10/13 10:12:18 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_flag.h"

void	flg_low_d(t_flags *const restrict aflags)
{
	(*aflags) |= flg_d;
}
