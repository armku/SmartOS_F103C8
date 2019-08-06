using NewLife.Build;

var build = Builder.Create("GCCArm");
build.Init(false);
build.CPU = "Cortex-M4";
build.Defines.Add("STM32F4");
build.AddIncludes("..\\..\\..\\LibF4\\CMSIS");
build.AddIncludes("..\\..\\..\\LibF4\\Inc");
build.AddIncludes("..\\", false);
build.AddIncludes("..\\..\\", false);
build.AddFiles(".", "*.c;*.cpp;*.s");
build.AddFiles("..\\CortexM", "*.c;*.cpp;*.s");
build.Libs.Clear();
build.CompileAll();
build.BuildLib("..\\..\\SmartOS_F4");

build.Debug = true;
build.CompileAll();
build.BuildLib("..\\..\\SmartOS_F4");