#include "LiveComponent.h"
#include "core/Application.h"

EntityComponentSystem& LiveComponent::ECS()
{
    return *Application::Get().GetECS();
}
