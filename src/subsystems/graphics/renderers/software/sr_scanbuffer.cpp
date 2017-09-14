#include "sr_scanbuffer.h"

namespace MagusEngine
{
	
	SR_Scanbuffer::SR_Scanbuffer()
	{

	}

	void SR_Scanbuffer::Initialise(SR_Framebuffer* frame)
	{
		_frame = frame;

	}

	void SR_Scanbuffer::FillTriangle(Vertex v1, Vertex v2, Vertex v3, Texture* texture)
	{
		_currentTexture = texture;

		/* Convert vertices to screen space */
		Matrix4f screenSpace;
		screenSpace.BuildScreenSpaceTransform(400.0f, 300.0f);
		Vertex minY = v1.Transform(screenSpace).PrespectiveDivide();
		Vertex midY = v2.Transform(screenSpace).PrespectiveDivide();
		Vertex maxY = v3.Transform(screenSpace).PrespectiveDivide();

		if (maxY.GetY() < midY.GetY())
		{
			Vertex temp = maxY;
			maxY = midY;
			midY = temp;
		}

		if (midY.GetY() < minY.GetY())
		{
			Vertex temp = midY;
			midY = minY;
			minY = temp;
		}

		if (maxY.GetY() < midY.GetY())
		{
			Vertex temp = maxY;
			maxY = midY;
			midY = temp;
		}

		ScanTriangle(minY, midY, maxY, minY.TriangleAreaTimesTwo(maxY, midY) >= 0.0f);

	}

	void SR_Scanbuffer::ScanTriangle(Vertex minYVert, Vertex midYVert, Vertex maxYVert, bool side)
	{
		SR_Varier colorVarier = SR_Varier(&minYVert, &midYVert, &maxYVert);

		SR_Edge topToBottom =		SR_Edge(colorVarier, &minYVert, &maxYVert, 0);
		SR_Edge topToMiddle =		SR_Edge(colorVarier, &minYVert, &midYVert, 0);
		SR_Edge middleToBottom =	SR_Edge(colorVarier, &midYVert, &maxYVert, 1);


		ScanEdge(&colorVarier, &topToBottom, &topToMiddle, side);
		ScanEdge(&colorVarier, &topToBottom, &middleToBottom, side);
	}


	void SR_Scanbuffer::ScanEdge(SR_Varier* colorVarier, SR_Edge* e1, SR_Edge* e2, bool side)
	{
		SR_Edge* left = e1;
		SR_Edge* right = e2;

		if (side)
		{
			SR_Edge* temp = left;
			left = right;
			right = temp;
		}

		int yStart = (int)e2->GetYStart();
		int yEnd = (int)e2->GetYEnd();
		for (int x = yStart; x < yEnd; x++)
		{
			DrawScanLine(colorVarier, left, right, x);
			left->Step();
			right->Step();
		}
	}

	void SR_Scanbuffer::DrawScanLine(SR_Varier* colorVarier, SR_Edge* left, SR_Edge* right, int j)
	{
		int xMin = (int)ceil(left->GetX());
		int xMax = (int)ceil(right->GetX());
		float xPrestep = xMin - left->GetX();

		Vector2f uv = left->GetUV() + ((*colorVarier->GetUVXStep()) * xPrestep);

		Vector4f color = left->GetColor() + ((*colorVarier->GetColorXStep()) * xPrestep);

		for (int i = xMin; i < xMax; i++)
		{
			//_frame->DrawPixel(i, j, color.x, color.y, color.z, 1.0f);
			int srcX = (int)(uv.x * (_currentTexture->GetWidth() - 1) + 0.5f);
			int srcY = (int)(uv.y * (_currentTexture->GetHeight() - 1) + 0.5f);

			_frame->CopyPixel(i, j, srcX, srcY, _currentTexture);

			//color = color + (*colorVarier->GetColorXStep());
			uv = uv + (*colorVarier->GetUVXStep());
		}
	}
}