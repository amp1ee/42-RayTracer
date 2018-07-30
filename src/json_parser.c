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

int			match_brack(char open, char close)
{
	if ((open == '[' && close == ']') || (open == '{' && close == '}'))
		return (1);
	return (0);
}

char		*ft_brackets(char *str, int len)
{
	int		top;
	char	*stack;

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

static char		*free_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	len1;
	size_t	len2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(new = ft_strnew(len1 + len2)))
		return (NULL);
	ft_strcat(new, s1);
	ft_strcat(new, s2);
	free(s1);
	free(s2);
	return (new);
}

char			*ft_fgets(char *file)
{
	int		fd;
	char	*str;
	char	*tmp;

	if ((fd = open(file, O_RDONLY)) < 0)
	{
		exit_message("Can not open file");
	}
	str = ft_strnew(0);
	while (ft_get_next_line(fd, &tmp) > 0)
	{
		str = free_strjoin(str, tmp);
	}
	free(tmp);
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

char		*json_get_array(char *str, char *pattern, char *stack, int top)
{
	char	*start;
	char	*ret;
	char	*s_ptr;
	char	*copy;

	copy = str;
	if (!(start = ft_strstr(copy, pattern)))
		exit_message(ft_strjoin("Unable to find \n", pattern));
	s_ptr = start;
	stack = ft_strnew(ft_strlen(start));
	while (*s_ptr)
	{
		if (*s_ptr == '[')
			stack[top++] = *s_ptr;
		if (*s_ptr == ']')
			if (--top == 0)
				break ;
		s_ptr++;
	}
	free(stack);
	ret = ft_get_substr(start, start, s_ptr);
	ft_memmove(start, s_ptr + 1, ft_strlen(s_ptr));
	return (ret);
}

cl_float3		json_arr_to_vector(char *str,
			char *pattern, char *start, char *end)
{
	cl_float3	vector;
	char		**tab;
	float		arr[3];
	int			i;

	if (!(start = ft_strstr(str, pattern)))
		return (json_arr_to_vector("[0,0,0]", "[", NULL, NULL));
	start = ft_strstr(start, "[");
	end = ft_strstr(start, "]");
	start = ft_get_substr(start, start + 1, end);
	tab = ft_strsplit(start, ',');
	free(start);
	i = -1;
	while (tab[++i])
		arr[i] = ft_atof(tab[i]);
	ft_del_str(tab);
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
	char	*substr;
	char	*copy;

	copy = ft_strdup(*str);
	substr = json_get_array(copy, "\"camera\"", NULL, 0);
	free(copy);
	camera->p = json_arr_to_vector(substr, "\"origin\"", NULL, NULL);
	camera->d = json_arr_to_vector(substr, "\"direction\"", NULL, NULL);
	free(substr);
}

char		*json_get_object(char *str, char *pattern)
{
	char	*start;
	char	*end;
	char	*ret;

	if (!(start = ft_strstr(str, pattern)))
		return (NULL);
	end = ft_strstr(start, "}");
	ret = ft_get_substr(str, start, end + 1);
	ft_memmove(str, end + 1, ft_strlen(end) + 1);
	return (ret);
}

float			json_get_float(char *str, char *pattern)
{
	float		ret;
	char		*substr;

	substr = ft_strstr(str, pattern);
	if (substr == NULL)
		return (0);
	while (!ft_isdigit(*substr))
		substr++;
	ret = ft_atof(substr);
	return (ret);
}

cl_float3		json_arr_to_color(char *str,
					char *pattern, char *start, char *end)
{
	cl_float3	color;
	float		arr[3];
	char		**tab;
	int			i;

	start = ft_strstr(str, pattern);
	if (start == NULL)
		return (json_arr_to_color("[0,0,0]", "[", NULL, NULL));
	start = ft_strstr(start, "[");
	end = ft_strstr(start, "]");
	start = ft_get_substr(start, start + 1, end);
	tab = ft_strsplit(start, ',');
	free(start);
	i = 0;
	while (tab[i] != NULL)
	{
		arr[i] = ft_atoi(tab[i]);
		i++;
	}
	color = (cl_float3){.x = arr[0], .y = arr[1], .z = arr[2]};
	ft_del_str(tab);
	return (color);
}

void			get_fig_type(t_figure *object, char *str)
{
	if (ft_strstr(str, "\"sphere\"") != NULL)
		object->type = 3;
	else if (ft_strstr(str, "\"cone\"") != NULL)
		object->type = 4;
	else if (ft_strstr(str, "\"cylinder\"") != NULL)
		object->type = 5;
	else if (ft_strstr(str, "\"plane\"") != NULL)
		object->type = 6;
	else if (ft_strstr(str, "\"disk\"") != NULL)
		object->type = 7;
	else if (ft_strstr(str, "\"cube\"") != NULL)
		object->type = 8;
	else if (ft_strstr(str, "\"hyperboloid\"") != NULL)
		object->type = HYPERBOLOID;
	else if (ft_strstr(str, "\"2sheet_hyperboloid\"") != NULL)
		object->type = TWOSHEET_HYPERBOLOID;
	else if (ft_strstr(str, "\"paraboloid\"") != NULL)
		object->type = PARABOLOID;
	else if (ft_strstr(str, "\"ellipsoid\"") != NULL)
		object->type = ELLIPSOID;
}

t_figure		*get_object(char *str)
{
	t_figure	*object;

	if (!(object = (t_figure *)malloc(sizeof(t_figure))))
		return (NULL);
	get_fig_type(object, str);
	object->p = json_arr_to_vector(str, "\"origin\"", NULL, NULL);
	object->d = json_arr_to_vector(str, "\"direction\"", NULL, NULL);
	object->radius = json_get_float(str, "\"radius\"");
	object->size = json_get_float(str, "\"size\"");
	object->min = json_arr_to_vector(str, "\"min\"", NULL, NULL);
	object->max = json_arr_to_vector(str, "\"max\"", NULL, NULL);
	object->color = json_arr_to_color(str, "\"color\"", NULL, NULL);
	object->cap = json_get_float(str, "\"cap\"");
	object->matirial = 0;
	object->angle = 0;
	object->rfl = json_get_float(str, "\"reflective\"");
	if (object->rfl > 0)
		object->matirial = 1;
	object->text = 1;
	return (object);
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

char			*json_get_name(char *str, char *pattern)
{
	char		*ret;
	char		*substr;
	char		**splitted;

	substr = ft_strstr(str, pattern);
	if (!substr)
	{
		return (NULL);
	}
	splitted = ft_strsplit(substr, '\"');
	ret = ft_strdup(splitted[2]);
	ft_del_str(splitted);
	return (ret);
}

static int	read_texture(char *file, t_texture *text)
{
	SDL_Surface	*surface;

	if (!(surface = IMG_Load(file)))
		return (0);
	text->pix = malloc(sizeof(int) * surface->w * surface->h);
	ft_memcpy(text->pix, surface->pixels,
		sizeof(int) * surface->w * surface->h);
	text->h = surface->h;
	text->w = surface->w;
	SDL_FreeSurface(surface);
	return (1);
}

t_texture		*get_texture(char *str, t_opencl *cl, cl_float3 color)
{
	t_texture	*text;
	char		*name;
	int			res;

	if (!(name = json_get_name(str, "\"texture\""))
		|| !(text = malloc(sizeof(t_texture))))
		return (NULL);
	if (!(res = read_texture(name, text)))
	{
		if (!ft_strcmp(name, "perlin"))
			get_disruption(text, cl, color, 1);
		else if (!ft_strcmp(name, "chessboard"))
			get_disruption(text, cl, color, 2);
		else
		{
			free(name);
			free(text);
			return (NULL);
		}
	}
	free(name);
	return (text);
}

t_fig_text		*fill_t_fig_text(char *obj_str, t_opencl *cl, char *type)
{
	t_fig_text	*obj;

	if (!(obj = ft_memalloc(sizeof(t_fig_text))))
		exit_message("mem alloc err");
	if (!ft_strcmp(type, "\"objects\""))
	{
		obj->fig = get_object(obj_str);
		obj->text = get_texture(obj_str, cl, obj->fig->color);
		if (!obj->text)
			obj->fig->text = 0;
	}
	else if (!ft_strcmp(type, "\"light\""))
		obj->fig = get_light(obj_str);
	return (obj);
}

t_slist			*parse_objects(char **str, char *type, t_opencl *cl)
{
	char		*substr;
	char		*obj_str;
	t_slist		*list;
	t_fig_text	*obj;
	char		*copy;

	list = NULL;
	substr = json_get_array(*str, type, NULL, 0);
	copy = substr;
	while (*substr)
	{
		obj_str = json_get_object(substr, "{");
		if (obj_str)
		{
			obj = fill_t_fig_text(obj_str, cl, type);
			ft_list_push_back(&list, obj);
		}
		free(obj_str);
		substr++;
	}
	free(copy);
	return (list);
}

void			get_counters(t_scene *sc, int sz, int num)
{
	if (!num)
		sc->o_num = sz;
	else
		sc->l_num = sz;
}

void			free_tmp(t_slist **tmp)
{
	free(((t_fig_text *)(*tmp)->data)->fig);
	free((*tmp)->data);
	free((*tmp));
}

static t_figure	*array_cast(t_slist *lst, t_scene *sc, int num, t_slist **text)
{
	int			sz;
	int			i;
	t_figure	*ret;
	t_slist		*tmp;

	sz = ft_list_count(lst);
	get_counters(sc, sz, num);
	if (!(ret = malloc(sizeof(t_figure) * sz)))
		exit_message("memory allocation err");
	i = -1;
	while (++i < sz)
	{
		tmp = lst;
		ret[i] = *(((t_fig_text *)tmp->data)->fig);
		ret[i].index = i;
		if (((t_fig_text *)tmp->data)->text && !num)
		{
			((t_fig_text *)tmp->data)->text->index = i;
			ft_list_push_back(text, ((t_fig_text *)(tmp->data))->text);
		}
		lst = lst->next;
		free_tmp(&tmp);
	}
	return (ret);
}

cl_int3			*get_texture_info(t_slist *lst)
{
	cl_int3		*info;
	t_texture	*tmp;
	int			i;

	if (!(info = (cl_int3 *)malloc(sizeof(cl_int3) * ft_list_count(lst))))
		return (NULL);
	i = 0;
	while (lst)
	{
		tmp = lst->data;
		info[i] = (cl_int3) {.x = tmp->h,
								.y = tmp->w,
								.z = tmp->index };
		lst = lst->next;
		i++;
	}
	return (info);
}

static int		size_texture(t_slist *lst)
{
	int			i;
	t_texture	*tmp;

	i = 0;
	while (lst)
	{
		tmp = lst->data;
		i += tmp->h * tmp->w;
		lst = lst->next;
	}
	return (i);
}

int				*ft_intcat(int *dest, int *src, int *sz1, int sz2)
{
	int i;

	i = -1;
	while (++i < sz2)
	{
		dest[i + *sz1] = src[i];
	}
	*sz1 += sz2;
	return (dest);
}

int				*get_texture_array(t_slist *lst)
{
	int			*res;
	t_texture	*tmp_text;
	int			*tmp_int;
	int			size;
	int			count;

	count = 0;
	size = size_texture(lst);
	if (!(res = (int *)malloc(sizeof(int) * size)))
		return (NULL);
	while (lst)
	{
		tmp_text = lst->data;
		tmp_int = tmp_text->pix;
		res = ft_intcat(res, tmp_int, &count, tmp_text->h * tmp_text->w);
		lst = lst->next;
	}
	return (res);
}

void		*free_lst1(t_slist *list)
{
	t_slist *tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(((t_texture *)tmp->data)->pix);
		free(tmp->data);
		free(tmp);
	}
	return (NULL);
}

void			filling_textures(t_scene *scene, t_slist *text_list)
{
	if (!text_list)
	{
		scene->textures_num = 1;
		scene->textures = malloc(sizeof(int));
		scene->textures[0] = 0;
		scene->textures_info = malloc(sizeof(cl_int3));
		scene->textures_info[0] = (cl_int3){.x=0, .y=0, .z=0};
	}
	else
	{
		scene->textures = get_texture_array(text_list);
		scene->textures_num = ft_list_count(text_list);
		scene->textures_info = get_texture_info(text_list);
		free_lst1(text_list);
	}
}

t_scene			*parse_json(char *file, t_opencl *cl)
{
	t_scene	*scene;
	char	*json_str;
	t_slist	*text_list;
	char	*copy;
	t_slist	*tmp;

	text_list = NULL;
	if (!(scene = (t_scene *)malloc(sizeof(t_scene))))
		exit_message("Memallocation error");
	json_str = ft_fgets(file);
	copy = json_str;
	if (ft_brackets(json_str, ft_strlen(json_str)) != NULL)
		exit_message("No valid");
	parse_camera(&json_str, &scene->cam);
	tmp = parse_objects(&json_str, "\"light\"", cl);
	scene->lights = array_cast(tmp, scene, 1, &text_list);
	tmp = parse_objects(&json_str, "\"objects\"", cl);
	scene->objects = array_cast(tmp, scene, 0, &text_list);
	filling_textures(scene, text_list);
	free(copy);
	return (scene);
}
