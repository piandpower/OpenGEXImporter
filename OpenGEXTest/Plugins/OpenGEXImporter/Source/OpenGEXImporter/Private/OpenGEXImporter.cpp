#include "OpenGEXImporterPrivatePCH.h"
#include "OpenGEXImporter.h"

#include "OpenGEXParser.h"

namespace OpenGEX
{
	TSharedPtr<FOpenGEXImporter> FOpenGEXImporter::StaticInstance = nullptr;

	struct FOpenGEXImporter::FDImplementation
	{
		OGEXParser::OpenGEXParser* MyOpenGEXParser;

		FDImplementation()
		{
			MyOpenGEXParser = new OGEXParser::OpenGEXParser();
		}

		~FDImplementation()
		{
			delete MyOpenGEXParser;
			MyOpenGEXParser = nullptr;
		}
	};

	FOpenGEXImporter::FOpenGEXImporter()
	{
		DImpl = new FDImplementation;
	}

	FOpenGEXImporter::~FOpenGEXImporter()
	{
		if (DImpl)
		{
			delete DImpl;
			DImpl = nullptr;
		}
	}

	FOpenGEXImporter* FOpenGEXImporter::GetInstance()
	{
		if (!StaticInstance.IsValid())
		{
			StaticInstance = MakeShareable(new FOpenGEXImporter());
		}

		return StaticInstance.Get();
	}

	bool FOpenGEXImporter::ImportFromBuffer(const uint8* InBuffer, int Len)
	{
		const char* Buffer = nullptr;
		if (Len >= 3 &&(InBuffer[0] == 0xEF && InBuffer[1] == 0xBB && InBuffer[2] == 0xBF))
		{
			Buffer = (char*)(InBuffer + 3);
			Len -= 3;
		}
		else
		{
			Buffer = (char*)InBuffer;
		}

		bool bResult = DImpl->MyOpenGEXParser->parse(Buffer, Len);

		return false;
	}

	void FOpenGEXImporter::Clear()
	{
		DImpl->MyOpenGEXParser->clear();
	}
}
