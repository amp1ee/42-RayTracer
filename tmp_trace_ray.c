
t_uint			trace_ray(float3 O, float3 D, float min, float max,
						__constant t_obj *objs, __constant t_light *light)
{
	t_obj_data	obj_data;

	float3		P;
	float3		R;
	float3		N;

	float		light_coef;
	float		r[REFLECT_DEPTH] = {0};
	float3		loc_color[REFLECT_DEPTH] = {0};
	float3		ret_color = 0;

	int			it = -1;

	while(++it < REFLECT_DEPTH)
	{
		obj_data = closest_intersection(O, D, min, max, objs);
		if (obj_data.obj.type < 0)
			break ;
		P = O + obj_data.closest_t * D;
		N = calc_normal(P, D, obj_data.obj);

		light_coef = compute_lighting(P, N, O, -D, obj_data.obj.spec, light, objs);
		light_coef > 1 ? light_coef = 1 : 0;

		loc_color[it] = (float3){obj_data.obj.color >> 16 & 0xFF,
								obj_data.obj.color >> 8 & 0xFF,
								obj_data.obj.color & 0xFF};
		loc_color[it] *= light_coef;
		r[it] = obj_data.obj.refl;
		if (r[it] <= 0)
		{
			r[it++] = r[it - 1];
			break ;
		}
		loc_color[it] *= (1.0F - r[it]);
		R = reflect_ray(-D, N);
		O = P;
		D = R;
		min = 0.001;
	}
	while (--it > 0)
		ret_color = sum_colors(ret_color, loc_color[it]) * r[it - 1];
	ret_color = sum_colors(ret_color, loc_color[0] * (1.0F - r[0]));
	return ((uint)ret_color.x * 0x10000 + (uint)ret_color.y * 0x100 + (uint)ret_color.z);
}














float3 TraceRay1(float3 O, float3 D, float min, float max, int depth, __global t_figure *figures,
					__global t_figure *light, int o_n, int l_n)
{
	float closest;
	t_figure figure;
	float c_l = 0;
	t_closest clos = closest_fig(O, D, min, max, figures, o_n, l_n);
	closest = clos.closest;
	if (closest == INFINITY)
		return (float3){0, 0, 0};
	figure = clos.figure;

	
	float3 P = O + D * closest;
	float3 N;
	float r = figure.reflect;
	if (figure.type == PLANE)
	{
		float3 d = {figure.d.x, figure.d.y, figure.d.z};
		if (dot(D, d) < 0)
			N = (d / fast_length(d));
		else 
			N = (-d / fast_length(d));
		c_l = compute_light(P, N, -D, 10, figures, light, o_n, l_n);
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
		c_l = compute_light(P, N, -D, 10, figures, light, o_n, l_n);
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
		c_l = compute_light(P, N, -D, 50, figures, light, o_n, l_n);
	}
	c_l > 1.0F ? c_l = 1.0f : 0;
	float3 local_c = (float3){figure.color.r * c_l,
						figure.color.g * c_l,
						figure.color.b * c_l};
	if (depth <= 0)
		return local_c;

	//float3 RerfRay = RefractRay(D, N, 1, 2);

	float3 ReflRay = ReflectRay(-D, N);


	float3 ref_col = TraceRay1(P, ReflRay, 0.001, max, depth - 1, figures, light, o_n, l_n);
	return (float3){ local_c.r* (1.f - r) + ref_col.r * r,
						local_c.g * (1.f - r) + ref_col.g * r,
						local_c.b * (1.f - r) + ref_col.b * r};
}







t_color TraceRay(float3 O, float3 D, float min, float max, __global t_figure *figures,
					__global t_figure *light, int o_n, int l_n)
{
	t_color ret;
	float3 P;
	float3 N;
	t_color local_c;
	t_color ref_col;
	float r;

	for (int i = 5; i >= 0; i--)
	{
		float c_l = 0;
		t_closest clos = closest_fig(O, D, min, max, figures, o_n, l_n);
		float closest = clos.closest;
		if (closest == INFINITY)
			return (t_color){0, 0, 0};
		t_figure figure = clos.figure;
		r = figure.reflect;

		P = O + D * closest;
		if (figure.type == PLANE)
		{
			float3 d = {figure.d.x, figure.d.y, figure.d.z};
			if (dot(D, d) < 0)
				N = (d / fast_length(d));
			else 
				N = (-d / fast_length(d));
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
		c_l > 1.0F ? c_l = 1.0f : 0;
		if (i == 0)
			local_c = (t_color){ figure.color.r * c_l,
								figure.color.g * c_l,
								figure.color.b * c_l };
		else
			ref_col = (t_color){ figure.color.r * c_l,
								figure.color.g * c_l,
								figure.color.b * c_l };
		float3 ReflRay = ReflectRay(-D, N);
		O = P;
		D = ReflRay;
	}

	//float3 RerfRay = RefractRay(D, N, 1, 2);

	//t_color ref_col = TraceRay(P, ReflRay, 0.001, max, depth - 1, figures, light, o_n, l_n);

	return (t_color){ local_c.r* (1.f - r) + ref_col.r * r,
						local_c.g * (1.f - r) + ref_col.g * r,
						local_c.b * (1.f - r) + ref_col.b * r};
}
