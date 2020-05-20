#pragma once
#include <string>
#include <vlCore/Vector4.hpp>
#include <AppLogic/AppModes/AppMode.h>
#include <vlCore/String.hpp>

class ImageEffectList;

namespace VLExtension
{
class TextureViewActor;
}

namespace vl
{
    class Image;
}

class Editor3DMode: public AppMode
{
    VL_INSTRUMENT_CLASS( Editor3DMode, AppMode )
public:
    Editor3DMode();
    virtual QWidget* CreateWidget( QWidget* parent ) override;

private:
};