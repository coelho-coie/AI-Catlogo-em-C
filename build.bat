@echo off
setlocal

rem Localiza vcvars64.bat caso cl nao esteja no PATH
where cl >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    if exist "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat" (
        call "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat" >nul
    ) else if exist "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" (
        call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" >nul
    )
)

echo Compilando testes.exe...
cl /nologo /W3 /utf-8 /D_CRT_SECURE_NO_WARNINGS /Fe:testes.exe testes.c agente.c leitura.c
if %ERRORLEVEL% NEQ 0 (
    echo [ERRO] Falha ao compilar testes.exe
    exit /b 1
)

echo Compilando pim2.exe...
cl /nologo /W3 /utf-8 /D_CRT_SECURE_NO_WARNINGS /Fe:pim2.exe main.c menu.c agente.c leitura.c
if %ERRORLEVEL% NEQ 0 (
    echo [ERRO] Falha ao compilar pim2.exe
    exit /b 1
)

echo Compilacao concluida com sucesso!
exit /b 0
