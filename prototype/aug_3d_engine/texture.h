/**
 * Texture.h
 *
 * (cc) Creative Commons Attribution-Noncommercial-Share Alike 2.5 Licence
 * Callum Hay, 2009
 *
 * You may not use this work for commercial purposes.
 * If you alter, transform, or build upon this work, you may distribute the 
 * resulting work only under the same or similar licence to this one.
 */

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

// AugEngine Includes
#include "common.h"

// Abstract Texture class
class Texture {
public:
	enum TextureFilterType { Nearest, Linear, NearestMipmap, Bilinear, Trilinear };

	Texture(TextureFilterType texFilter, int textureType);
	virtual ~Texture();

	unsigned int GetTextureID() const {
		return this->texID;
	}
	
	int GetTextureType() const {
		return this->textureType;
	}

	size_t GetWidth() const {
		return this->width;
	}

	size_t GetHeight() const {
		return this->height;
	}

	TextureFilterType GetFilter() const {
		return this->texFilter;
	}

	// Functions for binding and unbinding the texture - these should
	// ALWAYS be used over manually doing it - both
	// help isolate problems with the OGL state
	void BindTexture() const {
		glEnable(this->textureType);
		glBindTexture(this->textureType, this->texID);
	}
	void UnbindTexture() const {
		glBindTexture(this->textureType, 0);
		glDisable(this->textureType);
	}

    bool IsMipmappedFilter() {
        return IsMipmappedFilter(this->texFilter);
    }
	void GenerateMipmaps() {
		glGenerateMipmapEXT(this->textureType);
	}

protected:
	TextureFilterType texFilter;
	int textureType;
    GLint internalFormat;
	GLuint texID;
	size_t width, height;

	static void SetFilteringParams(TextureFilterType texFilter, int glTexType);
	static bool IsMipmappedFilter(TextureFilterType texFilter) {
		return !(texFilter == Nearest || texFilter == Linear);
	}

	bool Load2DOr1DTextureFromBuffer(unsigned char* fileBuffer, long fileBufferLength, TextureFilterType texFilter = Nearest);
	bool Load2DOr1DTextureFromImg(const std::string& filepath, TextureFilterType texFilter = Nearest);

private:
    DISALLOW_COPY_AND_ASSIGN(Texture);
};

#endif