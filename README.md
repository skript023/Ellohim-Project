<h1 align="center">Ellohim Project</h1>
<p align="center">
  <a href="https://github.com/skript023/Ellohim-Project/blob/main/LICENSE">
    <img src="https://img.shields.io/github/license/skript023/Ellohim-Project.svg?style=flat-square"/>
   </a>
  <a href="https://github.com/skript023/Ellohim-Project/actions">
      <img src="https://img.shields.io/github/workflow/status/skript023/Ellohim-Project/CI/main?style=flat-square"/>
   </a>
  <br>
  A simple recovery mod menu for Grand Theft Auto Online.
  Strictly for educational purposes.
</p>

## Note
* This script running very unstable may cause game crashes
* Most of script in this project has been detected by anti-cheat
* I've create a new undetected one privately using different method

## Features
* ImGui–based user interface
* Unloading at runtime
* Log console
* Script fibers
* Fiber pool
* Access to YSC script globals
* scrProgram–based native hook

## Building
To build BigBaseV2 you need:
* Visual Studio 2019
* [Premake 5.0](https://premake.github.io/download.html) in your PATH

To set up the build environment, run the following commands in a terminal:
```dos
git clone https://github.com/skript023/Ellohim-Project.git --recurse-submodules
GenerateProjects.bat
```
Now, you will be able to open the solution, and simply build it in Visual Studio.
