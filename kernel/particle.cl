typedef struct	s_vec3
{
	float	x;
	float	y;
	float	z;
}				vec3;

/* ########################################################################## */

/* vector addition */
void	add_vec3(__global vec3 *result, float3 *vec)
{
	result->x += vec->x;
	result->y += vec->y;
	result->z += vec->z;
}

/* ########################################################################## */

__kernel void	update_speed(__global vec3 *position, __global vec3 *speed,
	__global vec3 *cursor)
{
	int		id;
	float3	pos_vec;
	float3	acceleration;
	float	distance;

	/* get particle's id and skip mid particle ids */
	if (get_global_id(0) % 3 != 0)
		return ;
	id = get_global_id(0) / 3;

	pos_vec = (float3)(position[id].x, position[id].y, position[id].z);\
	acceleration = (float3)(cursor->x, cursor->y, cursor->z);

	/* compute particle weight (time=1) */
	acceleration -= pos_vec;
	distance = fast_length(acceleration);
	if (distance == 0.0)
		acceleration = (float3)(0);
	else
		acceleration /= distance * distance;

	/* apply acceleration (particle mass = 1) */
	add_vec3(speed + id, &acceleration);
}

__kernel void	update_position(__global float *position, __global float *speed)
{
	int id;
	
	id = get_global_id(0);
	position[id] += speed[id] * 2e-5;
}
