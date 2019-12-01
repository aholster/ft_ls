/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_generate_date.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 05:59:42 by aholster       #+#    #+#                */
/*   Updated: 2019/11/27 14:38:21 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <time.h>

#include "../incl/ft_file_format.h"
#include "../ft_ls.h"

static void	relevant_date(\
				const time_t *restrict *const restrict afile_time,\
				const struct stat *const restrict astat,\
				const t_flags aflags)
{
	const struct timespec	*holder;

	ft_relevant_time(&holder, astat, aflags);
	*afile_time = &(holder->tv_sec);
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
				const time_t *const restrict af_time,\
				const char *const restrict date_str)
{
	time_t					c_time;

	if (time(&c_time) == -1)
	{
		return (-1);
	}
	else
	{
		if (*af_time + E_SIXMONTH > c_time || c_time + E_SIXMONTH < *af_time)
		{
			sprintf(buf, "%.12s", date_str + 4);
		}
		else
		{
			sprintf(buf, "%.7s %.4s", date_str + 4, date_str + 20);
		}
		return (1);
	}
}

int			ft_generate_date(const t_finfo *const restrict afile,\
				t_compcaps *const restrict acaps,\
				const t_flags aflags)
{
	const time_t *restrict	afile_time;
	const char *restrict	date_str;
	char					buf[MDATELEN + 1];

	relevant_date(&afile_time, &(afile->stat), aflags);
	date_str = ctime(afile_time);
	if (date_str == NULL)
	{
		return (-1);
	}
	else
	{
		if ((aflags & flg_T) > 0)
		{
			snprintf(buf, sizeof(buf), "%.20s", date_str + 4);
			return (ft_fvec_enter_comp(afile, f_date, buf, MDATELEN + 1));
		}
		else if (small_time(buf, afile_time, date_str) == -1)
			return (-1);
		return (ft_fvec_enter_comp(afile, f_date, buf, DATELEN + 1));
	}
	(void)acaps;
}
