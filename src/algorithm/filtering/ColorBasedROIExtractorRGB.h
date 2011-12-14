/*
 * ColorBasedROIExtractorRGB.h
 *
 *  Created on: Dec 2, 2011
 *      Author: Pinaki Sunil Banerjee
 */

#ifndef COLORBASEDROIEXTRACTORRGB_H_
#define COLORBASEDROIEXTRACTORRGB_H_

#include "IColorBasedROIExtractor.h"
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <stdint.h>

namespace BRICS_3D {

class ColorBasedROIExtractorRGB : public IColorBasedROIExtractor  {

	int red;
	int green;
	int blue;
	double distanceThresholdMinimum;
	double distanceThresholdMaximum;
public:
	ColorBasedROIExtractorRGB();
	virtual ~ColorBasedROIExtractorRGB();
    void extractColorBasedROI(BRICS_3D::ColoredPointCloud3D *in_cloud, BRICS_3D::ColoredPointCloud3D *out_cloud);
    void extractColorBasedROI(BRICS_3D::ColoredPointCloud3D *in_cloud, BRICS_3D::PointCloud3D *out_cloud);

    int getBlue() const
    {
        return blue;
    }

    double getDistanceThresholdMinimum() const
    {
        return distanceThresholdMinimum;
    }

    void setDistanceThresholdMinimum(double distanceThreshold)
    {
        this->distanceThresholdMinimum = distanceThreshold;
    }


    double getDistanceThresholdMaximum() const
    {
        return distanceThresholdMaximum;
    }

    void setDistanceThresholdMaximum(double distanceThreshold)
    {
        this->distanceThresholdMaximum = distanceThreshold;
    }


    int getGreen() const
    {
        return green;
    }

    int getRed() const
    {
        return red;
    }

    void setBlue(int blue)
    {
        this->blue = blue;
    }


    void setGreen(int green)
    {
        this->green = green;
    }

    void setRed(int red)
    {
        this->red = red;
    }

};

}

#endif /* COLORBASEDROIEXTRACTORRGB_H_ */