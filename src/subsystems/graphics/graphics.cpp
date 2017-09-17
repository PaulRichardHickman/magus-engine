#include "graphics.h"

#ifdef _WIN32
#include "renderers/windows/graphics_blender.h"
#include "renderers/windows/renderer_windows_opengl.h"
#else
#include "renderers/linux/graphics_blender.h"
#include "renderers/linux/renderer_linux_opengl.h"
#endif

#include "renderers/software/renderer_software_initialise_visitor.h"
#include "renderers/software/renderer_software_render_visitor.h"
#include "renderers/software/renderer_software.h"

namespace MagusEngine
{
	Graphics::Graphics()
	{
		_os = 0;
	}

	bool Graphics::Initialise(OS_Interface* os, Resources* resources, FrameworkConfig* config, int maxSceneCount)
	{
		_os = os;
		_resources = resources;
		_config = config;

		//_softwareRendererThread = std::thread(&Graphics::SoftwareRender, this);

		_rootScene.Initialise("Root Node", maxSceneCount);

		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//glfwSetErrorCallback(OS::ErrorCallback);

		_window = glfwCreateWindow(_config->width, _config->height, _config->title, NULL, NULL);
		if (_window == NULL)
		{
			printf("Failed to create GLFW window");
			glfwTerminate();
			return false;
		}
		glfwMakeContextCurrent(_window);
		//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


		/* Low level Hardware renderer, provided by the OS */
		_lowLevelHardwareRenderer = os->GetLowLevelRenderer();
		/* Once windows is ready we can initilase the low level renderer */
		_lowLevelHardwareRenderer->Initialise(this, _config->width, _config->height, 1000.0f, -1.0f, false);

		_lowLevelSoftwareRenderer = new Renderer_Software(_config);
		_lowLevelSoftwareRenderer->Initialise(os, _config->width, _config->height, 0, 10000, false);

		_projectionMatrix.BuildOrthographic(0.0f, (float)config->width, (float)config->height, 0.0f, 1.0f, -1.0f);

		return true;
	}


	bool Graphics::Shutdown()
	{
		_os = 0;
		_lowLevelHardwareRenderer = 0;
		_lowLevelSoftwareRenderer = 0;

		return true;
	}

	void Graphics::AddScene(SceneNode* sceneNode)
	{
		_rootScene.AddChild(sceneNode);
	}


	SceneNode* Graphics::GetRootSceneNode() { return &_rootScene; }

	bool Graphics::InitialiseFrame()
	{
		int t = 0;
		/* retrieve hardware path visitors */
		_hardwareInitialiseVisitor = _os->GetLowLevelRendererInitialisationVisitor();
		
		printf("INIT %d\n", t); t++;
		_hardwareInitialiseVisitor->Initialise(_lowLevelHardwareRenderer, _resources);
		
		printf("INIT %d\n", t); t++;
		_hardwareRenderVisitor = _os->GetLowLevelRendererRenderVisitor();
		
		printf("INIT %d\n", t); t++;
		_hardwareRenderVisitor->Initialise(_lowLevelHardwareRenderer, _resources);
		
		printf("INIT %d\n", t); t++;
		/* Initialise software path visitors */
		_softwareInitialiseVisitor = new Renderer_Software_Initialise_Visitor((Renderer_Software*)_lowLevelSoftwareRenderer);
		
		printf("INIT %d\n", t); t++;
		_softwareInitialiseVisitor->Initialise(_lowLevelSoftwareRenderer, _resources);
		
		printf("INIT %d\n", t); t++;

		_softwareRenderVisitor = new Renderer_Software_Render_Visitor();
		
		printf("INIT %d\n", t); t++;
		_softwareRenderVisitor->Initialise(_lowLevelSoftwareRenderer, _resources);

		printf("INIT %d\n", t); t++;
		
		/* Set the Projection Matrix for both renderers */
		_lowLevelHardwareRenderer->SetCurrentProjectionMatrix(&_projectionMatrix);
		printf("INIT %d\n", t); t++;
		_lowLevelSoftwareRenderer->SetCurrentProjectionMatrix(&_projectionMatrix);
		printf("INIT %d\n", t); t++;

		_graphicsBlender = new Graphics_Blender();
		printf("INIT %d\n", t); t++;
		_graphicsBlender->Initialise(_lowLevelHardwareRenderer, _lowLevelSoftwareRenderer, _config->width, _config->height);
		printf("INIT %d\n", t); t++;

		_rootScene.Accept(_hardwareInitialiseVisitor);

		printf("INIT %d\n", t); t++;
		_rootScene.Accept(_softwareInitialiseVisitor);
		printf("INIT %d\n", t); t++;

		return true;
	}

	bool Graphics::Frame()
	{
		bool result;

		// Render the graphics scene.
		result = Render();
		if (!result)
		{
			return false;
		}


		glfwSwapBuffers(_window);
		glfwPollEvents();

		return (bool)glfwWindowShouldClose(_window);
	}


	bool Graphics::Render()
	{
		/* Begin Hardware Renderer scene */
		_lowLevelHardwareRenderer->BeginScene(0.2f, 0.3f, 0.3f, 1.0f);

		/* Walk the scene using the hardware visitor */
		_rootScene.Accept(_hardwareRenderVisitor);

		/* End the Hardware Renderer scene */
		_lowLevelHardwareRenderer->EndScene();

		_lowLevelSoftwareRenderer->BeginScene(0.0f, 0.0f, 0.0f, 0.0f);

		_rootScene.Accept(_softwareRenderVisitor);

		_lowLevelSoftwareRenderer->EndScene();

		_graphicsBlender->Render();

		return true;
	}

	bool Graphics::SoftwareRender()
	{
		while (true)
		{
			/* Begin the Software Renderer scene */
			_lowLevelSoftwareRenderer->BeginScene(1.0f, 0.0f, 0.0f, 1.0f);

			/* End the Software Renderer scene*/
			_lowLevelSoftwareRenderer->EndScene();
		}

		return true;
	}
}