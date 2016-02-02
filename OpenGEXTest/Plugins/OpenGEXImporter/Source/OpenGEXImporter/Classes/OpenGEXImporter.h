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
		{

		}

		Type MetricType;
	};

	struct FMetricInfoGroup
	{
		FMetricInfo MetricInfos[FMetricInfo::Max];

		void Clear()
		{
			MetricInfos[FMetricInfo::Distance].FloatValue = 1.0f;
			MetricInfos[FMetricInfo::Angle].FloatValue = 1.0f;
			MetricInfos[FMetricInfo::Time].FloatValue = 1.0f;
			MetricInfos[FMetricInfo::Up].StringValue = "z";
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

		const FMetricInfoGroup& GetMetricInfoGroup() const { return MetricInfoGroup; }

		bool ImportFromBuffer(const uint8* Buffer, int Len);

		void Clear();

	protected:
		void handleNodes(ODDLParser::DDLNode* Node);

		void handleMetricNode(ODDLParser::DDLNode* Node);

	protected:
		FMetricInfoGroup MetricInfoGroup;

	protected:
		static TSharedPtr<FOpenGEXImporter> StaticInstance;

		struct FDImplementation;

		FDImplementation* DImpl;
	};
}