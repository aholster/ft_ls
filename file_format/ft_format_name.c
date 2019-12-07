/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_format_name.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 14:48:59 by aholster       #+#    #+#                */
/*   Updated: 2019/12/07 03:43:05 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/ft_printf.h"

#include "../incl/ft_file_format.h"
#include "../libft/libft.h"

static void		replace_with_question(char *str)
{
	size_t	index;

	index = 0;
	while (str[index] != '\0')
	{
		if (ft_isprint(str[index]) == 0)
		{
			str[index] = '?';
		}
		index++;
	}
}

static const char	*g_chart[255] = {
	['\0'] = "\\0",
	['\r'] = "\\r",
	['\n'] = "\\n",
	['\v'] = "\\v",
	['\a'] = "\\a",
	['\b'] = "\\b",
	['\f'] = "\\f",
	['\t'] = "\\t",
	['\"'] = "\\\"",
	['\\'] = "\\\\",
};

static size_t	replace_advanced(const char *const restrict str,\
					const size_t source_size,\
					char name_buf[MAX_NAMELEN],\
					const t_flags flags)
{
	size_t		si;
	size_t		ti;

	si = 0;
	ti = 0;
	while (si + 1 < source_size)
	{
		if (ft_isprint(str[si]) == 1 && g_chart[(str[si] & 0xFF)] == NULL)
		{
			name_buf[ti] = str[si];
			ti += 1;
		}
		else if ((flags & flg_b) == flg_b && g_chart[(str[si] & 0xFF)] != NULL)
		{
			ft_memcpy(name_buf + ti, g_chart[(str[si] & 0xFF)], 2);
			ti += 2;
		}
		else
		{
			ft_sprintf(name_buf + ti, "\\%.3hho", str[si]);
			ti += 4;
		}
		si++;
	}
	return (ti);
}

size_t			ft_format_name(const char *const restrict source,\
					const size_t source_size,\
					char name_buf[MAX_NAMELEN],\
					const t_flags aflags)
{
	size_t		len;

	len = 0;
	if ((aflags & (flg_w | flg_q)) > 0)
	{
		ft_memcpy(name_buf, source, source_size);
		len = source_size - 1;
	}
	if ((aflags & flg_q) > 0)
	{
		replace_with_question(name_buf);
	}
	else if ((aflags & (flg_B | flg_b)) > 0)
	{
		len = replace_advanced(source, source_size, name_buf, aflags);
	}
	name_buf[len] = '\0';
	return (len);
}
