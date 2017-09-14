#ifndef _RENDERER_INTERFACE_H_
#define _RENDERER_INTERFACE_H_

/* System Include */

/* Local Project Includes */
#include "../../math/matrix.h"
#include "../../math/vertex.h"
#include "../../resources/texture.h"
#include "../../resources/material.h"
#include "renderer_structures.h"

namespace MagusEngine
{
	class Shader;

	class Renderer_Interface
	{
	public:
		virtual bool Initialise(void*, int, int, float, float, bool) = 0;

		virtual void Shutdown() = 0;

		virtual void BeginScene(float, float, float, float) = 0;
		virtual void EndScene() = 0;

		virtual void CheckError() = 0;

		virtual void DrawRectangle(int x, int y, int width, int height) = 0;

		/* Data Loading API*/
		virtual unsigned int GenerateVertexBuffer(Vertex* vertices, unsigned int vertexCount) = 0;
		virtual unsigned int GenerateIndicesBuffer(unsigned int* indices, unsigned int indicesCount) = 0;
		virtual unsigned int DrawBuffers(VBO_Structure* bufferData) = 0;
		virtual void SetCurrentModelMatrix(Matrix4f* matrix) = 0;
		virtual void SetMaterial(Material* material) = 0;
		virtual void SetTexture(Texture* texture) = 0;

		/* Shader API */
		virtual void CompileShaderObject(Shader* shader) = 0;
		virtual void SetCurrentShader(Shader* shader) = 0;

		/* Texture API */
		virtual void CreateTexture(Texture* texture) = 0;

		/* Common Getters */
		Shader* GetShader();
		Material* GetMaterial();
		Texture* GetTexture();

	public:
		void* _windowSystemHandle;

	protected:
		Shader* _CurrentShader;
		Material* _CurrentMaterial;
		Texture * _CurrentTexture;
	};
}

#endif