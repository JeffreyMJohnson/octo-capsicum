#pragma once

#include "../nsfwgl/nsfw.h"

#include "Camera.h"

class CPass : public nsfw::RenderPass
{
	nsfw::Asset<nsfw::ASSET::TEXTURE> albedo, position, normal, depth, light;

public:
											
	CPass(const char *shaderName, const char *fboName) 
	: RenderPass(shaderName, fboName), albedo("GPassAlbedo"), position("GPassPosition"), // NAMES ARE FROM ASSET LIBRARY!
	normal("GPassNormal"),depth("GPassDepth"), light("LPassColor"){}


	void prep(){
		//TODO_D("glUseProgram, glClear, glBindFrameBuffer, glViewPort, glEnable etc...");
		//
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(0.25f, 0.25f, 0.55f, 1);

		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(*shader);


	}
	void post(){
		//TODO_D("Unset any gl settings");
		//
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindVertexArray(0);
		glUseProgram(0);
	}


	void draw()
	{
		// Set uniforms for textures we're going to composite-> NAMES ARE FROM SHADER!
		setUniform("Albedo",	nsfw::UNIFORM::TEX2, albedo,   0);
		setUniform("Position",	nsfw::UNIFORM::TEX2, position, 1);
		setUniform("Normal",	nsfw::UNIFORM::TEX2, normal,   2);
		setUniform("Depth",		nsfw::UNIFORM::TEX2, depth,    3);
		setUniform("Light",		nsfw::UNIFORM::TEX2, light,    4);

		setUniform("TexelScalar", nsfw::UNIFORM::MAT4, glm::value_ptr(nsfw::Window::instance().getTexelAdjustmentMatrix()));

		unsigned quadVAOHandle = nsfw::Assets::instance().get<nsfw::ASSET::VAO>("Quad");
		unsigned quadNumtris   = nsfw::Assets::instance().get<nsfw::ASSET::SIZE>("Quad");

		glBindVertexArray(quadVAOHandle);
		glDrawElements(GL_TRIANGLES, quadNumtris, GL_UNSIGNED_INT, 0);

		TODO_D("GL BindVAO/DrawElements with quad size and vao");
	}
};