/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flag_parser.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/10 02:11:26 by aholster       #+#    #+#                */
/*   Updated: 2019/10/30 21:41:30 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_ls.h"
#include "./../libft/libft.h"
#include "ft_flag_parser.h"

static void	bad_flag(const unsigned char flag_chr)
{
	dprintf(2, "ft_ls: illegal option -- %c\n%s", flag_chr, USAGE);
	exit(-1);
}

static void	flag_trans_tbl(const unsigned char flag_chr,\
				t_flags *const restrict aflags)
{
	static const t_flg_handler	trans_tbl[128] = {
		['L'] = &flg_cap_l,
		['R'] = &flg_cap_r,
		['a'] = &flg_low_a,
		['d'] = &flg_low_d,
		['f'] = &flg_low_f,
		['i'] = &flg_low_i,
		['l'] = &flg_low_l,
		['r'] = &flg_low_r,
		['t'] = &flg_low_t,
		['u'] = &flg_low_u,
		['1'] = &flg_one,
	};

	if (trans_tbl[flag_chr] != NULL)
		trans_tbl[flag_chr](aflags);
	else
		bad_flag(flag_chr);
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
				flag_trans_tbl(flag_block[index], aflags);
			index++;
		}
		(*aargv)++;
		(*aargc)--;
	}
}
