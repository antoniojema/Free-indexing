@echo off
setLocal enableDelayedExpansion

set "configs=vcpp,intel,vcpp_single,intel_single"

set error=false
set argCount=0
for %%x in (%*) do (
    set /A argCount+=1
    call :inList %%x "%configs%" is_in
    if !is_in!==true (
        echo ### Making build of configuration: %%x ###
        %~dp0build_scripts\make_win_%%x.bat
    ) else (
        echo ### ERROR: Invalid configuration %%x. ###
        set error=true
    )
)

if %argCount% == 0 (
   echo ### ERROR: Need to specify a configuration name. ###
   set error=true
)

if %error%==true (
    call :displayConfigs
)

goto:eof

::---------------::
::   Functions   ::
::---------------::

:: Takes: nothing
:displayConfigs
    echo Possible configurations:
    for %%a in (%configs%) do (
        echo     %%a
    )
goto :eof

:: Takes: element list
:: Returns: bool
:inList
    for %%a in (%~2) do (
        if %~1==%%a (
            set is_in=true
            goto:eof
        )
    )
    set "%~3=false"
goto :eof
