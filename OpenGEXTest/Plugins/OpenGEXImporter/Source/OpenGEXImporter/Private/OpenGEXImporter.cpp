#include "OpenGEXImporterPrivatePCH.h"
#include "OpenGEXImporter.h"

#include "openddlparser/OpenDDLParser.h"

namespace OpenGEX
{
	TSharedPtr<FOpenGEXImporter> FOpenGEXImporter::StaticInstance = nullptr;

	FOpenGEXImporter::FOpenGEXImporter()
	{

	}

	FOpenGEXImporter* FOpenGEXImporter::GetInstance()
	{
		if (!StaticInstance.IsValid())
		{
			StaticInstance = MakeShareable(new FOpenGEXImporter());
		}

		return StaticInstance.Get();
	}
}
