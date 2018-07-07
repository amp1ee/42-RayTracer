/* **************************************************************************** */
/*                                                                              */
/*                                                         :::      ::::::::    */
/*    1.h.cl                                             :+:      :+:    :+:    */
/*                                                     +:+ +:+         +:+      */
/*    By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+         */
/*                                                 +#+#+#+#+#+   +#+            */
/*    Created: 2018/06/19 13:41:34 by mstorcha          #+#    #+#              */
/*    Updated: 2018/06/19 13:41:45 by mstorcha         ###   ########.fr        */
/*                                                                              */
/* **************************************************************************** */

#ifndef RENDERING_H_CL

# define RENDERING_H_CL
# define HEIGHT 1200
# define WIDTH 1200

/*
** 1 - cam
** 2 - light
** 3 - sphere
** 4 - cone
** 5 - cylinder
** 6 - plane
*/

# define PLANE 6
# define CYLINDER 5
# define CONE 4
# define SPHERE 3

typedef struct	s_figure
{
	int			type;
	float		radius;
	float		angle;
	float		reflect;
	float		refract;
	float3		color;
	float3		p;
	float3		d;
}				t_figure;

typedef struct	s_closest
{
	float		closest;
	t_figure	figure;
}				t_closest;

float	sum_color(float f, float s);
/*
**	EFFECTS
*/

void			e_sepia(float3 *c);
void			e_grades_gray(float3 *c);
void			e_negative(float3 *c);
void			e_black_white(float3 *c);
void			gauss_blur(__global int * data, int i, int j);

/*
**
*/

float3			RefractRay(float3 R, float3 N, float n1, float n2);
float3			ReflectRay(float3 R, float3 N);
float3			return_f_color(int c);
int				return_int_color(float3 c);
float2 			IntersectRaySphere(float3 O, float3 D, t_figure sphere);
float2 			IntersectRayCylinder(float3 O, float3 D, t_figure cyl);
float2 			IntersectRayCone(float3 O, float3 D, t_figure cone);
float 			IntersectRayPlane(float3 O, float3 D, t_figure plane);

float			compute_light(float3 P, float3 N, float3 V, float s, __global t_figure *figures,
					__global t_figure *light, int o_n, int l_n);

t_closest		closest_fig(float3 O, float3 D,
					float min, float max, __global t_figure *figures, int o_n, int l_n);

float3			rotate_ort(float3 point, float3 rot);

float3 			TraceRay(float3 O, float3 D, float min, float max, __global t_figure *figures,
					__global t_figure *light, int o_n, int l_n);

__kernel void 	rendering(__global int * data, __global t_figure *figures,
					__global t_figure *light, t_figure cam,
					int l_n, int o_n);

#endif
