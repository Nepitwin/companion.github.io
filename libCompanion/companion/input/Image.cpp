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

#include "Image.h"

Companion::Input::Image::Image() {
    index = 0;
}

Companion::Input::Image::~Image() {

}

void Companion::Input::Image::addImagePath(std::string path) {
    images.push_back(path);
}

cv::Mat Companion::Input::Image::obtainImage() {

    cv::Mat image;

    if(index < images.size()) {
        // Open image to read
        image = cv::imread(images.at(index));
        // Set next index position to load image.
        index++;
    }

    return image;
}