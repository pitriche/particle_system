/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:14:54 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/23 10:53:46 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"
#include <iostream>	/* cerr, cin */
#include <cstdlib>	/* exit, malloc */
#include <fcntl.h>	/* open */
#include <unistd.h>	/* read, close, lseek */

namespace Utils
{
	void	error_quit(const std::string &str)
	{
		std::cerr << str << std::endl;
		exit(0);
	}

	char	*read_file(const char *filename)
	{
		char	*content;
		int		fd;
		size_t	file_size;

		fd = open(filename, 'r');
		if (fd < 0)
			error_quit("Cannot open file [" + std::string(filename) + "]");

		/* get file size */
		file_size = (size_t)lseek(fd, 0, SEEK_END);
		lseek(fd, 0, SEEK_SET);
		
		content = (char *)malloc(file_size + 1);
		read(fd, content, file_size);
		content[file_size] = 0;
		close(fd);
		return (content);
	}
}
