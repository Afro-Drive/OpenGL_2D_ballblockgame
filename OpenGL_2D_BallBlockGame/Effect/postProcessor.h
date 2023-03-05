#ifndef POST_PROCESSOR_H
#define POST_PROCESSOR_H

#include<glad/gl.h>
#include<glm/glm.hpp>

#include"texture.h"
#include"spriteRenderer.h"
#include"shader.h"


/// <summary>
/// PostProcessors hosts all PostProcessing effects for the Game.
/// It renders the game on a textured quad after which one can
/// enable specific effects by enabling either the Confuse, Chaos
/// or Snake boolean.
/// It is required to call BeginRender() before rendering the game
/// and EndRender() after rendering the game for the class to work.
/// </summary>
class PostProcessor
{
	public:
		// state
		Shader PostProcessingShader;
		Texture2D Texture;
		unsigned int Width, Height;
		// options
		bool Confuse, Chaos, Shake;
		// constructor
		PostProcessor(Shader shader, unsigned int width, unsigned int height);
		/// <summary>
		/// prepares the postprocessor's framebuffer operations before rendering the game
		/// </summary>
		void BeginRender();
		/// <summary>
		/// should be called after rendering the game, so it stores all the rendered data into a texture object
		/// </summary>
		void EndRender();
		/// <summary>
		/// renders the PostProcessor texture quad (as a screen-encompassing large sprite)
		/// </summary>
		/// <param name="time"></param>
		void Render(float time);
	private:
		// render state
		unsigned int MSFBO, FBO; // MSFBO = Multisampled FBO. FBO is regular, used for blitting MS color-buffer to texture
		unsigned int RBO; // RBO is used for multisamplered color buffer
		unsigned int VAO;
		// initialize quad for rendering postprocessing texture
		void initRenderData();
};

#endif