#include "AppModeList.h"
#include <AppLogic/AppModes/ImageProcessingMode.h>

AppModeList::AppModeList()
    : super( L"AppModeList" )
{
	std::vector<vl::ref<AppMode>> appModes =
	{
		new ImageProcessingMode
	};

	for ( auto& appMode : appModes )
	{
		Add( appMode.get() );
	}
}