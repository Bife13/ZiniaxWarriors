:: This is th actual path to the unreal engine, so make sure it follows the correct path in your machines
set UE4Dir="C:\Program Files\Epic Games\UE_4.27\Engine\Binaries\Win64\UE4Editor.exe"

:: Project directory, this is auto configured, if you have a different project name then switch change this
set ProjectDir="%cd%/ZiniaxWarriors.uproject"

:: Nothing To Do Here Just The Role (Client (game) Or Server (server))
set Role=-game

:: Port To Use! This would be passed in as a parameter by the matchmaking server
set Port="1337"

:: Default Map To Load Into As A Server
set Map="127.0.0.1:1337"

:: Comment this out if you dont want your server logging
set Log=-log

:: Finally Run The Command
%UE4Dir% %ProjectDir% %Map% %Role% %Log% -ResX=800 -ResY=700 -WinX=800 -WinY=30 -windowed
