#include "graphics.h"


class Texture
{
public:
  Texture(const char* file);
  ~Texture();

  void bind();

protected:

  void load(const char* file);

  GLuint m_texture = 0;
};
