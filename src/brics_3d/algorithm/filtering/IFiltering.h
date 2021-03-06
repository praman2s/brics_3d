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
#ifndef BRICS_3D_IFILTERING_H_
#define BRICS_3D_IFILTERING_H_

#include "brics_3d/core/PointCloud3D.h"

namespace brics_3d {

/**
 * @brief Generic interface for a point cloud filtering component.
 * @ingroup filtering
 *
 */
class IFiltering {
public:
	IFiltering(){};
	virtual ~IFiltering(){};

	/**
	 * @brief Filter a point cloud.
	 * @param[in] originalPointCloud The input point cloud that will be filtered. This data will not
	 * be modified.
	 * @param[out] resultPointCloud The filtered point cloud with.
	 */
	virtual void filter(PointCloud3D* originalPointCloud, PointCloud3D* resultPointCloud) = 0;
};

}

#endif /* BRICS_3D_IFILTERING_H_ */

/* EOF */
