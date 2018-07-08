/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.cl                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 14:28:30 by mstorcha          #+#    #+#             */
/*   Updated: 2018/06/12 14:28:33 by mstorcha         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "rendering.h.cl"
#include "./opencl/intersections.cl"
#include "./opencl/effects.cl"

void	swap(float f, float s)
{
	float tmp = f;
	f = s;
	s = tmp;
}

int		return_int_color(float3 c)
{
	return ((int)c.x * 0x10000 + (int)c.y * 0x100 + (int)c.z);
}

float	sum_color(float f, float s)
{
	float r;

	r = clamp(f + s, 0.0f, 255.0f);
	r = clamp(f + s, 0.0f, 255.0f);
	r = clamp(f + s, 0.0f, 255.0f);

	return r;
}

float3		rotate_ort(float3 point, float3 rot)
{
	float3 od;
	float3 dv;
	float3 tr;
	float3 rot_rad;

	rot_rad.x = rot.x * M_PI / 180.0;
	rot_rad.y = rot.y * M_PI / 180.0;
	rot_rad.z = rot.z * M_PI / 180.0;
	od.x = point.x;
	od.y = point.y * cos(rot_rad.x) + point.z * sin(rot_rad.x);
	od.z = point.z * cos(rot_rad.x) - point.y * sin(rot_rad.x);
	dv.x = od.x * cos(rot_rad.y) - od.z * sin(rot_rad.y);
	dv.y = od.y;
	dv.z = od.z * cos(rot_rad.y) + od.x * sin(rot_rad.y);
	tr.x = dv.x * cos(rot_rad.z) + dv.y * sin(rot_rad.z);
	tr.y = dv.y * cos(rot_rad.z) - dv.x * sin(rot_rad.z);
	tr.z = dv.z;
	return tr;
}

t_closest		closest_fig(float3 O, float3 D,
			float min, float max, __global t_figure *figures, int o_n, int l_n)
{
	t_figure ret;
	float closest = INFINITY;
	for (int i = 0; i < o_n; i++)
	{
		if (figures[i].type == CYLINDER)
		{
			float2 tmp = IntersectRayCylinder(O, D, figures[i]);
			if (tmp.x >= min && tmp.x <= max && tmp.x < closest)
			{
				closest = tmp.x;
				ret = figures[i];
			}
			if (tmp.y >= min && tmp.y <= max && tmp.y < closest)
			{
				closest = tmp.y;
				ret = figures[i];
			}
			continue ;
		}
		else if (figures[i].type == CONE)
		{
			float2 tmp = IntersectRayCone(O, D, figures[i]);
			if (tmp.x >= min && tmp.x <= max && tmp.x < closest)
			{
				closest = tmp.x;
				ret = figures[i];
			}
			if (tmp.y >= min && tmp.y <= max && tmp.y < closest)
			{
				closest = tmp.y;
				ret = figures[i];
			}
			continue ;
		}
		else if (figures[i].type == PLANE)
		{
			float t = IntersectRayPlane(O, D, figures[i]);
			if (t >= min && t <= max && t < closest)
			{
				closest = t;
				ret = figures[i];
			}
			continue ;
		}
		else if (figures[i].type == SPHERE)
		{
			float2 tmp = IntersectRaySphere(O, D, figures[i]);
			if (tmp.x >= min && tmp.x <= max && tmp.x < closest)
			{
				closest = tmp.x;
				ret = figures[i];
			}
			if (tmp.y >= min && tmp.y <= max && tmp.y < closest)
			{
				closest = tmp.y;
				ret = figures[i];
			}
			continue ;
		}
	}
	return (t_closest){closest, ret};
}

float   compute_light(float3 P, float3 N, float3 V, float s, __global t_figure *figures,
                    __global t_figure *light, int o_n, int l_n)
{
    float koef = 0;
    for (int i = 0; i < l_n; i++)
    {
        t_figure l = light[i];
        float3 Lp = {l.p.x, l.p.y, l.p.z};
        float3 L = Lp - P;
        //shadow
        t_closest clos = closest_fig(P, L, 0.001, 0.99, figures, o_n, l_n);
        float closest = INFINITY;
        closest = clos.closest;
        if (closest != INFINITY)
            continue;
        //difuse
        float n_dot_l = dot(N,L);
        if (n_dot_l > 0)
            koef += l.angle * n_dot_l / (fast_length(N) * fast_length(L));
        //zerk
        if (s != -1)
        {
            float3 R = N * 2 * n_dot_l - L;
            float r_dot_v = dot(R,V);
            if (r_dot_v > 0)
                koef += l.angle*pow(r_dot_v / (fast_length(R) * fast_length(V)), s);
        }
    }
    return (koef > 1.0) ? 1.0 : koef;
}

float3	ReflectRay(float3 R, float3 N)
{
	return 2 * N * dot(R, N) - R;
}

float3	RefractRay(float3 R, float3 N, float n1, float n2)
{
	float n = n1 / n2;
	float cosI = - dot(N, R);
	float sinT2 = n * n * (1.f - cosI * cosI);
	if (sinT2 > 1.f || sinT2 < -1.f)
		return (float3){ 0.f, 0.f, 0.f};
	float cosT = sqrt(1.f - sinT2);
	return n * R + (n * cosI - cosT) * N;
}

void 	fresnel(float3 R, float3 N, float n1, float n2, float kr) 
{ 
	float ior = n1 / n2;
    float cosi = clamp((float)dot(R, N), -1.f, 1.f); 
    float etai = 1, etat = ior; 
    if (cosi > 0) 
    	swap(etai, etat);

    float sint = etai / etat * sqrt(max(0.f, 1 - cosi * cosi));

    if (sint >= 1)
        kr = 1;
    else
    { 
        float cost = sqrtf(max(0.f, 1 - sint * sint)); 
        cosi = fabsf(cosi); 
        float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost)); 
        float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost)); 
        kr = (Rs * Rs + Rp * Rp) / 2; 
    }
} 

float3 TraceRay(float3 O, float3 D, float min, float max, __global t_figure *figures,
					__global t_figure *light, int o_n, int l_n)
{
	float3 P;
	float3 N;
	float3 local_c[NUM_REFL] = {0};
	float rfl[NUM_REFL] = {0};
	float rfr[NUM_REFL] = {0};
	int i;
	float3 ret_col = 0;
	float closest;
	t_figure figure;

	for (i = 0; i < NUM_REFL; i++)
	{
		float c_l = 0;
		t_closest clos = closest_fig(O, D, min, max, figures, o_n, l_n);
		closest = clos.closest;
		if (closest == INFINITY)
			break;
		figure = clos.figure;

		P = O + D * closest;
		if (figure.type == PLANE)
		{
			float3 d = {figure.d.x, figure.d.y, figure.d.z};
			if (dot(d,D) < 0)
				N = fast_normalize(d);
			else 
			 	N = fast_normalize(-d);
			c_l = compute_light(P, N, -D, 20, figures, light, o_n, l_n);
		}
		else if (figure.type == CONE)
		{
			float3 d = {figure.d.x, figure.d.y, figure.d.z};
			float3 p = {figure.p.x, figure.p.y, figure.p.z};

			float3 T = d-p;
			T = T / fast_length(T);
			N = P - p;
			T = T * dot(N, T);
			N = N - T;
			N = fast_normalize(N);

			c_l = compute_light(P, N, -D, 20, figures, light, o_n, l_n);
		}
		else if (figure.type == SPHERE)
		{
			float3 p = {figure.p.x, figure.p.y, figure.p.z};
			N = P - p;
			N = N / fast_length(N);
			c_l = compute_light(P, N, -D, 20, figures, light, o_n, l_n);
		}
		else if (figure.type == CYLINDER)
		{
			float3 p = {figure.p.x, figure.p.y, figure.p.z};
			float3 d = {figure.d.x, figure.d.y, figure.d.z};
			N = P - p;
			float3 T = d - p;
			T = T / fast_length(T);
			T = T * dot(N, T);
			N = (N - T) / fast_length(N - T);
			c_l = compute_light(P, N, -D, 20, figures, light, o_n, l_n);
		}
		local_c[i] = (float3){ figure.color.x * c_l,
								figure.color.y * c_l,
								figure.color.z * c_l };
		rfl[i] = figure.reflect;
		if (rfl[i] <= 0)
		{
			rfl[i++] = rfl[i - 1];
			break;
		}
		local_c[i] = (float3){ local_c[i].x * (1.0f - rfl[i]),
								local_c[i].y * (1.0f - rfl[i]),
								local_c[i].z  * (1.0f - rfl[i]) };
		float3 refr_r = RefractRay(P, N, 1.0f, 5.0f);
		float3 ReflRay = ReflectRay(-D, N);
		O = P;
		D = ReflRay;
		min  = 0.001;
	}
	--i;
	for (; i > 0; i--)
	{
		ret_col.r = sum_color(local_c[i].x, ret_col.x) * rfl[i - 1];
		ret_col.g = sum_color(local_c[i].y, ret_col.y) * rfl[i - 1];	
		ret_col.b = sum_color(local_c[i].z, ret_col.z) * rfl[i - 1];
	}
	ret_col.r = sum_color(local_c[0].x * (1.0f - rfl[0]), ret_col.x);
	ret_col.g = sum_color(local_c[0].y * (1.0f - rfl[0]), ret_col.y);
	ret_col.b = sum_color(local_c[0].z * (1.0f - rfl[0]), ret_col.z);

	return ret_col;
}

__kernel void rendering(__global int * data, __global t_figure *figures,
					__global t_figure *light, t_figure cam,
					int l_n, int o_n)
{
	int j = get_global_id(0);
	int i = get_global_id(1);


	float d = 1; // vv from cam
	float3 O = { cam.p.x, cam.p.y, cam.p.z };
	float3 D;
	D.x = ((float)i - (float)WIDTH / 2) * 0.5 / (float)WIDTH;
	D.y = (-(float)j + (float)WIDTH / 2) * 0.5 / (float)HEIGHT;
	D.z = d;
	D = rotate_ort(D, cam.d);

	float3 c = TraceRay(O, D, 1.0F, INFINITY, figures, light, o_n, l_n);

	data[j * 1200 + i] = return_int_color(c);
}
