#include "Texture.h"
#include <fstream>
#include <vector>
#include <iostream>


Texture::Texture(const char* file)
{
  load(file);
}


Texture::~Texture()
{

}


void Texture::load(const char* file)
{
  // FILE* f = fopen(
  // "data/lowpoly_tree/obj/lightmap.data",
  // "rb");
  //
  // BYTE* data = new BYTE[3*512*512];
  //
  // for (int i = 0; i < 512*512; ++i)
  // {
  //   BYTE r = ;
  //   BYTE g = ;
  //   BYTE b = ;
  //
  //   data[3-]
  // }
  std::ifstream input( file, std::ios::binary );
  // copies all data into buffer
  std::vector<char> buffer((
        std::istreambuf_iterator<char>(input)),
        (std::istreambuf_iterator<char>()));

  std::cout << (int)buffer[0] << (int)buffer[1] << (int)buffer[2] << std::endl;

  glActiveTexture(GL_TEXTURE1);

  glGenTextures(1, &m_texture);

  glBindTexture(GL_TEXTURE_2D, m_texture);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

  glGenerateMipmap(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, m_texture);

  std::cout << "Texture: " << m_texture << std::endl;
}


void Texture::bind()
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_texture);
}
