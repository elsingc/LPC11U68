@ECHO off
SET FIRMWARE=firmware
ECHO fixing checksum...........
fix_checksum %FIRMWARE%.bin
erase e:firmware.bin
SLEEP 1
ECHO replace firmware.bin......
COPY %FIRMWARE%.bin e:
SLEEP 1