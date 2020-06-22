#include "Mode3DList.h"
#include "Mode3D.h"
#include <AppLogic/Editor3D/Modes3D/PBRViewMode.h>

Mode3DList::Mode3DList()
	: super( L"Mode3DList" )
{
	std::vector<vl::ref<Mode3D>> modes3D =
	{
		new PBRViewMode
	};

	for ( auto mode3D : modes3D )
	{
		Add( mode3D.get() );
	}
}