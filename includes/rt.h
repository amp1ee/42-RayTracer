/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 13:21:58 by mstorcha          #+#    #+#             */
/*   Updated: 2018/05/23 13:24:38 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define HEIGHT 1200
# define WIDTH 1200
# define MAX_SOURCE_SIZE 0x100000

# include "../libft/libft.h"
# include "../frameworks/minilibx_macos/mlx.h"
# include <math.h>
# include "SDL.h"

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#  include <CL/cl.h>
# endif

/*
** 1 - cam
** 2 - light
** 3 - sphere
** 4 - cone
** 5 - cylinder
** 6 - plane
*/

typedef struct	s_figure
{
	int			type;
	float		radius;
	float		angle;
	float		reflect;
	float		refract;
	cl_float3	color;
	cl_float3	p;
	cl_float3	d;
}				t_figure;

typedef struct	s_slist
{
	void				*data;
	struct s_slist		*next;
}				t_slist;

typedef struct	s_scene
{
	t_figure	*lights;
	t_figure	*objects;
	int			l_num;
	int			o_num;
	t_figure	cam;
}				t_scene;

typedef struct	s_image
{
	void		*data;
	int			*ptr;
	int			bits;
	int			sz_l;
	int			endi;
}				t_image;

typedef struct	s_opencl
{
	cl_platform_id		platform_id;
	cl_device_id		device_id;
	unsigned int		ret_num_plat;
	unsigned int		ret_num_devices;
	cl_context			context;
	cl_command_queue	command_queue;
	size_t				source_size;
	char				*source_str;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				memobj_data;
	cl_mem				memobj_figures;
	cl_mem				memobj_light;
}				t_opencl;

typedef struct	s_main
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_image		image;
	t_scene		*scene;
	t_opencl	*cl;
}				t_main;

void			start_cl(t_opencl *cl);
void			mid_cl(t_opencl *cl, t_main *mlx, int memlenth);
void			args_cl(t_opencl *cl, t_main *mlx);
void			init_cl(t_main *mlx);
void			rendering(t_main *mlx);

void			exit_message(const char *str);
t_slist			*readf(char **argv);

float			v_length(cl_float3 p);
cl_float3		num_dil(cl_float3 p, float n);
float			v_length(cl_float3 p);
int				return_color(cl_float3 c);
t_scene			*scene_create(char **argv);
int				key(int key_code, t_main *mlx);
void			ft_list_push_back(t_slist **begin_list, void *data);

t_slist			*list_objects(char **argv);
void			*free_lst(t_slist *list);

t_slist			*get_lights(t_slist *strs);
int				get_camera(t_slist *strs, t_figure *cam);
t_figure		*get_figure(t_slist *strs);
int				count_elems(char **str);
t_slist			*no_empty(t_slist *lst);
int				return_point(char **splitted, char *value, cl_float3 *p);
int				return_value(char **splitted, char *value, float *val);
cl_float3		p_to_c(cl_float3 p);
int				return_color_t(char **splitted, char *value, cl_float3 *p);

cl_float3		*norming(cl_float3 *p);
int				ft_list_count(t_slist *begin_list);
int				na(char *name);

#endif
