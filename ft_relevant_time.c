/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_relevant_time.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 04:39:45 by aholster       #+#    #+#                */
/*   Updated: 2019/11/13 09:13:44 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "incl/ft_flag.h"
#include <time.h>
#include <sys/stat.h>

void		ft_relevant_time(const struct timespec **const arec_time,\
				const struct stat *const restrict astat,\
				const t_flags aflags)
{
	if ((aflags & flg_c) > 0)
	{
		*arec_time = &(astat->st_ctimespec);
	}
	else if ((aflags & flg_u) > 0)
	{
		*arec_time = &(astat->st_atimespec);
	}
	else if ((aflags & flg_U) > 0)
	{
		*arec_time = &(astat->st_birthtimespec);
	}
	else
	{
		*arec_time = &(astat->st_mtimespec);
	}
}
