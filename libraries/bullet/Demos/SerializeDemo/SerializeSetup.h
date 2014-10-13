#ifndef SERIALIZE_SETUP_H
#define SERIALIZE_SETUP_H
#include "../../Demos/CommonRigidBodySetup.h"

class SerializeSetup : public CommonRigidBodySetup
{
public:
    SerializeSetup();
    virtual ~SerializeSetup();
    
	virtual void initPhysics(GraphicsPhysicsBridge& gfxBridge);
};

#endif //SERIALIZE_SETUP_H
