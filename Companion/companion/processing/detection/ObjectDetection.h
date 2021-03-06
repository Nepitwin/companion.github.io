/*
 * This program is an object recognition framework written with OpenCV.
 * Copyright (C) 2016-2018 Andreas Sekulski, Dimitri Kotlovsky
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

#ifndef COMPANION_OBJECTDETECTION_H
#define COMPANION_OBJECTDETECTION_H

#include <companion/algo/detection/ShapeDetection.h>
#include <companion/model/result/DetectionResult.h>
#include <companion/processing/ImageProcessing.h>

namespace Companion {
	namespace Processing {
		namespace Detection
		{
			/**
			 * Object detection implementation to detect objects within an image like faces or shapes.
			 * @author Andreas Sekulski, Dimitri Kotlovsky
			 */
			class COMP_EXPORTS ObjectDetection : public ImageProcessing {

			public:

				/**
				 * Object detection constructor.
				 * @param detection Detection algorithm to detect ROI's.
				 */
				ObjectDetection(PTR_SHAPE_DETECTION detection);

				/**
				 * Destructor.
				 */
				virtual ~ObjectDetection() = default;

				/**
				 * Try to detect all objects in the given frame.
				 * @param frame Frame to check for an object location.
				 * @return A vector of results for the given frame or an empty vector if no objects are detected.
				 */
				CALLBACK_RESULT Execute(cv::Mat frame);

			private:

				/**
				 * Detection algorithm to search for ROI's.
				 */
				PTR_SHAPE_DETECTION detection;
			};
		}
	}
}

#endif //COMPANION_OBJECTDETECTION_H
