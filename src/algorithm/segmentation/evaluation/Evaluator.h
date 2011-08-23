/*
 * Evaluator.h
 *
 * @author: Pinaki Banerjee
 * @date: Apr 10, 2011
 * @version: 0.1
 * @description
 * This class contains all the information required for performing the evaluation of an algorithm
 * */

#ifndef EVALUATOR_H_
#define EVALUATOR_H_
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <stdlib.h>
using namespace std;
namespace BRICS_3D{

class Evaluator {
private:
	std::string gtBaseName;
	std::string msBaseName;
	std::string fileExt;				//store filename details
	int countGt;						//store no of regions in Ground Truth Image
	int countMs;						//stores no of regions in Machine Segmented Image
	std::string regionCorrespondence; 	//store information of GT-MS region correspondence
	int imageSize;
	bool initializationStatus;
public:
	vector<std::string> *vectorGt;	//store GT region points
	vector<std::string> *vectorMs;	//store MS region points
	Evaluator();
	virtual ~Evaluator();

	void setGtBaseName(std::string baseName);
	std::string getGtBaseName();

	void setMsBaseName(std::string baseName);
	std::string getMsBaseName();

	void setFileExt(std::string ext);
	std::string getFileExt();

	void setCountGt(int count);
	int getCountGt();

	void setCountMs(int count);
	int getCountMs();

	void setRegionCorrespondence(std::string regCorres);
	std::string getRegionCorrespondence();

	void setImageSize(int size);
	int getImageSize();

	/**
	 * Initialize the vectors by reading the required GT and MS files
	 */
	void Initialize();
	bool IsInitialized();

};

}

#endif /* EVALUATOR_H_ */