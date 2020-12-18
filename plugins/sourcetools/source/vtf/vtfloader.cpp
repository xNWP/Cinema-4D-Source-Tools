#include "vtfloader.h"

#include "vtfformat.h"

#include <c4d.h>
#include <vector>

// LUT's for quick conversions
static constexpr UChar LUT4[] = {0,   17,  34,  51,  68,  85,  102, 119,
                                 136, 153, 170, 187, 204, 221, 238, 255};
static constexpr UChar LUT5[] = {0,   8,   16,  25,  33,  41,  49,  58,
                                 66,  74,  82,  90,  99,  107, 115, 123,
                                 132, 140, 148, 156, 165, 173, 181, 189,
                                 197, 206, 214, 222, 230, 239, 247, 255};
static constexpr UChar LUT6[] = {
    0,   4,   8,   12,  16,  20,  24,  28,  32,  36,  40,  45,  49,
    53,  57,  61,  65,  69,  73,  77,  81,  85,  89,  93,  97,  101,
    105, 109, 113, 117, 121, 125, 130, 134, 138, 142, 146, 150, 154,
    158, 162, 166, 170, 174, 178, 182, 186, 190, 194, 198, 202, 206,
    210, 215, 219, 223, 227, 231, 235, 239, 243, 247, 251, 255};

struct PIX565 {
  UInt16 z : 5;
  UInt16 y : 6;
  UInt16 x : 5;
};

struct PIX5551 {
  UInt16 w : 5;
  UInt16 x : 5;
  UInt16 y : 5;
  UInt16 z : 1;
};

struct PIX4444 {
  UInt16 w : 4;
  UInt16 x : 4;
  UInt16 y : 4;
  UInt16 z : 4;
};

class RGB888 {
public:
  UChar R;
  UChar G;
  UChar B;

  RGB888() : R(0), G(0), B(0) {}
  RGB888(const PIX565 &pix) {
    R = LUT5[pix.x];
    G = LUT6[pix.y];
    B = LUT5[pix.z];
  }

  RGB888(UChar _R, UChar _G, UChar _B) : R(_R), G(_G), B(_B) {}

  RGB888 operator*(const Float32 &rhs) const {
    RGB888 rval = *this;
    rval.R = UChar(Round(Float32(R) * rhs));
    rval.G = UChar(Round(Float32(G) * rhs));
    rval.B = UChar(Round(Float32(B) * rhs));
    return rval;
  }

  RGB888 &operator*=(const Float32 &rhs) {
    this->R = UChar(Round(Float32(this->R) * rhs));
    this->G = UChar(Round(Float32(this->G) * rhs));
    this->B = UChar(Round(Float32(this->B) * rhs));
    return *this;
  }

  RGB888 operator+(const RGB888 &rhs) const {
    RGB888 rval = *this;
    rval.R += rhs.R;
    rval.G += rhs.G;
    rval.B += rhs.B;
    return rval;
  }
};

template <typename T> T Lerp(const T &start, const T &end, const Float32 &t) {
  Float32 tLocal;
  if (t < 0)
    tLocal = 0;
  else if (t > 1)
    tLocal = 1;
  else
    tLocal = t;

  T startLocal = T(start * (1 - t));
  T endLocal = T(end * t);

  return startLocal + endLocal;
}

UChar Lerp(const UChar &start, const UChar &end, const Float32 t) {
  Float32 tLocal;
  if (t < 0)
    tLocal = 0;
  else if (t > 1)
    tLocal = 1;
  else
    tLocal = t;

  Float32 startLocal = Float32(start) * (1.0f - t);
  Float32 endLocal = Float32(end) * t;

  return UChar(Round(startLocal + endLocal));
}

std::vector<UChar> ExtractTexelEntries(const UInt32 &TexelMap) {
  std::vector<UChar> rval;
  rval.resize(16);

  rval[0] = UChar((TexelMap & 0x00000003));
  rval[1] = UChar((TexelMap & 0x0000000C) >> 2);
  rval[2] = UChar((TexelMap & 0x00000030) >> 4);
  rval[3] = UChar((TexelMap & 0x000000C0) >> 6);
  rval[4] = UChar((TexelMap & 0x00000300) >> 8);
  rval[5] = UChar((TexelMap & 0x00000C00) >> 10);
  rval[6] = UChar((TexelMap & 0x00003000) >> 12);
  rval[7] = UChar((TexelMap & 0x0000C000) >> 14);
  rval[8] = UChar((TexelMap & 0x00030000) >> 16);
  rval[9] = UChar((TexelMap & 0x000C0000) >> 18);
  rval[10] = UChar((TexelMap & 0x00300000) >> 20);
  rval[11] = UChar((TexelMap & 0x00C00000) >> 22);
  rval[12] = UChar((TexelMap & 0x03000000) >> 24);
  rval[13] = UChar((TexelMap & 0x0C000000) >> 26);
  rval[14] = UChar((TexelMap & 0x30000000) >> 28);
  rval[15] = UChar((TexelMap & 0xC0000000) >> 30);

  return rval;
}

std::vector<UChar> ExtractAlphaEntriesDXT3(const UInt64 &TexelMap) {
  std::vector<UChar> rval;
  rval.resize(16);

  rval[0] = LUT4[TexelMap & 0x000000000000000F];
  rval[1] = LUT4[(TexelMap & 0x00000000000000F0) >> 4];
  rval[2] = LUT4[(TexelMap & 0x0000000000000F00) >> 8];
  rval[3] = LUT4[(TexelMap & 0x000000000000F000) >> 12];
  rval[4] = LUT4[(TexelMap & 0x00000000000F0000) >> 16];
  rval[5] = LUT4[(TexelMap & 0x0000000000F00000) >> 20];
  rval[6] = LUT4[(TexelMap & 0x000000000F000000) >> 24];
  rval[7] = LUT4[(TexelMap & 0x00000000F0000000) >> 28];
  rval[8] = LUT4[(TexelMap & 0x0000000F00000000) >> 32];
  rval[9] = LUT4[(TexelMap & 0x000000F000000000) >> 36];
  rval[10] = LUT4[(TexelMap & 0x00000F0000000000) >> 40];
  rval[11] = LUT4[(TexelMap & 0x0000F00000000000) >> 44];
  rval[12] = LUT4[(TexelMap & 0x000F000000000000) >> 48];
  rval[13] = LUT4[(TexelMap & 0x00F0000000000000) >> 52];
  rval[14] = LUT4[(TexelMap & 0x0F00000000000000) >> 56];
  rval[15] = LUT4[(TexelMap & 0xF000000000000000) >> 60];

  return rval;
}

std::vector<UChar> ExtractAlphaEntriesDXT5(const UInt64 &TexelMap) {
  UChar MapCodes[16];
  UChar Alphas[8];
  std::vector<UChar> rval;
  rval.resize(16);

  Alphas[0] = UChar(TexelMap & 0x00000000000000FF);
  Alphas[1] = UChar((TexelMap & 0x000000000000FF00) >> 8);

  MapCodes[0] = UChar((TexelMap & 0x0000000000070000) >> 16);
  MapCodes[1] = UChar((TexelMap & 0x0000000000380000) >> 19);
  MapCodes[2] = UChar((TexelMap & 0x0000000001C00000) >> 22);
  MapCodes[3] = UChar((TexelMap & 0x000000000E000000) >> 25);
  MapCodes[4] = UChar((TexelMap & 0x0000000070000000) >> 28);
  MapCodes[5] = UChar((TexelMap & 0x0000000380000000) >> 31);
  MapCodes[6] = UChar((TexelMap & 0x0000001C00000000) >> 34);
  MapCodes[7] = UChar((TexelMap & 0x000000E000000000) >> 37);
  MapCodes[8] = UChar((TexelMap & 0x0000070000000000) >> 40);
  MapCodes[9] = UChar((TexelMap & 0x0000380000000000) >> 43);
  MapCodes[10] = UChar((TexelMap & 0x0001C00000000000) >> 46);
  MapCodes[11] = UChar((TexelMap & 0x000E000000000000) >> 49);
  MapCodes[12] = UChar((TexelMap & 0x0070000000000000) >> 52);
  MapCodes[13] = UChar((TexelMap & 0x0380000000000000) >> 55);
  MapCodes[14] = UChar((TexelMap & 0x1C00000000000000) >> 58);
  MapCodes[15] = UChar((TexelMap & 0xE000000000000000) >> 61);

  if (Alphas[0] > Alphas[1]) {
    Alphas[2] = Lerp(Alphas[0], Alphas[1], 1.0f / 7.0f);
    Alphas[3] = Lerp(Alphas[0], Alphas[1], 2.0f / 7.0f);
    Alphas[4] = Lerp(Alphas[0], Alphas[1], 3.0f / 7.0f);
    Alphas[5] = Lerp(Alphas[0], Alphas[1], 4.0f / 7.0f);
    Alphas[6] = Lerp(Alphas[0], Alphas[1], 5.0f / 7.0f);
    Alphas[7] = Lerp(Alphas[0], Alphas[1], 6.0f / 7.0f);
  } else {
    Alphas[2] = Lerp(Alphas[0], Alphas[1], 1.0f / 5.0f);
    Alphas[3] = Lerp(Alphas[0], Alphas[1], 2.0f / 5.0f);
    Alphas[4] = Lerp(Alphas[0], Alphas[1], 3.0f / 5.0f);
    Alphas[5] = Lerp(Alphas[0], Alphas[1], 4.0f / 5.0f);
    Alphas[6] = 0x00;
    Alphas[7] = 0xFF;
  }

  UChar it = 0;
  for (auto &i : MapCodes)
    rval[it++] = Alphas[i];

  return rval;
}

Bool VTFLoaderData::Identify(const Filename &name, UChar *probe, Int32 size) {
  if (!probe || size < 4)
    return false;

  const char *sig = "VTF";

  if (!strcmp((const char *)probe, sig))
    return true;

  return false;
}

IMAGERESULT VTFLoaderData::Load(const Filename &name, BaseBitmap *bm,
                                Int32 frame) {
  AutoAlloc<BaseFile> file;
  if (!file)
    return IMAGERESULT::OUTOFMEMORY;

  if (!file->Open(name, FILEOPEN::READ, FILEDIALOG::NONE, BYTEORDER::V_INTEL))
    return IMAGERESULT::FILEERROR;

  // read header
  vtf_header header;
  file->ReadBytes(&header, sizeof(vtf_header), true);

  // check for non-supported formats
  if (header.version[0] > 7 || header.version[1] > 5)
    return IMAGERESULT::WRONGTYPE;
  if ((UInt32)header.flags & (UInt32)VTF_IMAGEFLAGS::TEXTUREFLAGS_ENVMAP)
    return IMAGERESULT::WRONGTYPE;
  if (header.version[1] >= 2 && header.depth > 1)
    return IMAGERESULT::WRONGTYPE;

  // check for non-standard dimensions
  if (header.width == 0 || header.height == 0)
    return IMAGERESULT::WRONGTYPE;
  if (header.width > 16000 || header.height > 16000)
    return IMAGERESULT::WRONGTYPE;

  const Float32 WidthExp = Log2(Float32(header.width));
  const Float32 HeightExp = Log2(Float32(header.height));
  if (WidthExp != Int32(WidthExp) || HeightExp != Int32(HeightExp))
    return IMAGERESULT::WRONGTYPE;

  // normalize frame count
  if (header.frames == 0)
    header.frames = 1;

  // finally load the image doing any conversions as needed
  if (header.highResImageFormat == VTF_IMAGEFORMAT::IMAGE_FORMAT_NONE) {
    return IMAGERESULT::WRONGTYPE;
  } else if (header.highResImageFormat ==
             VTF_IMAGEFORMAT::IMAGE_FORMAT_RGBA8888) {
    if (bm->Init(header.width, header.height, 24) != IMAGERESULT::OK)
      return IMAGERESULT::MISC_ERROR;

    // determine offset of high-res data
    const UInt32 size = UInt32(header.width) * UInt32(header.height) * 4;
    const UInt32 offset =
        UInt32(file->GetLength()) - size * (UInt32(header.frames) - frame);

    // read in raw data
    UChar *const data = new UChar[size];
    if (!data)
      return IMAGERESULT::OUTOFMEMORY;

    file->Seek(offset, FILESEEK::START);
    if (file->ReadBytes(data, size, true) != size) {
      delete[] data;
      return IMAGERESULT::FILEERROR;
    }

    // Add Alpha Channel
    BaseBitmap *Alpha = bm->AddChannel(true, true);
    if (!Alpha) {
      delete[] data;
      return IMAGERESULT::OUTOFMEMORY;
    }

    UChar *ColourData =
        new UChar[UInt32(header.width) * UInt32(header.height) * 3];
    if (!ColourData) {
      delete[] data;
      return IMAGERESULT::OUTOFMEMORY;
    }

    // Separate out Colour And Alpha
    Bool ok = true;
    for (UInt32 i = 0; i < size / 4 && ok; ++i) {
      ok = bm->SetAlphaPixel(Alpha, i % header.width, i / header.height,
                             data[i * 4 + 3]); // Set A
      ColourData[i * 3] = data[i * 4];         // Set R
      ColourData[i * 3 + 1] = data[i * 4 + 1]; // Set G
      ColourData[i * 3 + 2] = data[i * 4 + 2]; // Set B
    }

    delete[] data;

    // fill bitmap
    for (UInt32 y = 0; y < header.height && ok; ++y) {
      ok = bm->SetPixelCnt(0, y, header.width,
                           ColourData + (y * header.width * 3), COLORBYTES_RGB,
                           COLORMODE::RGB, PIXELCNT::NONE);
    }

    delete[] ColourData;

    return ok ? IMAGERESULT::OK : IMAGERESULT::MISC_ERROR;
  } else if (header.highResImageFormat ==
             VTF_IMAGEFORMAT::IMAGE_FORMAT_ABGR8888) {
    if (bm->Init(header.width, header.height, 24) != IMAGERESULT::OK)
      return IMAGERESULT::MISC_ERROR;

    // determine offset of high-res data
    const UInt32 size = UInt32(header.width) * UInt32(header.height) * 4;
    const UInt32 offset =
        UInt32(file->GetLength()) - size * (UInt32(header.frames) - frame);

    // read in raw data
    UChar *const data = new UChar[size];
    if (!data)
      return IMAGERESULT::OUTOFMEMORY;

    file->Seek(offset, FILESEEK::START);
    if (file->ReadBytes(data, size, true) != size) {
      delete[] data;
      return IMAGERESULT::FILEERROR;
    }

    // Add Alpha Channel
    BaseBitmap *Alpha = bm->AddChannel(true, true);
    if (!Alpha) {
      delete[] data;
      return IMAGERESULT::OUTOFMEMORY;
    }

    UChar *const ColourData =
        new UChar[UInt32(header.width) * UInt32(header.height) * 3];
    if (!ColourData) {
      delete[] data;
      return IMAGERESULT::OUTOFMEMORY;
    }

    // Separate out Alpha And Colour Data
    Bool ok = true;
    for (UInt32 i = 0; i < size / 4 && ok; ++i) {
      ok = bm->SetAlphaPixel(Alpha, i % header.width, i / header.width,
                             data[i * 4]);
      ColourData[i * 3 + 2] = data[i * 4 + 1]; // Set B
      ColourData[i * 3 + 1] = data[i * 4 + 2]; // Set G
      ColourData[i * 3] = data[i * 4 + 3];     // Set R
    }

    delete[] data;

    // fill bitmap
    for (UInt32 y = 0; y < header.height && ok; ++y) {
      ok = bm->SetPixelCnt(0, y, header.width,
                           ColourData + (y * header.width * 3), COLORBYTES_RGB,
                           COLORMODE::RGB, PIXELCNT::NONE);
    }

    delete[] ColourData;

    return ok ? IMAGERESULT::OK : IMAGERESULT::MISC_ERROR;
  } else if (header.highResImageFormat ==
                 VTF_IMAGEFORMAT::IMAGE_FORMAT_RGB888 ||
             header.highResImageFormat ==
                 VTF_IMAGEFORMAT::IMAGE_FORMAT_RGB888_BLUESCREEN) {
    if (bm->Init(header.width, header.height, 24) != IMAGERESULT::OK)
      return IMAGERESULT::MISC_ERROR;

    // determine offset of high-res data
    const UInt32 size = UInt32(header.width) * UInt32(header.height) * 3;
    const UInt32 offset =
        UInt32(file->GetLength()) - size * (UInt32(header.frames) - frame);

    // read in raw data
    UChar *const data = new UChar[size];
    if (!data)
      return IMAGERESULT::OUTOFMEMORY;

    file->Seek(offset, FILESEEK::START);
    if (file->ReadBytes(data, size, true) != size) {
      delete[] data;
      return IMAGERESULT::FILEERROR;
    }

    // fill bitmap
    Bool ok = true;
    for (UInt32 y = 0; y < header.height && ok; ++y) {
      ok = bm->SetPixelCnt(0, y, header.width, data + (y * header.width * 3),
                           COLORBYTES_RGB, COLORMODE::RGB, PIXELCNT::NONE);
    }

    delete[] data;

    return ok ? IMAGERESULT::OK : IMAGERESULT::MISC_ERROR;
  } else if (header.highResImageFormat ==
                 VTF_IMAGEFORMAT::IMAGE_FORMAT_BGR888 ||
             header.highResImageFormat ==
                 VTF_IMAGEFORMAT::IMAGE_FORMAT_BGR888_BLUESCREEN) {
    if (bm->Init(header.width, header.height, 24) != IMAGERESULT::OK)
      return IMAGERESULT::MISC_ERROR;

    // determine offset of high-res data
    const UInt32 size = UInt32(header.width) * UInt32(header.height) * 3;
    const UInt32 offset =
        UInt32(file->GetLength()) - size * (UInt32(header.frames) - frame);

    // read in raw data
    UChar *const data = new UChar[size];
    if (!data)
      return IMAGERESULT::OUTOFMEMORY;

    file->Seek(offset, FILESEEK::START);
    if (file->ReadBytes(data, size, true) != size) {
      delete[] data;
      return IMAGERESULT::FILEERROR;
    }

    // C4D supports RGB but not BGR, so we'll convert to BGR
    for (UInt32 i = 0; i < size / 3; ++i) {
      const UChar B = data[i * 3];
      data[i * 3] = data[i * 3 + 2]; // set R
      data[i * 3 + 2] = B;           // set B
    }

    // fill bitmap
    Bool ok = true;
    for (UInt32 y = 0; y < header.height && ok; ++y) {
      ok = bm->SetPixelCnt(0, y, header.width, data + (y * header.width * 3),
                           COLORBYTES_RGB, COLORMODE::RGB, PIXELCNT::NONE);
    }

    delete[] data;

    return ok ? IMAGERESULT::OK : IMAGERESULT::MISC_ERROR;
  } else if (header.highResImageFormat ==
             VTF_IMAGEFORMAT::IMAGE_FORMAT_RGB565) {
    if (bm->Init(header.width, header.height, 24) != IMAGERESULT::OK)
      return IMAGERESULT::MISC_ERROR;

    // determine offset of high-res data
    const UInt32 size = UInt32(header.width) * UInt32(header.height) * 2;
    const UInt32 offset =
        UInt32(file->GetLength()) - size * (UInt32(header.frames) - frame);

    // read in raw data
    UChar *const data = new UChar[size];
    if (!data)
      return IMAGERESULT::OUTOFMEMORY;

    file->Seek(offset, FILESEEK::START);
    if (file->ReadBytes(data, size, true) != size) {
      delete[] data;
      return IMAGERESULT::FILEERROR;
    }

    // C4D supports RGB888 but not RGB565, so we'll convert to RGB888
    UChar *const formattedData =
        new UChar[UInt32(header.width) * UInt32(header.height) * 3];
    if (!formattedData) {
      delete[] data;
      return IMAGERESULT::OUTOFMEMORY;
    }

    for (UInt32 i = 0; i < size / 2; ++i) {
      PIX565 *const ptr = (PIX565 *)(data + (i * 2));
      formattedData[i * 3] = LUT5[ptr->x];     // set R
      formattedData[i * 3 + 1] = LUT6[ptr->y]; // set G
      formattedData[i * 3 + 2] = LUT5[ptr->z]; // set B
    }

    delete[] data;

    // fill bitmap
    Bool ok = true;
    for (UInt32 y = 0; y < header.height && ok; ++y) {
      ok = bm->SetPixelCnt(0, y, header.width,
                           formattedData + (y * header.width * 3),
                           COLORBYTES_RGB, COLORMODE::RGB, PIXELCNT::NONE);
    }

    delete[] formattedData;

    return ok ? IMAGERESULT::OK : IMAGERESULT::MISC_ERROR;
  } else if (header.highResImageFormat == VTF_IMAGEFORMAT::IMAGE_FORMAT_I8) {
    if (bm->Init(header.width, header.height, 8, INITBITMAPFLAGS::GRAYSCALE) !=
        IMAGERESULT::OK)
      return IMAGERESULT::MISC_ERROR;

    // determine offset of high-res data
    const UInt32 size = UInt32(header.width) * UInt32(header.height);
    const UInt32 offset =
        UInt32(file->GetLength()) - size * (UInt32(header.frames) - frame);

    // read in raw data
    UChar *const data = new UChar[size];
    if (!data)
      return IMAGERESULT::OUTOFMEMORY;

    file->Seek(offset, FILESEEK::START);
    if (file->ReadBytes(data, size, true) != size) {
      delete[] data;
      return IMAGERESULT::FILEERROR;
    }

    // fill bitmap
    Bool ok = true;
    for (UInt32 y = 0; y < header.height && ok; ++y) {
      ok = bm->SetPixelCnt(0, y, header.width, data + (y * header.width),
                           COLORBYTES_GRAY, COLORMODE::GRAY, PIXELCNT::NONE);
    }

    delete[] data;

    return ok ? IMAGERESULT::OK : IMAGERESULT::MISC_ERROR;
  } else if (header.highResImageFormat == VTF_IMAGEFORMAT::IMAGE_FORMAT_IA88) {
    if (bm->Init(header.width, header.height, 8, INITBITMAPFLAGS::GRAYSCALE) !=
        IMAGERESULT::OK)
      return IMAGERESULT::MISC_ERROR;

    // determine offset of high-res data
    const UInt32 size = UInt32(header.width) * UInt32(header.height) * 2;
    const UInt32 offset =
        UInt32(file->GetLength()) - size * (UInt32(header.frames) - frame);

    // read in raw data
    UChar *const data = new UChar[size];
    if (!data)
      return IMAGERESULT::OUTOFMEMORY;

    file->Seek(offset, FILESEEK::START);
    if (file->ReadBytes(data, size, true) != size) {
      delete[] data;
      return IMAGERESULT::FILEERROR;
    }

    // fill bitmap
    BaseBitmap *alpha = bm->AddChannel(true, true);
    if (!alpha) {
      delete[] data;
      return IMAGERESULT::MISC_ERROR;
    }

    // separate out I and A
    UChar *const IData = new UChar[size / 2];
    UChar *const AData = new UChar[size / 2];

    for (UInt32 i = 0; i < size / 2; ++i) {
      IData[i] = data[i * 2];
      AData[i] = data[i * 2 + 1];
    }

    // Set Alpha
    Bool ok = true;
    for (UInt32 i = 0; i < size / 2 && ok; ++i)
      ok = bm->SetAlphaPixel(alpha, i % header.width, i / header.width,
                             AData[i]);

    if (!ok) {
      delete[] data;
      delete[] IData;
      delete[] AData;
      return IMAGERESULT::MISC_ERROR;
    }

    // Set Color Data
    for (UInt32 y = 0; y < header.height && ok; ++y)
      ok = bm->SetPixelCnt(0, y, header.width, IData + (y * header.width),
                           COLORBYTES_GRAY, COLORMODE::GRAY, PIXELCNT::NONE);

    delete[] data;
    delete[] IData;
    delete[] AData;

    return ok ? IMAGERESULT::OK : IMAGERESULT::MISC_ERROR;
  } else if (header.highResImageFormat == VTF_IMAGEFORMAT::IMAGE_FORMAT_P8) {
    return IMAGERESULT::WRONGTYPE;
  } else if (header.highResImageFormat == VTF_IMAGEFORMAT::IMAGE_FORMAT_A8) {
    if (bm->Init(header.width, header.height, 8, INITBITMAPFLAGS::GRAYSCALE) !=
        IMAGERESULT::OK)
      return IMAGERESULT::MISC_ERROR;

    // determine offset of high-res data
    const UInt32 size = UInt32(header.width) * UInt32(header.height);
    const UInt32 offset =
        UInt32(file->GetLength()) - size * (UInt32(header.frames) - frame);

    // read in raw data
    UChar *const data = new UChar[size];
    if (!data)
      return IMAGERESULT::OUTOFMEMORY;

    file->Seek(offset, FILESEEK::START);
    if (file->ReadBytes(data, size, true) != size) {
      delete[] data;
      return IMAGERESULT::FILEERROR;
    }

    // fill bitmap
    BaseBitmap *alpha = bm->AddChannel(true, true);
    if (!alpha) {
      delete[] data;
      return IMAGERESULT::MISC_ERROR;
    }

    // Set Alpha
    Bool ok = true;
    for (UInt32 i = 0; i < size && ok; ++i)
      ok =
          bm->SetAlphaPixel(alpha, i % header.width, i / header.width, data[i]);

    if (!ok) {
      delete[] data;
      return IMAGERESULT::MISC_ERROR;
    }

    // Set Color Data
    for (UInt32 i = 0; i < size && ok; ++i)
      ok = bm->SetPixel(i % header.width, i / header.width, 0xFF, 0xFF, 0xFF);

    delete[] data;

    return ok ? IMAGERESULT::OK : IMAGERESULT::MISC_ERROR;
  } else if (header.highResImageFormat ==
             VTF_IMAGEFORMAT::IMAGE_FORMAT_ARGB8888) {
    if (bm->Init(header.width, header.height, 24) != IMAGERESULT::OK)
      return IMAGERESULT::MISC_ERROR;

    // determine offset of high-res data
    const UInt32 size = UInt32(header.width) * UInt32(header.height) * 4;
    const UInt32 offset =
        UInt32(file->GetLength()) - size * (UInt32(header.frames) - frame);

    // read in raw data
    UChar *const data = new UChar[size];
    if (!data)
      return IMAGERESULT::OUTOFMEMORY;

    file->Seek(offset, FILESEEK::START);
    if (file->ReadBytes(data, size, true) != size) {
      delete[] data;
      return IMAGERESULT::FILEERROR;
    }

    // Add Alpha Channel
    BaseBitmap *Alpha = bm->AddChannel(true, true);
    if (!Alpha) {
      delete[] data;
      return IMAGERESULT::OUTOFMEMORY;
    }

    // Separate out Alpha and Colour Data
    UChar *ColourData =
        new UChar[UInt32(header.width) * UInt32(header.height) * 3];
    if (!ColourData) {
      delete[] data;
      return IMAGERESULT::OUTOFMEMORY;
    }

    Bool ok = true;
    for (UInt32 i = 0; i < size / 4 && ok; ++i) {
      ColourData[i * 3] = data[i * 4 + 1];     // Set R
      ColourData[i * 3 + 1] = data[i * 4 + 2]; // Set G
      ColourData[i * 3 + 2] = data[i * 4 + 3]; // Set B
      ok = bm->SetAlphaPixel(Alpha, i % header.width, i / header.height,
                             data[i * 4]); // Set A
    }

    delete[] data;

    // fill bitmap
    for (UInt32 y = 0; y < header.height && ok; ++y) {
      ok = bm->SetPixelCnt(0, y, header.width,
                           ColourData + (y * header.width * 3), COLORBYTES_RGB,
                           COLORMODE::RGB, PIXELCNT::NONE);
    }

    delete[] ColourData;

    return ok ? IMAGERESULT::OK : IMAGERESULT::MISC_ERROR;
  } else if (header.highResImageFormat ==
             VTF_IMAGEFORMAT::IMAGE_FORMAT_BGRA8888) {
    if (bm->Init(header.width, header.height, 24) != IMAGERESULT::OK)
      return IMAGERESULT::MISC_ERROR;

    // determine offset of high-res data
    const UInt32 size = UInt32(header.width) * UInt32(header.height) * 4;
    const UInt32 offset =
        UInt32(file->GetLength()) - size * (UInt32(header.frames) - frame);

    // read in raw data
    UChar *const data = new UChar[size];
    if (!data)
      return IMAGERESULT::OUTOFMEMORY;

    file->Seek(offset, FILESEEK::START);
    if (file->ReadBytes(data, size, true) != size) {
      delete[] data;
      return IMAGERESULT::FILEERROR;
    }

    // Add Alpha Channel
    BaseBitmap *Alpha = bm->AddChannel(true, true);
    if (!Alpha) {
      delete[] data;
      return IMAGERESULT::OUTOFMEMORY;
    }

    UChar *ColourData =
        new UChar[UInt32(header.width) * UInt32(header.height) * 3];
    if (!ColourData) {
      delete[] data;
      return IMAGERESULT::OUTOFMEMORY;
    }

    Bool ok = true;
    for (UInt32 i = 0; i < size / 4 && ok; ++i) {
      ColourData[i * 3] = data[i * 4 + 2];     // Set R
      ColourData[i * 3 + 1] = data[i * 4 + 1]; // Set G
      ColourData[i * 3 + 2] = data[i * 4];     // Set B
      ok = bm->SetAlphaPixel(Alpha, i % header.width, i / header.width,
                             data[i * 4 + 3]); // Set A
    }

    delete[] data;

    // fill bitmap
    for (UInt32 y = 0; y < header.height && ok; ++y) {
      ok = bm->SetPixelCnt(0, y, header.width,
                           ColourData + (y * header.width * 3), COLORBYTES_RGB,
                           COLORMODE::RGB, PIXELCNT::NONE);
    }

    delete[] ColourData;

    return ok ? IMAGERESULT::OK : IMAGERESULT::MISC_ERROR;
  } else if (header.highResImageFormat == VTF_IMAGEFORMAT::IMAGE_FORMAT_DXT1) {
    if (bm->Init(header.width, header.height, 24) != IMAGERESULT::OK)
      return IMAGERESULT::MISC_ERROR;

    // determine offset of high-res data
    const UInt32 CompressedSize =
        UInt32(UInt32(header.width) * UInt32(header.height) * 0.5f);
    const UInt32 offset = UInt32(file->GetLength()) -
                          CompressedSize * (UInt32(header.frames) - frame);

    // read in raw data
    UChar *const CompressedData = new UChar[CompressedSize];
    if (!CompressedData)
      return IMAGERESULT::OUTOFMEMORY;

    file->Seek(offset, FILESEEK::START);
    if (file->ReadBytes(CompressedData, CompressedSize, true) !=
        CompressedSize) {
      delete[] CompressedData;
      return IMAGERESULT::FILEERROR;
    }

    // Decompress The Data
    Bool ok = true;
    for (UInt32 b = 0;
         b < (UInt32(header.width) * UInt32(header.height) / 16) && ok; ++b) {
      PIX565 *const CompressedColour_0 = (PIX565 *)(CompressedData + (b * 8));
      PIX565 *const CompressedColour_1 = CompressedColour_0 + 1;

      const RGB888 Colour_0(*CompressedColour_0);
      const RGB888 Colour_1(*CompressedColour_1);
      const RGB888 Colour_2 = Lerp(Colour_0, Colour_1, 1.0f / 3.0f);
      const RGB888 Colour_3 = Lerp(Colour_0, Colour_1, 2.0f / 3.0f);

      UInt32 *const LookUpTable = (UInt32 *)(CompressedColour_1 + 1);
      const auto LookUpArray = ExtractTexelEntries(*LookUpTable);

      for (UChar i = 0; i < 16 && ok; ++i) {
        RGB888 Colour;
        if (LookUpArray[i] == 0b00)
          Colour = Colour_0;
        else if (LookUpArray[i] == 0b01)
          Colour = Colour_1;
        else if (LookUpArray[i] == 0b10)
          Colour = Colour_2;
        else
          Colour = Colour_3;

        const UInt32 Column = ((b * 4) % header.width) + (i % 4);
        const UInt32 Row = 4 * ((b * 4) / header.width) + (i / 4);

        ok = bm->SetPixel(Column, Row, Colour.R, Colour.G, Colour.B);
      }
    }

    delete[] CompressedData;

    return ok ? IMAGERESULT::OK : IMAGERESULT::MISC_ERROR;
  } else if (header.highResImageFormat == VTF_IMAGEFORMAT::IMAGE_FORMAT_DXT3) {
    if (bm->Init(header.width, header.height, 24) != IMAGERESULT::OK)
      return IMAGERESULT::MISC_ERROR;

    // determine offset of high-res data
    const UInt32 CompressedSize = UInt32(header.width) * UInt32(header.height);
    const UInt32 offset = UInt32(file->GetLength()) -
                          CompressedSize * (UInt32(header.frames) - frame);

    // read in raw data
    UChar *const CompressedData = new UChar[CompressedSize];
    if (!CompressedData)
      return IMAGERESULT::OUTOFMEMORY;

    file->Seek(offset, FILESEEK::START);
    if (file->ReadBytes(CompressedData, CompressedSize, true) !=
        CompressedSize) {
      delete[] CompressedData;
      return IMAGERESULT::FILEERROR;
    }

    // Add Alpha
    BaseBitmap *alpha = bm->AddChannel(true, true);
    if (!alpha) {
      delete[] CompressedData;
      return IMAGERESULT::MISC_ERROR;
    }

    // Decompress The Data
    Bool ok = true;
    for (UInt32 b = 0;
         b < (UInt32(header.width) * UInt32(header.height) / 16) && ok; ++b) {
      // Read in Alpha Data
      std::vector<UChar> AlphaArray =
          ExtractAlphaEntriesDXT3(*(UInt64 *)(CompressedData + (b * 16)));

      PIX565 *const CompressedColour_0 =
          (PIX565 *)(CompressedData + (b * 16) + 8);
      PIX565 *const CompressedColour_1 = CompressedColour_0 + 1;

      const RGB888 Colour_0(*CompressedColour_0);
      const RGB888 Colour_1(*CompressedColour_1);
      const RGB888 Colour_2 = Lerp(Colour_0, Colour_1, 1.0f / 3.0f);
      const RGB888 Colour_3 = Lerp(Colour_0, Colour_1, 2.0f / 3.0f);

      UInt32 *const LookUpTable = (UInt32 *)(CompressedColour_1 + 1);
      const auto LookUpArray = ExtractTexelEntries(*LookUpTable);

      for (UChar i = 0; i < 16 && ok; ++i) {
        RGB888 Colour;
        if (LookUpArray[i] == 0b00)
          Colour = Colour_0;
        else if (LookUpArray[i] == 0b01)
          Colour = Colour_1;
        else if (LookUpArray[i] == 0b10)
          Colour = Colour_2;
        else
          Colour = Colour_3;

        const UInt32 Column = ((b * 4) % header.width) + (i % 4);
        const UInt32 Row = 4 * ((b * 4) / header.width) + (i / 4);

        ok = bm->SetPixel(Column, Row, Colour.R, Colour.G, Colour.B);
        if (ok)
          ok = bm->SetAlphaPixel(alpha, Column, Row, AlphaArray[i]);
      }
    }

    delete[] CompressedData;

    return ok ? IMAGERESULT::OK : IMAGERESULT::MISC_ERROR;
  } else if (header.highResImageFormat == VTF_IMAGEFORMAT::IMAGE_FORMAT_DXT5) {
    if (bm->Init(header.width, header.height, 24) != IMAGERESULT::OK)
      return IMAGERESULT::MISC_ERROR;

    // determine offset of high-res data
    const UInt32 CompressedSize = UInt32(header.width) * UInt32(header.height);
    const UInt32 offset = UInt32(file->GetLength()) -
                          CompressedSize * (UInt32(header.frames) - frame);

    // read in raw data
    UChar *const CompressedData = new UChar[CompressedSize];
    if (!CompressedData)
      return IMAGERESULT::OUTOFMEMORY;

    file->Seek(offset, FILESEEK::START);
    if (file->ReadBytes(CompressedData, CompressedSize, true) !=
        CompressedSize) {
      delete[] CompressedData;
      return IMAGERESULT::FILEERROR;
    }

    // Add Alpha
    BaseBitmap *alpha = bm->AddChannel(true, true);
    if (!alpha) {
      delete[] CompressedData;
      return IMAGERESULT::MISC_ERROR;
    }

    // Decompress The Data
    Bool ok = true;
    for (UInt32 b = 0;
         b < (UInt32(header.width) * UInt32(header.height) / 16) && ok; ++b) {
      // Read in Alpha Data
      std::vector<UChar> AlphaArray =
          ExtractAlphaEntriesDXT5(*(UInt64 *)(CompressedData + (b * 16)));

      PIX565 *const CompressedColour_0 =
          (PIX565 *)(CompressedData + (b * 16) + 8);
      PIX565 *const CompressedColour_1 = CompressedColour_0 + 1;

      const RGB888 Colour_0(*CompressedColour_0);
      const RGB888 Colour_1(*CompressedColour_1);
      const RGB888 Colour_2 = Lerp(Colour_0, Colour_1, 1.0f / 3.0f);
      const RGB888 Colour_3 = Lerp(Colour_0, Colour_1, 2.0f / 3.0f);

      UInt32 *const LookUpTable = (UInt32 *)(CompressedColour_1 + 1);
      const auto LookUpArray = ExtractTexelEntries(*LookUpTable);

      for (UChar i = 0; i < 16 && ok; ++i) {
        RGB888 Colour;
        if (LookUpArray[i] == 0b00)
          Colour = Colour_0;
        else if (LookUpArray[i] == 0b01)
          Colour = Colour_1;
        else if (LookUpArray[i] == 0b10)
          Colour = Colour_2;
        else
          Colour = Colour_3;

        const UInt32 Column = ((b * 4) % header.width) + (i % 4);
        const UInt32 Row = 4 * ((b * 4) / header.width) + (i / 4);

        ok = bm->SetPixel(Column, Row, Colour.R, Colour.G, Colour.B);
        if (ok)
          ok = bm->SetAlphaPixel(alpha, Column, Row, AlphaArray[i]);
      }
    }

    delete[] CompressedData;

    return ok ? IMAGERESULT::OK : IMAGERESULT::MISC_ERROR;
  } else if (header.highResImageFormat ==
             VTF_IMAGEFORMAT::IMAGE_FORMAT_BGRX8888) {
    if (bm->Init(header.width, header.height, 24) != IMAGERESULT::OK)
      return IMAGERESULT::MISC_ERROR;

    // determine offset of high-res data
    const UInt32 DataSize = UInt32(header.width) * UInt32(header.height) * 4;
    const UInt32 offset =
        UInt32(file->GetLength()) - DataSize * (UInt32(header.frames) - frame);

    // read in raw data
    UChar *const Data = new UChar[DataSize];
    if (!Data)
      return IMAGERESULT::OUTOFMEMORY;

    file->Seek(offset, FILESEEK::START);
    if (file->ReadBytes(Data, DataSize, true) != DataSize) {
      delete[] Data;
      return IMAGERESULT::FILEERROR;
    }

    // Add XChannel
    BaseBitmap *XChannel = bm->AddChannel(false, true);
    if (!XChannel) {
      delete[] Data;
      return IMAGERESULT::MISC_ERROR;
    }

    // Separate Colour Data
    UChar *const ColourData =
        new UChar[UInt32(header.width) * UInt32(header.height) * 3];
    if (!ColourData) {
      delete[] Data;
      return IMAGERESULT::MISC_ERROR;
    }

    // Fill ColourData Array and Set X channel
    Bool ok = true;
    for (UInt32 i = 0; (i < UInt32(header.width) * UInt32(header.height)) && ok;
         ++i) {
      ColourData[i * 3] = Data[i * 4 + 2];     // Set R
      ColourData[i * 3 + 1] = Data[i * 4 + 1]; // Set G
      ColourData[i * 3 + 2] = Data[i * 4];     // Set B
      ok = bm->SetAlphaPixel(XChannel, i % header.width, i / header.width,
                             Data[i * 4 + 3]);
    }

    delete[] Data;

    // Fill Colour Bitmap
    for (UInt32 y = 0; y < header.height && ok; ++y)
      ok = bm->SetPixelCnt(0, y, header.width,
                           ColourData + (y * header.width * 3), COLORBYTES_RGB,
                           COLORMODE::RGB, PIXELCNT::NONE);

    delete[] ColourData;

    return ok ? IMAGERESULT::OK : IMAGERESULT::MISC_ERROR;
  } else if (header.highResImageFormat ==
             VTF_IMAGEFORMAT::IMAGE_FORMAT_BGR565) {
    if (bm->Init(header.width, header.height, 24) != IMAGERESULT::OK)
      return IMAGERESULT::MISC_ERROR;

    // determine offset of high-res data
    const UInt32 size = UInt32(header.width) * UInt32(header.height) * 2;
    const UInt32 offset =
        UInt32(file->GetLength()) - size * (UInt32(header.frames) - frame);

    // read in raw data
    UChar *const data = new UChar[size];
    if (!data)
      return IMAGERESULT::OUTOFMEMORY;

    file->Seek(offset, FILESEEK::START);
    if (file->ReadBytes(data, size, true) != size) {
      delete[] data;
      return IMAGERESULT::FILEERROR;
    }

    // C4D supports RGB888 but not BGR565, so we'll convert to RGB888
    UChar *const formattedData =
        new UChar[UInt32(header.width) * UInt32(header.height) * 3];
    if (!formattedData) {
      delete[] data;
      return IMAGERESULT::OUTOFMEMORY;
    }

    for (UInt32 i = 0; i < size / 2; ++i) {
      PIX565 const *const ptr = (PIX565 *)(data + (i * 2));
      formattedData[i * 3] = LUT5[ptr->z];     // set R
      formattedData[i * 3 + 1] = LUT6[ptr->y]; // set G
      formattedData[i * 3 + 2] = LUT5[ptr->x]; // set B
    }

    delete[] data;

    // fill bitmap
    Bool ok = true;
    for (UInt32 y = 0; y < header.height && ok; ++y) {
      ok = bm->SetPixelCnt(0, y, header.width,
                           formattedData + (y * header.width * 3),
                           COLORBYTES_RGB, COLORMODE::RGB, PIXELCNT::NONE);
    }

    delete[] formattedData;

    return ok ? IMAGERESULT::OK : IMAGERESULT::MISC_ERROR;
  } else if (header.highResImageFormat ==
             VTF_IMAGEFORMAT::IMAGE_FORMAT_BGRX5551) {
    if (bm->Init(header.width, header.height, 24) != IMAGERESULT::OK)
      return IMAGERESULT::MISC_ERROR;

    // determine offset of high-res data
    const UInt32 DataSize = UInt32(header.width) * UInt32(header.height) * 2;
    const UInt32 offset =
        UInt32(file->GetLength()) - DataSize * (UInt32(header.frames) - frame);

    // read in raw data
    UChar *const Data = new UChar[DataSize];
    if (!Data)
      return IMAGERESULT::OUTOFMEMORY;

    file->Seek(offset, FILESEEK::START);
    if (file->ReadBytes(Data, DataSize, true) != DataSize) {
      delete[] Data;
      return IMAGERESULT::FILEERROR;
    }

    // Add XChannel
    BaseBitmap *XChannel = bm->AddChannel(false, true);
    if (!XChannel) {
      delete[] Data;
      return IMAGERESULT::MISC_ERROR;
    }

    // Separate Colour Data
    UChar *const ColourData =
        new UChar[UInt32(header.width) * UInt32(header.height) * 3];
    if (!ColourData) {
      delete[] Data;
      return IMAGERESULT::MISC_ERROR;
    }

    // Fill ColourData Array and Set X channel
    Bool ok = true;
    for (UInt32 i = 0; (i < UInt32(header.width) * UInt32(header.height)) && ok;
         ++i) {
      PIX5551 const *const Pix = (PIX5551 *)(Data + (i * 2));
      ColourData[i * 3] = LUT5[Pix->y];     // Set R
      ColourData[i * 3 + 1] = LUT5[Pix->x]; // Set G
      ColourData[i * 3 + 2] = LUT5[Pix->w]; // Set B
      ok = bm->SetAlphaPixel(XChannel, i % header.width, i / header.width,
                             Pix->z == 1 ? 0xFF : 0x0);
    }

    delete[] Data;

    // Fill Colour Bitmap
    for (UInt32 y = 0; y < header.height && ok; ++y)
      ok = bm->SetPixelCnt(0, y, header.width,
                           ColourData + (y * header.width * 3), COLORBYTES_RGB,
                           COLORMODE::RGB, PIXELCNT::NONE);

    delete[] ColourData;

    return ok ? IMAGERESULT::OK : IMAGERESULT::MISC_ERROR;
  } else if (header.highResImageFormat ==
             VTF_IMAGEFORMAT::IMAGE_FORMAT_BGRA4444) {
    if (bm->Init(header.width, header.height, 32) != IMAGERESULT::OK)
      return IMAGERESULT::MISC_ERROR;

    // determine offset of high-res data
    const UInt32 CompressedSize =
        UInt32(header.width) * UInt32(header.height) * 2;
    const UInt32 offset = UInt32(file->GetLength()) -
                          CompressedSize * (UInt32(header.frames) - frame);

    // read in raw data
    UChar *const data = new UChar[CompressedSize];
    if (!data)
      return IMAGERESULT::OUTOFMEMORY;

    file->Seek(offset, FILESEEK::START);
    if (file->ReadBytes(data, CompressedSize, true) != CompressedSize) {
      delete[] data;
      return IMAGERESULT::FILEERROR;
    }

    // Add Alpha Channel
    BaseBitmap *Alpha = bm->AddChannel(true, true);
    if (!Alpha) {
      delete[] data;
      return IMAGERESULT::OUTOFMEMORY;
    }

    UChar *const ColourData =
        new UChar[UInt32(header.height) * UInt32(header.width) * 3];
    if (!ColourData) {
      delete[] data;
      return IMAGERESULT::MISC_ERROR;
    }

    Bool ok = true;
    for (UInt32 i = 0; i < UInt32(header.width) * UInt32(header.height) && ok;
         ++i) {
      PIX4444 const *const Pix = (PIX4444 *)(data + (i * 2));
      ColourData[i * 3] = LUT4[Pix->y];     // Set R
      ColourData[i * 3 + 1] = LUT4[Pix->x]; // Set G
      ColourData[i * 3 + 2] = LUT4[Pix->w]; // Set B
      ok = bm->SetAlphaPixel(Alpha, i % header.width, i / header.width,
                             LUT4[Pix->z]); // Set A
    }

    delete[] data;

    // fill bitmap
    for (UInt32 y = 0; y < header.height && ok; ++y) {
      ok = bm->SetPixelCnt(0, y, header.width,
                           ColourData + (y * header.width * 3), COLORBYTES_RGB,
                           COLORMODE::RGB, PIXELCNT::NONE);
    }

    delete[] ColourData;

    return ok ? IMAGERESULT::OK : IMAGERESULT::MISC_ERROR;
  } else if (header.highResImageFormat ==
             VTF_IMAGEFORMAT::IMAGE_FORMAT_DXT1_ONEBITALPHA) {
    if (bm->Init(header.width, header.height, 32) != IMAGERESULT::OK)
      return IMAGERESULT::MISC_ERROR;

    // determine offset of high-res data
    const UInt32 CompressedSize =
        UInt32(UInt32(header.width) * UInt32(header.height) * 0.5f);
    const UInt32 offset = UInt32(file->GetLength()) -
                          CompressedSize * (UInt32(header.frames) - frame);

    // read in raw data
    UChar *const CompressedData = new UChar[CompressedSize];
    if (!CompressedData)
      return IMAGERESULT::OUTOFMEMORY;

    file->Seek(offset, FILESEEK::START);
    if (file->ReadBytes(CompressedData, CompressedSize, true) !=
        CompressedSize) {
      delete[] CompressedData;
      return IMAGERESULT::FILEERROR;
    }

    // Add Alpha Channel
    BaseBitmap *alpha = bm->AddChannel(true, true);
    if (!alpha) {
      delete[] CompressedData;
      return IMAGERESULT::MISC_ERROR;
    }

    // Decompress The Data
    Bool ok = true;
    for (UInt32 b = 0;
         b < (UInt32(header.width) * UInt32(header.height) / 16) && ok; ++b) {
      PIX565 *const CompressedColour_0 = (PIX565 *)(CompressedData + (b * 8));
      PIX565 *const CompressedColour_1 = CompressedColour_0 + 1;

      const RGB888 Colour_0(*CompressedColour_0);
      const RGB888 Colour_1(*CompressedColour_1);
      const RGB888 Colour_2 = Lerp(Colour_0, Colour_1, 1.0f / 2.0f);
      const RGB888 Colour_3 = RGB888(0, 0, 0);

      UInt32 *const LookUpTable = (UInt32 *)(CompressedColour_1 + 1);
      const auto LookUpArray = ExtractTexelEntries(*LookUpTable);

      for (UChar i = 0; i < 16 && ok; ++i) {
        RGB888 Colour;
        UChar AlphaPix;
        if (LookUpArray[i] == 0b00) {
          Colour = Colour_0;
          AlphaPix = 0xFF;
        } else if (LookUpArray[i] == 0b01) {
          Colour = Colour_1;
          AlphaPix = 0xFF;
        } else if (LookUpArray[i] == 0b10) {
          Colour = Colour_2;
          AlphaPix = 0xFF;
        } else {
          Colour = Colour_3;
          AlphaPix = 0x0;
        }

        const UInt32 Column = ((b * 4) % header.width) + (i % 4);
        const UInt32 Row = 4 * ((b * 4) / header.width) + (i / 4);

        ok = bm->SetPixel(Column, Row, Colour.R, Colour.G, Colour.B);
        if (ok)
          ok = bm->SetAlphaPixel(alpha, Column, Row, AlphaPix);
      }
    }

    delete[] CompressedData;

    return ok ? IMAGERESULT::OK : IMAGERESULT::MISC_ERROR;
  } else if (header.highResImageFormat ==
             VTF_IMAGEFORMAT::IMAGE_FORMAT_BGRA5551) {
    if (bm->Init(header.width, header.height, 24) != IMAGERESULT::OK)
      return IMAGERESULT::MISC_ERROR;

    // determine offset of high-res data
    const UInt32 DataSize = UInt32(header.width) * UInt32(header.height) * 2;
    const UInt32 offset =
        UInt32(file->GetLength()) - DataSize * (UInt32(header.frames) - frame);

    // read in raw data
    UChar *const Data = new UChar[DataSize];
    if (!Data)
      return IMAGERESULT::OUTOFMEMORY;

    file->Seek(offset, FILESEEK::START);
    if (file->ReadBytes(Data, DataSize, true) != DataSize) {
      delete[] Data;
      return IMAGERESULT::FILEERROR;
    }

    // Add Alpha Channel
    BaseBitmap *AlphaChannel = bm->AddChannel(true, true);
    if (!AlphaChannel) {
      delete[] Data;
      return IMAGERESULT::MISC_ERROR;
    }

    // Separate Colour Data
    UChar *const ColourData =
        new UChar[UInt32(header.width) * UInt32(header.height) * 3];
    if (!ColourData) {
      delete[] Data;
      return IMAGERESULT::MISC_ERROR;
    }

    // Fill ColourData Array and Set X channel
    Bool ok = true;
    for (UInt32 i = 0; (i < UInt32(header.width) * UInt32(header.height)) && ok;
         ++i) {
      PIX5551 const *const Pix = (PIX5551 *)(Data + (i * 2));
      ColourData[i * 3] = LUT5[Pix->y];     // Set R
      ColourData[i * 3 + 1] = LUT5[Pix->x]; // Set G
      ColourData[i * 3 + 2] = LUT5[Pix->w]; // Set B
      ok = bm->SetAlphaPixel(AlphaChannel, i % header.width, i / header.width,
                             Pix->z == 1 ? 0xFF : 0x0);
    }

    delete[] Data;

    // Fill Colour Bitmap
    for (UInt32 y = 0; y < header.height && ok; ++y)
      ok = bm->SetPixelCnt(0, y, header.width,
                           ColourData + (y * header.width * 3), COLORBYTES_RGB,
                           COLORMODE::RGB, PIXELCNT::NONE);

    delete[] ColourData;

    return ok ? IMAGERESULT::OK : IMAGERESULT::MISC_ERROR;
  } else if (header.highResImageFormat == VTF_IMAGEFORMAT::IMAGE_FORMAT_UV88) {
    if (bm->Init(header.width, header.height, 24) != IMAGERESULT::OK)
      return IMAGERESULT::MISC_ERROR;

    // determine offset of high-res data
    const UInt32 size = UInt32(header.width) * UInt32(header.height) * 2;
    const UInt32 offset =
        UInt32(file->GetLength()) - size * (UInt32(header.frames) - frame);

    // read in raw data
    UChar *const data = new UChar[size];
    if (!data)
      return IMAGERESULT::OUTOFMEMORY;

    file->Seek(offset, FILESEEK::START);
    if (file->ReadBytes(data, size, true) != size) {
      delete[] data;
      return IMAGERESULT::FILEERROR;
    }

    // add in a black blue channel
    UChar *const ImageData =
        new UChar[UInt32(header.height) * UInt32(header.width) * 3];
    if (!ImageData) {
      delete[] data;
      return IMAGERESULT::MISC_ERROR;
    }

    for (size_t i = 0; i < UInt32(header.height) * UInt32(header.width); ++i) {
      ImageData[i * 3] = data[i * 2];         // Set U to R
      ImageData[i * 3 + 1] = data[i * 2 + 1]; // Set V to G
      ImageData[i * 3 + 2] = 0x00;            // Set B to black
    }

    delete[] data;

    // fill bitmap
    Bool ok = true;
    for (UInt32 y = 0; y < header.height && ok; ++y) {
      ok = bm->SetPixelCnt(0, y, header.width,
                           ImageData + (y * header.width * 3), COLORBYTES_RGB,
                           COLORMODE::RGB, PIXELCNT::NONE);
    }

    delete[] ImageData;

    return ok ? IMAGERESULT::OK : IMAGERESULT::MISC_ERROR;
  } else if (header.highResImageFormat ==
             VTF_IMAGEFORMAT::IMAGE_FORMAT_UVWQ8888) {
    if (bm->Init(header.width, header.height, 24) != IMAGERESULT::OK)
      return IMAGERESULT::MISC_ERROR;

    // determine offset of high-res data
    const UInt32 DataSize = UInt32(header.width) * UInt32(header.height) * 4;
    const UInt32 offset =
        UInt32(file->GetLength()) - DataSize * (UInt32(header.frames) - frame);

    // read in raw data
    UChar *const Data = new UChar[DataSize];
    if (!Data)
      return IMAGERESULT::OUTOFMEMORY;

    file->Seek(offset, FILESEEK::START);
    if (file->ReadBytes(Data, DataSize, true) != DataSize) {
      delete[] Data;
      return IMAGERESULT::FILEERROR;
    }

    // Add QChannel
    BaseBitmap *QChannel = bm->AddChannel(false, true);
    if (!QChannel) {
      delete[] Data;
      return IMAGERESULT::MISC_ERROR;
    }

    // Separate Colour Data
    UChar *const ColourData =
        new UChar[UInt32(header.width) * UInt32(header.height) * 3];
    if (!ColourData) {
      delete[] Data;
      return IMAGERESULT::MISC_ERROR;
    }

    // Fill ColourData Array and Set Q channel
    Bool ok = true;
    for (UInt32 i = 0; (i < UInt32(header.width) * UInt32(header.height)) && ok;
         ++i) {
      ColourData[i * 3] = Data[i * 4];         // Set R to U
      ColourData[i * 3 + 1] = Data[i * 4 + 1]; // Set G to V
      ColourData[i * 3 + 2] = Data[i * 4 + 2]; // Set B to W
      ok = bm->SetAlphaPixel(QChannel, i % header.width, i / header.width,
                             Data[i * 4 + 3]);
    }

    delete[] Data;

    // Fill Colour Bitmap
    for (UInt32 y = 0; y < header.height && ok; ++y)
      ok = bm->SetPixelCnt(0, y, header.width,
                           ColourData + (y * header.width * 3), COLORBYTES_RGB,
                           COLORMODE::RGB, PIXELCNT::NONE);

    delete[] ColourData;

    return ok ? IMAGERESULT::OK : IMAGERESULT::MISC_ERROR;
  } else if (header.highResImageFormat ==
             VTF_IMAGEFORMAT::IMAGE_FORMAT_RGBA16161616F) {
    return IMAGERESULT::WRONGTYPE;
  } else if (header.highResImageFormat ==
             VTF_IMAGEFORMAT::IMAGE_FORMAT_RGBA16161616) {
    return IMAGERESULT::WRONGTYPE;
  } else if (header.highResImageFormat ==
             VTF_IMAGEFORMAT::IMAGE_FORMAT_UVLX8888) {
    if (bm->Init(header.width, header.height, 24) != IMAGERESULT::OK)
      return IMAGERESULT::MISC_ERROR;

    // determine offset of high-res data
    const UInt32 DataSize = UInt32(header.width) * UInt32(header.height) * 4;
    const UInt32 offset =
        UInt32(file->GetLength()) - DataSize * (UInt32(header.frames) - frame);

    // read in raw data
    UChar *const Data = new UChar[DataSize];
    if (!Data)
      return IMAGERESULT::OUTOFMEMORY;

    file->Seek(offset, FILESEEK::START);
    if (file->ReadBytes(Data, DataSize, true) != DataSize) {
      delete[] Data;
      return IMAGERESULT::FILEERROR;
    }

    // Add XChannel
    BaseBitmap *XChannel = bm->AddChannel(false, true);
    if (!XChannel) {
      delete[] Data;
      return IMAGERESULT::MISC_ERROR;
    }

    // Separate Colour Data
    UChar *const ColourData =
        new UChar[UInt32(header.width) * UInt32(header.height) * 3];
    if (!ColourData) {
      delete[] Data;
      return IMAGERESULT::MISC_ERROR;
    }

    // Fill ColourData Array and Set X channel
    Bool ok = true;
    for (UInt32 i = 0; (i < UInt32(header.width) * UInt32(header.height)) && ok;
         ++i) {
      ColourData[i * 3] = Data[i * 4];         // Set R to U
      ColourData[i * 3 + 1] = Data[i * 4 + 1]; // Set G to V
      ColourData[i * 3 + 2] = Data[i * 4 + 2]; // Set B to L
      ok = bm->SetAlphaPixel(XChannel, i % header.width, i / header.width,
                             Data[i * 4 + 3]);
    }

    delete[] Data;

    // Fill Colour Bitmap
    for (UInt32 y = 0; y < header.height && ok; ++y)
      ok = bm->SetPixelCnt(0, y, header.width,
                           ColourData + (y * header.width * 3), COLORBYTES_RGB,
                           COLORMODE::RGB, PIXELCNT::NONE);

    delete[] ColourData;

    return ok ? IMAGERESULT::OK : IMAGERESULT::MISC_ERROR;
  }

  return IMAGERESULT::MISC_ERROR;
}

Bool VTFLoaderData::RegisterPlugin() {
  if (!RegisterBitmapLoaderPlugin(ID_VTFLOADER, "Valve Texture Format Loader"_s,
                                  0, NewObjClear(VTFLoaderData)))
    return false;

  return true;
}