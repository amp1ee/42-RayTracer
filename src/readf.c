/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:31:24 by mstorcha          #+#    #+#             */
/*   Updated: 2018/03/12 14:31:26 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				return_color_t(char **splitted, char *value, cl_float3 *p)
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
			*p = (cl_float3){.x=ft_atof(char_nums[0]),
				.y=ft_atof(char_nums[1]), .z=ft_atof(char_nums[2])};
			ft_del_str(char_nums);
			return (1);
		}
	}
	*p = (cl_float3){.x=255, .y=255, .z=255};
	return (0);
}

t_slist			*readf(char **argv)
{
	int		fd;
	t_slist	*new;
	char	*tmp;
	int		res;

	res = 1;
	fd = open(argv[1], O_RDONLY);
	new = NULL;
	if (fd == -1)
		return (NULL);
	while (res != 0)
	{
		res = ft_get_next_line(fd, &tmp);
		if (res == -1)
			return (NULL);
		if (res != 0)
		{
			ft_list_push_back(&new, ft_strdup(tmp));
			ft_strdel(&tmp);
		}
		else
			free(tmp);
	}
	return (new);
}

static t_slist	*get_fig_lst(t_slist *strs)
{
	t_slist		*figures;
	t_figure	*fig;

	figures = NULL;
	while (strs)
	{
		fig = get_figure(strs);
		if (!fig)
		{
			strs = strs->next;
			continue ;
		}
		ft_list_push_back(&figures, fig);
		strs = strs->next;
	}
	return (figures);
}

static t_figure	*array_cast_ps(t_slist *lst, t_scene *sc, int num)
{
	int			sz;
	int			i;
	t_figure	*ret;
	t_slist		*tmp;

	sz = ft_list_count(lst);
	if (num == 0)
		sc->o_num = sz;
	else
		sc->l_num = sz;
	if (!(ret = malloc(sizeof(t_figure) * sz)))
		exit_message("memory allocation err");
	i = -1;
	while (++i < sz)
	{
		tmp = lst;
		ret[i] = *((t_figure *)tmp->data);
		lst = lst->next;
		free(tmp->data);
		free(tmp);
	}
	return (ret);
}

t_scene			*scene_create(char **argv)
{
	t_scene		*new;
	t_slist		*strs;
	t_slist		*lst;

	if (!(new = malloc(sizeof(t_scene))))
		exit_message("memory allocation err");
	lst = readf(argv);
	strs = no_empty(lst);
	if (!(get_camera(strs, &(new->cam))))
		exit_message("invalid cart");
	new->lights = array_cast_ps(get_lights(strs), new, 1);
	new->objects = array_cast_ps(get_fig_lst(strs), new, 0);
	free_lst(strs);
	return (new);
}
