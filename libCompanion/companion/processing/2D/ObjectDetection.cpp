/*
 * This program is an image recognition library written with OpenCV.
 * Copyright (C) 2016-2017 Andreas Sekulski
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ObjectDetection.h"

Companion::Processing::ObjectDetection::ObjectDetection(Companion::Configuration *companion,
                                                        Companion::Algorithm::Matching *matchingAlgo,
                                                        Companion::SCALING scaling,
														Companion::Algorithm::ShapeDetection *shapeDetection) 
{
    this->companion = companion;
    this->matchingAlgo = matchingAlgo;
    this->scaling = scaling;
	this->shapeDetection = shapeDetection;
}

Companion::Processing::ObjectDetection::~ObjectDetection() 
{
    
}

CALLBACK_RESULT Companion::Processing::ObjectDetection::execute(cv::Mat frame) 
{

	Companion::Model::Result* result = nullptr;
    Model::Processing::FeatureMatchingModel* scene;
	CALLBACK_RESULT objects;
    std::vector<Model::Processing::ImageRecognitionModel*> models;
	std::vector<Companion::Draw::Frame*> rois;
	int oldX, oldY, index;

    if (!frame.empty()) 
	{
        scene = new Model::Processing::FeatureMatchingModel();
		Model::Processing::FeatureMatchingModel* objectModel;
        models = companion->getModels();

        oldX = frame.cols;
        oldY = frame.rows;

        // Shrink the image with a given scale factor or a given output width. Use this list for good 16:9 image sizes:
        // https://antifreezedesign.wordpress.com/2011/05/13/permutations-of-1920x1080-for-perfect-scaling-at-1-77/
        Util::resizeImage(frame, this->scaling);
        scene->setImage(frame);

		if (shapeDetection != nullptr)
		{
			// If shape detection should be used obtain all posible rois from frame.
			rois = shapeDetection->executeAlgorithm(scene->getImage());
		}

        for(unsigned long x = 0; x < models.size(); x++) 
		{

			objectModel = dynamic_cast<Companion::Model::Processing::FeatureMatchingModel*>(models.at(x));
			if (!objectModel) 
			{
				// If wrong model types are used
				throw Companion::Error::Code::wrong_model_type;
			}

			if (rois.size() == 0)
			{
				// If rois not found or used
				result = matchingAlgo->executeAlgorithm(scene, objectModel, nullptr);
			}
			else
			{
				index = 0;
				// If rois found
				while (index < rois.size()) // Search only so long if a object was detected or all rois are checked.
				{
					result = matchingAlgo->executeAlgorithm(scene, objectModel, rois.at(index));
					index++;
				}
			}

			// Put in method
			if (result != nullptr) 
			{
				// Create old image size
				result->getModel()->ratio(frame.cols, frame.rows, oldX, oldY);
				// Store detected object and its ID to vector.
				objects.push_back(result);
			}
        }
        
        frame.release();
        delete scene;
    }

    return objects;
}