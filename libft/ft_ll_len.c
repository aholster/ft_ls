/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ll_len.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 15:27:12 by aholster       #+#    #+#                */
/*   Updated: 2019/11/07 15:27:50 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_ll_len(long long n, const unsigned int base)
{
	unsigned int length;

	length = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		length++;
	while (n != 0)
	{
		n = n / base;
		length++;
	}
	return (length);
}
