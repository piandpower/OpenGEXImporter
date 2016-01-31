#pragma once

#include "ModuleInterface.h"
#include "ModuleManager.h"		// For inline LoadModuleChecked()

/**
 * The public interface of the SpeedTreeImporter module
 */
class IOpenGEXImporter : public IModuleInterface
{

public:

	/**
	 * Singleton-like access to IOpenGEXImporter
	 *
	 * @return Returns OpenGEXImporter singleton instance, loading the module on demand if needed
	 */
	static inline IOpenGEXImporter& Get()
	{
		return FModuleManager::LoadModuleChecked<IOpenGEXImporter>("OpenGEXImporter");
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

