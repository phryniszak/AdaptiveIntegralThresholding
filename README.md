# AdaptiveIntegralThresholding
Adaptive Threshold Using Integral Image

Based on https://github.com/rmtheis/bradley-adaptive-thresholding

Converted to opencv 4

It gives better result then opencv cv::adaptiveThreshold

Previous version has a small bug as integral mat returned by opencv is one row and column bigger then source mat and it was not accounted in computation.
