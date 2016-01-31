#include "OpenGEXImporterPrivatePCH.h"
#include "ModuleManager.h"

/**
 * OpenGEXImporter module implementation (private)
 */
class FSOpenGEXImporterModule : public IOpenGEXImporter
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
