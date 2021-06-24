/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenCL.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:14:54 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/24 11:06:39 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OpenCL.hpp"
#include "Utils.hpp"
#include <iostream>	/* cout */

OpenCL::OpenCL(void) { }


void	OpenCL::init(void)
{
	cl_int		err_code;
	std::string ssource;
	const char	*source;
	char		buffer[512];

	/* fetch GPU */
	clGetDeviceIDs(0, CL_DEVICE_TYPE_GPU, 1, &this->device, 0);

	/* create context and command queue */
	this->context = clCreateContext(0, 1, &this->device, 0, 0, 0);
	this->queue = clCreateCommandQueue(this->context, this->device, 0, 0);
	
	/* compile kernels */
	ssource = Utils::read_file("kernel/test.cl");
	source = ssource.c_str();

	this->program_test = clCreateProgramWithSource(this->context, 1, &source, 0,
		0);
	
	clBuildProgram(this->program_test, 0, 0, 0, 0, 0);
	this->kernel_test = clCreateKernel(this->program_test, "test_add", &err_code);
	if (err_code != 0)
		Utils::openCL_error_log(*this, err_code);

	this->buffer = clCreateBuffer(this->context, CL_MEM_READ_WRITE, 48, 0, 0);
}
