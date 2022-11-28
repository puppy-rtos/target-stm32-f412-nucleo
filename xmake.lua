
includes("toolchains/*.lua")

add_rules("mode.debug", "mode.release")

add_defines("USE_HAL_DRIVER", "STM32F412Zx")
add_includedirs("Drivers/STM32F4xx_HAL_Driver/Inc", 
                "Drivers/STM32F4xx_HAL_Driver/Inc/Legacy", 
                "Core/Inc", 
                "Drivers/CMSIS/Device/ST/STM32F4xx/Include",
                "Drivers/CMSIS/Include", 
                "../kernel/include",
                "../nr_micro_shell/inc"
                )

-- target("kernel")
--     add_rules("mdk.static")
--     add_files("../kernel/**.c")

target("hello")
    -- add_deps("kernel")
    add_files("../kernel/**.c")
    add_files("Core/Src/*.c", "/Drivers/**.c")
    add_files("../nr_micro_shell/src/*.c", "../nr_micro_shell/examples/nr_micro_shell_commands.c")
    if is_plat("armclang") then
        add_files("Drivers/CMSIS/Device/ST/STM32F4xx/arm/*.s")
        set_toolchains("armclang")
        set_arch("cortex-m4")
        add_rules("mdk.binary")
        set_runtimes("microlib")
        add_ldflags('--strict --scatter link.sct')
        after_build(function (package)
            os.exec("D:/Progm/Keil_v5/ARM/ARMCLANG/bin/fromelf.exe --bin $(buildir)/armclang/cortex-m4/debug/hello.axf --output puppy.bin")
        end)
    elseif is_plat("gcc") then
        add_files("Drivers/CMSIS/Device/ST/STM32F4xx/gcc/*.s")
        set_toolchains("arm-none-eabi")
        set_extension(".elf")
        set_arch("cortex-m4")
        add_links("c", "m", "nosys");
        add_ldflags(' -T link.lds')
        after_build(function (package)
            os.exec("D:/Progm/env-windows/tools/gnu_gcc/arm_gcc/mingw/bin/arm-none-eabi-objcopy.exe -O binary $(buildir)/gcc/cortex-m4/debug/hello.elf puppy.bin")
        end)       
    end
