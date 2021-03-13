#include "Matrix.h"





/// <summary>
/// default constructor: set all values to zero
/// </summary>
/// <returns> creates the null matrix</returns>
MyMatrix::MyMatrix()
{
	m11 = 0.0f;
	m12 = 0.0f;
	m13 = 0.0f;
	m21 = 0.0f;
	m22 = 0.0f;
	m23 = 0.0f;
	m31 = 0.0f;
	m32 = 0.0f;
	m33 = 0.0f;
}

/// <summary>
/// Matrix constructor
/// </summary>
/// <param name="t_m11">value for m11</param>
/// <param name="t_m12">value for m12</param>
/// <param name="t_m13">value for m13</param>
/// <param name="t_m21">value for second row fisrt element</param>
/// <param name="t_m22">value for second row second element</param>
/// <param name="t_m23">value for second row third element</param>
/// <param name="t_m31">value for m31</param>
/// <param name="t_m32">value for m32</param>
/// <param name="t_m33">value for m33</param>
/// <returns>matrix with the nine values passed in</returns>
MyMatrix::MyMatrix(
	float t_m11, 
	float t_m12, 
	float t_m13,	
	float t_m21, 
	float t_m22, 
	float t_m23, 
	float t_m31, 
	float t_m32, 
	float t_m33)
{
	m11 = t_m11;
	m12 = t_m12;
	m13 = t_m13;
	m21 = t_m21;
	m22 = t_m22;
	m23 = t_m23;
	m31 = t_m31;
	m32 = t_m32;
	m33 = t_m33;
}


/// <summary>
/// Addition overload of plus operator
/// </summary>
/// <param name="t_right">matrix on the right</param>
/// <returns>sum of both matrix</returns>
MyMatrix MyMatrix::operator+(MyMatrix t_right)
{
	MyMatrix result;
	result.m11 = m11 + t_right.m11;
	result.m12 = m12 + t_right.m12;
	result.m13 = m13 + t_right.m13;
	
	result.m21 = m21 + t_right.m21;
	result.m22 = m22 + t_right.m22;
	result.m23 = m23 + t_right.m23;

	result.m31 = m31 + t_right.m31;
	result.m32 = m32 + t_right.m32;
	result.m33 = m33 + t_right.m33;


	return result;
}

/// <summary>
/// subtraction
/// </summary>
/// <param name="t_right"></param>
/// <returns></returns>
MyMatrix MyMatrix::operator-(MyMatrix t_right)
{
	MyMatrix result;
	result.m11 = m11 - t_right.m11;
	result.m12 = m12 - t_right.m12;
	result.m13 = m13 - t_right.m13;

	result.m21 = m21 - t_right.m21;
	result.m22 = m22 - t_right.m22;
	result.m23 = m23 - t_right.m23;

	result.m31 = m31 - t_right.m31;
	result.m32 = m32 - t_right.m32;
	result.m33 = m33 - t_right.m33;


	return result;
}

MyMatrix MyMatrix::operator*(MyMatrix t_right)
{
	MyMatrix result;
	result.m11 = (m11 * t_right.m11) + (m12 * t_right.m21) + (m13 * t_right.m31);
	result.m12 = (m11 * t_right.m12) + (m12 * t_right.m22) + (m13 * t_right.m32);
	result.m13 = (m11 * t_right.m13) + (m12 * t_right.m23) + (m13 * t_right.m33);

	result.m21 = (m21 * t_right.m11) + (m22 * t_right.m21) + (m23 * t_right.m31);
	result.m22 = (m21 * t_right.m12) + (m22 * t_right.m22) + (m23 * t_right.m32);
	result.m23 = (m21 * t_right.m13) + (m22 * t_right.m23) + (m23 * t_right.m33);

	result.m31 = (m31 * t_right.m11) + (m32 * t_right.m21) + (m33 * t_right.m31);
	result.m32 = (m31 * t_right.m12) + (m32 * t_right.m22) + (m33 * t_right.m32);
	result.m33 = (m31 * t_right.m13) + (m32 * t_right.m23) + (m33 * t_right.m33);
	return result;
}

MyMatrix MyMatrix::operator*(int t_scale)
{
	float floatValue = static_cast<float>(t_scale);
	MyMatrix result = this->operator*(floatValue);
	return result;	
}

MyMatrix MyMatrix::operator*(float t_scale)
{
	MyMatrix result{
		m11 * t_scale,
		m12 * t_scale,
		m13 * t_scale,
		m21 * t_scale,
		m22 * t_scale,
		m23 * t_scale,
		m31 * t_scale,
		m32 * t_scale,
		m33 * t_scale };
	return result;
}

MyMatrix MyMatrix::operator*(double t_scale)
{
	float floatValue = static_cast<float>(t_scale);
	MyMatrix result = this->operator*(floatValue);
	return result;
}

bool MyMatrix::operator==(MyMatrix t_right)
{
	bool result{ false };
	result = (m11 == t_right.m11
		&& m12 == t_right.m12
		&& m13 == t_right.m13
		&& m21 == t_right.m21
		&& m22 == t_right.m22
		&& m23 == t_right.m23
		&& m31 == t_right.m31
		&& m32 == t_right.m32
		&& m33 == t_right.m33);
	return result;
}

bool MyMatrix::operator!=(MyMatrix t_right)
{
	bool result{ false };
	result = !(this->operator==(t_right));
	return result;
}



MyMatrix MyMatrix::getTranspose() const
{
	MyMatrix result;
	result.m11 = m11;
	result.m12 = m21;
	result.m31 = m13;
	result.m21 = m12;
	result.m22 = m22;
	result.m23 = m32;
	result.m13 = m31;
	result.m32 = m23;
	result.m33 = m33;

	return result;
}

void MyMatrix::transpose()
{
	float swapValue = 0.0f;
	swapValue = m12;
	m12 = m21;
	m21 = swapValue;
	swapValue = m13;
	m13 = m31;
	m31 = swapValue;
	swapValue = m23;
	m23 = m32;
	m32 = swapValue;
}

float MyMatrix::determinant()
{
	float result = 0;
	result = m11 * m22 * m33
		- m11 * m32 * m23
		+ m21 * m32 * m13
		- m31 * m22 * m13
		+ m31 * m12 * m23
		- m21 * m12 * m33;
	return result;
}

MyMatrix MyMatrix::getInverse()
{
	MyMatrix result;
	float det = 0;
	det = determinant();
	if (det == 0)
	{
		return MyMatrix{};
	}
	else
	{
		float scale = 1 / det;

		result.m11 = scale * (m22 * m33 - m23 * m32);
		result.m12 = scale * (m13 * m32 - m12 * m33);
		result.m13 = scale * (m12 * m23 - m13 * m22);

		result.m21 = scale * (m23 * m31 - m21 * m33);
		result.m22 = scale * (m11 * m33 - m13 * m31);
		result.m23 = scale * (m13 * m21 - m11 * m23);

		result.m31 = scale * (m21 * m32 - m22 * m31);
		result.m32 = scale * (m12 * m31 - m11 * m32);
		result.m33 = scale * (m11 * m22 - m12 * m21);

		return result;
	}
}

MyMatrix MyMatrix::rotationClockwiseX(float t_angleDegrees)
{
	float angleRadians = t_angleDegrees * PI / 180.0f;
	return MyMatrix{
		1.0 , 0.0f , 0.0f,
		0.0f ,std::cosf(angleRadians) ,std::sinf(angleRadians),
		0.0f , -std::sinf(angleRadians), std::cosf(angleRadians) };
}

MyMatrix MyMatrix::rotationClockwiseY(float t_angleDegrees)
{
	float angleRadians = t_angleDegrees * PI / 180.0f;
	return MyMatrix{
		std::cosf(angleRadians), 0.0f, -std::sinf(angleRadians),
		0.0f ,1.0f ,0.0f,
		std::sinf(angleRadians), 0.0f, std::cosf(angleRadians)
	};
	return MyMatrix();
}

MyMatrix MyMatrix::rotationClockwiseZ(float t_angleDegrees)
{
	float angleRadians = t_angleDegrees * PI / 180.0f;
	return MyMatrix{
		std::cosf(angleRadians), std::sinf(angleRadians), 0.0f,
		-std::sinf(angleRadians), std::cosf(angleRadians), 0.0f,
		0.0f, 0.0f, 1.0f };
}

MyMatrix::MyMatrix(MyVector3 t_row1, MyVector3 t_row2, MyVector3 t_row3):
	m11{ t_row1.x },
	m12{ t_row1.y },
	m13{ t_row1.z },
	m21{ t_row2.x },
	m22{ t_row2.y },
	m23{ t_row2.z },
	m31{ t_row3.x },
	m32{ t_row3.y },
	m33{ t_row3.z }
{
	
}

MyVector3 MyMatrix::row(const int t_row) const
{
	switch (t_row)
	{
	case 0:
		return MyVector3{ m11, m12, m13 };
	case 1:
		return MyVector3{ m21, m22, m23 };
	case 2:
		return MyVector3{ m31, m32, m33 };
	}
	return MyVector3{}; // shouldn't get here learn to count from zero
}

MyVector3 MyMatrix::column(const int t_column) const
{
	switch (t_column)
	{
	case 0:
		return MyVector3{ m11, m21, m31 };
	case 1:
		return MyVector3{ m12, m22, m32 };
	case 2:
		return MyVector3{ m13, m23, m33 };
	}
	return MyVector3();// shouldn't get here learn to count from zero
}

MyVector3 MyMatrix::operator*(const MyVector3 t_vector) const
{
	// need to 	edit this
	return MyVector3{ row(0).dot(t_vector), row(1).dot(t_vector), row(2).dot(t_vector) };
	return MyVector3();
}

MyMatrix MyMatrix::translation(const MyVector3 t_displacement)
{
	// make sure z == 1
	return MyMatrix{
		1.0f , 0.0f , t_displacement.x,
		0.0f , 1.0f , t_displacement.y,
		0.0f , 0.0f , 1.0f };
	
}

MyMatrix MyMatrix::scale(const float t_scalingfactor)
{
	return MyMatrix{
		t_scalingfactor, 0.0f , 0.0f,
		0.0f ,t_scalingfactor, 0.0f,
		0.0f , 0.0f ,t_scalingfactor };
}
