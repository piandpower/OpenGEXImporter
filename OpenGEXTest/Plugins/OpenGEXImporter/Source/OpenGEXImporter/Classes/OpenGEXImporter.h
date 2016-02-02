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

	struct FVertexContainer
	{
		TArray<FVector> Vertices;
		TArray<FVector> Normals;
		TArray<FVector> TextureCoords[32];
	};

	class OPENGEXIMPORTER_API FOpenGEXImporter
	{
	public:
		FOpenGEXImporter();

		~FOpenGEXImporter();

		static FOpenGEXImporter* GetInstance();

		bool ImportFromBuffer(const uint8* Buffer, int Len);

		void Clear();

	protected:
		static TSharedPtr<FOpenGEXImporter> StaticInstance;
	};
}