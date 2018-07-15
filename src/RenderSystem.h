#pragma once
#include <string>
#include <vector>

#include "graphics.h"



class Mesh;


// Controls the shaders and render loops
class RenderSystem
{

public:
  RenderSystem();
  ~RenderSystem();

  void init();

  void draw();

  // Important square drawing
  static void drawObjModel_square();

  // Camera move callback
  void zoom(int);
  GLint uniformMVP;
  GLint uniformDiffuse;
  GLint uniformAlpha;

protected:

  void draw1Pass();
  void drawUI();

  // Vars
  long m_shader;
  GLuint programObject;

  unsigned int m_default_framebuffer = 0;

  // Non - core

  // View settings
  double m_cameraX = 0;
  double m_cameraY = 0;
  int m_zoomFactor = 3;
  float m_zoom = 0.5 + 0.5 * (1<<3);

  // Meshes
  std::vector<Mesh*> m_meshes;

  // Uniforms OLD
  GLint uniform_s_GBuffer;
  GLint lightPos, lightCol;
};
