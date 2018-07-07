/* **************************************************************************** */
/*                                                                              */
/*                                                         :::      ::::::::    */
/*    intersections.h.cl                                 :+:      :+:    :+:    */
/*                                                     +:+ +:+         +:+      */
/*    By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+         */
/*                                                 +#+#+#+#+#+   +#+            */
/*    Created: 2018/07/02 13:37:39 by mstorcha          #+#    #+#              */
/*    Updated: 2018/07/02 13:37:41 by mstorcha         ###   ########.fr        */
/*                                                                              */
/* **************************************************************************** */

#include "rendering.h.cl"

float2 IntersectRayCone(float3 O, float3 D, t_figure cone)
{
	float A = cone.angle;
	float3 d = {cone.d.x, cone.d.y, cone.d.z};
	float3 p = {cone.p.x, cone.p.y, cone.p.z};

	float3 V = D;
	float3 P = O;
	float3 Pa = {cone.p.x, cone.p.y, cone.p.z};
	float3 Va = (d - p) / fast_length(d - p);
	float3 dP = P - Pa;

	float sc1 = dot(V, Va);
	float sc2 = dot(dP, Va);
	float3 tmp1 = V - Va * dot(V, Va);
	float3 tmp2 = dP - Va * dot(Va, dP);

	float A1 = cos(A) * cos(A) * dot(tmp1, tmp1)
					- sin(A) * sin(A)* sc1 * sc1;
	float B1 = 2.0 * cos(A) * cos(A) * dot(tmp1, tmp2)
					- 2.0 * sin(A) * sin(A) * sc1 * sc2;
	float C1 = cos(A) * cos(A) * dot(tmp2, tmp2)
					- sin(A) * sin(A)* sc2 * sc2;

	float desk = B1 * B1 - 4.0 * A1 * C1;
	if (desk < 0)
		return (float2){INFINITY, INFINITY};
	
	float t1 = (-B1 + sqrt(desk)) / (2.0 * A1);
	float t2 = (-B1 - sqrt(desk)) / (2.0 * A1);
	return (float2){t1, t2};
}

float2 IntersectRaySphere(float3 O, float3 D, t_figure sphere)
{
	float R = sphere.radius;
	float3 C = {sphere.p.x, sphere.p.y, sphere.p.z};
	float3 oc = (float3){O.x - C.x, O.y - C.y, O.z - C.z};

	float k1 = D.x * D.x + D.y * D.y + D.z * D.z;
	float k2 = 2 * (oc.x * D.x + oc.y * D.y + oc.z * D.z);
	float k3 = oc.x * oc.x + oc.y * oc.y + oc.z * oc.z - R * R;

	float desk = k2 * k2 - 4 * k1 * k3;
	if (desk < 0)
		return (float2){INFINITY, INFINITY};
	
	float t1 = (-k2 + sqrt(desk)) / (2 * k1);
	float t2 = (-k2 - sqrt(desk)) / (2 * k1);
	return (float2){t1, t2};
}

float2 IntersectRayCylinder(float3 O, float3 D, t_figure cyl)
{
	float R = cyl.radius;

	float3 V = D;
	float3 P = O;
	float3 P2 = {cyl.d.x, cyl.d.y, cyl.d.z};
	float3 P1 = {cyl.p.x, cyl.p.y, cyl.p.z};
	float3 Va = (P2 - P1) / fast_length(P2 - P1);	
	float3 dP = P - P1;

	float3 tmp1 = V - (Va * dot(V, Va));
	float3 tmp2 = dP - (Va * dot(Va, dP));
	float A = dot(tmp1, tmp1);
	float B = 2 * dot(tmp1, tmp2);
	float C = dot(tmp2, tmp2) - R * R;

	float desk = B * B - 4 * A * C;
	if (desk < 0)
		return (float2){INFINITY, INFINITY};
	
	float t1 = (-B + sqrt(desk)) / (2 * A);
	float t2 = (-B - sqrt(desk)) / (2 * A);
	return (float2){t1, t2};
}

float IntersectRayPlane(float3 O, float3 D, t_figure plane)
{
	float	t;
	float3	l_temp;
	float3 d = {plane.d.x, plane.d.y, plane.d.z};
	float3 p = {plane.p.x, plane.p.y, plane.p.z};

	l_temp = p - O;
	t = dot(l_temp, d);
	t = t / dot(D, d);
	return t;
}

