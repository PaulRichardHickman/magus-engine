#ifndef _VERTEX_H_
#define _VERTEX_H_

/* Local Project Includes */
#include "vector.h"
#include "matrix.h"

typedef char Byte;

namespace MagusEngine
{
	class Vertex
	{
	public:
		Vertex();
		Vertex(float x, float y, float z, float r, float g, float b, float a);
		Vertex(Vector4f position, Vector4f color, Vector2f uv);

		Vector4f* GetPosition();
		Vector4f* GetColor();
		Vector2f* GetUV();

		float GetX();
		float GetY();
		float GetZ();
		float GetW();

		float GetR();
		float GetG();
		float GetB();
		float GetA();
		
		float GetU();
		float GetV();

		void SetX(float x);
		void SetY(float y);
		void SetZ(float x);
		void SetW(float y);

		void SetR(float r);
		void SetG(float g);
		void SetB(float b);
		void SetA(float a);
		
		void SetU(float u);
		void SetV(float v);

		float TriangleAreaTimesTwo(Vertex b, Vertex c);

		Vertex Transform(Matrix4f matrix);
		Vertex PrespectiveDivide();

	private:
		Vector4f _position;
		Vector4f _color;
		Vector2f _uv;
	};
}

#endif