#include "matrix.h"

namespace MagusEngine
{
	Matrix2f::Matrix2f() { BuildIdentity(); };

	float Matrix2f::Get(int i, int j) { return m[i][j]; }
	void Matrix2f::Set(int i, int j, float v) { m[i][j] = v; }

	void Matrix2f::BuildIdentity()
	{
		m[0][0] = 1.0f;	m[0][1] = 0.0f;
		m[1][0] = 0.0f;	m[1][1] = 1.0f;
	}




	Matrix3f::Matrix3f() { BuildIdentity(); };

	float Matrix3f::Get(int i, int j) { return m[i][j]; }
	void Matrix3f::Set(int i, int j, float v) { m[i][j] = v; }

	void Matrix3f::BuildIdentity()
	{
		m[0][0] = 1.0f;	m[0][1] = 0.0f;	m[0][2] = 0.0f;
		m[1][0] = 0.0f;	m[1][1] = 1.0f;	m[1][2] = 0.0f;
		m[2][0] = 0.0f;	m[2][1] = 0.0f;	m[2][2] = 1.0f;
	}



	Matrix4f::Matrix4f() { BuildIdentity(); };

	float Matrix4f::Get(int i, int j) { return m[i][j]; }
	void Matrix4f::Set(int i, int j, float v) { m[i][j] = v; }



	float* Matrix4f::GetData() { return &m[0][0]; }

	void Matrix4f::BuildIdentity()
	{
		m[0][0] = 1.0f;	m[0][1] = 0.0f;	m[0][2] = 0.0f;	m[0][3] = 0.0f;
		m[1][0] = 0.0f;	m[1][1] = 1.0f;	m[1][2] = 0.0f;	m[1][3] = 0.0f;
		m[2][0] = 0.0f;	m[2][1] = 0.0f;	m[2][2] = 1.0f;	m[2][3] = 0.0f;
		m[3][0] = 0.0f;	m[3][1] = 0.0f;	m[3][2] = 0.0f;	m[3][3] = 1.0f;
	}

	void Matrix4f::BuildTranslation(float x, float y, float z)
	{
		m[0][0] = 1.0f;	m[0][1] = 0.0f;	m[0][2] = 0.0f;	m[0][3] = x;
		m[1][0] = 0.0f;	m[1][1] = 1.0f;	m[1][2] = 0.0f;	m[1][3] = y;
		m[2][0] = 0.0f;	m[2][1] = 0.0f;	m[2][2] = 1.0f;	m[2][3] = z;
		m[3][0] = 0.0f;	m[3][1] = 0.0f;	m[3][2] = 0.0f;	m[3][3] = 1.0f;
	}

	void Matrix4f::BuildTranslation(Vector3f* vec)
	{
		BuildTranslation(vec->x, vec->y, vec->z);
	}

	void Matrix4f::BuildRotation(float x, float y, float z)
	{
		float xRads = (x * (float)PI) / 180.0f;
		float yRads = (y * (float)PI) / 180.0f;
		float zRads = (z * (float)PI) / 180.0f;

		float cx = cosf(xRads);
		float sx = sinf(xRads);
		float cy = cosf(yRads);
		float sy = sinf(yRads);
		float cz = cosf(zRads);
		float sz = sinf(zRads);

		m[0][0] = cy * cz;	m[0][1] = (cz * sx * sy) - (cx * sz);	m[0][2] = (cx * cz * sy) + (sx * sz);	m[0][3] = 0.0f;
		m[1][0] = cy * sz;	m[1][1] = (cx * cz) + (sx * sy * sz);	m[1][2] = (cx * sy * sz) - (cz * sx);	m[1][3] = 0.0f;
		m[2][0] = -sy;		m[2][1] = cy * sx;						m[2][2] = cx * cy;						m[2][3] = 0.0f;
		m[3][0] = 0.0f;		m[3][1] = 0.0f;							m[3][2] = 0.0f;							m[3][3] = 1.0f;
	}

	void Matrix4f::BuildRotation(Vector3f* vec)
	{
		BuildRotation(vec->x, vec->y, vec->z);
	}

	void Matrix4f::BuildScale(float x, float y, float z)
	{
		m[0][0] = x;	m[0][1] = 0.0f;	m[0][2] = 0.0f;	m[0][3] = 0.0f;
		m[1][0] = 0.0f;	m[1][1] = y;	m[1][2] = 0.0f;	m[1][3] = 0.0f;
		m[2][0] = 0.0f;	m[2][1] = 0.0f;	m[2][2] = z;	m[2][3] = 0.0f;
		m[3][0] = 0.0f;	m[3][1] = 0.0f;	m[3][2] = 0.0f;	m[3][3] = 1.0f;
	}

	void Matrix4f::BuildScale(Vector3f* vec)
	{
		BuildScale(vec->x, vec->y, vec->z);
	}

	void Matrix4f::BuildOrthographic(float left, float right, float top, float bottom, float znear, float zfar)
	{
		float width = right - left;
		float height = top - bottom;
		float depth = zfar - znear;

		m[0][0] = 2.00f / width; 	m[0][1] = 0.0f;				m[0][2] = 0.0f;				m[0][3] = -(right + left) / width;
		m[1][0] = 0.0f;				m[1][1] = 2.0f / height;	m[1][2] = 0.0f;				m[1][3] = -(top + bottom) / height;
		m[2][0] = 0.0f;				m[2][1] = 0.0f;				m[2][2] = -2.0f / depth;	m[2][3] = -(zfar + znear) / depth;
		m[3][0] = 0.0f;				m[3][1] = 0.0f;				m[3][2] = 0.0f;				m[3][3] = 1.0f;
	}

	void Matrix4f::BuildPerspective(float fov, float ratio, float znear, float zfar)
	{
		const float zrange = znear - zfar;
		const float tanHalfFOV = tanf((fov * (PI / 180)) / 2.0);

		float scale = tan(fov * 0.5 * PI / 180) * znear;
		float r = ratio * scale;
		float l = -r;
		float t = scale;
		float b = -t;

		BuildFrustum(b, t, l, r, znear, zfar);
	}

	void Matrix4f::BuildFrustum(float l, float r, float t, float b, float n, float f)
	{
		m[0][0] = 2.0f * n / (r -  l);		m[0][1] = 0.0f;					m[0][2] = (r + l) / (r - l);		m[0][3] = 0.0f;
		m[1][0] = 0.0f;						m[1][1] = 2.0f * n / (t - b);	m[1][2] = (t + b) / (t - b);		m[1][3] = 0.0f;
		m[2][0] = 0.0f;						m[2][1] = 0.0f;					m[2][2] = -(f + n) / (f - n);		m[2][3] = -2.0f * f * n / (f - n);
		m[3][0] = 0.0f;						m[3][1] = 0.0f;					m[3][2] = -1.0f;					m[3][3] = 0.0f;
	}

	void Matrix4f::BuildScreenSpaceTransform(float halfwidth, float halfheight)
	{
		m[0][0] = halfwidth;	m[0][1] = 0.0f;			m[0][2] = 0.0f;		m[0][3] = halfwidth - 0.5f;
		m[1][0] = 0.0f;			m[1][1] = -halfheight;	m[1][2] = 0.0f;		m[1][3] = halfheight - 0.5f;
		m[2][0] = 0.0f;			m[2][1] = 0.0f;			m[2][2] = 1.0f;		m[2][3] = 0.0f;
		m[3][0] = 0.0f;			m[3][1] = 0.0f;			m[3][2] = 0.0f;		m[3][3] = 1.0f;
	}


	void Matrix4f::BuildLookAt(Vector3f eye, Vector3f target, Vector3f up)
	{
		Vector3f zAxis = Vector3f::Normalise(target - eye);
		Vector3f xAxis = Vector3f::Normalise(Vector3f::Cross(up, zAxis));
		Vector3f yAxis = Vector3f::Cross(zAxis, xAxis);


		m[0][0] = xAxis.x;			m[0][1] = yAxis.x;			m[0][2] = zAxis.x;				m[0][3] = 0.0f;
		m[1][0] = xAxis.y;			m[1][1] = yAxis.y;			m[1][2] = zAxis.y;				m[1][3] = 0.0f;
		m[2][0] = xAxis.z;			m[2][1] = yAxis.z;			m[2][2] = zAxis.z;				m[2][3] = 0.0f;
		m[3][0] = -xAxis.Dot(&eye);	m[3][1] = -yAxis.Dot(&eye);	m[3][2] = -zAxis.Dot(&eye);		m[3][3] = 1.0f;

		//Vector3f zAxis = Vector3f::Normalise(eye - target);
		//Vector3f xAxis = Vector3f::Normalise(Vector3f::Cross(up, zAxis));
		//Vector3f yAxis = Vector3f::Cross(zAxis, xAxis);


		//Matrix4f orientation;
		//orientation.m[0][0] = xAxis.x;	orientation.m[0][1] = yAxis.x;	orientation.m[0][2] = zAxis.x;	orientation.m[0][3] = 0.0f;
		//orientation.m[1][0] = xAxis.y;	orientation.m[1][1] = yAxis.y;	orientation.m[1][2] = zAxis.y;	orientation.m[1][3] = 0.0f;
		//orientation.m[2][0] = xAxis.z;	orientation.m[2][1] = yAxis.z;	orientation.m[2][2] = zAxis.z;	orientation.m[2][3] = 0.0f;
		//orientation.m[3][0] = 0.0f;		orientation.m[3][1] = 0.0f;		orientation.m[3][2] = 0.0f;		orientation.m[3][3] = 1.0f;


		//Matrix4f translation;
		//translation.m[0][0] = 1.0f;		translation.m[0][1] = 0.0f;		translation.m[0][2] = 0.0f;		translation.m[0][3] = 0.0f;
		//translation.m[1][0] = 0.0f;		translation.m[1][1] = 1.0f;		translation.m[1][2] = 0.0f;		translation.m[1][3] = 0.0f;
		//translation.m[2][0] = 0.0f;		translation.m[2][1] = 0.0f;		translation.m[2][2] = 1.0f;		translation.m[2][3] = 0.0f;
		//translation.m[3][0] = -eye.x;	translation.m[3][1] = -eye.y;	translation.m[3][2] = -eye.z;	translation.m[3][3] = 1.0f;

		//Matrix4f result = orientation * translation;

		//for (int i = 0; i < 4; i++)
		//	for (int j = 0; j < 4; j++)
		//		m[i][j] = result.m[i][j];

	}

	Matrix4f Matrix4f::operator*(const Matrix4f& b)
	{
		Matrix4f t = Matrix4f();
		
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				t.Set(i, j, m[i][0] * b.m[0][j] +
							m[i][1] * b.m[1][j] +
							m[i][2] * b.m[2][j] +
							m[i][3] * b.m[3][j]);
			}	
		}

		return t;
	}

	Vector4f Matrix4f::operator*(const Vector4f& b)
	{
		
		return Vector4f(
			(m[0][0] * b.x) + (m[0][1] * b.y) + (m[0][2] * b.z) + (m[0][3] * b.w),
			(m[1][0] * b.x) + (m[1][1] * b.y) + (m[1][2] * b.z) + (m[1][3] * b.w),
			(m[2][0] * b.x) + (m[2][1] * b.y) + (m[2][2] * b.z) + (m[2][3] * b.w),
			(m[3][0] * b.x) + (m[3][1] * b.y) + (m[3][2] * b.z) + (m[3][3] * b.w)		
		);
	}
}