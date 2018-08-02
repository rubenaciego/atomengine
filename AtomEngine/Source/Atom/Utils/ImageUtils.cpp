#include <FreeImage.h>
#include <Atom/Utils/ImageUtils.hpp>

namespace atom
{
	unsigned char* LoadImage(const char* filename, int* width, int* height)
	{
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP *dib = nullptr;

		fif = FreeImage_GetFileType(filename, 0);

		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filename);
		if (fif == FIF_UNKNOWN)
			return nullptr;

		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, filename);
		if (!dib)
			return nullptr;

		unsigned int bpp = FreeImage_GetBPP(dib);
		unsigned int pitch = FreeImage_GetPitch(dib);

		BYTE* bits = FreeImage_GetBits(dib);
		*width = FreeImage_GetWidth(dib);
		*height = FreeImage_GetHeight(dib);

		int size = *width * *height * bpp / 8;
		BYTE* result = new BYTE[size];
		memcpy(result, bits, size);

		FreeImage_Unload(dib);
		return result;
	}
}
