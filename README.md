WiLinker - Wireless Linker
==========================

### 硬件
1. stm32f103c8t6
2. nrf24l01

### 软件
1. dapboot
2. daplink

### 工具
Keil 软件默认生成的文件为 XXX.hex 文件，而通过其他工具下载程序时，需要将 XXX.hex
文件转换成 XXX.bin 文件，在 Keil 官网找到了几种转换方式，经过很多尝试之后，只有
Keil 自带的工具可以使用，各种转换方式如下：

1. fromelf.exe --> [可用](http://www.keil.com/support/docs/3213.htm)
2. srec_cat.exe --> [不可用](http://www.keil.com/support/docs/4038.htm)
3. BIN2HEX --> [不可用](http://www.keil.com/download/docs/7.asp)
4. DfuSe USB 设备固件安装包 --> [待测试](https://www.stmcu.org.cn/document/detail/index/id-215019)

### 注意事项
1. 使用 dapboot-v1.11-bluepill.bin 时，应用程序链接地址需要向后偏移 8KB，因为 dapboot 占用了前 8KB，
如果不修改链接地址，应用程序将无法正确执行。
2. 使用 highboot-v1.11-bluepill.bin 时，应用程序的链接地址默认 0x8000000 即可。
3. 使用 WebUSB 时，火狐浏览器不可用，谷歌浏览器可用。
4. 在使用 SWD 对 BluePill 进行下载时，单纯的 SWD 接线导致 J-Flash 和 Keil 都无法识别 BluePill，
而完全按照 JTAG 的链接方式连线之后，再选择 SWD 模式下载时，可以成功下载程序。

### 参考资料
1. [BluePill Arduino 手册](https://www.techshopbd.com/uploads/product_document/STM32bluepillarduinoguide(1).pdf)