#pragma once

#ifdef BO_PLATFORM_WINDOWS

extern Borealis::Application* Borealis::CreateApplication();

int main(int argc, char** argv)
{
	Borealis::Log::Init();
	BO_CORE_WARN("Initialized Log!");
	int a = 5;
	BO_INFO("Hello! Var={0}", a);

	auto app = Borealis::CreateApplication();
	app->Run();
	delete app;
}

#endif