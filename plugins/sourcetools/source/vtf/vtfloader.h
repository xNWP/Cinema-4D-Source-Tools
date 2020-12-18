#pragma once

#include "c4d_filterdata.h"

#define ID_VTFLOADER 1053587

class VTFLoaderData : public BitmapLoaderData {
public:
  Bool Identify(const Filename &name, UChar *probe, Int32 size) override;
  IMAGERESULT Load(const Filename &name, BaseBitmap *bm, Int32 frame) override;

  static Bool RegisterPlugin();
};