#pragma once

#ifdef AQC_PLATFORM_WINDOWS

extern AQC::Application* AQC::CreateApplication();

int main(int argc, char** argv)
{
	AQC::Log::Init();

	auto app = AQC::CreateApplication();
	app->Run();
	delete app;
}

#endif 