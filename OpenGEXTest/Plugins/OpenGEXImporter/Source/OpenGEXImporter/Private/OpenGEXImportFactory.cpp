#include "OpenGEXImporterPrivatePCH.h"
#include "OpenGEXImportFactory.h"
#include "OpenGEXImporter.h"

#include "Engine/StaticMesh.h"

#define LOCTEXT_NAMESPACE "OpenGEXImportFactory"

UOpenGEXImportFactory::UOpenGEXImportFactory()
	: Super(FObjectInitializer::Get())
{
	bText = false;
	bEditorImport = true;
	Formats.Add(TEXT("ogex;OpenGEX meshes and animations"));
}

void UOpenGEXImportFactory::CleanUp()
{

}

bool UOpenGEXImportFactory::ConfigureProperties()
{
	return true;
}

void UOpenGEXImportFactory::PostInitProperties()
{
	Super::PostInitProperties();

	bText = false;
	bEditorImport = true;
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

UObject* UOpenGEXImportFactory::FactoryCreateBinary(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	FEditorDelegates::OnAssetPreImport.Broadcast(this, InClass, InParent, InName, Type);

	OpenGEX::FOpenGEXImporter* OpenGEXImporter = OpenGEX::FOpenGEXImporter::GetInstance();
	OpenGEXImporter->ImportFromBuffer(Buffer, (int)(BufferEnd - Buffer));

	UStaticMesh* StaticMesh = nullptr;

	FEditorDelegates::OnAssetPostImport.Broadcast(this, StaticMesh);

	return StaticMesh;
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

#undef LOCTEXT_NAMESPACE
