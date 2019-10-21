@echo off

echo 该文件用于清理不需要的CMSIS组件。这会默认删除一些文件，并向你询问是否删除更多文件。如果你不知道删除这些文件的后果，请一律选N。

rmdir /s /q "Core_A" "CoreValidation" "DAP" "Documentation" "Doxygen" "Driver" "Pack" "RTOS" "RTOS2" "Utilities"

rmdir /s /q "Core\Template" "DSP\DSP_Lib_TestSuite" "DSP\Examples" "DSP\Projects"  "NN\Examples" "NN\NN_Lib_Tests" "NN\Scripts" 

echo 删除DSP_Lib和NN_Lib的源文件？
rmdir /s "NN\Source" "DSP\Source"
echo 删除不需要的静态库可以节约大量时间。需要保留哪个编译器的静态库？
echo 删除ARM的静态库？
rmdir /s "DSP\Lib\ARM"
echo 删除GCC的静态库？
rmdir /s "DSP\Lib\GCC"
echo 删除IAR的静态库？
rmdir /s "DSP\Lib\IAR"

echo 操作完成
pause