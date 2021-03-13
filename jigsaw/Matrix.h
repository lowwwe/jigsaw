#ifndef MATRIX
#define MATRIX


#include "MyVector3.h"


struct MyMatrix
{
	float m11;
	float m12;
	float m13;
	float m21;
	float m22;
	float m23;
	float m31;
	float m32;
	float m33;

	MyMatrix();

	MyMatrix( float t_m11,
			float t_m12,
			float t_m13,
			float t_m21,
			float t_m22,
			float t_m23,
			float t_m31,
			float t_m32,
			float t_m33 );


	MyMatrix operator + (MyMatrix t_right);
	MyMatrix operator - (MyMatrix t_right);
	MyMatrix operator * (MyMatrix t_right);
	MyMatrix operator * (int t_scale);
	MyMatrix operator * (float t_scale);
	MyMatrix operator * (double t_scale);

	bool operator == (MyMatrix t_right);
	bool operator != (MyMatrix t_right);


	MyMatrix getTranspose() const;
	void transpose();

	float determinant();
	MyMatrix getInverse();

	static MyMatrix rotationClockwiseX(float t_angleDegrees);
	static MyMatrix rotationClockwiseY(float t_angleDegrees);
	static MyMatrix rotationClockwiseZ(float t_angleDegrees);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	MyMatrix(MyVector3 row1, MyVector3 row2, MyVector3 row3);
	MyVector3 row(const int t_row)const; // m11 , m12, m13
	MyVector3 column(const int t_column) const; // m11, m21, m31
	MyVector3 operator *(const MyVector3 t_vector)const;
	static MyMatrix translation(const MyVector3 t_displacement); // 2d translation make sure z=1
	static MyMatrix scale(const float t_scalingfactor);
};

#endif // !MATRIX