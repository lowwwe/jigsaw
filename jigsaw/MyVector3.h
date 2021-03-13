#ifndef MYVECTOR3_HPP 
#define MYVECTOR3_HPP

const float  PI = 3.14159265358979f;

/// <summary>
/// your name here or no marks
/// don't edit anything here except comments
/// 

#include <iostream>
#include <SFML/Graphics.hpp>


class MyVector3
{
public:
	float x;
	float y;
	float z;

	MyVector3();
	~MyVector3();
	std::string toString();



	MyVector3(float x, float y, float z);
	MyVector3(sf::Vector3f t_sfVector);
	MyVector3(sf::Vector3i t_sfVector);
	MyVector3(sf::Vector2i t_sfVector);
	MyVector3(sf::Vector2u t_sfVector);
	MyVector3(sf::Vector2f t_sfVector);


	MyVector3 operator +(const MyVector3 t_right) const;
	MyVector3 operator -(const MyVector3 t_right) const;
	MyVector3 operator *(const float t_scalar) const;
	MyVector3 operator /(const float t_divisor) const;
	MyVector3 operator +=(const MyVector3 t_right);
	MyVector3 operator -=(const MyVector3 t_right);

	bool operator == (const MyVector3 t_right) const;
	bool operator != (const MyVector3 t_right) const;

	// negative of a vector 
	//MyVector3 operator -();  // this changes the vector
	MyVector3 operator -() const;
	//new methods for bouncing off sides of table in billiard game
	void reverseX(); // this negates the x element of the vector
	void reverseY();  // this negates the y element of the vector

	float length()const;
	float lengthSquared()const;
	float dot(const MyVector3 t_other) const;
	MyVector3 crossProduct(const MyVector3 t_other)const;
	float angleBetween(const MyVector3 t_other)const;  // answer in degrees
	MyVector3 unit() const;  // vector doesn't change
	void normalise(); // vector changes and will have length 1 
	MyVector3 projection(const MyVector3 t_onto)const;
	// projection onto the other vector so answer will parallel to other vector.
	MyVector3 rejection(const MyVector3 t_onto)const;

	// conversion code will be used in casts
	operator sf::Vector3i();// {2.4,-2.6,3.0} ->  {2,-3,3}
	operator sf::Vector3f();// {2.4,-2.6,3.0} ->  {2.4~,-2.6~, 3.0}
	operator sf::Vector2f(); // {2.4,-2.6,3.0} ->  {2.4~,-2.6~}
	operator sf::Vector2i();// {2.4,-2.6,3.0} ->  {2,-3}
	operator sf::Vector2u();// {2.4,-2.6,3.0} ->  {2,3}  pay attention to example

};



#endif // !MYVECTOR3_HPP