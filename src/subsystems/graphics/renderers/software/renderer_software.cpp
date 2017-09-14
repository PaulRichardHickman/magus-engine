#include "renderer_software.h"

namespace MagusEngine
{
	Renderer_Software::Renderer_Software(FrameworkConfig* config)
	{
		/* Allocate memory for vbos (KB)*/
		_vboMemory = (Vertex*)malloc(sizeof(Vertex) * config->sr_vbo_memorylimit );
		_vboMemoryLimit = config->sr_vbo_memorylimit;
		_vboMemoryHead = _vboMemory;

		/* Allocate memory for ibos (KB)*/
		_iboMemory = (unsigned int*)malloc(sizeof(unsigned int) * config->sr_ibo_memorylimit);
		_iboMemoryLimit = config->sr_ibo_memorylimit;
		_iboMemoryHead = _iboMemory;

		/* Allocate vbo buffer table */
		_vboMemoryBufferTable = (MemoryBuffer*)malloc(sizeof(MemoryBuffer) * (config->sr_vbo_limit));
		_vboMemoryBufferTableLimit = config->sr_vbo_limit;
		_vboMemoryBufferCount = 0;

		/* Allocate ibo buffer table */
		_iboMemoryBufferTable = (MemoryBuffer*)malloc(sizeof(MemoryBuffer) * (config->sr_ibo_limit));
		_iboMemoryBufferTableLimit = config->sr_ibo_limit;
		_iboMemoryBufferCount = 0;
	}

	bool Renderer_Software::InitialiseExtensions()
	{
		return true;
	}

	bool Renderer_Software::Initialise(void* system, int screenWidth, int screenHeight, float screenDepth, float screenNear, bool vsync)
	{
		/* Set class variables */
		_screenSizeWidth = screenWidth;
		_screenSizeHeight = screenHeight;
		_screenPixelDepth = screenDepth;

		/* Allocate data for front buffer */
		_framebuffer.Initialise(screenWidth, screenHeight, screenDepth);

		/* Initialise debug bitmap */
		_debugBitmap.Initialise(screenWidth, screenHeight);

		/* Initialise the scane buffer */
		_scanbuffer.Initialise(&_framebuffer);

		return true;
	}
	
	void Renderer_Software::Shutdown()
	{
	}

	void Renderer_Software::DrawRectangle(int x, int y, int width, int height)
	{
		
	}

	void Renderer_Software::BeginScene(float red, float green, float blue, float alpha)
	{
		_framebuffer.Clear(red, green, blue, alpha);

		return;
	}
	
	void Renderer_Software::EndScene()
	{
		
		_debugBitmap.Save((BYTE*)_framebuffer.GetData(), 32, 24, "C:\\Temp\\image.bmp");
		return;
	}
	
	void Renderer_Software::CheckError()
	{
	}

	/* Data Loading API */
	unsigned int Renderer_Software::GenerateVertexBuffer(Vertex* vertices, unsigned int vertexCount)
	{
		unsigned int vbohandle = 0;
		MemoryBuffer* vbo = &_vboMemoryBufferTable[_vboMemoryBufferCount];


		/* store start and end pointers to memory buffer */
		vbo->start = _vboMemoryHead;
		vbo->end = _vboMemoryHead + (sizeof(Vertex) * vertexCount);

		/* Copy data into vbo memory */
		memcpy_s(_vboMemoryHead, sizeof(Vertex) * vertexCount, vertices, sizeof(Vertex) * vertexCount);

		/* Move the head to next next available byte */
		_vboMemoryHead += (sizeof(Vertex) * vertexCount);

		/* Store vbo memory handle */
		vbohandle = _vboMemoryBufferCount;

		/* Increment the buffer count */
		_vboMemoryBufferCount++;

		return vbohandle;
	}

	unsigned int Renderer_Software::GenerateIndicesBuffer(unsigned int* indices, unsigned int indicesCount)
	{
		unsigned int ibohandle = 0;
		MemoryBuffer* ibo = &_iboMemoryBufferTable[_iboMemoryBufferCount];


		/* store start and end pointers to memory buffer */
		ibo->start = _iboMemoryHead;
		ibo->end = _iboMemoryHead + (sizeof(unsigned int) * indicesCount);

		/* Copy data into ibo memory */
		memcpy_s(_iboMemoryHead, sizeof(unsigned int) * indicesCount, indices, sizeof(unsigned int) * indicesCount);

		/* Move the head to next next available byte */
		_iboMemoryHead += (sizeof(unsigned int) * indicesCount);

		/* Store ibo memory handle */
		ibohandle = _iboMemoryBufferCount;

		/* Increment the buffer count */
		_iboMemoryBufferCount++;

		return ibohandle;
	}


	unsigned int Renderer_Software::DrawBuffers(VBO_Structure* bufferData)
	{

		/* Apply Vertex Functions */
		Matrix4f tempProjection = Matrix4f();
		tempProjection.BuildOrthographic(0.0f, 800.0f, 600.0f, 0.0f, 1.0f, -1.0f);

		Matrix4f mvp = tempProjection * (*_modelMatrix);

		/* Get vbo structure */
		MemoryBuffer* vboMemoryBuffer = &_vboMemoryBufferTable[bufferData->vertexhandle];

		Vertex* vertices = (Vertex*)vboMemoryBuffer->start;



		Vertex minYVert = Vertex(-100.0f, -100.0f, 0.0f).Transform(mvp);
		Vertex midYVert = Vertex(-100.0f, 100.0f, 0.0f).Transform(mvp);
		Vertex maxYVert = Vertex(100.0f, -100.0f, 0.0f).Transform(mvp);

		Vertex genMinYVert = vertices[0].Transform(mvp);
		Vertex genMidnYVert = vertices[1].Transform(mvp);
		Vertex genMaxYVert = vertices[2].Transform(mvp);

		//_scanbuffer.FillTriangle(minYVert, midYVert, maxYVert);
		_scanbuffer.FillTriangle(vertices[0].Transform(mvp), vertices[1].Transform(mvp), vertices[2].Transform(mvp));
		_scanbuffer.FillTriangle(vertices[1].Transform(mvp), vertices[2].Transform(mvp), vertices[3].Transform(mvp));


		//_scanbuffer.FillShape(100, 300);

		return 0;
	}

	void Renderer_Software::SetCurrentModelMatrix(Matrix4f* matrix)
	{
		_modelMatrix = matrix;
		return;
	}

	void Renderer_Software::SetMaterial(Material* material)
	{
		return;
	}

	void Renderer_Software::SetTexture(Texture* texture)
	{
		return;
	}

	/* Shader API */
	void Renderer_Software::CompileShaderObject(Shader* shader)
	{
		return;
	}

	void Renderer_Software::SetCurrentShader(Shader* shader)
	{
		return;
	}

	/* Texture API */
	void Renderer_Software::CreateTexture(Texture* texture)
	{

	}

	void Renderer_Software::SaveBitmap()
	{
		
	}


	Byte* Renderer_Software::GetFramebufferData()
	{
		return _framebuffer.GetData();
	}
}