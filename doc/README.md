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
而完全按照 [JTAG](doc/jtag.md) 的连接方式连线之后，再选择 SWD 模式下载时，可以成功下载程序。
5. 一定要使用能够进行数据通信的 MicroUSB 线，比如手机充电线。
6. 使用 USB Hub 时，系统无法识别 DFU Boot USB 设备。
7. 如果出现 JFlash 无法连接的情况，请首先检查是不是杜邦线的问题，换换其他线多次尝试之后再确定是真的连接不上，
还是因为杜邦线接触不良导致的。
8. 由于下载的程序禁用了 SWD 功能，所以在此下载时 J-Flash 无法连接板子，此时可以通过按住板子的 Reset 按键不放，
同时在 J-Flash 上点击连接即可正常连接，不过此时仍然无法进行下载和擦除芯片，可能是因为板子一直通着电，
硬件配置并没有失效，所以将板子彻底断电，并将 BOOT0 和 BOOT1 都置高，防止板子上电再执行 Flash 中的程序，
将铁直尺放在所有引脚上给板子放电，等待几分钟，重新上电即可正常连接板子，也可以正常擦除芯片以及下载程序；
当出现问题时，如果连接成功了，首先尝试擦除芯片，彻底阻止程序再运行。

### 参考资料
1. [BluePill Arduino 手册](https://www.techshopbd.com/uploads/product_document/STM32bluepillarduinoguide(1).pdf)