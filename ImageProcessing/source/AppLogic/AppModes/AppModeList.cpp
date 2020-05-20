#include "AppModeList.h"
#include <AppLogic/AppModes/ImageProcessingMode.h>
#include <AppLogic/AppModes/Editor3DMode.h>

AppModeList::AppModeList()
    : super( L"AppModeList" )
{
	std::vector<vl::ref<AppMode>> appModes =
	{
		new ImageProcessingMode,
		new Editor3DMode
	};

	for ( auto& appMode : appModes )
	{
		Add( appMode.get() );
	}
}