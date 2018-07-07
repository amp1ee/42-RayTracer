/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 13:26:55 by mstorcha          #+#    #+#             */
/*   Updated: 2018/06/04 13:26:58 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				na(char *name)
{
	if (!ft_strcmp(name, "camera"))
		return (1);
	else if (!ft_strcmp(name, "light"))
		return (2);
	else if (!ft_strcmp(name, "sphere"))
		return (3);
	else if (!ft_strcmp(name, "cone"))
		return (4);
	else if (!ft_strcmp(name, "cylinder"))
		return (5);
	else if (!ft_strcmp(name, "plane"))
		return (6);
	else
		return (0);
}

static void		fill_fig(int name, char **splitted, t_figure **fig)
{
	return_color_t(splitted, "clr:", (&(*fig)->color));
	return_point(splitted, "pnt:", &((*fig)->p));
	return_value(splitted, "rfl:", &((*fig)->reflect));
	return_value(splitted, "rfr:", &((*fig)->refract));
	if (name == 3)
	{
		return_value(splitted, "rds:", &((*fig)->radius));
		if ((*fig)->radius <= 0)
			exit_message("radius < 0");
	}
	else if (name == 5)
	{
		return_point(splitted, "dir:", norming(&((*fig)->d)));
		return_value(splitted, "rds:", &((*fig)->radius));
		if ((*fig)->radius <= 0)
			exit_message("radius < 0");
	}
	else if (name == 4)
	{
		return_point(splitted, "dir:", norming(&((*fig)->d)));
		return_value(splitted, "alp:", &((*fig)->angle));
		(*fig)->angle = (*fig)->angle * M_PI / 180;
	}
	else if (name == 6)
		return_point(splitted, "dir:", norming(&((*fig)->d)));
}

t_slist			*get_lights(t_slist *strs)
{
	t_slist		*lights;
	char		**splitted;
	t_figure	*light;

	lights = NULL;
	while (strs && (splitted = ft_strsplit(strs->data, ' ')))
	{
		if (na(splitted[0]) && (na(splitted[0]) == 2)
			&& (light = malloc(sizeof(t_figure))))
		{
			if (!return_point(splitted, "pnt:", &(light->p)) ||
				!return_value(splitted, "int:", &(light->angle)) ||
				(light->angle <= 0 || light->angle >= 1))
			{
				ft_del_str(splitted);
				free(light);
				strs = strs->next;
				continue ;
			}
			ft_list_push_back(&lights, light);
		}
		ft_del_str(splitted);
		strs = strs->next;
	}
	return (lights);
}

int				get_camera(t_slist *strs, t_figure *cam)
{
	char		**splitted;

	while (strs && (splitted = ft_strsplit(strs->data, ' '))
				&& count_elems(splitted) > 1)
	{
		if (na(splitted[0]) && (na(splitted[0]) == 1) &&
			return_point(splitted, "dir:", &(cam->d)) &&
			return_point(splitted, "pnt:", &(cam->p)))
		{
			ft_del_str(splitted);
			return (1);
		}
		ft_del_str(splitted);
		strs = strs->next;
	}
	return (0);
}

t_figure		*get_figure(t_slist *strs)
{
	char		**splitted;
	int			name;
	t_figure	*fig;

	if (!(splitted = ft_strsplit(strs->data, ' ')))
		exit_message("memory allocation err");
	name = na(splitted[0]);
	if (ft_strcmp(splitted[count_elems(splitted) - 1], "}")
			|| ft_strcmp(splitted[1], "{") || !name ||
			!(fig = malloc(sizeof(t_figure))))
		return (ft_del_str(splitted));
	fig->type = name;
	if ((name == 3) || (name == 4)
		|| (name == 5) || (name == 6))
		fill_fig(name, splitted, &fig);
	else
	{
		free(fig);
		return (ft_del_str(splitted));
	}
	ft_del_str(splitted);
	return (fig);
}
