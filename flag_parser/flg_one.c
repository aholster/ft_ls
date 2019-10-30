/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flg_one.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 21:40:11 by aholster       #+#    #+#                */
/*   Updated: 2019/10/30 21:40:30 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_flag.h"

void	flg_one(t_flags *const restrict aflags)
{
	(*aflags) |= flg_1;
}
