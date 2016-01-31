#include "OpenGEXImporterPrivatePCH.h"
#include "OpenGEXImportFactory.h"

#include "Engine/StaticMesh.h"

#define LOCTEXT_NAMESPACE "OpenGEXImportFactory"

UOpenGEXImportFactory::UOpenGEXImportFactory()
	: Super(FObjectInitializer::Get())
{

}

FText UOpenGEXImportFactory::GetDisplayName() const
{
	return LOCTEXT("OpenGEXFactoryDescription", "OpenGEX");
}

bool UOpenGEXImportFactory::DoesSupportClass(UClass * Class)
{
	return Class == UStaticMesh::StaticClass();
}

UClass* UOpenGEXImportFactory::ResolveSupportedClass()
{
	return UStaticMesh::StaticClass();
}

UObject* UOpenGEXImportFactory::FactoryCreateBinary(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn)
{
	return nullptr;
}

bool UOpenGEXImportFactory::FactoryCanImport(const FString& Filename)
{
	FString Extension = FPaths::GetExtension(Filename);
	if (Extension == TEXT("ogex"))
	{
		return true;
	}

	return false;
}

