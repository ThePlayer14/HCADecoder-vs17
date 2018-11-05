# HCADecoder-vs17

# Introduction
This project is the Visual Studio 2017 bundle of Nyagamon's HCADecoder.
The text in the sources are translated into English for better understanding of the functions.

# Building
1. Open HCADecoder.sln or HCADecoder.vcxproj with Visual Studio 2017
2. In Visual Studio, select "Build HCADecoder" and the built binary will be in a "Release" folder for the selected architecture (default:x86)

# Notes
If you are switching architectures (for instance, switching x86 into x64), make sure you set the sources to not use precompiled headers, or the building process will fail.
You can set precompiled header options by right-clicking on a source file and selecting "Properties".
