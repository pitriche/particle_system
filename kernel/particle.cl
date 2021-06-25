typedef struct	s_vec3
{
	float	x;
	float	y;
	float	z;
}				vec3; /* to use instead of floats */

__kernel void	update_speed(__global float *position, __global float *speed,
	__global float *cursor)
{
	int id;
	
	id = get_global_id(0);
	// buf1[id] += id % 2 == 0 ? 0.5f : -0.4f;
}

__kernel void	update_position(__global float *position, __global float *speed,
	__global float *cursor)
{
	int id;
	
	id = get_global_id(0);
}
