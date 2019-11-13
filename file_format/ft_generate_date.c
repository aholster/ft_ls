/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_generate_date.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 05:59:42 by aholster       #+#    #+#                */
/*   Updated: 2019/11/13 15:40:55 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <time.h>

#include "../incl/ft_file_format.h"
#include "../ft_ls.h"

static void	relevant_date(\
				const time_t *restrict *const restrict arec_time,\
				const struct stat *const restrict astat,\
				const t_flags aflags)
{
	const struct timespec	*holder;

	ft_relevant_time(&holder, astat, aflags);
	*arec_time = &(holder->tv_sec);
}

/*
**		breakdown of time string and handling
**					20
**	    |RECENT      |
**		4     7		  20|	4
**	    |OLD    |       |    |
**	|Thu Nov 24 18:22:48 1986\n\0
*/

static int	small_time(char buf[MDATELEN + 1],\
				const time_t *const restrict arec_time,\
				const char *const restrict date)
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
			snprintf(buf, MDATELEN + 1, "%.12s", date + 4);
		}
		else
		{
			snprintf(buf, MDATELEN + 1, "%.7s %.4s", date + 4, date + 20);
		}
		return (1);
	}
}

int			ft_generate_date(const t_finfo *const restrict afile,\
				t_compcaps *const restrict acaps,\
				const t_flags aflags)
{
	const time_t *restrict	arec_time;
	const char *restrict	date;
	char					buf[MDATELEN + 1];

	relevant_date(&arec_time, &(afile->stat), aflags);
	date = ctime(arec_time);
	if (date == NULL)
	{
		return (-1);
	}
	else
	{
		if ((aflags & flg_T) > 0)
		{
			snprintf(buf, sizeof(buf), "%.20s", date + 4);
			return (ft_fvec_enter_comp(afile->fvect, f_date,\
							buf, MDATELEN + 1));
		}
		else if (small_time(buf, arec_time, date) == -1)
			return (-1);
		return (ft_fvec_enter_comp(afile->fvect, f_date, buf, DATELEN + 1));
	}
	(void)acaps;
}
