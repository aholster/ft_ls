/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flg_low_t.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/11 03:47:38 by aholster       #+#    #+#                */
/*   Updated: 2019/10/11 03:47:43 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_flag.h"

void	flg_low_t(t_flags *const restrict aflags)
{
	(*aflags) &= flg_t;
}
