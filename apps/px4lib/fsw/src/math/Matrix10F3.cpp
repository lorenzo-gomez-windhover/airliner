#include "math/Matrix10F3.hpp"
#include <math.h>

using namespace math;


Matrix10F3::Matrix10F3(Vector3F m0, Vector3F m1, Vector3F m2, Vector3F m3, Vector3F m4, Vector3F m5, Vector3F m6, Vector3F m7, Vector3F m8, Vector3F m9) :
	data{m0, m1, m2, m3, m4, m5, m6, m7, m8, m9},
	nan{NAN,NAN,NAN}
{
};


Matrix10F3::Matrix10F3() :
	data{
		{0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0}
	},
    nan{NAN,NAN,NAN}
{
};


Matrix10F3::~Matrix10F3()
{
};


Vector3F& Matrix10F3::operator [] (uint32 i)
{
	if(i >= 10)
	{
		return nan;
	}
	else
	{
		return data[i];
	}
};


Vector3F Matrix10F3::operator [] (uint32 i) const
{
	if(i >= 10)
	{
		return nan;
	}
	else
	{
		return data[i];
	}
};


Matrix3F10 Matrix10F3::Transpose(void)
{
	Matrix3F10 res;

	for(int i = 0; i < ROWS; i++)
	{
		for(int j = 0; j < COLS; j++)
		{
			res[j][i] = data[i][j];
		}
	}

	return res;
}


Matrix10F3 Matrix10F3::Identity() {
    Matrix10F3 matOut(
    		{1.0f, 0.0f, 0.0f},
    		{0.0f, 1.0f, 0.0f},
    		{0.0f, 0.0f, 1.0f},
			{0.0, 0.0, 0.0},
			{0.0, 0.0, 0.0},
			{0.0, 0.0, 0.0},
			{0.0, 0.0, 0.0},
			{0.0, 0.0, 0.0},
			{0.0, 0.0, 0.0},
			{0.0, 0.0, 0.0});

    return matOut;
}


void Matrix10F3::Zero(void)
{
	for(int i = 0; i < ROWS; i++)
	{
    	for(int j = 0; j < COLS; j++)
		{
			data[i][j] = 0.0f;
		}
	}
}


// overload * operator to provide a matrix product
Matrix10F3 Matrix10F3::operator*(const Matrix10F3 &matIn)
{
    Matrix10F3 matOut;
    float value = 0.0f;

    // TODO: verify correct
    for(int i = 0; i < ROWS; i++)
    {
    	for(int j = 0; j < COLS; j++)
		{

    		for(int k = 0; k < ROWS; k++)
			{
    			value += data[i][j] * matIn[j][k];
			}

    		matOut[i][j] = value;
    		value = 0.0f;
		}
    }

    return matOut;
}

// overload * operator to provide a matrix product
Matrix10F3 Matrix10F3::operator*(const Matrix3F3 &matIn)
{
    Matrix10F3 matOut;
    matOut.Zero();

    // TODO: verify correct
    for(int i = 0; i < ROWS; i++)
    {
    	for(int j = 0; j < COLS; j++)
		{

    		for(int k = 0; k < 3; k++)
			{
    			matOut[i][j] += data[i][j] * matIn[j][k];
			}
		}
    }

    return matOut;
}

// overload * operator to provide a matrix product
Matrix10F10 Matrix10F3::operator*(const Matrix3F10 &matIn)
{
    Matrix10F10 matOut;
    matOut.Zero();
    //matOut.Print();

    // TODO: verify correct
    for(int i = 0; i < ROWS; i++)
    {
    	for(int k = 0; k < 10; k++)
		{

    		for(int j = 0; j < 3; j++)
			{
    			matOut[i][k] += data[i][j] * matIn[j][k];
			}
		}
    }

    return matOut;
}


// overload * operator to provide a matrix vector product
Vector3F Matrix10F3::operator*(const Vector3F &vecIn)
{
    Vector3F vecOut;
    float value = 0.0f;

    // TODO: verify correct
    for(int i = 0; i < ROWS; i++)
    {
    	for(int j = 0; j < COLS; j++)
		{
    		value += data[i][j]*vecIn[j];

    		vecOut[i] = value;
    		value = 0.0f;
		}
    }

    return vecOut;
}


Matrix10F3 Matrix10F3::operator*(const float &scalar)
{
    Matrix10F3 matOut;

    // TODO: verify correct
    for(int i = 0; i < ROWS; i++)
    {
    	for(int j = 0; j < COLS; j++)
		{
    		matOut[j][i] = scalar*data[j][i];
		}
    }

    return matOut;
}


Matrix10F3 Matrix10F3::operator+(const Matrix10F3 &matIn) const
{
    Matrix10F3 matOut;

    // TODO: verify correct
	for(int i = 0; i < ROWS; i++)
	{
		for(int j = 0; j < COLS; j++)
		{
			matOut[j][i] = data[j][i] + matIn[j][i];
		}
	}

    return matOut;
}


//Matrix10F3 Matrix10F3::RotationMatrix(Matrix10F3::Rotation_t boardRotation)
//{
//	Matrix10F3 matrix;
//
//	float roll  = M_DEG_TO_RAD_F * (float)Matrix10F3::RotLookup[boardRotation].roll;
//	float pitch = M_DEG_TO_RAD_F * (float)Matrix10F3::RotLookup[boardRotation].pitch;
//	float yaw   = M_DEG_TO_RAD_F * (float)Matrix10F3::RotLookup[boardRotation].yaw;
//
//	return Matrix10F3::FromEuler(roll, pitch, yaw);
//}
//
//
//
//Matrix10F3 Matrix10F3::FromEuler(float roll, float pitch, float yaw)
//{
//	Matrix10F3 matrix;
//
//	float cp = cosf(pitch);
//	float sp = sinf(pitch);
//	float cr = cosf(roll);
//	float sr = sinf(roll);
//	float cy = cosf(yaw);
//	float sy = sinf(yaw);
//
//	matrix[0][0] = cp * cy;
//	matrix[0][1] = (sr * sp * cy) - (cr * sy);
//	matrix[0][2] = (cr * sp * cy) + (sr * sy);
//	matrix[1][0] = cp * sy;
//	matrix[1][1] = (sr * sp * sy) + (cr * cy);
//	matrix[1][2] = (cr * sp * sy) - (sr * cy);
//	matrix[2][0] = -sp;
//	matrix[2][1] = sr * cp;
//	matrix[2][2] = cr * cp;
//
//	return matrix;
//}
//
//
//
//Vector3F Matrix10F3::ToEuler(void) const
//{
//	Vector3F euler;
//	euler[1] = asinf(-data[2][0]);
//
//	if (fabsf(euler[1] - M_PI_2) < 1.0e-3f) {
//		euler[0] = 0.0f;
//		euler[2] = atan2f(data[1][2] - data[0][1], data[0][2] + data[1][1]) + euler[0];
//
//	} else if (fabsf(euler[1] + M_PI_2) < 1.0e-3f) {
//		euler[0] = 0.0f;
//		euler[2] = atan2f(data[1][2] - data[0][1], data[0][2] + data[1][1]) - euler[0];
//
//	} else {
//		euler[0] = atan2f(data[2][1], data[2][2]);
//		euler[2] = atan2f(data[1][0], data[0][0]);
//	}
//
//	return euler;
//}
