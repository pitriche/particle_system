#version 410 core

uniform vec3	particle_color;
uniform vec3	cursor_position;
uniform float	reference_length;

in vec3			particle_position_geometry;

out vec4		outColor;

void	main()
{
	float dist;
	
	dist = length(particle_position_geometry - cursor_position);
	dist /= reference_length;
	
	/* floor brightness */
	dist += 0.1;

	outColor = vec4(particle_color * dist, 1.0);
	// outColor = vec4(0.1, 1.0, 0.1, 1.0);
}
