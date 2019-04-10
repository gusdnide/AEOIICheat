# ScreenShot

![N|Solid](https://guidedhacking.com/attachments/screenshot_1-png.5760/)
![Build Status](https://guidedhacking.com/attachments/screenshot_2-png.5761/)

## Hooks
GetEntity
```
AoK HD.exe+A5ABE - 8B 89 FC 00 00 00        - mov ecx,[ecx+000000FC]
AoK HD.exe+A5AC4 - 66 0F D6 00            - movq [eax],xmm0

//ECX : Entitiy  address
//0xFC = Pos Y offset 
```
GetLocalGame
```
AoK HD.exe+464094 - F3 0F 10 82 10 01 00 00   - movss xmm0,[edx+00000110]
AoK HD.exe+46409C - 0F 2E 83 A4 01 00 00      - ucomiss xmm0,[ebx+000001A4]
AoK HD.exe+4640A3 - 9F                    - lahf
```