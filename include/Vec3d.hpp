/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec3d.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:13:45 by pitriche          #+#    #+#             */
/*   Updated: 2021/04/01 17:33:13 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3D_HPP
# define VEC3D_HPP

# include <iostream>
# include <cmath>

template<typename T>
class Vec3d
{
	public :
		T	x;
		T	y;
		T	z;

		Vec3d<T>(void) { }
		Vec3d<T>(T x_, T y_, T z_) : x(x_), y(y_), z(z_) { }
		Vec3d<T>(const Vec3d &src) { *this = src; }
		virtual ~Vec3d<T>(void) { }

		void		normalize(void)
		{
			T	norm;

			norm = sqrt(this->x * this->x + this->y * this->y + this->z *
				this->z);
			this->x /= norm;
			this->y /= norm;
			this->z /= norm;
		}

		Vec3d<T>	&operator=(const Vec3d<T> &rhs)
		{
			this->x = rhs.x;
			this->y = rhs.y;
			this->z = rhs.z;
			return (*this);
		}

		/*
		** Vector addition
		*/
		Vec3d<T>	operator+(const Vec3d<T> &rhs) const
		{
			return (Vec3d<T>(this->x + rhs.x, this->y + rhs.y,
				this->z + rhs.z));
		}

		/*
		** Vector substraction
		*/
		Vec3d<T>	operator-(const Vec3d<T> &rhs) const
		{
			return (Vec3d<T>(this->x - rhs.x, this->y - rhs.y,
				this->z - rhs.z));
		}

		/*
		** Dot product
		*/
		T			operator*(const Vec3d<T> &rhs) const
		{ return (this->x * rhs.x + this->y * rhs.y + this->z * rhs.z); }

		/*
		** Scaling
		*/
		Vec3d<T>	operator*(T rhs) const
		{ return (Vec3d<T>(this->x * rhs, this->y * rhs, this->z * rhs)); }

		/*
		** Scaling
		*/
		Vec3d<T>	operator/(T rhs) const
		{ return (Vec3d<T>(this->x / rhs, this->y / rhs, this->z / rhs)); }

		/*
		** XYZ acces with index: x = vec[0], y = vec[1], z = vec[2] 
		*/
		T			&operator[](int i)
		{
			switch (i)
			{
				case 0:
					return (this->x);
				case 1:
					return (this->y);
				case 2:
					return (this->z);
				default:
					throw std::out_of_range("Invalid Index");
			}
		}

	protected:
	private:
};

template<typename T> 
std::ostream	&operator<<(std::ostream &lhs, const Vec3d<T> &vec)
{
	return (lhs << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]");
}

#endif
