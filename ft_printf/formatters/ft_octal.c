/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_octal.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/03 15:08:26 by jesmith        #+#    #+#                */
/*   Updated: 2019/10/04 17:57:14 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_formatters.h"

static int				ft_octal_noprec(const char *const restrict buffer,\
							const unsigned short nb_len,\
							t_writer *const restrict clipb)
{
	t_flag *const restrict	flags = clipb->flags;
	const int				minus = flg_verif('-', flags);

	if (minus == -1 && flg_verif('0', flags) == -1 \
	&& flags->padding > 0)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	if (flg_verif('0', flags) == 1 && minus == -1)
	{
		if ((flags->padding - flags->precision) > nb_len)
		{
			if (ft_zero_padder(nb_len, clipb) == -1)
				return (-1);
		}
	}
	if (clipb->self(buffer, (size_t)nb_len, clipb) == -1)
		return (-1);
	if (minus == 1 && flags->padding > nb_len)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	return (1);
}

static int				ft_octal_prec(const char *const restrict buffer,\
							const unsigned short nb_len,\
							t_writer *const restrict clipb)
{
	t_flag *const restrict	flags = clipb->flags;
	const int				minus = flg_verif('-', flags);

	if (minus == -1 && flags->padding > nb_len)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	if (flags->precision > nb_len)
		if (ft_zero_padder(nb_len, clipb) == -1)
			return (-1);
	if (clipb->self(buffer, (size_t)nb_len, clipb) == -1)
		return (-1);
	if (minus == 1 && flags->padding > nb_len)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	return (1);
}

static unsigned short	ft_int_len(char *const restrict buffer,\
							const unsigned long long nb,\
							t_writer *const restrict clipb)
{
	unsigned long long	temp_num;
	unsigned short		num_len;
	unsigned short		cur_len;
	char				*base;

	base = "01234567";
	temp_num = nb;
	num_len = ft_ull_len(nb, 8);
	cur_len = num_len - 1;
	if (flg_verif('#', clipb->flags) == 1 && nb != 0)
	{
		cur_len++;
		buffer[0] = '0';
		num_len++;
	}
	while (temp_num >= 8)
	{
		buffer[cur_len] = base[(temp_num % 8)];
		temp_num /= 8;
		cur_len--;
	}
	buffer[cur_len] = base[temp_num];
	return (num_len);
}

int						ft_octal(va_list args, t_writer *const restrict clipb)
{
	char				buffer[20];
	unsigned long long	nb;
	unsigned short		nb_len;
	int					prec;
	int					exten;

	prec = flg_verif('.', clipb->flags);
	exten = flg_verif('#', clipb->flags);
	ft_unsignconv(args, &nb, clipb->flags);
	nb_len = ft_int_len(buffer, nb, clipb);
	if (exten == -1 && prec == 1 && nb == 0 && clipb->flags->padding == 0)
		return (1);
	if (exten == -1 && prec == 1 && nb == 0 && clipb->flags->precision == 0)
		ft_strcpy((char*)buffer, " ");
	if (prec == 1)
		return (ft_octal_prec(buffer, nb_len, clipb));
	if (prec == -1)
		return (ft_octal_noprec(buffer, nb_len, clipb));
	return (1);
}
