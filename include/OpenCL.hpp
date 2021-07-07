/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenCL.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:13:45 by pitriche          #+#    #+#             */
/*   Updated: 2021/07/07 15:12:37 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENCL_HPP
# define OPENCL_HPP

# include <OpenCL/cl.h>		/* cl_* */
# include <OpenGL/OpenGL.h>	/* CGLGetCurrentContext */

struct cl_data
{
	float	mass;
	float	cursor[3];
};

struct Kernel
{
	cl_kernel	update_speed;		/* range : each particle */
	cl_kernel	update_position;	/* range : each float */

	cl_kernel	init_sphere;		/* range : each particle */
	cl_kernel	init_disk;			/* range : each particle */
	cl_kernel	init_cube_full;		/* range : each particle */
	cl_kernel	init_cube;			/* range : each particle */
};

struct OpenCL
{
	public :
		OpenCL(void);

		cl_device_id		device;
		cl_context			context;
		cl_command_queue	queue;

		cl_program			program;
		Kernel				kernel;

		cl_mem				buffer_pos;
		cl_mem				buffer_speed;
		cl_mem				buffer_data;

		CGLContextObj		cgl_context;
		CGLShareGroupObj	sharegroup;

		void	init(GLuint vbo);

	private:
};

#endif
