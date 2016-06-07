//
//  ResourceUtility.cpp
//  agentGridProto
//
//  Created by D J Clarke on 19/07/2015.
//
//

#include "ResourceUtility.h"
#include "Resource.h"

bool ResourceUtility::CanAddResources(Resource& res, int amt){
	if(res.GetAmtResource() + amt <= GridValues::MAX_RESOURCES){
		return true;
	}
	//	cout<<"Cell: "<<GetId()<<" Is full of type "<<resType<<endl;
	return false;
}

bool ResourceUtility::HasResources(Resource& res, int amt){
	if(amt <= res.GetAmtResource()){
		return true;
	}
	//	cout<<"Cell: "<<GetId()<<" Has no resources of type "<<resType<<endl;
	return false;
}

// -----------------------------------------------------------------
// Resource Changers

bool ResourceUtility::AddResource(Resource& res, int amt) {
	if(CanAddResources(res, amt) && amt > 0){
		res.ChangeResourceAmt(amt);
		return true;
	}
	return false;
}

int ResourceUtility::RemoveResources(Resource& res, int amt){
	int amtRes = res.GetAmtResource();
	
	if(HasResources(res, amt)){
		res.ChangeResourceAmt(-amt);
		return amt; // if it has the resources, return demanded amount
	} else if(!HasResources(res, amt) && amtRes != 0){
		int remainder = amtRes; // take what is left from resources
		amtRes = 0; // resources now empty
		return remainder; // else return remainder
	}
	
	return 0;
}
