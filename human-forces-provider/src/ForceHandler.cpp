//
//  ForceHandler.cpp
//  HumanDynamicsEstimation
//
//  Created by Claudia Latella on 28/02/17.
//
//

#include "ForceHandler.h"
#include "FrameTransformer.h"

#include <thrifts/Force6D.h>
#include <yarp/os/LogStream.h>

namespace human {
    ForceHandler::ForceHandler(std::string attachedLink,
                               std::string referenceFrame)
    : m_frameTransformer(0)
    , m_attachedLink(attachedLink)
    , m_referenceFrame(referenceFrame)
    , m_packedForce(6, 0.0) {}
    
    
    void ForceHandler::setTransformer(FrameTransformer *frameTransformer)
    {
        m_frameTransformer = frameTransformer;
    }

    
    FrameTransformer* ForceHandler::getTransformer()
    {
        return m_frameTransformer;
    }
    
    
    bool ForceHandler::readForce(Force6D &packedForce)
    {
        packedForce.appliedLink = m_attachedLink;
        packedForce.expressedFrame = m_referenceFrame;
        
        if (!this->lowLevelRead(m_packedForce)) {
            yError() << "Something wrong in the forces reading!";
            return false;
        }

        if (m_frameTransformer) {
            //TODO: Check if the input and output variable can be the same
            if (!m_frameTransformer->transformForceFrame(m_packedForce,
                                                         m_packedForce,
                                                         packedForce.appliedLink))
            {
                yError() << "Something wrong in the forces transformation!";
                return false;
            }
        }
        
        packedForce.fx = m_packedForce(0);
        packedForce.fy = m_packedForce(1);
        packedForce.fz = m_packedForce(2);
        packedForce.ux = m_packedForce(3);
        packedForce.uy = m_packedForce(4);
        packedForce.uz = m_packedForce(5);
        
        return true;
    }
}
