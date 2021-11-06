#pragma once
#include "wrapperPch.h"
#include "Image.h"
namespace OGL {
	class Texture2D
	{
	protected:
		GLuint m_object;
	public:
		bool immutable = false;

		//Bindless 
		void genHandle(); //Texture state cannot be changed after this call is made
		void delHandle() const;
		GLuint64 handle; // Used for bindless operations

		//Binded
		void use(unsigned slot) const; // Bind texture to a texture slot, do not use with bindless

		Texture2D(Image img, bool useMips = true);
		Texture2D() = default;
		void destroy() const;
	};
}

