/*
 * CircleAnomalyDetector.h
 *
 *  Created on: 8 срхїз 2020
 *      Author: Eli
 */

#ifndef CircleAnomalyDetector_H_
#define CircleAnomalyDetector_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>

struct correlatedFeatures {
	string feature1, feature2;  // names of the correlated features
	float corrlation;
	Line lin_reg;
	float threshold;
	float cx, cy;
};


class CircleAnomalyDetector :public TimeSeriesAnomalyDetector {
protected:
	vector<correlatedFeatures> cf;
	float threshold;
public:
	CircleAnomalyDetector();
	virtual ~CircleAnomalyDetector();

	virtual void learnNormal(const TimeSeries& ts);
	virtual vector<AnomalyReport> detect(const TimeSeries& ts);
	vector<correlatedFeatures> getNormalModel() {
		return cf;
	}
	void setCorrelationThreshold(float threshold) {
		this->threshold = threshold;
	}
	void mostCorrelatedFeature(const char* CSVfileName, char** l, int size, const char* att, char* s);
	void getAnomalyTimeSteps(const char* CSVfileName, char** l, int size, const char* oneWay, const char* otherWay, char* f);
	// helper methods
protected:
	vector<Point*> floatsToPoints(vector <float> x, vector <float> y);
	virtual void learnHelper(const TimeSeries& ts, float p/*pearson*/, string f1, string f2, Point** ps);
	virtual bool isAnomalous(float x, float y, correlatedFeatures c);
	Point** toPoints(vector<float> x, vector<float> y);
	float findThreshold(Point** ps, size_t len, Line rl);
	//ronia helper methods
	float getCorrelation(string& f1, string& f2, const TimeSeries& ts);
	int getSize();
};



#endif /* CircleAnomalyDetector_H_ */

