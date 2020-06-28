### JTAG 引脚
| —— | —— | —— | —— | 缺 | 口 | —— | —— | —— | —— |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 01 | 02 | 03 | 04 | 05 | 06 | 07 | 08 | 09 | 10 |
| VDD | TRST | TDI | TMS | TCK | RTCK | TDO | RST | NC | NC |
| 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 |
| VCC | GND | GND | GND | GND | GND | GND | GND | GND | GND |

### 接线
| Pin | 编号 | JTAG | 编号 |
| :-: | :--: | :--: | :--: |
| NRST | # | RST | 10 |
| # | A15 | TDI | 04 |
| # | B3 | TDO | 09 |
| # | B4 | TRST | 02 |
| SWCLK | PA14 | TCK | 06 |
| SWDIO | PA13 | TMS | 05 |