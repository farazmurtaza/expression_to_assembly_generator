g++ -o eval eval.cpp
eval.exe "22      *  (50 + (36 / 12 )     - 16)"
ml.exe /c /coff output.asm
link.exe /subsystem:console output.obj
output.exe
pause