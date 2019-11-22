/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_generate_size.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 08:25:41 by aholster       #+#    #+#                */
/*   Updated: 2019/11/20 06:50:33 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "../ft_printf/ft_printf.h"

#include <sys/types.h>
#include "../incl/ft_file_format.h"

static int	put_device_modes(const struct stat *const restrict astat,\
				t_compcaps *const restrict acaps,\
				char buffer[64])
{
	int				len;
	const uint32_t	min_dev = minor(astat->st_rdev);
	const uint32_t	maj_dev = major(astat->st_rdev);

	if (min_dev > 127)
	{
		len = ft_snprintf(buffer, 64, "%3u, %#.8x", maj_dev, min_dev);
	}
	else
	{
		len = snprintf(buffer, 64, "%3u, %3u", maj_dev, min_dev);
		if (len > acaps->fsize_len)
		{
			acaps->fsize_len = len;
		}
	}
	if (len == -1)
	{
		return (-1);
	}
	return (len);
}

static int	put_size(const struct stat *const restrict astat,\
				char buffer[64],\
				const t_flags aflags)
{
	int		len;

	len = snprintf(buffer, 64, "%llu", astat->st_size);
	if (len == -1)
	{
		return (-1);
	}
	(void)aflags;
	return (len);
}

int			ft_generate_size(const t_finfo *const restrict afile,\
				t_compcaps *const restrict acaps,\
				const t_flags aflags)
{
	char	numbuf[64];
	int		status;

	if (S_ISCHR(afile->stat.st_mode) == 1 || S_ISBLK(afile->stat.st_mode) == 1)
	{
		status = put_device_modes(&(afile->stat), acaps, numbuf);
	}
	else
	{
		status = put_size(&(afile->stat), numbuf, aflags);
		if (status > acaps->fsize_len)
		{
			acaps->fsize_len = status;
		}
	}
	if (status == -1)
	{
		return (-1);
	}
	if (ft_fvec_enter_comp(afile, f_size, numbuf,\
			(size_t)status + 1) == -1)
	{
		return (-1);
	}
	return (1);
}
