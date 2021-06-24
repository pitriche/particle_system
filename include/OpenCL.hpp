/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenCL.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:13:45 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/24 11:03:57 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENCL_HPP
# define OPENCL_HPP

# include <OpenCL/cl.h>

struct OpenCL
{
	public :
		OpenCL(void);

		cl_device_id		device;
		cl_context			context;
		cl_command_queue	queue;

		cl_program			program_test;
		cl_kernel			kernel_test;

		cl_mem				buffer;

		void	init(void);

	private:
};

#endif