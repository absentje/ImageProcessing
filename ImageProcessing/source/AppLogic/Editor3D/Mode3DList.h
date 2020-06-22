#pragma once
#include <AppLogic/SelectTools/SelectableList.h>
#include <vlGraphics/SceneManagerActorTree.hpp>

class Mode3DList: public SelectableList
{
	VL_INSTRUMENT_CLASS( Mode3DList, SelectableList );
public:
	Mode3DList( vl::SceneManagerActorTree* scene );

private:
};