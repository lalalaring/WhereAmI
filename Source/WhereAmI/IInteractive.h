#pragma once
#include "IInteractive.generated.h"


/**
 * Interface to be implemented 
 */
UINTERFACE(MinimalAPI)
class UInteractive: public UInterface
{
	GENERATED_UINTERFACE_BODY()
};
class IInteractive
{
	GENERATED_IINTERFACE_BODY()

public:
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE( FUseDelegate );
	DECLARE_DYNAMIC_MULTICAST_DELEGATE( FStartViewDelegate );
	DECLARE_DYNAMIC_MULTICAST_DELEGATE( FEndViewDelegate );

	UPROPERTY(BlueprintAssignable)
	FUseDelegate Use;

	UPROPERTY(BlueprintAssignable)
	FStartViewDelegate StartView;

	UPROPERTY(BlueprintAssignable)
	FEndViewDelegate EndView;

};
