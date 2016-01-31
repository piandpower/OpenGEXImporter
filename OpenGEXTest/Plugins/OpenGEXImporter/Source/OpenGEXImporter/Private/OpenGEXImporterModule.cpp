#include "OpenGEXImporterPrivatePCH.h"
#include "ModuleManager.h"

/**
 * OpenGEXImporter module implementation (private)
 */
class FOpenGEXImporterModule : public IOpenGEXImporter
{
public:
	virtual void StartupModule() override
	{
	}


	virtual void ShutdownModule() override
	{
	}

};

IMPLEMENT_MODULE(FOpenGEXImporterModule, OpenGEXImporter);
