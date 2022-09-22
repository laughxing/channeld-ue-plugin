#include "ChanneldReplication.h"

TMap<const UClass*, const FReplicatorCreateFunc> ChanneldReplication::ReplicatorRegistry;

void ChanneldReplication::RegisterReplicator(const UClass* TargetClass, const FReplicatorCreateFunc& Func)
{
	ReplicatorRegistry.Add(TargetClass, Func);
	UE_LOG(LogChanneld, Log, TEXT("Registered replicator for %s, registry Size: %d"), *TargetClass->GetFullName(), ReplicatorRegistry.Num());
}

FChanneldReplicatorBase* ChanneldReplication::FindAndCreateReplicator(UObject* ReplicatedObj)
{
	// Iterate the base class until find the matching replicator
	for (const UClass* Class = ReplicatedObj->GetClass(); Class != nullptr; Class = Class->GetSuperClass())
	{
		if (ReplicatorRegistry.Contains(Class))
		{
			const FReplicatorCreateFunc& Func = ReplicatorRegistry.FindRef(Class);
			auto Replicator = Func(ReplicatedObj);
			UE_LOG(LogChanneld, Verbose, TEXT("Created %s replicator for object: %s"), *Class->GetFullName(), *ReplicatedObj->GetFullName());
			return Replicator;
		}
	}

	UE_LOG(LogChanneld, Log, TEXT("Unable to find replicator for %s, registry Size: %d"), *ReplicatedObj->GetFullName(), ReplicatorRegistry.Num());
	return nullptr;
}