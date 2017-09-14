#ifndef _RENDERER_WINDOWS_INITIALISE_VISITOR_H_
#define _RENDERER_WINDOWS_INITIALISE_VISITOR_H_

/* System Includes */

/* Local Project Includes */
#include "../../../scenemanagement/visitor.h"
#include "../../../math/vertex.h"
#include "../../../resources/resources.h"

namespace MagusEngine
{
	/*
		Name:  Renderer_Windows_Initialise_Visitor
		Type: Class
		Purpose: Implements a initialisation visitor specific to windows to create opengl content on the gpu
	*/
	class Renderer_Windows_Initialise_Visitor : public Visitor
	{
	public:
		/* 
			Default contstructor
		*/
		Renderer_Windows_Initialise_Visitor();

		/* Visitor Functions */
		bool Initialise(Renderer_Interface* lowlevelRenderer, Resources* resources);

		void PreVisit(SceneNode* sceneNode);
		void Visit(SceneNode* sceneNode);
		void PostVisit(SceneNode* sceneNode);
		
		void PreVisit(Component* component);
		void Visit(Component* component);
		void PostVisit(Component* component);

		void PreVisit(Graphic2D* graphic2D);
		void Visit(Graphic2D* graphic2D);
		void PostVisit(Graphic2D* graphic2D);

		void PreVisit(Rectangle* rectangle);
		void Visit(Rectangle* rectangle);
		void PostVisit(Rectangle* rectangle);

		void PreVisit(Line* line);
		void Visit(Line* line);
		void PostVisit(Line* line);

		void PreVisit(Text* text);
		void Visit(Text* text);
		void PostVisit(Text* text);

		/* Getters */
		Renderer_Interface* GetLowLevelRenderer();

	private:
		Renderer_Interface* _lowLevelRenderer;
		Resources*			_resources;
		Vertex _vertexBuildBuffer[1000];
		unsigned int _indicesBuildBuffer[4000];

		bool		_buildCritical;
	};
}

#endif
