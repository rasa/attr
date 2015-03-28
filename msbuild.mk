all:
	MSBuild.exe /nologo attr.sln /p:Configuration=Debug
	MSBuild.exe /nologo attr.sln /p:Configuration=Release

clean:
	MSBuild.exe /nologo attr.sln /p:Configuration=Debug   /t:clean
	MSBuild.exe /nologo attr.sln /p:Configuration=Release /t:clean

upgrade:
	devenv attr.sln /upgrade
	
.PHONY:	all clean upgrade

