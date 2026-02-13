#include <Borealis.h>

class ExampleLayer : public Borealis::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override
	{
		BO_INFO("ExampleLayer::Update");
	}

	void OnEvent(Borealis::Event& event) override
	{
		BO_TRACE("{0}", event);
	}
};

class Sandbox : public Borealis::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{}
};

Borealis::Application* Borealis::CreateApplication()
{
	return new Sandbox();
}