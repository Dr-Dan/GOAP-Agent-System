//
//  ResourceUtility.cpp
//  agentGridProto
//
//  Created by D J Clarke on 19/07/2015.
//
//

#include "ResourceUtility.h"
#include "Resource.h"
#include "AgentAttributes.h"
#include "GridCell.h"
#include "GridAgent.h"

bool ResourceUtility::CanAddResources(Resource* res, int amt){
	if(res->GetAmtResource() + amt <= GridValues::MAX_RESOURCES){
		return true;
	}
	std::cout<<"cell is full"<<std::endl;
	//	cout<<"Cell: "<<GetId()<<" Is full of type "<<resType<<endl;
	return false;
}

bool ResourceUtility::HasResources(Resource* res, int amt){
	if(amt <= res->GetAmtResource()){
		return true;
	}
	//	cout<<"Cell: "<<GetId()<<" Has no resources of type "<<resType<<endl;
	return false;
}

// -----------------------------------------------------------------
// Resource Changers

bool ResourceUtility::AddResource(Resource* res, int amt) {
	if(CanAddResources(res, amt) && amt > 0){
		res->ChangeResourceAmt(amt);
		return true;
	}
	return false;
}

int ResourceUtility::RemoveResources(Resource* res, int amt){
	int amtRes = res->GetAmtResource();
	
	if(HasResources(res, amt)){
		res->ChangeResourceAmt(-amt);
		return amt; // if it has the resources, return demanded amount
	} else if(amtRes != 0){
		int remainder = amtRes; // take what is left from resources
		res->SetResourceAmt(0); // resources now empty
		return remainder; // else return remainder
	}
	
	return 0;
}


bool ResourceUtility::PickupResource(ItemType resType, float amt, AgentAttributes* attribs, GridCell* targetCell){
	Resource* res = targetCell->GetResourceHandler()->GetResource(resType);
	if(attribs->CanPickupResource(resType, amt)){
		attribs->PickupResource(resType, RemoveResources(res, amt));
		return true;
	}
	cout<<"I can't take more resources"<<endl;
	return false;
}

bool ResourceUtility::DepositResource(ItemType resType, float amt, AgentAttributes* attribs, GridCell* targetCell){
	if(attribs->CanUseResource(resType, amt)){
		bool can_deposit = AddResource(targetCell->GetResourceHandler()->GetResource(resType), amt);
		//		bool can_deposit = targetCellOther->AddResource(resType, amt);
		if(can_deposit){
			
//			mapResources[resType].amtCarried -= amt;
			attribs->ChangeResourceAmount(resType, -amt);
			return true;
		} else {
			cout<<"Cannot deposit type: "<< resType<<endl;
		}
		
	} else{
		cout<<"I don't have the resources"<<endl;
	}
	
	return false;
}

bool ResourceUtility::GiveResource(ItemType resType, float amt, AgentAttributes* attribs, GridAgent* agentOther){
	if(attribs->CanUseResource(resType, amt)){
		if(agentOther->attributes.PickupResource(resType, amt)){
			return true;
		}
	}
	cout<<"I don't have the resources"<<endl;
	return false;
}

