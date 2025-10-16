set_project("ShadowPlay2")
set_arch("x64")
set_languages("cxx17")
set_warnings("all")
add_rules("mode.debug", "mode.release")

if is_plat("windows") then 
    add_requires("vulkansdk", "glfw", "glm", "d3d11")
end 
if is_plat("linux") then 
    add_requires("cmake::Vulkan", "glfw", "glm")
end 

target("ShadowPlay2")
    set_kind("shared")
    set_targetdir("ShadowPlay2")
    add_files("ShadowPlay2/Core/RHI/*.cpp")
    add_files("ShadowPlay2/Core/RHI/OpenGL/*.cpp")
    add_files("ShadowPlay2/Core/RHI/Vulkan/*.cpp")
    add_files("ShadowPlay2/Core/RHI/DirectX/*.cpp")
    add_files("ShadowPlay2/Core/Presentation/*.cpp")
    add_files("ShadowPlay2/Core/Presentation/Win32/*.cpp")
    add_files("ShadowPlay2/Core/Presentation/General/*.cpp")
    add_files("ShadowPlay2/Core/HAL/Memory/*.cpp")
    add_files("ShadowPlay2/Core/HAL/Async/*.cpp")
    add_files("ShadowPlay2/Core/Common/*.cpp")
    add_files("ShadowPlay2/Core/Tools/*.cpp")
    add_files("ShadowPlay2/Engine/World/*.cpp")
    add_files("ShadowPlay2/Engine/Render/*.cpp")
    add_files("ShadowPlay2/*.cpp")
    add_files("Vendor/glad/src/*.c")
    add_headerfiles("ShadowPlay2/Core/RHI/*.h")
    add_headerfiles("ShadowPlay2/Core/RHI/OpenGL/*.h")
    add_headerfiles("ShadowPlay2/Core/RHI/Vulkan/*.h")
    add_headerfiles("ShadowPlay2/Core/RHI/DirectX/*.h")
    add_headerfiles("ShadowPlay2/Core/Presentation/*.h")
    add_headerfiles("ShadowPlay2/Core/Presentation/Win32/*.h")
    add_headerfiles("ShadowPlay2/Core/Presentation/General/*.h")
    add_headerfiles("ShadowPlay2/Core/HAL/Memory/*.h")
    add_headerfiles("ShadowPlay2/Core/HAL/Async/*.h")
    add_headerfiles("ShadowPlay2/Core/Common/*.h")
    add_headerfiles("ShadowPlay2/Core/Tools/*.h")
    add_headerfiles("ShadowPlay2/Engine/World/*.h")
    add_headerfiles("ShadowPlay2/Engine/Render/*.h")
    add_headerfiles("ShadowPlay2/Engine/Math/*.h")
    add_headerfiles("ShadowPlay2/*.h")
    add_includedirs("ShadowPlay2")
    add_includedirs("Vendor/glad/include")

    set_pcxxheader("ShadowPlay2/ShadowPreCompileHeader.h")

    add_defines("SHADOWPLAY_CORE_EXPORT")
    add_defines("SHADOWPLAY_ACC_AVX")
    add_defines("SHADOWPLAY_API_VK")
    add_defines("SHADOWPLAY_API_DIRECTX")
    if is_plat("windows") then
        add_defines("SHADOWPLAY_PLAT_WIN")
        add_defines("NOMINMAX")
        add_packages("vulkansdk", "glfw", "glm", "d3d11")
    end
    if is_plat("linux") then
        add_defines("SHADOWPLAY_PLAT_LINUX")
        add_packages("cmake::Vulkan", "glfw", "glm")
    end
    if is_mode("debug") then
        add_defines("SHADOWPLAY_DEBUG")
    end

    set_symbols("debug")
    set_strip("all")

    set_basename("ShadowPlay2")
    set_targetdir("bin/$(arch)/$(mode)")
    set_objectdir("bin-int/$(arch)/$(mode)")
target_end()

target("SPDemo")
    set_kind("binary")
    add_deps("ShadowPlay2")
    set_targetdir("SPDemo")
    add_files("SPDemo/*.cpp")
    add_headerfiles("SPDemo/*.h")
    add_includedirs("ShadowPlay2")

    set_symbols("debug")
    set_strip("all")

    if is_plat("windows") then
        add_defines("SHADOWPLAY_PLAT_WIN")
    end
    if is_plat("linux") then
        add_defines("SHADOWPLAY_PLAT_LINUX")
    end

    set_basename("SPDemo")
    set_targetdir("bin/$(arch)/$(mode)")
    set_objectdir("bin-int/$(arch)/$(mode)")
target_end()
