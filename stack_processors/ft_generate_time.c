/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_generate_time.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/02 13:44:21 by aholster       #+#    #+#                */
/*   Updated: 2019/11/02 17:35:59 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_stack_processors.h"
#include <time.h>

static void	relevant_time(const time_t *restrict *const restrict arec_time,\
				const struct stat *const restrict astat,\
				const t_flags *const restrict aflags)
{
	if (((*aflags) & flg_c) > 0)
	{
		*arec_time = &(astat->st_ctimespec.tv_sec);
	}
	else if (((*aflags) & flg_u) > 0)
	{
		*arec_time = &(astat->st_atimespec.tv_sec);
	}
	else if (((*aflags) & flg_U) > 0)
	{
		*arec_time = &(astat->st_birthtimespec.tv_sec);
	}
	else
	{
		*arec_time = &(astat->st_mtimespec.tv_sec);
	}
}

/*
**		breakdown of time string and handling
**					20
**	    |RECENT      |
**		4     7		  20|	4
**	    |OLD    |       |    |
**	|Thu Nov 24 18:22:48 1986\n\0
*/

static int	small_time(char *const restrict abuf,\
				size_t *const restrict aoffset,\
				const time_t *const restrict arec_time,\
				const char *const restrict time_buf)
{
	time_t					cur_time;

	if (time(&cur_time) == -1)
	{
		return (-1);
	}
	else
	{
		if (*arec_time + EPOCH_SIXMONTH >= cur_time)
		{
			if (sprintf(abuf, "%.12s ", time_buf + 4) == -1)
			{
				return (-1);
			}
		}
		else if (sprintf(abuf, "%.7s %.4s ", time_buf + 4, time_buf + 20) == -1)
		{
			return (-1);
		}
		*aoffset += TIMELEN;
		return (TIMELEN);
	}
}

int			ft_generate_time(char *const restrict abuf,\
				size_t *const restrict aoffset,\
				const struct stat *const restrict astat,\
				const t_flags *const restrict aflags)
{
	const time_t *restrict	arec_time;
	const char *restrict	time_buf;

	relevant_time(&arec_time, astat, aflags);
	time_buf = ctime(arec_time);
	if (time_buf == NULL)
	{
		return (-1);
	}
	else
	{
		if (((*aflags) & flg_T) > 0)
		{
			if (sprintf(abuf, "%.20s ", time_buf + 4) == -1)
			{
				return (-1);
			}
			*aoffset += MAX_TIMELEN;
		}
		else
		{
			return (small_time(abuf, aoffset, arec_time, time_buf));
		}
	}
	return (0);
}
