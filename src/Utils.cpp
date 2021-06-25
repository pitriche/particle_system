/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:14:54 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/24 13:37:02 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"
#include <iostream>	/* cerr, string */
#include <fstream>	/* ifstream */
#include <sstream>	/* ifstream */
#include <cstdlib>	/* exit */

namespace Utils
{
	void	error_quit(const std::string &str)
	{
		std::cerr << str << std::endl;
		exit(0);
	}

	std::string	read_file(const char *filename)
	{
		std::ifstream		fs;
		std::stringstream	ss;

		fs.open(filename);
		ss << fs.rdbuf();
		return (ss.str());
	}

	void		openCL_error_log(const OpenCL &cl, cl_int err_code)
	{
		char	buffer[512];

		if (err_code == -46)
			error_quit("Invalid Kernel name !");
		std::cerr << "Kernel compilation failed [" << err_code << "]" <<
			std::endl << "Compilation log:" << std::endl;
		clGetProgramBuildInfo(cl.program_test, cl.device,
			CL_PROGRAM_BUILD_LOG, 512, buffer, 0);
		std::cerr << buffer;
		exit(0);
	}

	void		openGL_error_log(unsigned int shader, int err_code,
				const char *filename)
	{
		char	buffer[512];

		std::cerr << "[" << filename << "] shader compilation failed: [" <<
		err_code << "/1]" << std::endl;
		glGetShaderInfoLog(shader, 512, NULL, buffer);
		std::cerr << "Compilation log:" << std::endl << buffer;
		exit(0);
	}
}
