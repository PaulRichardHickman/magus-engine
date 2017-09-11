#include "line.h"

namespace MagusEngine
{
	Line::Line()
	{
		_x1 = 0.0f;
		_y1 = 0.0f;
		_x2 = 0.0f;
		_y2 = 0.0f;
	}

	Line::Line(float x1, float y1, float x2, float y2)
	{
		_x1 = x1;
		_y1 = y1;
		_x2 = x2;
		_y2 = y2;
	}

	/* Drawable Functions */
	int Line::Build(Vertex* buffer)
	{
		/* calculate normal */
		Vector2f delta = Vector2f(_x2 - _x1, _y2 - _y1);

		Vector2f normal;
		
		/* point 1 */
		normal = Vector2f(-delta.GetY(), delta.GetX());
		normal.Normalise();
		buffer[0].SetX(_x1 + (normal.GetX() * _width));
		buffer[0].SetY(_y1 + (normal.GetY() * _width));

		normal = Vector2f(delta.GetY(), -delta.GetX());
		normal.Normalise();
		buffer[1].SetX(_x1 + (normal.GetX() * _width));
		buffer[1].SetY(_y1 + (normal.GetY() * _width));

		normal = Vector2f(-delta.GetY(), delta.GetX());
		normal.Normalise();
		buffer[2].SetX(_x2 + (normal.GetX() * _width));
		buffer[2].SetY(_y2 + (normal.GetY() * _width));

		normal = Vector2f(delta.GetY(), -delta.GetX());
		normal.Normalise();
		buffer[3].SetX(_x2 + (normal.GetX() * _width));
		buffer[3].SetY(_y2 + (normal.GetY() * _width));

		return 4;

	}

	/* Getters */
	float Line::GetX1() { return _x1; }
	float Line::GetY1() { return _y1; }
	float Line::GetX2() { return _x2; }
	float Line::GetY2() { return _y2; }
	float Line::GetWidth() { return _width; }

	/* Setters */
	void Line::SetX1(float x) { _x1 = x; }
	void Line::SetY1(float y) { _y1 = y; }
	void Line::SetX2(float x) { _x2 = x; }
	void Line::SetY2(float y) { _y2 = y; }
	void Line::SetWidth(float width) { _width = width; }

}