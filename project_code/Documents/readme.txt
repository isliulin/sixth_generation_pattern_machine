工程存储分配
$PROJ_DIR$\XMC4500xxxxx1024.icf



工程文件目录
$PROJ_DIR$\..\..\Libraries\XMCLib\inc
$PROJ_DIR$\..\..\Libraries\CMSIS\Include
$PROJ_DIR$\..\..\Libraries\CMSIS\Device\Infineon\XMC4500_series\Include
$PROJ_DIR$\..\..\Applications\App\inc
$PROJ_DIR$\..\..\Applications\Bsp\inc
$PROJ_DIR$\..\..\Applications\Motor\inc
$PROJ_DIR$\..\..\Applications\System\inc
$PROJ_DIR$\..\..\Applications\Unit\inc
$PROJ_DIR$\..\..\Applications\User\inc
$PROJ_DIR$\..\..\Applications\Test


2018.02.27
1.创建工程模板，规划文件名称以及文件类别。

2018.03.14
1.HRPWM如何应用，没有找到相关的例程？
2.编码器接口具体的读出数据是A相个数+B相个数分别读，还是在同一寄存器中一起读出？
3.CAN0的中断有8个中断入口，但是未找到CAN1的中断入口？

2018.04.11
1.资源分配情况需要与原理图确认

2018.04.30
1.XMC系列单片机起始地址可以是0x08000000起始地址，也可以是0x0C000000，具体原因不明。
2.Flash擦除后填充的竟然是0x00，而非0xFF，这与其他的单片机不同。

2018.06.26
1.XMC4402总的存储空间为256K，引导:32K，数据:32K，程序:192K
2.Flash的读写功能调试完成。

2018.08.28
1.增加MDK-ARM-V5和MDK-ARM-V4两个开发环境的工程兼容，DAVE暂未添加。
2.增加各个开发环境对IQmath库的支持，方便进行电机控制以及相关运算，以定点运算为主。



fromelf --bin --output "$L@L.bin"  "#L"

ARM Compiler could not determine the product installation it is part of. You might be able to resolve this by reinstalling the tools, or ensuring that ARM_TOOL_VARIANT and ARM_PRODUCT_PATH are set appropriately.
遗留问题：



未解问题：

1.uart需要增加printf功能定义；
2.spi通信需按照6字节完成；


