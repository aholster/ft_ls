/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_longformat_file.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 21:23:08 by aholster       #+#    #+#                */
/*   Updated: 2019/11/02 10:37:53 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_stack_processors.h"
#include <limits.h>
#include <time.h>

static void	relevant_time(const time_t *restrict *const restrict arec_time,\
				const struct stat *const restrict astat,\
				const t_flags *const restrict aflags)
{
	if (((*aflags) & flg_u) > 0)
	{
		*arec_time = &(astat->st_atimespec.tv_sec);
	}
	else
	{
		*arec_time = &(astat->st_mtimespec.tv_sec);
	}
}

/*
**					20
**	|RECENT              |
**			11		  20|	4
**	|UNI        |       |    |
**	|Thu Nov 24 18:22:48 1986\n\0
*/

static int	generate_time(char *const restrict abuf,\
				const struct stat *const restrict astat,\
				const t_flags *const restrict aflags)
{
	const char *restrict	time_buf;
	const time_t *restrict	rec_time;
	time_t					cur_time;
	int						fail;

	if (time(&cur_time) == -1)
	{
		return (-1);
	}
	relevant_time(&rec_time, astat, aflags);
	time_buf = ctime(rec_time);
	if (*rec_time + EPOCH_SIXMONTH >= cur_time)
	{
		fail = sprintf(abuf, "%.12s ", time_buf + 4);
	}
	else
	{
		fail = sprintf(abuf, "%.7s %.4s ", time_buf + 4, time_buf + 20);
	}
	if (fail == -1)
	{
		return (-1);
	}
	return (0);
}

int			ft_long_format_file(const t_finfo *const restrict cur_file,\
				t_list **const restrict aout_stack,\
				const t_longests *const restrict amin_fields,\
				const t_flags *const restrict aflags)
{
	char	holder[PATH_MAX + MAX_INODE_LEN + TIMELEN + 1001];
	int		status;

	status = generate_time(holder, &(cur_file->stat), aflags);
	if (status == -1)
	{
		return (-1);
	}
	status = snprintf(holder + TIMELEN, sizeof(holder) - TIMELEN, "%s", cur_file->s_name);
	if (status == -1)
	{
		return (-1);
	}
	else if (ft_lst_stack_push(aout_stack, holder, status + TIMELEN + 1) == -1)
	{
		return (-1);
	}
	(void)amin_fields;
	return (0);
}
