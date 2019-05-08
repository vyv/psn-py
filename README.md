![psn logo](https://github.com/vyv-ca/psn-cpp/blob/master/doc/psn-logo.png)

# An Open Protocol for On-Stage, Live 3D Position Data

Initially developed as a means for [**VYV**](https://www.vyv.ca)'s [**Photon**](https://www.vyv.ca/products/photon/) Media Server to internally communicate the position of freely-moving projection surfaces, [**PosiStageNet**](https://www.posistage.net/) became an open standard through a close collaboration between [**VYV**](https://www.vyv.ca) and [**MA Lighting**](https://www.malighting.com/), makers of the world-reknowned [**GrandMA2**](https://www.malighting.com/grandma2/) lighting console.

The result is a combined positioning and lighting system that allows for effects of an unparalleled scale, where large numbers of moving lights can precisely follow multiple performers on stage. The protocol’s applications do not stop at lighting – sound designers can use its data to accurately pan sound effects and music automatically according to the action on stage, and automation operators can obtain another level of feedback on the position of motor-driven stage elements – or even set targets. And that’s just the start; the applications of 3D stage positioning systems are only beginning to be explored.

If you have implemented [**PosiStageNet**](https://www.posistage.net/) in your system and would like to be mentioned on the website, or you have used [**PosiStageNet**](https://www.posistage.net/) for a project and would like to submit material for our Projects Showcase, or for other enquiries, please contact us at **info@posistage.net**

# Python Wrapper

This package contains a Python wrapper around the [**C++ implementation**](https://github.com/vyv/psn-cpp) of the protocol and pre-built Windows libraries for Python 3 x86/x64. It also contains a simple example of how to use the wrapper from the server or the client side.

The implementation is cross-platform so it should compile under Windows, Linux and Mac OS X. A Visual Studio project is given for compiling under Windows.

To clone the repository with all submodules, use `git clone https://github.com/vyv/psn-py/ --recursive`

For any question about the wrapper, please write at **info@posistage.net**

# Usage

To use the wrapper in your script, you need the 'psn' python module (psn.pyd). If you are running on Windows, copy the corresponding pre-built module found in the `libs` folder in the script folder. If you are running on Linux or OS X or using a Python version that is not liste in `libs`, you need to compile the library using a C++ compiler of your choice. If you compile the library using another IDE, please provide us the resulting library so we can add it to the list!
