/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenCL.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:14:54 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/28 15:58:50 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OpenCL.hpp"
#include "Utils.hpp"
#include "Defines.hpp"
#include <iostream>	/* cout */

OpenCL::OpenCL(void) { }

static void pront(float *d)
{
	for (unsigned i = 0; i < PARTICLES * 3; i += 3)
	{
		std::cout << d[i] << ", " << d[i + 1] << ", " << d[i + 2] << std::endl;
	}
}

void	OpenCL::init(void)
{
	cl_int		err_code;
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
		3 * sizeof(float), 0, 0);	/* maybe not a buffer */


	float	speed_data[PARTICLES * 3];
	bzero(speed_data, PARTICLES *3*4);

	float	cursor_data[3] = { ////////////////////////////////
		1.0f, 1.0f, 1.0f,
	};

	/* create program and get kernels */
	ssource = Utils::read_file("kernel/particle.cl");
	source = ssource.c_str();
	this->program = clCreateProgramWithSource(this->context, 1, &source, 0,
		0);
	clBuildProgram(this->program, 0, 0, 0, 0, 0);
	this->kernel_update_speed = clCreateKernel(this->program,
		"update_speed", &err_code);
	this->kernel_update_position = clCreateKernel(this->program,
		"update_position", &err_code);
	if (err_code != 0)
		Utils::openCL_error_log(*this, err_code);

	/* set kernel args */
	clSetKernelArg(this->kernel_update_speed, 0, sizeof(cl_mem), &this->buffer_pos);
	clSetKernelArg(this->kernel_update_speed, 1, sizeof(cl_mem), &this->buffer_speed);
	clSetKernelArg(this->kernel_update_speed, 2, sizeof(cl_mem), &this->buffer_cursor);
	clSetKernelArg(this->kernel_update_position, 0, sizeof(cl_mem), &this->buffer_pos);
	clSetKernelArg(this->kernel_update_position, 1, sizeof(cl_mem), &this->buffer_speed);



	// /* write in buffers */
	// clEnqueueWriteBuffer(this->queue, this->buffer_pos, CL_FALSE, 0,
	// 	PARTICLES * 3 * sizeof(float), (void *)pos_data, 0, 0, 0);
	clEnqueueWriteBuffer(this->queue, this->buffer_speed, CL_FALSE, 0,
		PARTICLES * 3 * sizeof(float), (void *)speed_data, 0, 0, 0);
	clEnqueueWriteBuffer(this->queue, this->buffer_cursor, CL_TRUE, 0,
		3 * sizeof(float), (void *)cursor_data, 0, 0, 0);

	// /* enqueue kernel operations */
	size_t	global_size[2] = {PARTICLES * 3, 0};
	// clEnqueueNDRangeKernel(this->queue, this->kernel_update_speed, 1, 0,
	// 	global_size, 0, 0, 0, 0);
	// clEnqueueNDRangeKernel(this->queue, this->kernel_update_position, 1, 0,
	// 	global_size, 0, 0, 0, 0);

	// /* retrive data */
	// clEnqueueReadBuffer(this->queue, this->buffer_speed, CL_TRUE, 0,
	// 	PARTICLES * 3 * sizeof(float), (void *)speed_data, 0, 0, 0);
	// clEnqueueReadBuffer(this->queue, this->buffer_pos, CL_TRUE, 0,
	// 	PARTICLES * 3 * sizeof(float), (void *)pos_data, 0, 0, 0);

	// /* Wait for finish - sync with GPU */
	clFinish(this->queue);





	// pront(pos_data);
	std::cout << std::endl;
	// pront(speed_data);

	// exit(0); ////////////
}
