// Renderer.cpp

#include "Renderer.h"
#include "Mesh.h"
#include <forward_list>
#include <GLFW\glfw3.h>
#include "GameObject.h"

#include <glm\gtc\type_ptr.hpp>

//experimental
#include <math.h>

RenderQueue Renderer::rqueue;
CameraQueue Renderer::cqueue;

int Renderer::init()
{
	// Set the opengl clear color to black and clear the screen
	glClearColor( 0, 0, 0, 1 );
	glEnable( GL_DEPTH_TEST );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	return 0;
}

int Renderer::render( GLFWwindow* window )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Create an iterator
	//std::forward_list< GameObject* >::iterator object;

	GameObject* object = rqueue.front();

	//Get the current camera
	Camera* cam = cqueue.front();

	//change the camera's position
	cam->transform.global.x = 3*sin( (float)glfwGetTime() );
	cam->transform.global.y = 3*cos( (float)glfwGetTime() );

	//Iterate throught the render queue
    //for (object = rqueue.begin() ; object != rqueue.end(); object++){

		// Bind the mesh
		glBindVertexArray( object->mesh->vao );


		// Create the model matrix
		glm::mat4 model;
		glUniformMatrix4fv( object->mesh->mat->model, 1, GL_FALSE, glm::value_ptr( model ) );


		//Generate the view matrix
		glm::mat4 view = glm::lookAt(
			cam->transform.global,
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 1.0f)
		);
		glUniformMatrix4fv( object->mesh->mat->view, 1, GL_FALSE, glm::value_ptr( view ) );

		glUniformMatrix4fv( object->mesh->mat->proj, 1, GL_FALSE, glm::value_ptr( cam->perspective ) );
		
		//Draw the mesh
		glDrawElements( GL_TRIANGLES, (GLsizei)object->mesh->elements.size(), GL_UNSIGNED_INT, 0 );
	//};
	
	glBindVertexArray( 0 );
	
	//update the screen
	glfwSwapBuffers( window );

	return 0;
}