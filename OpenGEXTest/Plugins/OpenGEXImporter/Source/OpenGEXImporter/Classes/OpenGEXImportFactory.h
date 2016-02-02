// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

/**
* Factory for importing OpenGEX
*/

#pragma once
#include "OpenGEXImportFactory.generated.h"

UCLASS(hidecategories = Object)
class OPENGEXIMPORTER_API UOpenGEXImportFactory : public UFactory
{
	GENERATED_BODY()
public:
	UOpenGEXImportFactory();

	// Begin UObject Interface
	virtual void CleanUp() override;
	virtual bool ConfigureProperties() override;
	virtual void PostInitProperties() override;
	// End UObject Interface

	// Begin UFactory Interface
	virtual FText GetDisplayName() const override;
	virtual bool DoesSupportClass(UClass * Class) override;
	virtual UClass* ResolveSupportedClass() override;
	virtual UObject* FactoryCreateBinary(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;
	virtual bool FactoryCanImport(const FString& Filename) override;
	// End UFactory Interface
};

