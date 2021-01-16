#ifndef LAYER_H
#define LAYER_H

#include "../Core/Core.h"
#include "../Event/Event.h"

namespace Engine
{
	class ENGINE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() { return m_debugName; }

	protected:
		std::string m_debugName;
	};
}

#endif
