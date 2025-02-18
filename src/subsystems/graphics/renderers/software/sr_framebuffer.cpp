#include "sr_framebuffer.h"

namespace MagusEngine
{
	SR_Framebuffer::SR_Framebuffer()
	{

	}

	bool SR_Framebuffer::Initialise(int width, int height, float depth)
	{
		_width = width;
		_height = height;

		_data = new Byte[width * height * 4];

		return true;
	}

	void SR_Framebuffer::Clear(float red, float green, float blue, float alpha)
	{
		int r = 0;
		int c = 0;

		Byte* bytePtr = &_data[0];

		/* Set the color of each pixel in the framebuffer */
		for (r = 0; r < _width; r++)
		{
			for (c = 0; c < _height; c++)
			{
				// BGRA format
				bytePtr[0]	= (Byte)(255.0f * blue);
				bytePtr[1]	= (Byte)(255.0f * green);
				bytePtr[2]	= (Byte)(255.0f * red);
				bytePtr[3]	= (Byte)(255.0f * alpha);

				bytePtr += 4;
			}
		}
	}

	void SR_Framebuffer::DrawPixel(int x, int y, float red, float green, float blue, float alpha)
	{ 
		unsigned int index = (x + y * _width) * 4;
		_data[index + 0] = (Byte)(255.0f * blue);
		_data[index + 1] = (Byte)(255.0f * green);
		_data[index + 2] = (Byte)(255.0f * red);
		_data[index + 3] = (Byte)(255.0f * alpha);
	}

	void SR_Framebuffer::CopyPixel(int destx, int desty, float srcx, float srcy, Texture* texture)
	{
		unsigned int destIndex = (unsigned int)(destx + desty * _width) * 4;
		unsigned int srcIndex = (unsigned int)(srcx + srcy * texture->GetWidth()) * 4;
		_data[destIndex + 0] = *(texture->GetData() + (srcIndex));
		_data[destIndex + 1] = *(texture->GetData() + (srcIndex + 1));
		_data[destIndex + 2] = *(texture->GetData() + (srcIndex + 2));
		_data[destIndex + 3] = *(texture->GetData() + (srcIndex + 3));
	}

	int SR_Framebuffer::GetWidth()
	{
		return _width;
	}

	int SR_Framebuffer::GetHeight()
	{
		return _height;
	}

	Byte* SR_Framebuffer::GetData()
	{
		return _data;
	}
}