# Chaikin's Curve Generator

## Building
1. Download the SFML 2.5.1 32-bit libraries for Visual C++ 15 from https://www.sfml-dev.org/download/sfml/2.5.1/.
2. Extract the SFML files into `C:\SFML-2.5.1`.
   1. Alternatively, extract the SFML files into your desired directory, then replace `C:\SFML-2.5.1\include` and `C:\SFML-2.5.1\lib` in ChaikinsCurves.vcxproj with `<your directory>\include` and `<your directory>\lib`, respectively.
3. Build the project in Visual Studio.

## How to use
* Click the **left mouse button** to add a vertex to the curve.
* Use the **left and right arrow keys** to increment or decrement the number of iterations, making the curve more or less smooth.
* Use the **up and down arrow keys** to cycle between the colors for the next vertex.
* Press **space** to reset the curve.
