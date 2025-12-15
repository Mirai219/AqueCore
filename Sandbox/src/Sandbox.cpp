#include "AqueCore.h"

class Sandbox : public AQC::Application
{
public:
	Sandbox()
	{

	}
	
	~Sandbox()
	{

	}
};

AQC::Application* AQC::CreateApplication()
{
	return new Sandbox();
}