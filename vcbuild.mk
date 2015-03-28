all:
	VCBuild.exe /nologo attr.vcproj /rebuild

clean:
	VCBuild.exe /nologo attr.vcproj /clean
	
upgrade:
	devenv attr.sln /upgrade

.PHONY:	all clean upgrade

