.include "macros.inc"
.file "targsupp.s"

.text
.balign 16

.global TRKAccessFile
.type TRKAccessFile, @function
TRKAccessFile:
    twui r0, 0x0
    blr
.size TRKAccessFile, . - TRKAccessFile

.global TRKOpenFile
.type TRKOpenFile, @function
TRKOpenFile:
    twui r0, 0x0
    blr
.size TRKOpenFile, . - TRKOpenFile

.global TRKCloseFile
.type TRKCloseFile, @function
TRKCloseFile:
    twui r0, 0x0
    blr
.size TRKCloseFile, . - TRKCloseFile

.global TRKPositionFile
.type TRKPositionFile, @function
TRKPositionFile:
    twui r0, 0x0
    blr
.size TRKPositionFile, . - TRKPositionFile
