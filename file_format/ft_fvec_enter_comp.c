/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_fvec_enter_comp.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 04:28:22 by aholster       #+#    #+#                */
/*   Updated: 2019/11/20 05:00:19 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_file_format.h"
#include "../libft/libft.h"

int			ft_fvec_enter_comp(const t_finfo *const restrict afile,\
				const t_component_names component_num,\
				const char *const restrict component_str,\
				const size_t component_size)
{
	char					*new_vec;
	t_fvec	*const restrict afvec = afile->fvect;

	if (afvec->tail + component_size > afvec->size)
	{
		new_vec = (char *)malloc(afvec->size * 2);
		if (new_vec == NULL)
		{
			return (-1);
		}
		else
		{
			ft_memcpy(new_vec, afvec->svec, afvec->size);
			afvec->size *= 2;
			free(afvec->svec);
			afvec->svec = new_vec;
		}
	}
	ft_memcpy(afvec->svec + afvec->tail, component_str, component_size);
	afvec->indices[component_num] = afvec->tail;
	afvec->tail += component_size;
	return (1);
}
