#include "AqueCore.h"

class Sandbox : public AQC::Application
{
public:
	Sandbox()
	{
		AQC_INFO("Create Sandbox Successfully!");
	}
	
	~Sandbox()
	{

	}
};

AQC::Application* AQC::CreateApplication()
{
	return new Sandbox();
}