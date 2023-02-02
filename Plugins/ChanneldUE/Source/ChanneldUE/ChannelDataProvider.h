#pragma once

#include "CoreMinimal.h"
#include "ChanneldTypes.h"
#include "channeld.pb.h"
#include "google/protobuf/message.h"
#include "unreal_common.pb.h"
#include "ChannelDataProvider.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UChannelDataProvider : public UInterface
{
	GENERATED_BODY()
};

class CHANNELDUE_API IChannelDataProvider
{
	GENERATED_BODY()
public:
	virtual UObject* GetTargetObject() = 0;
	// virtual channeldpb::ChannelType GetChannelType() = 0;
	// virtual google::protobuf::Message* GetChannelDataTemplate() const = 0;
	//virtual ChannelId GetChannelId() = 0;
	// virtual void SetChannelId(ChannelId ChId) = 0;
	virtual void OnAddedToChannel(ChannelId ChId) {}
	virtual void OnRemovedFromChannel(ChannelId ChId) {}
	virtual bool IsRemoved() = 0;
	virtual void SetRemoved(bool bInRemoved) = 0;
	virtual bool UpdateChannelData(google::protobuf::Message* ChannelData) = 0;
	virtual void OnChannelDataUpdated(google::protobuf::Message* ChannelData) = 0;
	
	static FString GetName(const IChannelDataProvider* Provider)
	{
		return Provider->_getUObject()->GetPathName();// GetClass()->GetFullName();
		//return Cast<UObjectBase>(Provider)->GetClass()->GetName();
	}

};
