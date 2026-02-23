#include <Borealis.h>

class ExampleLayer : public Borealis::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override
	{
		if (Borealis::Input::IsKeyPressed(BO_KEY_TAB))
			BO_TRACE("Tab key is pressed!");
	}

	void OnEvent(Borealis::Event& event) override
	{
		if (event.GetEventType() == Borealis::EventType::KeyPressed)
		{
			Borealis::KeyPressedEvent& e = (Borealis::KeyPressedEvent&)event;
			BO_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Borealis::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Borealis::ImGuiLayer());
	}

	~Sandbox()
	{}
};

Borealis::Application* Borealis::CreateApplication()
{
	return new Sandbox();
}