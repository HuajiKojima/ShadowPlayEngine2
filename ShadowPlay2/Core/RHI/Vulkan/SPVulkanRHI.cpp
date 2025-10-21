#include "ShadowPreCompileHeader.h"
#include "SPVulkanRHI.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace ShadowPlay
{
    struct SPVulkanRHIPrivate
    {
        // The large param is up, smaller is down.
		VkInstance m_instance = nullptr;			// 8 Bytes
    };

	void ReleaseVulkanRHIPrivate(SPVulkanRHIPrivate* m_pri)
	{
		if (m_pri != nullptr)
		{
			delete m_pri;
			m_pri = nullptr;
		}
	}
    
    SPVulkanRHI::SPVulkanRHI(const SPVulkanBaseRelays& relay):
		SPRHI(relay.m_baseRHIRelay),
		p_vk(new SPVulkanRHIPrivate, ReleaseVulkanRHIPrivate)
    {
    }
    SPVulkanRHI::~SPVulkanRHI()
    {
        SHADOWPLAY_ASSERT(p_vk != nullptr);
    }
    void SPVulkanRHI::RHIInit(uint32_t width, uint32_t height, const char *windowTitle)
    {
        SHADOWPLAY_ASSERT(p_vk != nullptr);
        setPrivate(width, height, windowTitle);
        CreateVulkanInstance();
    }
    void SPVulkanRHI::RHIRendering()
    {
        
    }
    void SPVulkanRHI::RHITerminate()
    {
        vkDestroyInstance(p_vk->m_instance, nullptr);
    }
    void SPVulkanRHI::CreateVulkanInstance()
    {
        uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		std::vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
		std::cout << "available_extensions" << std::endl;
		for (const auto& extension : extensions)
		{
			std::cout << "\t" << extension.extensionName << std::endl;
		}

		// Application Info
		// ----------------------------------------------------------------------------------------------------
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "ShadowPlay Application";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;
		appInfo.pNext = nullptr;								
		// ----------------------------------------------------------------------------------------------------

		// Instance create info
		// ----------------------------------------------------------------------------------------------------
		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		createInfo.pNext = nullptr;								

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::cout << "glfw_vulkan_extesions: " << std::endl;
		for (uint32_t i = 0; i < glfwExtensionCount; i++) 
		{
			std::cout << "\t" << std::string(glfwExtensions[i]) << std::endl;
		}

		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;
		createInfo.enabledLayerCount = 0;
		// ----------------------------------------------------------------------------------------------------

		if (vkCreateInstance(&createInfo, nullptr, &(p_vk->m_instance)) != VkResult::VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create Vulkan m_instance!");
		}
    }
}