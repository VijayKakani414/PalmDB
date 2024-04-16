// original source of this file shield_slam - https://github.com/MohitShridhar/shield_slam/blob/master/shield_slam/ORB.cpp

#ifndef ORB_H
#define ORB_H

#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>

#include "Common.hpp"

#define GRID_CELL_ROWS 1
#define GRID_CELL_COLS 1

#define KNN_RATIO_INIT_THRESHOLD 0.7
#define KNN_RATIO_TRACKING_THRESHOLD 0.75

class ORB
{

public:
	ORB( int n_features = 500 );
	virtual ~ORB() = default;

	void ExtractFeatures( Mat& img, KeypointArray& img_keypoints, Mat& img_desc );

	void MatchFeatures( Mat& desc_ref, Mat& desc_tar, vector<DMatch>& matches,
						KeypointArray& ref_keypoints, KeypointArray& tar_keypoints,
						PointArray& ref_matches, PointArray& tar_matches, Mat& matched_tar_desc,
						bool use_ratio_test = true );
	void MatchFeatures( Mat& desc_ref, Mat& desc_tar, vector<DMatch>& matches,
						bool use_ratio_test = true );

	void DetectAndMatch( Mat& img_ref, Mat& img_tar, vector<DMatch>& matches,
							PointArray& ref_matches, PointArray& tar_matches, Mat& matched_tar_desc,
							KeypointArray &ref_keypoints, KeypointArray &tar_keypoints,
							Mat &ref_desc, Mat &tar_desc );

private:
	Ptr<cv::FeatureDetector> detector;
	Ptr<cv::DescriptorExtractor> extractor;
	Ptr<cv::DescriptorMatcher> matcher;
};

#endif // ORB_H
