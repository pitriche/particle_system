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
/* #################			physics kernels				################# */
/* ########################################################################## */

__kernel void	update_speed(__global vec3 *position, __global vec3 *speed,
	__global vec3 *cursor)
{
	int		id;
	float3	pos_vec;
	float3	acceleration;
	float	distance;

	id = get_global_id(0);

	pos_vec = (float3)(position[id].x, position[id].y, position[id].z);\
	acceleration = (float3)(cursor->x, cursor->y, cursor->z);

	/* compute particle weight (time=1) */
	acceleration -= pos_vec;
	distance = fast_length(acceleration);
	if (distance == 0.0)
		acceleration = (float3)(0);
	else
		acceleration /= distance * exp(distance);

	/* apply acceleration (particle mass = 1) */
	add_vec3(speed + id, &acceleration);

	/* fixed value speed damping */
	float damping = 0.99995;
	speed[id].x *= damping;
	speed[id].y *= damping;
	speed[id].z *= damping;
}

__kernel void	update_position(__global float *position, __global float *speed)
{
	int id;
	
	id = get_global_id(0);
	float	physics_speed = 5e-4;
	position[id] += speed[id] * physics_speed;
}

/* ########################################################################## */
/* #################			initialize kernel			################# */
/* ########################################################################## */

float	rand_ish(int n)
{
	ulong	seed;

	seed = (n * 0x5DEECE66DL + 0xBL) & ((1L << 48) - 1);
	return ((float)(uint)(seed >> 16) / 4294967296.0);
}

__kernel void	init_sphere(__global vec3 *position, __global vec3 *speed)
{
	int		id;
	float	latitude;
	float	longitude;
	
	id = get_global_id(0);
	longitude = rand_ish(((id * 124322) >> 3) ^ id) * (float)M_PI * 2;
	latitude = rand_ish(((id * 12345) >> 2) ^ id) * (float)M_PI;
	position[id].x = sin(longitude) * sin(latitude);
	position[id].y = cos(longitude) * sin(latitude);
	position[id].z = cos(latitude);
	speed[id].x = 0.0f;
	speed[id].y = 0.0f;
	speed[id].z = 0.0f;
}

__kernel void	init_disk(__global vec3 *position, __global vec3 *speed)
{
	int		id;
	float	latitude;
	float	longitude;
	
	id = get_global_id(0);
	longitude = rand_ish(((id * 124322) >> 3) ^ id) * (float)M_PI * 2;
	latitude = rand_ish(((id * 12345) >> 2) ^ id) * (float)M_PI;
	position[id].x = sin(longitude) * sin(latitude);
	position[id].y = cos(longitude) * sin(latitude);
	position[id].z = 1;
	speed[id].x = 0.0f;
	speed[id].y = 0.0f;
	speed[id].z = 0.0f;
}

__kernel void	init_cube_full(__global vec3 *position, __global vec3 *speed)
{
	int		id;
	
	id = get_global_id(0);
	position[id].x = rand_ish(((id * 124322) >> 3) ^ id) * 1.8 - 0.9;
	position[id].y = rand_ish(((id * 124567) >> 3) ^ id) * 1.8 - 0.9;
	position[id].z = rand_ish(((id * 223562) >> 3) ^ id) * 1.8 - 0.9;
	speed[id].x = 0.0f;
	speed[id].y = 0.0f;
	speed[id].z = 0.0f;
}

__kernel void	init_cube(__global vec3 *position, __global vec3 *speed)
{
	int		id;
	int		side;
	float	fixed_side;

	id = get_global_id(0);
	side = (int)(rand_ish(((id * 1234) >> 3) ^ id) * 345542) % 3;
	fixed_side = (int)(rand_ish(((id * 23421) >> 3) ^ id) * 6312746) % 2;
	fixed_side = (fixed_side ? -0.9 : 0.9);
	switch (side)
	{
		case 0 :
			position[id].x = rand_ish(((id * 1234) >> 3) ^ id) * 1.8 - 0.9;
			position[id].y = rand_ish(((id * 4321) >> 3) ^ id) * 1.8 - 0.9;
			position[id].z = fixed_side;
			break;
		case 1 :
			position[id].x = rand_ish(((id * 1234) >> 3) ^ id) * 1.8 - 0.9;
			position[id].y = fixed_side;
			position[id].z = rand_ish(((id * 4321) >> 3) ^ id) * 1.8 - 0.9;
			break;
		case 2 :
			position[id].x = fixed_side;
			position[id].y = rand_ish(((id * 1234) >> 3) ^ id) * 1.8 - 0.9;
			position[id].z = rand_ish(((id * 4321) >> 3) ^ id) * 1.8 - 0.9;
			break;
	}
	speed[id].x = 0.0f;
	speed[id].y = 0.0f;
	speed[id].z = 0.0f;
}
