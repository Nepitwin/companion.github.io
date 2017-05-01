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

#ifndef COMPANION_COMPANION_H
#define COMPANION_COMPANION_H

#include <functional>
#include <thread>

#include "companion/thread/StreamWorker.h"
#include "companion/input/Stream.h"
#include "companion/model/ImageRecognitionModel.h"
#include "companion/algo/abstract/ImageRecognition.h"
#include "companion/processing/ImageProcessing.h"
#include "companion/util/Definitions.h"

namespace Companion {

    /**
     * Companion configuration class to setup an computer vision usage like feature matching.
     *
     * @author Andreas Sekulski
     */
    class COMP_EXPORTS Configuration {

    public:

        /**
         * Constructor to create an companion helper class to start image processing setup.
         */
        Configuration();

        /**
         * Default destructor.
         */
        virtual ~Configuration();

        /**
         * Executes companion configuration.
         * @param worker StreamWorker pointer to obtain video images.
         * @throws error Companion::Error::Code error code if an invalid configuration is set.
         */
        void run(Companion::Thread::StreamWorker &worker);

        /**
         * Stops current running stream worker if it's executes.
         */
        void stop();

        /**
         * Obtain streaming source pointer if set.
         * @throws Companion::Error::Code Companion error code if video source is not set.
         * @return Streaming source to obtain images.
         */
        Companion::Input::Stream *getSource() const;

        /**
         * Set streaming source to companion.
         * @param source Video source to set like an camera or video.
         */
        void setSource(Companion::Input::Stream *source);

        /**
         * Add searching model type. For example an object (feature) which should be detected.
         * @param model Model to search.
         * @return True if model is added false if not.
         */
        bool addModel(Companion::Model::ImageRecognitionModel *model);

        /**
         * Remove searched model.
         * @param model Model to remove.
         */
        void removeModel(Companion::Model::ImageRecognitionModel *model);

        /**
         * Clear all models which are searched.
         */
        void clearModels();

        /**
         * Get model vector which contains all searched models.
         * @return Vector from all searched models, if no models are set this vector is empty.
         */
        const std::vector<Companion::Model::ImageRecognitionModel *> &getModels() const;

        /**
         * Gets current processing algorithm which should be used.
         * @throws Companion::Error::Code Companion error code if image processing is not set.
         * @return Image processing algorithm which should be used.
         */
        Companion::Processing::ImageProcessing *getProcessing() const;

        /**
         * Set image processing algorithm for example ObjectDetection.
         * @param processing Image processing algorithm to use.
         */
        void setProcessing(Companion::Processing::ImageProcessing *processing);

        /**
         * Get skip frame rate.
         * @return Skirp frame rate, how many frames should be skipped.
         */
        int getSkipFrame() const;

        /**
         * Sets skip frame rate.
         * @param skipFrame Number of frames which should be skipped after image processing should be used.
         */
        void setSkipFrame(int skipFrame);

        /**
         * Sets an given result handler.
         *
         * Result handler return an set from all detected objects as an vector and frame. If video processing is finished
         * the boolean will be returned true in last image processing.
         *
         * @param callback Function pointer which contains result event handler.
         */
        void setResultHandler(std::function<SUCCESS_CALLBACK> callback);

        /**
         * Gets an callback handler if set.
         * @throws Companion::Error::Code Companion error code if callback is not set.
         * @return An callback handler if set.
         */
        const std::function<SUCCESS_CALLBACK> &getCallback() const;

        /**
         * Sets an error callback handler.
         * @param callback Error handler to set.
         */
        void setErrorHandler(std::function<ERROR_CALLBACK> callback);

        /**
         * Get error callback if exists.
         * @throws Companion::Error::Code Companion error code if callback is not set.
         * @return Error callback if set.
         */
        const std::function<ERROR_CALLBACK> &getErrorCallback() const;

    private:

        /**
         * Callback event handler to send results back to main application.
         */
        std::function<SUCCESS_CALLBACK> callback;

        /**
         * Callback for an error.
         */
        std::function<ERROR_CALLBACK> errorCallback;

        /**
         * Data stream source to obtain images.
         */
        Companion::Input::Stream *source;

        /**
         * Search models to detect objects from source.
         */
        std::vector<Companion::Model::ImageRecognitionModel *> models;

        /**
         * Image processing implementation for example an object detection.
         */
        Companion::Processing::ImageProcessing *processing;

        /**
         * Number of frames to skip to process next image.
         */
        int skipFrame;

        /**
         * Consumer thread to store image data.
         */
        std::thread consumer;

        /**
         * Producer thread to image processing given image data.
         */
        std::thread producer;

        /**
         * Stream worker which runs an single job.
         */
        Companion::Thread::StreamWorker *worker;

    };

}

#endif //COMPANION_COMPANION_H