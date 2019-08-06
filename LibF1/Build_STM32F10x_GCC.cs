using NewLife.Build;

var build = Builder.Create("GCCArm");
build.Init(false);
build.CPU = "Cortex-M3";
build.AddFiles(".", "*.c;*.cpp", true, "system_stm32f10x");
build.AddIncludes("cmsis", false);
build.AddIncludes("inc", false);
build.Defines.Add("USE_STDPERIPH_DRIVER");
build.CompileAll();
build.BuildLib("libSTM32F10x.a");

build.Debug = true;
build.CompileAll();
build.BuildLib("libSTM32F10x.a");
