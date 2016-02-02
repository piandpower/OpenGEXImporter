#pragma once

#include <string>

namespace ODDLParser {
	class DDLNode;
	struct Context;
}

namespace OpenGEX
{
	struct FMetricInfo
	{
		enum Type
		{
			Distance = 0,
			Angle,
			Time,
			Up,
			Max
		};


		std::string StringValue;
		float FloatValue;
		int IntValue;

		FMetricInfo()
			: StringValue("")
			, FloatValue(0.0f)
			, IntValue(-1) {
			// empty
		}
	};

	class OPENGEXIMPORTER_API FOpenGEXImporter
	{
	public:
		FOpenGEXImporter();

		~FOpenGEXImporter();

		static FOpenGEXImporter* GetInstance();

		bool ImportFromBuffer(const unsigned char* Buffer, int Len);

	protected:
		static TSharedPtr<FOpenGEXImporter> StaticInstance;
	};
}