/* 
* Header only implementation of a matrix data structure used for reading, writing,
* and manipulating greyscale images.
* 
* 'IMatrix' short for 'ImageMatrix'
*
Author: Raphael Senn
*/
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include <stdexcept>
#include <vector>
#include <string>



template <typename T>
class IMatrix {
  private:
    // ________________________________________________________________________ 
    // Membervariables and methods (privat)

    std::vector<std::vector<T> > image_;        // data (pixels) of the image data
    int maxValue_;                              // maximal value in image_ 
    std::size_t height_;                        // height of the image
    std::size_t width_;                         // widht of the image

  public:
    // ________________________________________________________________________ 
    // Constructors
    
    IMatrix() = default;                          // default constructor
    IMatrix(const std::string imageName);         // constructor, that builts from a file
    ~IMatrix() = default;                         // destructor

    // ________________________________________________________________________ 
    // Operators

    bool operator==(const IMatrix<T>& other) const;
  


    // ________________________________________________________________________ 
    // Methods

    void readImage(const std::string imageName);      // reads and image (.pgm file) and saves the data in image_
    void writeImage(const std::string imageName);          // writes the data from image_ into an .pgm file
};

// ________________________________________________________________________ 
// Here are the implementations - since this is a header-only file.

// ________________________________________________________________________ 
// Constructores and destructors

template <typename T>
inline IMatrix<T>::IMatrix(const std::string imageName) { readImage(imageName); };

// ________________________________________________________________________ 
// Operators

template <typename T>
inline bool IMatrix<T>::operator==(const IMatrix<T>& other) const {
  return (image_ == other.image_) && (maxValue_ == other.maxValue_) && (width_ == other.width_) && (height_ == other.height_);
}


// ________________________________________________________________________ 
// Methods

template <typename T>
inline void IMatrix<T>::readImage(const std::string imageName) {
  std::ifstream fin(imageName, std::ios::binary);
  if (!fin) {throw std::runtime_error("Cannot open image: " + imageName); } 
  
  std::string line; 

  // magic number
  std::getline(fin, line);
  
  // skip comments
  do { std::getline(fin, line); } while (line[0] == '#');
  
  // read width and height
  std::istringstream dimLine(line);
  dimLine >> width_ >> height_;
 
  // read max value
  fin >> maxValue_;
  fin.get();

  // allocate image
  image_.resize(height_, std::vector<T>(width_));

  // read all the pixel data at once
  std::vector<T> rawPixels;
  rawPixels.reserve(width_ * height_);
  T pixel;
  while (fin >> pixel) { rawPixels.push_back(pixel); }
  if (rawPixels.size() != width_ * height_) { throw std::runtime_error("Pixel count does not match image dimensions."); }

  // fill rawPixels into image_
  for (size_t i = 0; i < height_; ++i) {
    for (size_t j = 0; j < width_; ++j) {
      image_[i][j] = rawPixels[i * width_ + j];
    }
  }
}

template <typename T>
inline void IMatrix<T>::writeImage(const std::string imageName) {
  std::ofstream fout(imageName);
  if (fout.fail()) { std::runtime_error("Could not write image: " + imageName); }
  
  // write magic number
  fout << "P2\n";

  // write comment
  fout << "# pgm image written by IMatrix\n";

  fout << width_ << "  " << height_ << "\n";

  fout << maxValue_ << "\n";
  
  // write pixels
  for (size_t i = 0; i < height_; ++i) {
    int n = 0;
    for (size_t j = 0; j < width_; ++j) {
      fout << image_[i][j] << "  "; 
    }
    fout << "\n";
  }
  fout.close();

}
 

// ________________________________________________________________________ 
// Explicit instantiation for int, floats and doubles

template class IMatrix<int>;
template class IMatrix<float>;
template class IMatrix<double>;