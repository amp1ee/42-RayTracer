/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 13:24:25 by mstorcha          #+#    #+#             */
/*   Updated: 2018/06/04 13:24:27 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		count_elems(char **str)
{
	int i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

t_slist	*no_empty(t_slist *lst)
{
	t_slist *new;
	t_slist *tmp;

	new = NULL;
	tmp = lst;
	while (lst)
	{
		if (!ft_strcmp(lst->data, ""))
		{
			lst = lst->next;
			continue ;
		}
		ft_list_push_back(&new, ft_strdup(lst->data));
		lst = lst->next;
	}
	free_lst(tmp);
	return (new);
}

int		return_point(char **splitted, char *value, cl_float3 *p)
{
	char	**char_nums;
	int		i;

	i = -1;
	while (++i < count_elems(splitted))
	{
		if (!ft_strcmp(splitted[i], value))
		{
			char_nums = ft_strsplit(splitted[i + 1], ',');
			if (count_elems(char_nums) != 3)
			{
				ft_del_str(char_nums);
				break ;
			}
			*p = (cl_float3) {.x=ft_atof(char_nums[0]),
				.y=ft_atof(char_nums[1]), .z=ft_atof(char_nums[2])};
			ft_del_str(char_nums);
			return (1);
		}
	}
	*p = (cl_float3){.x=0, .y=0, .z=0};
	return (0);
}

int		return_value(char **splitted, char *value, float *val)
{
	int		i;

	i = -1;
	while (++i < count_elems(splitted))
	{
		if (!ft_strcmp(splitted[i], value))
		{
			*val = ft_atof(splitted[i + 1]);
			return (1);
		}
	}
	*val = 0.0;
	return (0);
}
