/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ull_len.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 15:27:10 by aholster       #+#    #+#                */
/*   Updated: 2019/11/07 15:28:03 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_ull_len(unsigned long long n, const unsigned int base)
{
	unsigned int length;

	length = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / base;
		length++;
	}
	return (length);
}
