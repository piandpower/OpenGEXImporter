#pragma once

namespace OpenGEX
{
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

		struct FDImplementation;

		FDImplementation* DImpl;
	};
}