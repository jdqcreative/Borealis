#pragma once

#include "Core.h"

#include "Window.h"
#include "Borealis/LayerStack.h"
#include "Events/Event.h"
#include "Borealis/Events/ApplicationEvent.h"

#include "Window.h"

namespace Borealis {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void Run();

		void OnEvent(Event& e);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}



