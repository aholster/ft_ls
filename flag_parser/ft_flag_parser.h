/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flag_parser.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/10 02:13:18 by aholster       #+#    #+#                */
/*   Updated: 2019/10/30 21:41:01 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FLAG_PARSER_H
# define FT_FLAG_PARSER_H

# include "./../incl/ft_flag.h"

# include <stddef.h>

typedef void	(*t_flg_handler)(t_flags *const restrict);

void	flg_cap_l(t_flags *const restrict aflags);
void	flg_cap_r(t_flags *const restrict aflags);
void	flg_low_a(t_flags *const restrict aflags);
void	flg_low_d(t_flags *const restrict aflags);
void	flg_low_f(t_flags *const restrict aflags);
void	flg_low_i(t_flags *const restrict aflags);
void	flg_low_l(t_flags *const restrict aflags);
void	flg_low_r(t_flags *const restrict aflags);
void	flg_low_t(t_flags *const restrict aflags);
void	flg_low_u(t_flags *const restrict aflags);
void	flg_one(t_flags *const restrict aflags);

#endif
