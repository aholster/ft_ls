/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flg_cap_l.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/16 15:03:18 by aholster       #+#    #+#                */
/*   Updated: 2019/10/16 15:03:26 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_flag.h"

void	flg_cap_l(t_flags *const restrict aflags)
{
	(*aflags) |= flg_L;
}
