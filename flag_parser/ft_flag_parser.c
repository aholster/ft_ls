/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flag_parser.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/10 02:11:26 by aholster       #+#    #+#                */
/*   Updated: 2019/11/13 12:12:55 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"
#include "../libft/libft.h"

static void	bad_flag(const unsigned char flag_chr)
{
	dprintf(2, "ft_ls: illegal option -- %c\n%s", flag_chr, USAGE);
	exit(-1);
}

static const t_flg_tbl	g_trans_tabl[128] = {
	['L'] = {flg_L, 0},
	['R'] = {flg_R, 0},
	['T'] = {flg_T, 0},
	['U'] = {flg_U, flg_c + flg_u},
	['a'] = {flg_a, 0},
	['c'] = {flg_c, flg_U + flg_u},
	['d'] = {flg_d + flg_a, 0},
	['f'] = {flg_f, 0},
	['g'] = {flg_g, 0},
	['i'] = {flg_i, 0},
	['l'] = {flg_l, 0},
	['n'] = {flg_n, 0},
	['o'] = {flg_o, 0},
	['r'] = {flg_r, 0},
	['t'] = {flg_t, 0},
	['u'] = {flg_u, flg_c + flg_U},
	['1'] = {flg_1, 0},
};

static void	flag_trans_tbl(const unsigned char flag_chr,\
				t_flags *const restrict aflags)
{
	if (g_trans_tabl[flag_chr].enable != 0)
	{
		(*aflags) |= g_trans_tabl[flag_chr].enable;
		(*aflags) &= ~(g_trans_tabl[flag_chr].disable);
	}
	else
	{
		bad_flag(flag_chr);
	}
}

void		ft_flag_parser(int *const restrict aargc,\
				char **restrict *const restrict aargv,\
				t_flags *const restrict aflags)
{
	size_t					index;
	size_t					len;
	const char *restrict	flag_block;

	while ((*aargc) != 0 && (**aargv)[0] == '-')
	{
		flag_block = (**aargv);
		index = 1;
		len = ft_strlen(flag_block);
		if (len == 1)
		{
			break ;
		}
		while (index < len)
		{
			if (flag_block[index] >= '\0')
			{
				flag_trans_tbl(flag_block[index], aflags);
			}
			index++;
		}
		(*aargv)++;
		(*aargc)--;
	}
}
