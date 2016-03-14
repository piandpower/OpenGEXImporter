#include "OpenGEXImporterPrivatePCH.h"
#include "ModuleManager.h"

void LoadOpenGEXLibrary()
{
	static bool bIsIntialized = false;
	if (!bIsIntialized)
	{
		bIsIntialized = true;
#if PLATFORM_WINDOWS
		//@todo if ogg is every ported to another platform, then use the platform abstraction to load these DLLs
		// Load the Ogg dlls
		FString VSVersion = TEXT("VS2013/");
		FString PlatformString = TEXT("Win32");
		FString DLLNameStub = TEXT(".dll");
#if _MSC_VER == 1900
		VSVersion = TEXT("VS2015/");
#endif
#if PLATFORM_64BITS
		PlatformString = TEXT("x64");
		DLLNameStub = TEXT(".dll");
#endif

#if UE_BUILD_DEBUG
		FString BuildFlag = TEXT("Debug");
#else
		FString BuildFlag = TEXT("Release");
#endif

		FString RootOpenGEXPath = FPaths::GamePluginsDir() / TEXT("OpenGEXImporter/Source/Thirdparty/OpenGEXParser/opengex-parser/bin/x64/VS2015/") + BuildFlag + TEXT("/");

		FString DLLToLoad = RootOpenGEXPath + TEXT("opengex-parser_") + BuildFlag + DLLNameStub;
		verifyf(LoadLibraryW(*DLLToLoad), TEXT("Failed to load DLL %s"), *DLLToLoad);
#endif	//PLATFORM_WINDOWS
	}
}

/**
 * OpenGEXImporter module implementation (private)
 */
class FOpenGEXImporterModule : public IOpenGEXImporterModule
{
public:
	virtual void StartupModule() override
	{
		LoadOpenGEXLibrary();
	}


	virtual void ShutdownModule() override
	{
	}

};

IMPLEMENT_MODULE(FOpenGEXImporterModule, OpenGEXImporter);

