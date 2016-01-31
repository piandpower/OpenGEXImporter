// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

/**
* Factory for importing OpenGEX
*/

#pragma once
#include "OpenGEXImportFactory.generated.h"

UCLASS(hidecategories = Object)
class UOpenGEXImportFactory : public UFactory
{
	GENERATED_BODY()
public:
	UOpenGEXImportFactory();

	// Begin UFactory Interface
	virtual FText GetDisplayName() const override;
	virtual bool DoesSupportClass(UClass * Class) override;
	virtual UClass* ResolveSupportedClass() override;
	virtual UObject* FactoryCreateBinary(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn) override;
	virtual bool FactoryCanImport(const FString& Filename) override;
	// End UFactory Interface
};

