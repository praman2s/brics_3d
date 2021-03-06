/******************************************************************************
* BRICS_3D - 3D Perception and Modeling Library
* Copyright (c) 2011, GPS GmbH
*
* Author: Sebastian Blumenthal
*
*
* This software is published under a dual-license: GNU Lesser General Public
* License LGPL 2.1 and Modified BSD license. The dual-license implies that
* users of this code may choose which terms they prefer.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License LGPL and the BSD license for
* more details.
*
******************************************************************************/

#ifndef BRICS_3D_ITERATIVECLOSESTPOINTFACTORY_H_
#define BRICS_3D_ITERATIVECLOSESTPOINTFACTORY_H_

#include "brics_3d/core/Logger.h"
#include "brics_3d/algorithm/registration/IIterativeClosestPoint.h"
#include "brics_3d/algorithm/registration/IIterativeClosestPointSetup.h"
#include <string>

#include <boost/shared_ptr.hpp>


namespace brics_3d {

typedef boost::shared_ptr<IIterativeClosestPoint> IIterativeClosestPointPtr;
typedef boost::shared_ptr<IIterativeClosestPointSetup> IIterativeClosestPointSetupPtr;

/**
 * @ingroup registration
 * @brief IterativeClosestPoint factory that can be configured with a XML file
 *
 */
class IterativeClosestPointFactory {
public:

	/**
	 * @brief Standard constructor
	 */
	IterativeClosestPointFactory();

	/**
	 * @brief Standard destructor
	 */
	virtual ~IterativeClosestPointFactory();

	/**
	 * @brief Factory method the returns an IterativeClosestPoint in a standard configuration.
	 */
	IIterativeClosestPointPtr createIterativeClosestPoint();

	/**
	 * @brief Factory method the returns an IterativeClosestPoint configured by an XML file
	 *
	 * Wrong parameters descriptions in the XML file will be handled as warnings and the default parameter is chosen.
	 *
	 * @param configurationFile Path to the XML configuration file
	 * @return Returns an instance of the abstract Iterative Closest Point interface
	 *
	 * <br><b>Example XML file:</b><br>
	 * <code>
	 * <!DOCTYPE dummy> <br>
	 * <BRICS_3D-Configuration> <br> <br>
	 *
	 * &nbsp;&nbsp;<IterativeClosestPoint implementation="IterativeClosestPoint" maxIterations="25" convergenceThreshold="0.001"> <br>
     * &nbsp;&nbsp;&nbsp;&nbsp;<PointCorrespondence implementation="PointCorrespondenceKDTree"></PointCorrespondence> <br>
	 * &nbsp;&nbsp;&nbsp;&nbsp;<RigidTransformationEstimation implementation="RigidTransformationEstimationSVD"></RigidTransformationEstimation> <br>
	 * &nbsp;&nbsp;</IterativeClosestPoint> <br> <br>
     *
     * </BRICS_3D-Configuration>
	 * </code>
	 * <br><br>
	 * <b>NOTE1:</b> The current implementation of the <code>ConfigurationFileHandlerTest</code> configuration file parser bases on the Xerces library.
	 * If it is not installed the default configuration is choosen.<br>
	 */
	IIterativeClosestPointPtr createIterativeClosestPoint(std::string configurationFile);

	/**
	 * @brief Get an ICP setup handle, if available
	 * @return Returns the handle to the IIterativeClosestPointSetup interface of the last invocation of
	 * createIterativeClosestPoint if available. Otherwise returns 0.
	 */
	IIterativeClosestPointSetupPtr getIcpSetupHandle();

private:

	IIterativeClosestPointSetupPtr icpConfigurator;

};

}

#endif /* BRICS_3D_ITERATIVECLOSESTPOINTFACTORY_H_ */

/* EOF */
