### PyUSB
首先，安装 PyUSB 包，然后下载 PyUSB 后端依赖库[https://github.com/libusb/libusb](https://github.com/libusb/libusb/releases/download/v1.0.23/libusb-1.0.23.7z)，
解压依赖库之后就可以得到 32 位和 64 位依赖文件，依赖库位宽一定要与 Python 相匹配，否则 PyUSB 仍将无法使用。
将 libusb-1.0.23\MS32(或MS64)\dll 下的 libusb-1.0.dll 和 libusb-1.0.lib 复制到 Python 安装目录的根目录下即可。
```
pip install pyusb
```

### 测试程序
```python
import usb
# 查找给定 ID 的 USB 设备
# usb.core.find(idVendor = 0x1209, idProduct = 0xdb42)
dev = usb.core.find(find_all=True)
print(dev)
```