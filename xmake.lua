add_rules("mode.debug", "mode.release")

set_runtimes("microlib")
add_defines("USE_HAL_DRIVER", "STM32F412Zx")
add_ldflags('--strict --scatter link.sct')
add_includedirs("Drivers/STM32F4xx_HAL_Driver/Inc", 
                "Drivers/STM32F4xx_HAL_Driver/Inc/Legacy", 
                "Core/Inc", 
                "Drivers/CMSIS/Device/ST/STM32F4xx/Include",
                "Drivers/CMSIS/Include", 
                "../kernel/include")

-- target("kernel")
--     add_rules("mdk.static")
--     add_files("../kernel/**.c")

target("hello")
    -- add_deps("kernel")
    add_files("../kernel/**.c")
    add_rules("mdk.binary")
    add_files("Core/Src/*.c", "/Drivers/**.c", "Drivers/STM32F4xx_HAL_Driver/Src/*.s")
