# AdaptiveIntegralThresholding
Adaptive Thresholding Using the Integral Image

Based on https://github.com/rmtheis/bradley-adaptive-thresholding
Converted to opencv 3

It gives better result then opencv cv::adaptiveThreshold

Build:

  cmake .

  make

Usage:

  ./aithreshold image.png output.png

image.png

![Image](https://github.com/zvezdochiot/aithreshold/blob/master/image.png)

output.png

![Image](https://github.com/zvezdochiot/aithreshold/blob/master/output.png)