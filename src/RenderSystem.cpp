#include "RenderSystem.h"
#include "shaders.h"
#include "Mesh.h"
#include <iostream>
#include <array>


RenderSystem::RenderSystem()
{
}


void RenderSystem::init()
{
  //
  //glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable( GL_BLEND );

   // Geometry pass shaders

	const char vertexShaderSource[] =
		"attribute vec4 vPosition;		                     \n"
    //"attribute vec3 vNormal;		                     \n"
    "attribute vec2 vUV; \n"
    "uniform mat4 MVP; \n"
    "uniform vec3 diffuse;  \n"
		"varying vec3 color;                                 \n" // To FS
    "varying vec2 uv;                                 \n"
		"void main()                                         \n"
		"{                                                   \n"
		"   gl_Position = MVP * vPosition;                         \n"
    "   color = diffuse;             \n"
    //"   color = vec3(1.0,1.0,1.0);  \n"
    //"   uv = vUV; \n"
    "   uv.x = vUV.x; \n"
    "   uv.y = vUV.y; \n"
		"}                                                   \n";

	const char fragmentShaderSource[] =
		"precision mediump float;                     \n"
    "uniform sampler2D BaseMap;									\n"
    "uniform float alpha;									\n"
		"varying vec3 color;                          \n"   // From VS
    "varying vec2 uv;                                 \n"
		"void main()                                  \n"
		"{                                            \n"
    //"  gl_FragColor = vec4 ( color, 1.0 );        \n"
    //"  vec3 shade = texture2D(BaseMap, vec2(uv[1], uv[0])).rgb; \n"
    //"  vec3 shade = vec3( uv.x, uv.y, 0.0 );        \n"
    //"  vec3 shade = texture2D(BaseMap, uv).rgb; \n"
    "  gl_FragColor = vec4(color, alpha);"
    //" color; \n"
    //"  gl_FragColor += vec4 ( 0.1*uv.x, 0.1*uv.y, 0.0, 0.0 );        \n"
		"}                                            \n";

	//load vertex and fragment shaders
	GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexShaderSource);
	GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
	programObject = buildProgram(vertexShader, fragmentShader, "vPosition", "vNormal");

  Mesh::attribute_v_coord = glGetAttribLocation(programObject, "vPosition");
  //Mesh::attribute_v_normal = glGetAttribLocation(programObject, "vNormal");
  Mesh::attribute_v_uv = glGetAttribLocation(programObject, "vUV");

  if (Mesh::attribute_v_normal == -1) std::cout << "attribute_v_normal err -1" << std::endl;
  if (Mesh::attribute_v_coord == -1) std::cout << "attribute_v_coord err -1" << std::endl;
  if (Mesh::attribute_v_uv == -1) std::cout << "attribute_v_uv err -1" << std::endl;

  std::cout << "attribute_v_coord " << Mesh::attribute_v_coord << std::endl;
  std::cout << "attribute_v_normal " << Mesh::attribute_v_normal << std::endl;
  std::cout << "attribute_v_uv " << Mesh::attribute_v_uv << std::endl;

  // Tex
  GLint texLoc;
  texLoc = glGetUniformLocation(programObject, "BaseMap");
  glUniform1i(texLoc, 0);

	//save location of uniform variables
  uniformDiffuse = glGetUniformLocation(programObject, "diffuse");
  uniformMVP = glGetUniformLocation(programObject, "MVP");
  uniformAlpha = glGetUniformLocation(programObject, "alpha");
}


RenderSystem::~RenderSystem()
{


}


void RenderSystem::zoom(int i)
{
  if (i > 0) m_zoomFactor += 1;
  if (i < 0) m_zoomFactor -= 1;
  if (m_zoomFactor < 2) m_zoomFactor = 2;
  if (m_zoomFactor > 6) m_zoomFactor = 6;

  m_zoom = 0.5 + 0.5 * (1<<m_zoomFactor);
}


void RenderSystem::draw()
{
  // Draw the whole screen
  glDepthFunc(GL_ALWAYS);
  draw1Pass();

  // 3. Render the UI overlay
  glDepthFunc(GL_ALWAYS);
  drawUI();
}


void RenderSystem::draw1Pass()
{

  glClearColor(0.f, 92.f / 255.f, 159.f / 255.f, 1.f); // "Skydiver"
  glClear( GL_COLOR_BUFFER_BIT );

  // Enable our shader programlightmap_house1
  glUseProgram(programObject);


  float v_side = 0.05f / m_zoom;
  glm::mat4 Projection = glm::ortho(-v_side*1280.f, v_side*1280.f, -v_side*720.f, v_side*720.f, 1.0f, 100.0f);

  // Camera matrix
  glm::mat4 View = glm::lookAt(
                glm::vec3(30, 30, 10), // Camera is at (4,3,3), in World Space
                glm::vec3(0, 0, 1), // and looks at the origin
                glm::vec3(0, 0, 1)  // Head is up (set to 0,-1,0 to look upside-down)
               );

  glm::mat4 VP = Projection * View;

  // glm::mat4 Model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 1.0, 0));
  // // Our ModelViewProjection : multiplication of our 3 matrices
  // glm::mat4 MVP = VP * Model;
  // // Upload it
  // glUniformMatrix4fv(uniformMVP, 1, GL_FALSE, &MVP[0][0]);
  // m_meshes[0]->draw();
  //
  //
  // s_texture2.bind();
  //
  // Model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, -1.0, 0));
  // MVP = VP * Model;
  // glUniformMatrix4fv(uniformMVP, 1, GL_FALSE, &MVP[0][0]);
  //
  // m_meshes[1]->draw();

}


void  RenderSystem::drawUI()
{

}


void  RenderSystem::drawObjModel_square()
{
  // pos - nor
  GLfloat vVertices2[] = {
     0.5f,  0.5f, 0.0f, 0.f, 0.0f, 1.f,
    -0.5f, -0.5f, 0.0f, 0.f, 0.0f, 1.f,
     0.5f, -0.5f, 0.0f, 0.f, 0.0f, 1.f,
     0.5f,  0.5f, 0.0f, 0.f, 0.0f, 1.f,
    -0.5f,  0.5f, 0.0f, 0.f, 0.0f, 1.f,
    -0.5f, -0.5f, 0.0f, 0.f, 0.0f, 1.f,
  };

	// This will identify our vertex buffer
	static GLuint vertexbuffer = 0;
	if (vertexbuffer == 0)
	{
		// Generate 1 buffer, put the resulting identifier in vertexbuffer
		glGenBuffers(1, &vertexbuffer);
		// The following commands will talk about our 'vertexbuffer' buffer
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		// Give our vertices to OpenGL.
		glBufferData(GL_ARRAY_BUFFER, sizeof(vVertices2), vVertices2, GL_STATIC_DRAW);
	}

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	float* ptr = 0;
	glVertexAttribPointer(
	   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	   3,                  // size
	   GL_FLOAT,           // type
	   GL_FALSE,           // normalized?
	   6*sizeof(GLfloat),                  // stride
	   (void*)(ptr+0)            // array buffer offset
	);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(
		 1,                  // attribute 1. No particular reason for 1, but must match the layout in the shader.
		 3,                  // size
		 GL_FLOAT,           // type
		 GL_FALSE,           // normalized?
		 6*sizeof(GLfloat),        // stride
		 (void*)(ptr+3)            // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 6); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}
