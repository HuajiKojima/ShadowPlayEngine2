set_project("ShadowPlay2")
set_arch("x64")
set_warnings("all")
add_rules("mode.debug", "mode.release")

add_requires("vulkansdk", "glfw", "glm")

target("ShadowPlay2")
    set_kind("shared")
    set_targetdir("ShadowPlay2")
    add_files("ShadowPlay2/Core/RHI/*.cpp")
    add_files("ShadowPlay2/Core/Memory/*.cpp")
    add_files("ShadowPlay2/*.cpp")
    add_headerfiles("ShadowPlay2/Core/RHI/*.h")
    add_headerfiles("ShadowPlay2/Core/Memory/*.h")
    add_headerfiles("ShadowPlay2/*.h")
    add_includedirs("ShadowPlay2")
    add_packages("vulkansdk", "glfw", "glm")

    set_pcxxheader("ShadowPlay2/ShadowPreCompileHeader.h")

    add_defines("SHADOWPLAY_CORE_EXPORT")
    add_defines("SHADOWPLAY_ACC_AVX")
    add_defines("SHADOWPLAY_API_VK")
    if is_plat("windows") then
        add_defines("SHADOWPLAY_PLAT_WIN")
    end
    if is_plat("linux") then
        add_defines("SHADOWPLAY_PLAT_LINUX")
    end
    if is_mode("debug") then
        add_defines("SHADOWPLAY_DEBUG")
    end

    set_symbols("debug")
    set_strip("all")

    set_basename("ShadowPlay2_$(mode)_$(arch)")
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

    set_basename("SPDemo_$(mode)_$(arch)")
    set_targetdir("bin/$(arch)/$(mode)")
    set_objectdir("bin-int/$(arch)/$(mode)")
target_end()
