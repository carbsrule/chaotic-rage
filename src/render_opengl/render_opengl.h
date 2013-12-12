// This file is part of Chaotic Rage (c) 2010 Josh Heidenreich
//
// kate: tab-width 4; indent-width 4; space-indent off; word-wrap off;

#pragma once
#include <SDL.h>
#include <map>

#include "../rage.h"
#include "glshader.h"
#include "../render/render_3d.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#define NUM_CHAR_TEX (128 - 32)

#include <guichan.hpp>
#include <guichan/sdl.hpp>
#include <guichan/opengl.hpp>
#include <guichan/opengl/openglsdlimageloader.hpp>

#include <glm/glm.hpp>

#include <assimp/scene.h>



// Constants for VBOs <-> Shaders
// (glBindAttribLocation)
#define ATTRIB_POSITION 0         // vPosition
#define ATTRIB_NORMAL 1           // vNormal
#define ATTRIB_TEXUV 2            // vTexUV
#define ATTRIB_BONEID 3           // vBoneIDs
#define ATTRIB_BONEWEIGHT 4       // vBoneWeights
#define ATTRIB_TEXTCOORD 5        // vCoord
#define ATTRIB_COLOR 6            // vColor
#define ATTRIB_TANGENT 7          // vTangent


struct VBOvertex
{
	float x, y, z;        // Vertex
	float nx, ny, nz;     // Normal
	float tx, ty;         // Tex
};

struct FreetypeChar
{
	GLuint tex;
	int x, y, w, h;
	float tx, ty;
	int advance;
};


class GLVAO;
class RenderOpenGLSettings;
class btIDebugDraw;


class RenderOpenGL : public Render3D
{
	friend class HUD;
	friend class Menu;
	friend class Intro;
	friend class GameState;
	
	private:
		SDL_Window *window;
		SDL_GLContext glcontext;
		
		// The current player being rendered (split screen)
		Player* render_player;
		
		// FreeType
		FT_Library ft;
		FT_Face face;
		vector<SpritePtr> loaded;
		FreetypeChar char_tex[NUM_CHAR_TEX];
		
		// VBOs
		GLuint font_vbo;
		GLuint sprite_vbo;
		
		// VAOs
		GLVAO* ter_vao;
		GLVAO* skybox_vao;
		GLVAO* particle_vao;
		
		// Heightmap
		unsigned int ter_size;
		
		// Water
		WavefrontObj *waterobj;
		
		// Debugging
		btIDebugDraw *physicsdebug;
		bool speeddebug;
		
		// Shaders
		bool shaders_loaded;		// true if loaded from a mod
		bool shaders_error;			// true if a shader load failed
		map<string, GLShader*> shaders;
		
		glm::mat4 projection;	// perspective
		glm::mat4 ortho;		// ortho
		glm::mat4 view;			// camera
		
		RenderOpenGLSettings* settings;
		int min_filter;
		int mag_filter;
		
	public:
		RenderOpenGL(GameState * st, RenderOpenGLSettings* settings);
		virtual ~RenderOpenGL();
		
	protected:
		virtual SpritePtr int_loadSprite(SDL_RWops *rw, string filename);

	public:
		// From class Render
		virtual void setScreenSize(int width, int height, bool fullscreen);
		virtual void render();
		virtual void renderSprite(SpritePtr sprite, int x, int y);
		virtual void renderSprite(SpritePtr sprite, int x, int y, int w, int h);
		virtual void preGame();
		virtual void postGame();
		virtual void clearPixel(int x, int y);
		virtual void freeSprite(SpritePtr sprite);
		virtual int getSpriteWidth(SpritePtr sprite);
		virtual int getSpriteHeight(SpritePtr sprite);
		virtual void loadHeightmap();
		virtual void freeHeightmap();
		virtual int getWidth() { return real_width; }
		virtual int getHeight() { return real_height; }
		
		virtual void setPhysicsDebug(bool status);
		virtual bool getPhysicsDebug();
		virtual void setSpeedDebug(bool status) { this->speeddebug = status; }
		virtual bool getSpeedDebug() { return this->speeddebug; }
		
	public:
		// From class Render3D
		virtual void saveScreenshot(string filename);
		virtual void initGuichan(gcn::Gui * gui, Mod * mod);
		virtual void preVBOrender();
		virtual void postVBOrender();
		virtual void renderObj (WavefrontObj * obj, glm::mat4 mvp);
		virtual void loadFont(string name, Mod * mod);
		virtual void renderText(string text, float x = 0.0f, float y = 0.0f, float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
		virtual unsigned int widthText(string text);
		virtual SpritePtr loadCubemap(string filename_base, string filename_ext, Mod * mod);

		void setSettings(RenderOpenGLSettings* settings);
		RenderOpenGLSettings* getSettings();
		
		bool reloadShaders();
		
	private:
		void createWater();
		void createSkybox();
		void renderAnimPlay(AnimPlay * play, Entity * e);
		void renderCharacter(char c, float &x, float &y);
		void createVBO (WavefrontObj * obj);
		void surfaceToOpenGL(SpritePtr sprite);
		void recursiveRenderAssimpModel(AnimPlay* ap, AssimpModel *am, AssimpNode *nd, GLShader *shader, glm::mat4 transform);
		
		void mainViewport(int s, int of);
		void mainRot();
		void skybox();
		void terrain();
		void entities();
		void physics();
		void water();
		void particles();
		void guichan();
		void hud(HUD * hud);
		void fps();
		
		void loadShaders();
		GLuint createShader(const char* code, GLenum type);
		GLShader* createProgram(const char* vertex, const char* fragment, string name);
		GLShader* loadProgram(Mod* mod, string name);
		void deleteProgram(GLShader* shader);
		void setupShaders();
};
