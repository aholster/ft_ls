/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_caphexpoint.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/10 12:13:37 by jesmith        #+#    #+#                */
/*   Updated: 2019/10/04 17:34:08 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_formatters.h"

static unsigned short		ft_hexpoint_prec(const char *const restrict buffer,\
								t_writer *const clipb,\
								size_t nb_len,\
								const short expon)
{
	t_flag *const restrict	flags = clipb->flags;
	size_t					dec_len;
	unsigned short			len;

	len = nb_len;
	if (len == 1 && buffer[1] == '.')
		len++;
	if (expon == -1025)
		len = 0;
	if (flg_verif('.', flags) == -1)
		len++;
	if (len > 2)
		dec_len = len - 2;
	else
		dec_len = 2;
	if (flg_verif('.', flags) == 1)
	{
		if (dec_len > flags->precision && dec_len < len)
			len = (len - dec_len) + flags->precision;
		else if (dec_len < flags->precision && len > 2)
			flags->precision -= dec_len;
		if (flags->precision == 0 && len == 2)
			len--;
	}
	return (len);
}

static unsigned short		ft_negpos_handler(t_writer *const restrict clipb,\
								const int is_neg,\
								const short expon)
{
	t_flag *const restrict	flags = clipb->flags;
	unsigned short			sign;
	unsigned short			expon_len;

	expon_len = ft_nbrlen((long long)expon, 10) + 3;
	sign = 0;
	if (is_neg > 0)
	{
		if (flg_verif('+', flags) == 1 || \
		flg_verif(' ', flags) == 1)
			sign++;
	}
	else if (is_neg < 0)
		sign++;
	if (expon >= 0)
		sign++;
	return (expon_len + sign);
}

static int					ft_front_pad(char *buffer, \
								const short expon,\
								t_writer *const restrict clipb,\
								const int is_neg)
{
	unsigned short			expon_len;
	unsigned short			str_len;
	short					nb_len;
	t_flag *const restrict	flags = clipb->flags;

	nb_len = is_neg;
	if (nb_len < 0)
		nb_len *= -1;
	str_len = ft_hexpoint_prec(buffer, clipb, nb_len, expon);
	expon_len = ft_negpos_handler(clipb, is_neg, expon);
	if (flg_verif('.', flags) == 1 && flags->precision == 0)
		expon_len--;
	if (flg_verif('-', flags) == -1 && flags->padding > flags->precision)
		if (ft_float_padder(expon_len + str_len, str_len - 2, clipb) == -1)
			return (-1);
	if (ft_prefix(is_neg, clipb) == -1)
		return (-1);
	if (clipb->self("0X", 2, clipb) == -1)
		return (-1);
	if (clipb->self(buffer, (size_t)str_len, clipb) == -1)
		return (-1);
	if (ft_caphexpoint_print(clipb, expon, expon_len, str_len) == -1)
		return (-1);
	return (1);
}

static short				ft_ull_to_hex(unsigned long long mantissa,\
								char *const restrict buffer,\
								t_writer *const restrict clipb,\
								short expon)
{
	unsigned short				index;
	unsigned short				len;
	const char *const restrict	base = "0123456789ABCDEF";

	if (mantissa == 0)
		buffer[0] = '0';
	index = ft_reversed(mantissa);
	len = index;
	if ((clipb->flags->precision != 0 || expon == 1020))
		index++;
	while (index > 0)
	{
		index--;
		if (index == 1 && (clipb->flags->precision != 0 || expon == 1020))
		{
			buffer[index] = '.';
			index--;
		}
		buffer[index] = base[mantissa & 0XFLLU];
		mantissa >>= 4;
	}
	return (len);
}

int							ft_caphexpoint(va_list args,\
								t_writer *const restrict clipb)
{
	char			buffer[16];
	t_float			conversion;
	long double		nb;
	int				is_neg;
	short			expon;

	is_neg = ft_longdouble_conv(args, &nb, clipb->flags);
	conversion.ld = nb;
	expon = (conversion.byte[4] & 0x7FFF) - 16386;
	if (nb == 0.0 || nb == -0.0)
		is_neg *= ft_float_exceptions(buffer, &expon, clipb->flags);
	else
		is_neg *= ft_ull_to_hex(conversion.llu, buffer, clipb, expon);
	ft_hexpoint_rounder(buffer, clipb->flags, &expon);
	if (ft_front_pad(buffer, expon, clipb, is_neg) == -1)
		return (-1);
	return (1);
}
