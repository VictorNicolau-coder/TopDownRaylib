# Como executar:


### MinGW64

adendo, utilize o w64devkit e o raylib x64, caso o contrário ocorrerá erros de compilção

```
gcc *.c -o run.exe -Iraylib/include -Lraylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm
```