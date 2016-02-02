#include "OpenGEXImporterPrivatePCH.h"
#include "OpenGEXImporter.h"

#include "openddlparser/OpenDDLParser.h"

namespace OpenGEX
{
	TSharedPtr<FOpenGEXImporter> FOpenGEXImporter::StaticInstance = nullptr;

	FOpenGEXImporter::FOpenGEXImporter()
	{

	}

	FOpenGEXImporter::~FOpenGEXImporter()
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

	bool FOpenGEXImporter::ImportFromBuffer(const unsigned char* InBuffer, int Len)
	{
		const char* Buffer = nullptr;
		if (Len >= 3)
		{
			if (InBuffer[0] == 0xEF && InBuffer[1] == 0xBB && InBuffer[2] == 0xBF)
			{
				Buffer = (char*)(InBuffer + 3);
				Len -= 3;
			}
		}
		else
		{
			Buffer = (char*)InBuffer;
		}

		ODDLParser::OpenDDLParser openDDLParser(Buffer, Len);

		return false;
	}
}
