#pragma once

#include "ModuleInterface.h"
#include "ModuleManager.h"		// For inline LoadModuleChecked()

/**
 * The public interface of the OpenGEXImporter module
 */
class IOpenGEXImporterModule : public IModuleInterface
{

public:

	/**
	 * Singleton-like access to IOpenGEXImporterModule
	 *
	 * @return Returns OpenGEXImporter singleton instance, loading the module on demand if needed
	 */
	static inline IOpenGEXImporterModule& Get()
	{
		return FModuleManager::LoadModuleChecked<IOpenGEXImporterModule>("OpenGEXImporter");
	}

	/**
	 * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	 *
	 * @return True if the module is loaded and ready to use
	 */
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("OpenGEXImporter");
	}


};
