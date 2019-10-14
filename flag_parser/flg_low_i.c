/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flg_low_i.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/14 10:32:52 by aholster       #+#    #+#                */
/*   Updated: 2019/10/14 10:33:07 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_flag.h"

void	flg_low_i(t_flags *const restrict aflags)
{
	(*aflags) |= flg_i;
}
