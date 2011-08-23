/*
 * demoSegmentationNormalPlane.cpp
 *
 *  Created on: Apr 24, 2011
 *      Author: reon
 */

#include "algorithm/segmentation/RegionBasedSACSegmentationUsingNormals.h"
#include "core/PointCloud3D.h"
#include "core/Point3D.h"
#include <iostream>
#include "algorithm/segmentation/features/NormalEstimation.h"
#include "algorithm/nearestNeighbor/NearestNeighborANN.h"

int main(){

//This is not a working copy. Will be updated once normal extraction is done.

	//Create a pointcloud object
	BRICS_3D::PointCloud3D cloud;

	//Create the NormalSet for this cloud
	BRICS_3D::NormalSet3D normalSet;

	//Create the NormalEstimator object
	BRICS_3D::NormalEstimation normalEstimator;

	//read the points into the pointcloud
	//Please modify the path if there is a file read error.
	cloud.readFromTxtFile("./trunk/src/algorithm/segmentation/evaluation/data/demoCloud.txt");

	if (cloud.getSize()>0){
	cout<< "INFO: Current PointCloud Size: " <<cloud.getSize()<<endl;
	} else {
		cout<< "INFO: Current PointCloud Size: " <<cloud.getSize()<<endl;
		return 0;
	}



	//Extract the normals for this pointcloud

	normalEstimator.setInputCloud(&cloud);
	normalEstimator.setSearchMethod(new BRICS_3D::NearestNeighborANN());
	normalEstimator.setkneighbours(10);
	normalEstimator.computeFeature(&normalSet);

	//Create the vector to hold the model coefficients
	Eigen::VectorXd modelCoefficients;

	//Create the vector to hold the indexes of the model inliers
	std::vector<int> inliers;
	//Create the SACSegmentation Object
	BRICS_3D::RegionBasedSACSegmentationUsingNormals sacSegmenterUsingNormals;

	//Initialize the segmenter
	sacSegmenterUsingNormals.setDistanceThreshold(0.01);
	sacSegmenterUsingNormals.setInputPointCloud(&cloud);
	sacSegmenterUsingNormals.setMaxIterations(1000);
	sacSegmenterUsingNormals.setMethodType(sacSegmenterUsingNormals.SAC_RANSAC);
	sacSegmenterUsingNormals.setModelType(sacSegmenterUsingNormals.OBJMODEL_CYLINDER);
	sacSegmenterUsingNormals.setOptimizeCoefficients(false);
	sacSegmenterUsingNormals.setProbability(0.99);
	sacSegmenterUsingNormals.setInputNormals(&normalSet);


	//Perform the segmentation
	sacSegmenterUsingNormals.segment(inliers,modelCoefficients);

	if (inliers.size() == 0)
	{
		cout<<"Could not estimate a cylindrical model for the given dataset."<<endl;
		return (-1);
	}else {
		cout<<"Found Inliers: " << inliers.size()<<endl;
	}

	cout<<"The model-coefficients are: (" << modelCoefficients[0]<<", " << modelCoefficients[1]<<
			", " << modelCoefficients[2]<<", " << modelCoefficients[3]<<")" <<endl;

	return(1);
}
