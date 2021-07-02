/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenCL.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:14:54 by pitriche          #+#    #+#             */
/*   Updated: 2021/07/02 18:51:20 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OpenCL.hpp"
#include "Utils.hpp"
#include "Defines.hpp"
#include <iostream>	/* cout */

OpenCL::OpenCL(void) { }

static cl_kernel	create_kernel(const OpenCL &cl, const char *filename)
{
	cl_int		err_code;
	cl_kernel	ret;

	ret = clCreateKernel(cl.program, filename, &err_code);
	if (err_code != 0)
		Utils::openCL_error_log(cl, err_code);
	return (ret);
}


#include "All.hpp" /////////////////////////////////
#include "OpenCL/cl_gl.h"
 
/*
cl_APPLE_SetMemObjectDestructor
cl_APPLE_ContextLoggingFunctions
cl_APPLE_clut
cl_APPLE_query_kernel_names
cl_APPLE_gl_sharing
cl_khr_gl_event
cl_khr_byte_addressable_store
cl_khr_global_int32_base_atomics
cl_khr_global_int32_extended_atomics
cl_khr_local_int32_base_atomics
cl_khr_local_int32_extended_atomics
cl_APPLE_fp64_basic_ops
cl_khr_fp64
cl_khr_3d_image_writes
cl_khr_depth_images
cl_khr_gl_depth_images
cl_khr_gl_msaa_sharing
cl_khr_image2d_from_buffer
cl_APPLE_ycbcr_422
cl_APPLE_rgb_422
*/

#pragma OPENCL EXTENSION CL_APPLE_gl_sharing : enable
#pragma OPENCL EXTENSION CL_KHR_gl_sharing : enable
#define CL_GL_CONTEXT_KHR	0x2008
#define CL_WGL_HDC_KHR		0x200B

void	OpenCL::init(GLuint vbo)
{
	std::string ssource;
	const char	*source;

	/* fetch GPU */
	clGetDeviceIDs(0, CL_DEVICE_TYPE_GPU, 1, &this->device, 0);








cl_context_properties props[] =
{
	//OpenCL platform
	// CL_CONTEXT_PLATFORM,	(cl_context_properties)platform,
	
	//OpenGL context
	// CL_GL_CONTEXT_KHR,		(cl_context_properties)all.gl.glcontext,
	//HDC used to create the OpenGL context
	// CL_WGL_HDC_KHR,			(cl_context_properties)hDC,
	0
};

	/* create context and command queue */
	this->context = clCreateContext(0, 1, &this->device, 0, 0, 0);
	std::cout << "context :" << this->context << "\n";
	this->queue = clCreateCommandQueue(this->context, this->device, 0, 0);


	/* create sharegroup */
	this->cgl_context = CGLGetCurrentContext();
	this->sharegroup = CGLGetShareGroup(this->cgl_context);
	std::cout << "cgl context " << cgl_context << "\n";
	std::cout << "sharegroup " << sharegroup << "\n";
	gcl_gl_set_sharegroup(this->sharegroup);




	/* use vbo as pos buffer */
	std::cout << "before " << vbo << "\n";
	int errcode = 0;
	this->buffer_pos = clCreateFromGLBuffer((cl_context)this->context, CL_MEM_READ_WRITE, vbo, &errcode);
	std::cout << "after " << this->buffer_pos << " err>" << errcode << "\n";


	/* Create buffers */
	// this->buffer_pos = clCreateBuffer(this->context, CL_MEM_READ_WRITE,
	// 	PARTICLES * 3 * sizeof(float), 0, 0);
	this->buffer_speed = clCreateBuffer(this->context, CL_MEM_READ_WRITE,
		PARTICLES * 3 * sizeof(float), 0, 0);
	this->buffer_cursor = clCreateBuffer(this->context, CL_MEM_READ_ONLY,
		3 * sizeof(float), 0, 0);

	/* create program and get kernels */
	ssource = Utils::read_file("kernel/particle.cl");
	source = ssource.c_str();
	this->program = clCreateProgramWithSource(this->context, 1, &source, 0,
		0);
	clBuildProgram(this->program, 0, 0, 0, 0, 0);
	this->kernel.update_speed = create_kernel(*this, "update_speed");
	this->kernel.update_position = create_kernel(*this, "update_position");

	this->kernel.init_sphere = create_kernel(*this, "init_sphere");
	this->kernel.init_disk = create_kernel(*this, "init_disk");
	this->kernel.init_cube_full = create_kernel(*this, "init_cube_full");
	this->kernel.init_cube = create_kernel(*this, "init_cube");

	/* set kernel args */
	clSetKernelArg(this->kernel.update_speed, 0, sizeof(cl_mem), &this->buffer_pos);
	clSetKernelArg(this->kernel.update_speed, 1, sizeof(cl_mem), &this->buffer_speed);
	clSetKernelArg(this->kernel.update_speed, 2, sizeof(cl_mem), &this->buffer_cursor);
	clSetKernelArg(this->kernel.update_position, 0, sizeof(cl_mem), &this->buffer_pos);
	clSetKernelArg(this->kernel.update_position, 1, sizeof(cl_mem), &this->buffer_speed);
	clSetKernelArg(this->kernel.init_cube, 0, sizeof(cl_mem), &this->buffer_pos);
	clSetKernelArg(this->kernel.init_cube, 1, sizeof(cl_mem), &this->buffer_speed);
	clSetKernelArg(this->kernel.init_cube_full, 0, sizeof(cl_mem), &this->buffer_pos);
	clSetKernelArg(this->kernel.init_cube_full, 1, sizeof(cl_mem), &this->buffer_speed);
	clSetKernelArg(this->kernel.init_sphere, 0, sizeof(cl_mem), &this->buffer_pos);
	clSetKernelArg(this->kernel.init_sphere, 1, sizeof(cl_mem), &this->buffer_speed);
	clSetKernelArg(this->kernel.init_disk, 0, sizeof(cl_mem), &this->buffer_pos);
	clSetKernelArg(this->kernel.init_disk, 1, sizeof(cl_mem), &this->buffer_speed);

	/* sync with GPU */
	clFinish(this->queue);

	// std::cerr << "clinit done\n";
}
