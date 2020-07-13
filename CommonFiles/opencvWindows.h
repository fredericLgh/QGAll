#pragma once

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/ml.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgcodecs.hpp"

#ifdef _WIN64

#ifdef _DEBUG  
#pragma comment(lib, "opencv2/vc15/lib/opencv_world410d.lib")
#else
#pragma comment(lib, "opencv2/vc15/lib/opencv_world410.lib")
#endif 

#endif