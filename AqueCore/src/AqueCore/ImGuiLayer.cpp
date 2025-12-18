#include "AqueCore/ImGuiLayer.h"
#include "imgui.h"
#include "AqueCore/ImGui/imgui_impl_glfw.h"
#include "AqueCore/ImGui/imgui_impl_opengl3.h"
#include "AqueCore/Application.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

AQC::ImGuiLayer::ImGuiLayer()
	: Layer("ImGui Layer")
{}

void AQC::ImGuiLayer::OnAttach()
{
	IMGUI_CHECKVERSION();
	ImGuiContext* ctx = ImGui::GetCurrentContext();
	if (!ctx)
		ctx = ImGui::CreateContext();
	ImGui::SetCurrentContext(ctx);

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
	io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;
	io.BackendFlags |= ImGuiBackendFlags_RendererHasViewports;

	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport

	// ----- Style -----
	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// ----- Get GLFW Window -----
	Application& app = Application::Get();
	GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

	// ----- Initialize Platform/Renderer bindings -----
	ImGui_ImplGlfw_InitForOpenGL(window, true);


	ImGui_ImplOpenGL3_Init("#version 130");
}

void AQC::ImGuiLayer::OnDetach()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void AQC::ImGuiLayer::Begin()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void AQC::ImGuiLayer::End()
{
	ImGuiIO& io = ImGui::GetIO();
	io = ImGui::GetIO();
	Application& app = Application::Get();
	io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

	// Rendering
	ImGui::Render();
	
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_context = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_context);
	}
}

void AQC::ImGuiLayer::OnImGuiRender()
{
	static bool showDemo = true;
	ImGui::ShowDemoWindow();
}
