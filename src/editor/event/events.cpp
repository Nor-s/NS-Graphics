#include "events.h"
#include "../app.h"

namespace ns::editor
{

void SceneRenderTargetResizeEvent::execute()
{
    App::SceneResize(sceneId_, resolution_);
}

void SceneFocusEvent::execute()
{
    App::SetSceneFocus(sceneId_, bIsFocus_);
}

}	 // namespace ns::editor