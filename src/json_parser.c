/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminadzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 16:46:08 by aminadzh          #+#    #+#             */
/*   Updated: 2018/07/21 18:57:46 by aminadzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char 		*ft_fgets(char *file)
{
	int 	fd;
	char 	*str;
	char 	*tmp;

	if ((fd = open(file, O_RDONLY)) < 0)
	{
		close(fd);
		ft_putendl("Can not open file");
		exit(0);
	}
	str = ft_strnew(0);
	while (ft_get_next_line(fd, &tmp) > 0)
	{
		str = ft_strjoin(str, tmp);
		free(tmp);
	}
	close(fd);
	return (str);
}

char			*ft_get_substr(const char *str, char *start, char *end)
{
	size_t		len;
	char		*new;

	len = 0;
	while (str != start)
		str++;
	while (start != end)
	{
		len++;
		start++;
	}
	new = ft_strsub(str, 0, len + 1);
	return (new);
}

char 		*json_get_array(char *str, char *pattern, char *stack, int top)
{
	char 	*start;
	char 	*ret;
	char 	*s_ptr;

	if (!(start = ft_strstr(str, pattern)))
	{
		printf("Unable to find %s\n", pattern);
		exit(0);
	}
	s_ptr = start;
	stack = ft_strnew(ft_strlen(start));
	while (*s_ptr)
	{
		if (*s_ptr == '[')
			stack[top++] = *s_ptr;
		if (*s_ptr == ']')
		{
			if (--top == 0)
				break;
		}
		s_ptr++;
	}
	ret = ft_get_substr(start, start, s_ptr);
	ft_memmove(start, s_ptr + 1, ft_strlen(s_ptr));
	return (ret);
}

cl_float3		json_arr_to_vector(char *str, char *pattern, char *start, char *end)
{
	cl_float3	vector;
	char 		**tab;
	float 		arr[3];
	int 		i;

	if (!(start = ft_strstr(str, pattern)))
	{
		return (json_arr_to_vector("[0,0,0]", "[", NULL, NULL));
//		exit(0);
	}
	start = ft_strstr(start, "[");
	end = ft_strstr(start, "]");
	start = ft_get_substr(start, start + 1, end);
	tab = ft_strsplit(start, ',');
	i = 0;
	while (*tab != NULL)
	{
		arr[i] = ft_atof(*tab);
		i++;
		tab++;
	}
	vector = (cl_float3){.x = arr[0], .y = arr[1], .z = arr[2]};
	return (vector);
}

cl_float3	get_unit_vector(cl_float3 vec)
{
	cl_float3	new;
	float		mag;

	mag = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	new.x = vec.x / mag;
	new.y = vec.y / mag;
	new.z = vec.z / mag;
	return (new);
}

void		parse_camera(char **str, t_figure *camera)
{
	char 	*substr;

	substr = json_get_array(*str, "\"camera\"", NULL, 0);
	camera->p = json_arr_to_vector(substr, "\"origin\"", NULL, NULL);
	camera->d = json_arr_to_vector(substr, "\"direction\"", NULL, NULL);
//	camera->d = get_unit_vector(camera->d);
}

char 		*json_get_object(char *str, char *pattern)
{
	char 	*start;
	char 	*end;
	char 	*ret;

	if (!(start = ft_strstr(str, pattern)))
		return (NULL);
	end = ft_strstr(start, "}");
	ret = ft_get_substr(str, start, end + 1);
	ft_memmove(str, end + 1, ft_strlen(end) + 1);
	return (ret);
}

float 			json_get_float(char *str, char *pattern)
{
	float 		ret;
	char 		*substr;

	substr = ft_strstr(str, pattern);
	if (substr == NULL)
		return (0);
	while (!ft_isdigit(*substr))
		substr++;
	ret = ft_atof(substr);
	return (ret);
}

cl_float3		json_arr_to_color(char *str, char *pattern, char *start, char *end)
{
	cl_float3	color;
	float		arr[3];
	char		**tab;
	int			i;

	start = ft_strstr(str, pattern);
	if (start == NULL)
	{
		printf("Unable to create vector by pattern \"%s\"\n", pattern);
		return (json_arr_to_color("[0,0,0]", "[", NULL, NULL));
	}
	start = ft_strstr(start, "[");
	end = ft_strstr(start, "]");
	start = ft_get_substr(start, start + 1, end);
	tab = ft_strsplit(start, ',');
	i = 0;
	while (*tab != NULL)
	{
		arr[i] = ft_atoi(*tab);
		i++;
		tab++;
	}
	color = (cl_float3){.x = arr[0], .y = arr[1], .z = arr[2]};
	return (color);
}

t_figure		*get_object(char *str)
{
	t_figure	*object;

	if (!(object = (t_figure *)malloc(sizeof(t_figure))))
		return (NULL);
	if (ft_strstr(str, "\"sphere\"") != NULL)
		object->type = 3;
	else if (ft_strstr(str, "\"cone\"") != NULL)
		object->type = 4;
	else if (ft_strstr(str, "\"cylinder\"") != NULL)
		object->type = 5;
	else if (ft_strstr(str, "\"plane\"") != NULL)
		object->type = 6;
	object->p = json_arr_to_vector(str, "\"origin\"", NULL, NULL);
	object->d = json_arr_to_vector(str, "\"direction\"", NULL, NULL);
	object->radius = json_get_float(str, "\"radius\"");
	object->color = json_arr_to_color(str, "\"color\"", NULL, NULL);
	object->matirial = 0;
	object->rfl = json_get_float(str, "\"reflective\"");
	if (object->rfl > 0)
		object->matirial = 1;
	object->rfr = json_get_float(str, "\"refractive\"");
	return (object);
}

t_slist			*parse_objects(char **str)
{
	char 		*substr;
	char 		*obj_str;
	t_slist		*list;
	t_figure	*object;

	list = NULL;
	substr = json_get_array(*str, "\"objects\"", NULL, 0);
	while (*substr)
	{
		obj_str = json_get_object(substr, "{");
		if (obj_str)
		{
			object = get_object(obj_str);
			ft_list_push_back(&list, object);
		}
		substr++;
	}
	return (list);
}

int 		match_brack(char open, char close)
{
	if ((open == '[' && close == ']') || (open == '{' && close == '}'))
		return (1);
	return (0);
}

char 		*ft_brackets(char *str, int len)
{
	int 	top;
	char 	*stack;

	top = 0;
	stack = ft_strnew(len);
	while (*str)
	{
		if (*str == '[' || *str == '{')
			stack[top++] = *str;
		if (*str == ']' || *str == '}')
		{
			if (!match_brack(stack[--top], *str))
			{
				free(stack);
				return (str);
			}
		}
		str++;
	}
	free(stack);
	return (NULL);
}

static t_figure	*array_cast(t_slist *lst, t_scene *sc, int num)
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
	if (!(ret = malloc(sizeof(t_figure) * sz + 1)))
		exit_message("memory allocation err");
	i = -1;
	while (++i < sz)
	{
		tmp = lst;
		ret[i] = *((t_figure *)tmp->data);
		ret[i].index = i;
		lst = lst->next;
		free(tmp->data);
		free(tmp);
	}
	return (ret);
}

t_figure		*get_light(char *str)
{
	t_figure	*light;

	if (!(light = (t_figure *)malloc(sizeof(t_figure))))
		return (NULL);
	if (ft_strstr(str, "\"ambient\"") != NULL)
		light->type = 1;
	else if (ft_strstr(str, "\"point\"") != NULL)
		light->type = 2;
	else if (ft_strstr(str, "\"direct\"") != NULL)
		light->type = 3;
	light->p = json_arr_to_vector(str, "\"position\"", NULL, NULL);
	light->d = json_arr_to_vector(str, "\"direction\"", NULL, NULL);
	light->angle = json_get_float(str, "\"intensity\"");

	return (light);
}

t_slist			*parse_light(char **str)
{
	char 		*substr;
	char 		*obj_str;
	t_slist		*list;
	t_figure	*object;

	list = NULL;
	substr = json_get_array(*str, "\"light\"", NULL, 0);
	while (*substr)
	{
		obj_str = json_get_object(substr, "{");
		if (obj_str)
		{
			object = get_light(obj_str);
			ft_list_push_back(&list, object);
		}
		substr++;
	}
	return (list);
}

t_scene		*parse_json(char *file)
{
	t_scene	*scene;
	char 	*json_str;

	if (!(scene = (t_scene *)malloc(sizeof(t_scene))))
		exit_message("Memallocation error");
	json_str = ft_fgets(file);
	if (ft_brackets(json_str, ft_strlen(json_str)) != NULL)
		exit (0);
	parse_camera(&json_str, &scene->cam);
	scene->lights = array_cast(parse_light(&json_str), scene, 1);
	scene->objects = array_cast(parse_objects(&json_str), scene, 0);
	return (scene);
}
