@ECHO OFF
"E:\Program Files\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "H:\DaR mega8\Firmware_mega8\labels.tmp" -fI -W+ie -o "H:\DaR mega8\Firmware_mega8\Firmware.hex" -d "H:\DaR mega8\Firmware_mega8\Firmware.obj" -e "H:\DaR mega8\Firmware_mega8\Firmware.eep" -m "H:\DaR mega8\Firmware_mega8\Firmware.map" "H:\DaR mega8\Firmware_mega8\main.asm"
