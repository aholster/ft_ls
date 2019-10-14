/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flg_low_f.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/14 10:13:05 by aholster       #+#    #+#                */
/*   Updated: 2019/10/14 10:13:26 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_flag.h"

void	flg_low_f(t_flags *const restrict aflags)
{
	(*aflags) |= flg_f;
}
