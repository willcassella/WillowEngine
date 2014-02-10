#ifndef RENDERER_H_
#define RENDERER_H_

#include <Engine.h>

enum RENDER_API {
	RENDER_NULL, RENDER_OPENGL
};

class Renderer
{
public:

	//static RENDER_API API;

	static int init( const RENDER_API& _API );

	static int render( const Scene& scene );
};

#endif