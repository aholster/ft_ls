/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printer.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/20 11:31:08 by aholster       #+#    #+#                */
/*   Updated: 2019/11/22 09:14:45 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/ioctl.h>

#include "../libft/libft.h"
#include "../incl/ft_flag.h"

static int	find_term_width(void)
{
	struct winsize termfo;

	if (isatty(1) == 1)
	{
		if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &termfo) != -1)
		{
			printf("term_width: %d\n", termfo.ws_row);
			return (termfo.ws_row);
		}
	}
	return (-1);
}

static int	stream_format_print(const t_list *restrict iterator,\
				int term_width)
{
	size_t	current_line;

	if (term_width < 0)
	{
		term_width = 80;
	}
	current_line = 0;
	while (iterator != NULL)
	{
		if (dprintf(1, "%s, ", iterator->content) == -1)
		{
			return (-1);
		}
		current_line += iterator->content_size - 1;
		if (current_line + iterator->content_size > (unsigned int)term_width)
		{
			write(1, "\n", 1);
			current_line = 0;
		}
		iterator = iterator->next;
	}
	return (1);
}

static int	per_line_print(const t_list *restrict iterator)
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

int			ft_printer(const t_list *const restrict out_list,\
				const int max_len,\
				const t_flags aflags)
{
	int			status;
	const int	term_width = find_term_width();

	(void)max_len;
	status = -1;
	if ((aflags & flg_m) > 0)
	{
		status = stream_format_print(out_list, term_width);
	}
	// else if ((aflags & flg_C) > 0)
	// {
	// 	status =
	// }
	// else if ((aflags & flg_x) > 0)
	// {
	// 	status =
	// }
	else if ((aflags & (flg_1 | flg_l)) > 0)
	{
		status = per_line_print(out_list);
	}
	return (status);
}
