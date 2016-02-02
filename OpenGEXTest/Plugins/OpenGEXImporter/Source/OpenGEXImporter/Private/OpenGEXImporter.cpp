#include "OpenGEXImporterPrivatePCH.h"
#include "OpenGEXImporter.h"

#include "openddlparser/OpenDDLParser.h"

namespace Grammar {
	static const std::string MetricType = "Metric";
	static const std::string Metric_DistanceType = "distance";
	static const std::string Metric_AngleType = "angle";
	static const std::string Metric_TimeType = "time";
	static const std::string Metric_UpType = "up";
	static const std::string NameType = "Name";
	static const std::string ObjectRefType = "ObjectRef";
	static const std::string MaterialRefType = "MaterialRef";
	static const std::string MetricKeyType = "key";
	static const std::string GeometryNodeType = "GeometryNode";
	static const std::string GeometryObjectType = "GeometryObject";
	static const std::string TransformType = "Transform";
	static const std::string MeshType = "Mesh";
	static const std::string VertexArrayType = "VertexArray";
	static const std::string IndexArrayType = "IndexArray";
	static const std::string MaterialType = "Material";
	static const std::string ColorType = "Color";
	static const std::string DiffuseColorToken = "diffuse";
	static const std::string SpecularColorToken = "specular";
	static const std::string EmissionColorToken = "emission";

	static const std::string DiffuseTextureToken = "diffuse";
	static const std::string DiffuseSpecularTextureToken = "specular";
	static const std::string SpecularPowerTextureToken = "specular_power";
	static const std::string EmissionTextureToken = "emission";
	static const std::string OpacyTextureToken = "opacity";
	static const std::string TransparencyTextureToken = "transparency";
	static const std::string NormalTextureToken = "normal";

	static const char *TextureType = "Texture";

	enum TokenType {
		NoneType = -1,
		MetricToken,
		NameToken,
		ObjectRefToken,
		MaterialRefToken,
		MetricKeyToken,
		GeometryNodeToken,
		GeometryObjectToken,
		TransformToken,
		MeshToken,
		VertexArrayToken,
		IndexArrayToken,
		MaterialToken,
		ColorToken,
		TextureToken
	};

	static const std::string ValidMetricToken[4] = {
		Metric_DistanceType,
		Metric_AngleType,
		Metric_TimeType,
		Metric_UpType
	};

	static int isValidMetricType(const char *token) {
		if (NULL == token) {
			return false;
		}

		int idx(-1);
		for (size_t i = 0; i < 4; i++) {
			if (ValidMetricToken[i] == token) {
				idx = (int)i;
				break;
			}
		}

		return idx;
	}

	static TokenType matchTokenType(const char *tokenType) {
		if (MetricType == tokenType) {
			return MetricToken;
		}
		else if (NameType == tokenType) {
			return NameToken;
		}
		else if (ObjectRefType == tokenType) {
			return ObjectRefToken;
		}
		else if (MaterialRefType == tokenType) {
			return MaterialRefToken;
		}
		else if (MetricKeyType == tokenType) {
			return MetricKeyToken;
		}
		else if (GeometryNodeType == tokenType) {
			return GeometryNodeToken;
		}
		else if (GeometryObjectType == tokenType) {
			return GeometryObjectToken;
		}
		else if (TransformType == tokenType) {
			return TransformToken;
		}
		else if (MeshType == tokenType) {
			return MeshToken;
		}
		else if (VertexArrayType == tokenType) {
			return VertexArrayToken;
		}
		else if (IndexArrayType == tokenType) {
			return IndexArrayToken;
		}
		else if (MaterialType == tokenType) {
			return MaterialToken;
		}
		else if (ColorType == tokenType) {
			return ColorToken;
		}
		else if (TextureType == tokenType) {
			return TextureToken;
		}

		return NoneType;
	}

} // Namespace Grammar

namespace OpenGEX
{
	TSharedPtr<FOpenGEXImporter> FOpenGEXImporter::StaticInstance = nullptr;

	struct FOpenGEXImporter::FDImplementation
	{
		ODDLParser::Context* ParserContext;

		FDImplementation()
			: ParserContext(nullptr)
		{

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

		ODDLParser::OpenDDLParser OpenDDLParserObj(Buffer, Len);
		bool bResult = OpenDDLParserObj.parse();
		if (bResult)
		{
			DImpl->ParserContext = OpenDDLParserObj.getContext();
			handleNodes(DImpl->ParserContext->m_root);
		}

		return false;
	}

	void FOpenGEXImporter::handleNodes(ODDLParser::DDLNode* Node)
	{
		if (Node == nullptr)
			return;

		ODDLParser::DDLNode::DllNodeList ChildNodes = Node->getChildNodeList();
		for (ODDLParser::DDLNode::DllNodeList::iterator iter = ChildNodes.begin(); iter != ChildNodes.end(); ++iter)
		{
			Grammar::TokenType tokenType(Grammar::matchTokenType((*iter)->getType().c_str()));
			switch (tokenType)
			{
			case Grammar::MetricToken:
			{
				handleMetricNode(*iter);
			}
			break;
			}
		}
	}

	static FMetricInfo::Type getMetricTypeFromText(ODDLParser::Text* key)
	{
		std::string keyStr(key->m_buffer, key->m_len);

		if (keyStr == "distance")
			return FMetricInfo::Distance;
		else if (keyStr == "angle")
			return FMetricInfo::Angle;
		else if (keyStr == "time")
			return FMetricInfo::Time;
		else if (keyStr == "up")
			return FMetricInfo::Up;

		return FMetricInfo::Max;
	}

	void FOpenGEXImporter::handleMetricNode(ODDLParser::DDLNode* Node)
	{
		if (Node == nullptr || DImpl->ParserContext == nullptr)
			return;

		if (DImpl->ParserContext->m_root != Node->getParent())
			return;

		ODDLParser::Property* prop(Node->getProperties());
		while (prop != nullptr)
		{
			if (!prop->m_key)
				continue;

			FMetricInfo::Type MetricType = getMetricTypeFromText(prop->m_key);
			if (MetricType == FMetricInfo::Max)
				continue;

			if (MetricType == FMetricInfo::Up)
			{
				if (prop->m_value->m_type == ODDLParser::Value::ddl_string)
				{
					MetricInfoGroup.MetricInfos[(int)MetricType].StringValue = prop->m_value->getString();
				}
			}
			else
			{
				if (prop->m_value->m_type == ODDLParser::Value::ddl_float)
				{
					MetricInfoGroup.MetricInfos[(int)MetricType].FloatValue = prop->m_value->getFloat();
				}
			}
			MetricInfoGroup.MetricInfos[(int)MetricType].MetricType = MetricType;

			prop = prop->m_next;
		}
	}

	void FOpenGEXImporter::Clear()
	{
		MetricInfoGroup.Clear();
	}
}
