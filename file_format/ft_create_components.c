/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_create_components.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/12 05:29:03 by aholster       #+#    #+#                */
/*   Updated: 2019/11/26 15:28:37 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>

#include "../incl/ft_file_format.h"
#include "../libft/libft.h"

static int	ft_attach_fvec(t_finfo *const restrict afile)
{
	t_fvec	*new;

	new = (t_fvec *)ft_calloc(sizeof(t_fvec), 1);
	if (new == NULL)
	{
		return (-1);
	}
	else
	{
		new->svec = (char *)malloc(sizeof(char) * VECTOR_START);
		if (new->svec == NULL)
		{
			free(new);
			return (-1);
		}
		else
		{
			new->size = VECTOR_START;
			afile->fvect = new;
			return (1);
		}
	}
}

int			ft_create_components(t_finfo *restrict afinfo,\
				t_compcaps *const restrict acaps,\
				const t_flags aflags)
{
	t_component_names	index;
	const t_comp_gen	component_table[T_COMPCOUNT] = {
		[f_inode] = &ft_generate_inode,
		[f_perm] = &ft_generate_permissions,
		[f_nlnk] = &ft_generate_hardlinks,
		[f_uid] = &ft_generate_uid,
		[f_gid] = &ft_generate_gid,
		[f_size] = &ft_generate_size,
		[f_date] = &ft_generate_date,
		[f_name] = &ft_generate_name,
	};

	while (afinfo != NULL)
	{
		index = 0;
		if (ft_attach_fvec(afinfo) == -1)
		{
			return (-1);
		}
		while (index < T_COMPCOUNT)
		{
			if (component_table[index](afinfo, acaps, aflags) == -1)
			{
				return (-1);
			}
			index++;
		}
		afinfo = afinfo->next;
	}
	return (1);
}
