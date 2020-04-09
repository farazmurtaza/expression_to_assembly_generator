includelib C:\Irvine\Kernel32.Lib
includelib C:\Irvine\User32.Lib
includelib C:\Irvine\Irvine32.lib
INCLUDE C:\Irvine\Irvine32.inc
.data
.code
main PROC
MOV EAX, 0
MOV AX, 22
PUSH AX
MOV AX, 50
PUSH AX
MOV AX, 36
PUSH AX
MOV AX, 12
PUSH AX
POP BX
POP AX
MOV DX, 0
DIV BX
PUSH AX
MOV AX, 16
PUSH AX
POP BX
POP AX
SUB AX, BX
PUSH AX
POP AX
POP BX
ADD AX, BX
PUSH AX
POP AX
POP BX
MUL BX
PUSH AX

call writedec
exit
main ENDP
END main
