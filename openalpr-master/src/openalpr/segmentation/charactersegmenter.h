/*
 * Copyright (c) 2014 New Designs Unlimited, LLC
 * Opensource Automated License Plate Recognition [http://www.openalpr.com]
 *
 * This file is part of OpenAlpr.
 *
 * OpenAlpr is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License
 * version 3 as published by the Free Software Foundation
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPENALPR_CHARACTERSEGMENTER_H
#define OPENALPR_CHARACTERSEGMENTER_H

#include "opencv2/imgproc/imgproc.hpp"
#include "constants.h"
#include "binarize_wolf.h"
#include "utility.h"
#include "characterregion.h"
#include "colorfilter.h"
#include "verticalhistogram.h"
#include "config.h"


//const float MIN_BOX_WIDTH_PX = 4; // 4 pixels

const cv::Scalar COLOR_DEBUG_EDGE(0,0,255); // Red
const cv::Scalar COLOR_DEBUG_SPECKLES(0,0,255); // Red
const cv::Scalar COLOR_DEBUG_MIN_HEIGHT(255,0,0); // Blue
const cv::Scalar COLOR_DEBUG_MIN_AREA(255,0,0); // Blue
const cv::Scalar COLOR_DEBUG_FULLBOX(255,255,0); // Blue-green
const cv::Scalar COLOR_DEBUG_COLORFILTER(255,0,255); // Magenta
const cv::Scalar COLOR_DEBUG_EMPTYFILTER(0,255,255); // Yellow

class CharacterSegmenter
{

  public:
    CharacterSegmenter(PipelineData* pipeline_data);
    virtual ~CharacterSegmenter();

    int confidence;


  private:
    Config* config;
    PipelineData* pipeline_data;
    
    CharacterAnalysis* charAnalysis;

    LineSegment top;
    LineSegment bottom;

    std::vector<cv::Mat> imgDbgGeneral;
    std::vector<cv::Mat> imgDbgCleanStages;

    std::vector<bool> filter(cv::Mat img, std::vector<std::vector<cv::Point> > contours, std::vector<cv::Vec4i> hierarchy);
    std::vector<bool> filterByBoxSize(std::vector< std::vector<cv::Point> > contours, std::vector<bool> goodIndices, float minHeightPx, float maxHeightPx);
    std::vector<bool> filterBetweenLines(cv::Mat img, std::vector<std::vector<cv::Point> > contours, std::vector<cv::Vec4i> hierarchy, std::vector<cv::Point> outerPolygon, std::vector<bool> goodIndices);
    std::vector<bool> filterContourHoles(std::vector<std::vector<cv::Point> > contours, std::vector<cv::Vec4i> hierarchy, std::vector<bool> goodIndices);

    std::vector<cv::Point> getBestVotedLines(cv::Mat img, std::vector<std::vector<cv::Point> > contours, std::vector<bool> goodIndices);
    int getGoodIndicesCount(std::vector<bool> goodIndices);

    cv::Mat getCharacterMask(cv::Mat img_threshold, std::vector<std::vector<cv::Point> > contours, std::vector<cv::Vec4i> hierarchy, std::vector<bool> goodIndices);
    cv::Mat getCharBoxMask(cv::Mat img_threshold, std::vector<cv::Rect> charBoxes);

    void removeSmallContours(std::vector<cv::Mat> thresholds, std::vector<std::vector<std::vector<cv::Point > > > allContours, float avgCharWidth, float avgCharHeight);

    cv::Mat getVerticalHistogram(cv::Mat img, cv::Mat mask);
    std::vector<cv::Rect> getHistogramBoxes(VerticalHistogram histogram, float avgCharWidth, float avgCharHeight, float* score);
    std::vector<cv::Rect> getBestCharBoxes(cv::Mat img, std::vector<cv::Rect> charBoxes, float avgCharWidth);
    std::vector<cv::Rect> combineCloseBoxes( std::vector<cv::Rect> charBoxes, float avgCharWidth);

    std::vector<cv::Rect> get1DHits(cv::Mat img, int yOffset);

    void cleanCharRegions(std::vector<cv::Mat> thresholds, std::vector<cv::Rect> charRegions);
    void cleanBasedOnColor(std::vector<cv::Mat> thresholds, cv::Mat colorMask, std::vector<cv::Rect> charRegions);
    void cleanMostlyFullBoxes(std::vector<cv::Mat> thresholds, const std::vector<cv::Rect> charRegions);
    std::vector<cv::Rect> filterMostlyEmptyBoxes(std::vector<cv::Mat> thresholds, const  std::vector<cv::Rect> charRegions);
    void filterEdgeBoxes(std::vector<cv::Mat> thresholds, const std::vector<cv::Rect> charRegions, float avgCharWidth, float avgCharHeight);

    int getLongestBlobLengthBetweenLines(cv::Mat img, int col);

    int isSkinnyLineInsideBox(cv::Mat threshold, cv::Rect box, std::vector<std::vector<cv::Point> > contours, std::vector<cv::Vec4i> hierarchy, float avgCharWidth, float avgCharHeight);

    std::vector<cv::Point> getEncapsulatingLines(cv::Mat img, std::vector<std::vector<cv::Point> > contours, std::vector<bool> goodIndices);
};

#endif // OPENALPR_CHARACTERSEGMENTER_H
