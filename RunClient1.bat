:: This is th actual path to the unreal engine, so make sure it follows the correct path in your machines
set UE4Dir="E:\Epic\Epic Games\UE_4.27\Engine\Binaries\Win64\UE4Editor.exe"

:: Project directory, this is auto configured, if you have a different project name then switch change this
set ProjectDir="%cd%/ZiniaxWarriors.uproject"

:: Default Map To Load Into As A Client
set Map=/Game/Maps/LoginMenu

:: Nothing To Do Here Just The Role (Client (game) Or Server (server))
set Role=-game

:: Comment this out if you dont want your server logging
set Log=-log



:: Finally Run The Command
%UE4Dir% %ProjectDir% %Map% %Role% %Log% -ResX=800 -ResY=700 -WinX=0 -WinY=30 -windowed
