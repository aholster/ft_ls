/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flag_parser.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/10 02:11:26 by aholster       #+#    #+#                */
/*   Updated: 2019/12/11 08:54:42 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/ft_printf.h"
#include <stdio.h>

#include "../ft_ls.h"
#include "../libft/libft.h"

static void	bad_flag(const unsigned char flag_chr)
{
	ft_dprintf(2, "ft_ls: illegal option -- %c\n%s", flag_chr, USAGE);
	exit(-1);
}

static const t_flg_tbl	g_trans_tabl[128] = {
	['B'] = {flg_B, flg_q + flg_w + flg_b},
	['C'] = {flg_C, flg_x + flg_l + flg_1},
	['F'] = {flg_F + flg_p, 0},
	['H'] = {flg_H, 0},
	['L'] = {flg_L, flg_P},
	['P'] = {flg_P, flg_L + flg_H},
	['R'] = {flg_R, 0},
	['T'] = {flg_T, 0},
	['U'] = {flg_U, flg_c + flg_u},
	['a'] = {flg_a, 0},
	['b'] = {flg_b, flg_q + flg_w + flg_B},
	['c'] = {flg_c, flg_U + flg_u},
	['d'] = {flg_d, 0},
	['f'] = {flg_f + flg_a, 0},
	['g'] = {flg_g + flg_l, 0},
	['i'] = {flg_i, 0},
	['l'] = {flg_l, flg_C + flg_x + flg_m + flg_1},
	['m'] = {flg_m, flg_C + flg_x + flg_l + flg_1},
	['n'] = {flg_n + flg_l, 0},
	['o'] = {flg_o + flg_l, 0},
	['p'] = {flg_p, flg_F},
	['q'] = {flg_q, flg_b + flg_B + flg_w},
	['r'] = {flg_r, 0},
	['t'] = {flg_t, 0},
	['u'] = {flg_u, flg_c + flg_U},
	['w'] = {flg_w, flg_b + flg_B + flg_q},
	['x'] = {flg_x, flg_C + flg_l + flg_1},
	['1'] = {flg_1, flg_C + flg_l + flg_x + flg_m},
};

static void	parse_argument_flags(const char *const restrict flag_block,\
				const size_t len,\
				t_flags *const restrict aflags)
{
	size_t			index;
	unsigned char	flag_chr;

	index = 1;
	while (index < len && flag_block[index] != '\0')
	{
		flag_chr = flag_block[index];
		if (flag_chr < 128 && g_trans_tabl[flag_chr].enable != 0)
		{
			(*aflags) |= g_trans_tabl[flag_chr].enable;
			(*aflags) &= ~(g_trans_tabl[flag_chr].disable);
		}
		else
		{
			bad_flag(flag_chr);
		}
		index++;
	}
}

void		ft_flag_parser(int *const restrict aargc,\
				char **restrict *const restrict aargv,\
				t_flags *const restrict aflags)
{
	size_t					len;

	while ((*aargc) != 0 && (**aargv)[0] == '-')
	{
		len = ft_strlen((**aargv));
		if (len <= 1)
		{
			break ;
		}
		else
		{
			parse_argument_flags((**aargv), len, aflags);
		}
		(*aargv)++;
		(*aargc)--;
	}
}
