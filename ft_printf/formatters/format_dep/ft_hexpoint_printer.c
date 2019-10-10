/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hexpoint_printer.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/03 17:57:29 by jesmith        #+#    #+#                */
/*   Updated: 2019/10/04 17:18:00 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incl/ft_formatters.h"

static int		ft_caphexponbuff(char *buffer, short expon)
{
	unsigned short	index;
	int				is_neg;
	unsigned short	backup_index;

	is_neg = expon;
	index = ft_nbrlen((long long)expon, 10);
	if (expon < 0)
		expon *= -1;
	else
		index++;
	backup_index = index;
	while (index > 1)
	{
		buffer[index] = (expon % 10) + '0';
		index--;
		expon /= 10;
	}
	if (is_neg < 0)
		buffer[1] = '-';
	else
		buffer[1] = '+';
	buffer[0] = 'P';
	return (backup_index + 1);
}

int				ft_caphexpoint_print(t_writer *const restrict clipb,\
						short expon,\
						unsigned short nb_len,
						unsigned short str_len)
{
	t_flag *const restrict	flags = clipb->flags;
	unsigned short			expon_len;
	char					new_buf[8];

	if (flg_verif('.', flags) == 1 && flags->precision != (str_len - 2))
		if (pad_zero(flags->precision, clipb) == -1)
			return (-1);
	expon_len = ft_caphexponbuff(new_buf, expon);
	if (clipb->self(new_buf, expon_len, clipb) == -1)
		return (-1);
	if (flags->precision == 0)
		str_len--;
	if (flg_verif('-', flags) == 1 && flags->padding > flags->precision)
		if (ft_float_padder(nb_len + str_len, str_len - 2, clipb) == -1)
			return (-1);
	return (1);
}

static int		ft_lowhexponbuff(char *buffer, short expon)
{
	unsigned short	index;
	int				is_neg;
	unsigned short	backup_index;

	is_neg = expon;
	index = ft_nbrlen((long long)expon, 10);
	if (expon < 0)
		expon *= -1;
	else
		index++;
	backup_index = index;
	while (index > 1)
	{
		buffer[index] = (expon % 10) + '0';
		index--;
		expon /= 10;
	}
	if (is_neg < 0)
		buffer[1] = '-';
	else
		buffer[1] = '+';
	buffer[0] = 'p';
	return (backup_index + 1);
}

int				ft_lowhexpoint_print(t_writer *const restrict clipb,\
						const short expon,\
						unsigned short nb_len,
						unsigned short str_len)
{
	t_flag *const restrict	flags = clipb->flags;
	unsigned short			expon_len;
	char					new_buf[8];

	if (flg_verif('.', flags) == 1 && \
	flags->precision != (str_len - 2))
		if (pad_zero(flags->precision, clipb) == -1)
			return (-1);
	expon_len = ft_lowhexponbuff(new_buf, expon);
	if (clipb->self(new_buf, expon_len, clipb) == -1)
		return (-1);
	if (flags->precision == 0)
		str_len--;
	if (flg_verif('-', flags) == 1 && flags->padding > flags->precision)
		if (ft_float_padder(nb_len + str_len, str_len - 2, clipb) == -1)
			return (-1);
	return (1);
}
