/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_multi_column_print.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/22 14:11:57 by aholster       #+#    #+#                */
/*   Updated: 2019/11/26 12:50:07 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../libft/libft.h"
#include "../incl/ft_flag.h"

static size_t	calc_col_cap(const size_t len, const size_t max_cols)
{
	size_t		iter;
	size_t		rows_necesary;
	size_t		lowest_rows;

	if (max_cols == 0)
	{
		return (1);
	}
	else
	{
		lowest_rows = len / max_cols + (len % max_cols != 0);
		iter = max_cols;
		while (iter > 1)
		{
			rows_necesary = len / iter + (len % iter != 0);
			if (lowest_rows < rows_necesary)
			{
				return (iter + 1);
			}
			iter--;
		}
		return (max_cols);
	}
}

static void		fill_in_list_arr(const t_list *restrict iterator,\
					const t_list **const restrict list_arr,\
					const size_t mini_lstcap)
{
	size_t	counter;
	size_t	index;

	counter = 0;
	index = 0;
	while (iterator != NULL)
	{
		if (counter % mini_lstcap == 0)
		{
			list_arr[index] = iterator;
			index++;
		}
		counter++;
		iterator = iterator->next;
	}
}

static int		print_out_list_arr(const t_list **const restrict list_arr,\
					const int max_len,\
					const size_t column_cap,\
					size_t segment_len)
{
	size_t	i;
	int		status;

	while (segment_len > 0)
	{
		i = 0;
		while (i < column_cap && list_arr[i] != NULL)
		{
			if (list_arr[i + 1] == NULL)
			{
				status = dprintf(1, "%s\n", list_arr[i]->content);
			}
			else
			{
				status = dprintf(1, "%-*s", max_len, list_arr[i]->content);
			}
			if (status == -1)
				return (-1);
			list_arr[i] = list_arr[i]->next;
			i++;
		}
		segment_len--;
	}
	return (1);
}

int				ft_multi_column_print(const t_list *const restrict iterator,\
					const int max_len,\
					const uint32_t term_width)
{
	const size_t	lst_len = ft_lstlen(iterator);
	const size_t	col_cap = calc_col_cap(lst_len, term_width / max_len);
	const size_t	segment_len = lst_len / col_cap + (lst_len % col_cap != 0);
	const t_list	**list_arr;

	list_arr = (const t_list **)ft_calloc(sizeof(t_list *), col_cap + 1);
	if (list_arr == NULL)
	{
		return (-1);
	}
	fill_in_list_arr(iterator, list_arr, segment_len);
	if (print_out_list_arr(list_arr, max_len, col_cap, segment_len) == -1)
	{
		free(list_arr);
		return (-1);
	}
	free(list_arr);
	return (1);
}
