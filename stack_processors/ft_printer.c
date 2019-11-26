/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printer.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/20 11:31:08 by aholster       #+#    #+#                */
/*   Updated: 2019/11/26 13:13:23 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "../libft/libft.h"
#include "../incl/ft_stack_processors.h"

static uint32_t	find_term_width(void)
{
	struct winsize termfo;

	if (isatty(1) == 1)
	{
		if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &termfo) != -1)
		{
			return (termfo.ws_col);
		}
	}
	return (80);
}

static int		stream_format_print(const t_list *restrict iterator,\
					const uint32_t term_width)
{
	ssize_t	current_line;

	current_line = 0;
	while (iterator->next != NULL)
	{
		if (dprintf(1, "%s, ", iterator->content) == -1)
		{
			return (-1);
		}
		current_line += iterator->content_size + 1;
		if (current_line + iterator->next->content_size + 1 >= term_width)
		{
			if (write(1, "\n", 1) == -1)
			{
				return (-1);
			}
			current_line = 0;
		}
		iterator = iterator->next;
	}
	if (dprintf(1, "%s\n", iterator->content) == -1)
	{
		return (-1);
	}
	return (1);
}

static int		multi_column_alt(const t_list *restrict iterator,\
					const int max_len,\
					const uint32_t term_width)
{
	size_t	current_line;

	current_line = 0;
	while (iterator != NULL)
	{
		current_line += max_len;
		if (current_line + max_len >= term_width || iterator->next == NULL)
		{
			if (dprintf(1, "%s\n", iterator->content) == -1)
			{
				return (-1);
			}
			current_line = 0;
		}
		else
		{
			if (dprintf(1, "%-*s", max_len, iterator->content) == -1)
			{
				return (-1);
			}
		}
		iterator = iterator->next;
	}
	return (1);
}

static int		per_line_print(const t_list *restrict iterator)
{
	while (iterator != NULL)
	{
		if (printf("%s\n", iterator->content) == -1)
		{
			return (-1);
		}
		iterator = iterator->next;
	}
	return (1);
}

int				ft_printer(const t_list *const restrict out_list,\
					const int max_len,\
					const t_flags aflags)
{
	int				status;
	const uint32_t	term_width = find_term_width();

	if (out_list != NULL)
	{
		status = -1;
		if ((aflags & flg_m) > 0)
		{
			status = stream_format_print(out_list, term_width);
		}
		else if ((aflags & flg_C) > 0)
		{
			status = ft_multi_column_print(out_list, max_len, term_width);
		}
		else if ((aflags & flg_x) > 0)
		{
			status = multi_column_alt(out_list, max_len, term_width);
		}
		else if ((aflags & (flg_1 | flg_l)) > 0)
		{
			status = per_line_print(out_list);
		}
		return (status);
	}
	return (1);
}
