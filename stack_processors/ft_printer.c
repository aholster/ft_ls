/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printer.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/20 11:31:08 by aholster       #+#    #+#                */
/*   Updated: 2019/11/26 10:21:34 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "../libft/libft.h"
#include "../incl/ft_stack_processors.h"
#include "../incl/ft_file_format.h"

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
					const t_flags is_color,\
					const uint32_t term_width)
{
	ssize_t			n;
	const size_t	offset = COLOR_LEN * ((is_color & flg_G) > 0);

	n = 0;
	while (iterator->next != NULL)
	{
		if (dprintf(1, "%s, ", iterator->content) == -1)
		{
			return (-1);
		}
		n += iterator->content_size + 1 - offset;
		if (n + iterator->next->content_size + 1 - offset >= term_width)
		{
			if (write(1, "\n", 1) == -1)
				return (-1);
			n = 0;
		}
		iterator = iterator->next;
	}
	if (dprintf(1, "%s, \n", iterator->content) == -1)
		return (-1);
	return (1);
}

static int		multi_column_alt(const t_list *restrict iterator,\
					const int byt_width,\
					const int vis_width,\
					const uint32_t term_width)
{
	size_t	current_line;

	current_line = 0;
	while (iterator != NULL)
	{
		current_line += vis_width;
		if (current_line + vis_width >= term_width || iterator->next == NULL)
		{
			if (dprintf(1, "%s\n", iterator->content) == -1)
			{
				return (-1);
			}
			current_line = 0;
		}
		else
		{
			if (dprintf(1, "%-*s", byt_width, iterator->content) == -1)
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

int				ft_printer(const t_list *const restrict lst,\
					const t_print_widths *const restrict awidths,\
					const t_flags aflags)
{
	const uint32_t	t_width = find_term_width();
	const int		byt_width = awidths->byt_width;
	const int		vis_width = awidths->vis_width;

	if (lst != NULL)
	{
		if ((aflags & flg_m) > 0)
		{
			return (stream_format_print(lst, aflags & flg_G, t_width));
		}
		else if ((aflags & flg_C) > 0)
		{
			return (ft_multi_column_print(lst, byt_width, vis_width, t_width));
		}
		else if ((aflags & flg_x) > 0)
		{
			return (multi_column_alt(lst, byt_width, vis_width, t_width));
		}
		else if ((aflags & (flg_1 | flg_l)) > 0)
		{
			return (per_line_print(lst));
		}
		return (-1);
	}
	return (1);
}
