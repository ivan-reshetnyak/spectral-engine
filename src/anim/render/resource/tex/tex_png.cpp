/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#pragma comment(lib, "libpng16")

#include "libpng/png.h"

#include "tex_png.h"

namespace spectral {
namespace tex {


png::png( const std::string &Name, int SamplerNumber ) : texture(Name, SamplerNumber) {
}


png::png( const std::string &Name, int SamplerNumber, const std::string &FileName ) : texture(Name, SamplerNumber) {
  Load(FileName);
}


void png::Load( const std::string &FileName ) {
  png_image image;
  memset(&image, 0, (sizeof image));
  image.version = PNG_IMAGE_VERSION;

  if (png_image_begin_read_from_file(&image, FileName.c_str()) != 0) {
    png_bytep buffer;
    image.format = PNG_FORMAT_RGBA;
    buffer = new png_byte[PNG_IMAGE_SIZE(image)];
    if (buffer != nullptr && png_image_finish_read(&image, nullptr, buffer, 0, nullptr) != 0) {
      Width = image.width;
      Height = image.height;

      Apply();
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
      glGenerateMipmap(GL_TEXTURE_2D);

      glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTextureParameteri(ID, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
      glTextureParameteri(ID, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    } else {
      if (buffer == nullptr)
        png_image_free(&image);
      else
        delete[] buffer;
    }
    delete[] buffer;
  }
}


} // End of 'tex' namespace
} // End of 'spectral' namespace
