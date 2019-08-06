using NewLife.Build;

var build = Builder.Create("MDK");
build.Init(false);
build.CPU = "Cortex-M3";
build.AddFiles(".", "*.c;*.cpp", true, "system_stm32f10x");
build.AddIncludes("cmsis", false);
build.AddIncludes("inc", false);
build.Defines.Add("USE_STDPERIPH_DRIVER");
build.CompileAll();
build.BuildLib();

//build.Debug = false;
//build.CompileAll();
//build.BuildLib();

build.Debug = true;
build.CompileAll();
build.BuildLib();