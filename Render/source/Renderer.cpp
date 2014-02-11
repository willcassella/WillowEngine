// Renderer.cpp

#include <iostream>
#include <GL\glew.h>
#include <Engine.h>
#include "Renderer.h"

//RENDER_API API = RENDER_NULL;

int Renderer::init( const RENDER_API& _API )
{
	//API = _API;

	// Set the opengl clear color to black and clear the screen and the depth buffer
	glClearColor( 0, 0, 0, 1 );
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_CULL_FACE );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	return 0;
}

int Renderer::render( const Scene& scene )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// For every camera
	for( int camID = 0; camID < scene.cameras.size(); camID++ ) {

		Camera cam = scene.cameras[camID];

		// For every object
		for( int objID = 0; objID < scene.objects.size(); objID++ ) {

			GameObject object = scene.objects[objID];

			// Bind the mesh
			glBindVertexArray( object.mesh->getVAO() );

			// Bind the material
			glUseProgram( object.mesh->getMaterial().getID() );

			// Bind the texture
			glBindTexture( GL_TEXTURE_2D, object.mesh->getMaterial().getTexture().getID() );
		
			// Get the model matrix
			Mat4 model = object.transform.getModel();
		
			// Get the view matrix
			Mat4 view = cam.transform.getModel().inverse();

			// Create the clipspace matrix
			Mat4 clipspace = cam.perspective * view * model;

			// Upload the matrix to the GPU
			glUniformMatrix4fv( object.mesh->getMaterial().getClipSpaceID(), 1, GL_FALSE,  clipspace[0] );
		
			//Draw the mesh
			glDrawElements( GL_TRIANGLES, (GLsizei)object.mesh->getNumElements(), GL_UNSIGNED_INT, 0 );
		}
	}

	glBindVertexArray( 0 );

	return 0;
}