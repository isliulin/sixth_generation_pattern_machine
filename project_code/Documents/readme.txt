���̴洢����
$PROJ_DIR$\XMC4500xxxxx1024.icf



�����ļ�Ŀ¼
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
1.��������ģ�壬�滮�ļ������Լ��ļ����

2018.03.14
1.HRPWM���Ӧ�ã�û���ҵ���ص����̣�
2.�������ӿھ���Ķ���������A�����+B������ֱ����������ͬһ�Ĵ�����һ�������
3.CAN0���ж���8���ж���ڣ�����δ�ҵ�CAN1���ж���ڣ�

2018.04.11
1.��Դ���������Ҫ��ԭ��ͼȷ��

2018.04.30
1.XMCϵ�е�Ƭ����ʼ��ַ������0x08000000��ʼ��ַ��Ҳ������0x0C000000������ԭ������
2.Flash���������ľ�Ȼ��0x00������0xFF�����������ĵ�Ƭ����ͬ��

2018.06.26
1.XMC4402�ܵĴ洢�ռ�Ϊ256K������:32K������:32K������:192K
2.Flash�Ķ�д���ܵ�����ɡ�

2018.08.28
1.����MDK-ARM-V5��MDK-ARM-V4�������������Ĺ��̼��ݣ�DAVE��δ��ӡ�
2.���Ӹ�������������IQmath���֧�֣�������е�������Լ�������㣬�Զ�������Ϊ����



fromelf --bin --output "$L@L.bin"  "#L"

ARM Compiler could not determine the product installation it is part of. You might be able to resolve this by reinstalling the tools, or ensuring that ARM_TOOL_VARIANT and ARM_PRODUCT_PATH are set appropriately.
�������⣺



δ�����⣺

1.uart��Ҫ����printf���ܶ��壻
2.spiͨ���谴��6�ֽ���ɣ�


