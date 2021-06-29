/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenCL.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:14:54 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/29 16:16:23 by pitriche         ###   ########.fr       */
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

void	OpenCL::init(void)
{
	std::string ssource;
	const char	*source;

	/* fetch GPU */
	clGetDeviceIDs(0, CL_DEVICE_TYPE_GPU, 1, &this->device, 0);

	/* create context and command queue */
	this->context = clCreateContext(0, 1, &this->device, 0, 0, 0);
	this->queue = clCreateCommandQueue(this->context, this->device, 0, 0);

	/* Create buffers */
	this->buffer_pos = clCreateBuffer(this->context, CL_MEM_READ_WRITE,
		PARTICLES * 3 * sizeof(float), 0, 0);
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

	this->kernel.init_cube = create_kernel(*this, "init_cube");
	this->kernel.init_cube_full = create_kernel(*this, "init_cube_full");
	this->kernel.init_sphere = create_kernel(*this, "init_sphere");

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

	/* sync with GPU */
	clFinish(this->queue);
}
