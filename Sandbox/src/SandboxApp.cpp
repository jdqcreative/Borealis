#include <Borealis.h>

class Sandbox : public Borealis::Application
{
public:
	Sandbox()
	{}

	~Sandbox()
	{}
};

Borealis::Application* Borealis::CreateApplication()
{
	return new Sandbox();
}