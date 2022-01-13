<h2>Introduction</h2>
  <p>This repository contains Corinne Fair's work as a Graduate Research Assistant to Dr. Carlos Castellanos at RIT. The purpose of this work is to use computer vision in
  order to detect shapes and movement patterns within bacterial colonies such that these patterns can be replicated virtually or robotically alter their growth; the end goal
  is still being determined. The project primarily uses OpenCV and openFrameworks to achieve this, and the repository contains several different projects that each explore 
  different implementations and functions of these libraries in order to create different visual effects. Below is a short overview of each project and its purpose as well as
  a general setup guide.</p>

<h2>Overview of Project</h2>
<ul>
  <li>Canny Edge Detection: TODO</li>
  <li>Canny Contour Detection: TODO</li>
  <li>Background Subtraction: TODO</li>
  <li>Swarming: TODO</li>
  <li>Swarming3D: TODO</li>
  <li>Swarming Meshes: TODO</li>
</ul>
  
<h2>Setup Guide</h2>
  <p>This setup guide is written for Visual Studio 2019 on Windows.
  <ol>
    <li>Start by cloning this repository to your system using <tt>git clone https://github.com/crfair/beauty_GRA_work.git</tt> in the file location you would like to store it</li>
    <li>Download a stable OpenCV release for Windows (this project uses 4.5.3 at time of writing) from https://opencv.org/releases/. Run the executable that downloads and extract the contents to your desired location.</li>
    <li>You will need to add OpenCV's binaries to your system path. The beginning of the path will vary depending on where you extracted it to, but it should be something like <tt>C:\OpenCV-4.5.3\opencv\build\x64\vc15\bin</tt>.</li>
    <li>Download the latest Windows release of openFrameworks. <b>Note that at the time of writing, openFrameworks states that it only supports Visual Studio 2017; however, openFrameworks projects can be retargeted to work on VS 2019.</b> Extract the zip file to your desired location.</li>
    <li>The method of setting up each project in VS will vary depending on if it is an openFrameworks or OpenCV project. BackgroundSubtraction, CannyCountourDetection, and CannyEdgeDetection are OpenCV projects, while swarming, swarming_meshes, and swarming3D are openFrameworks projects.</li>
    <li>For OpenCV projects, on the VS 2019 startup screen, select the "Continue without code" button and when the main VS window opens, navigate to File -> New -> Project from existing code. Navigate to one of the OpenCV projects (e.g. backgroundSubtraction) and select it as the file path, then name the project the same name. On the next screen, select "Console application project" and click finish. The project should format itself automatically, but there will be some errors.</li>
    <li>In order to resolve the errors, we need to manually include OpenCV in the project. First, conform that the project is set to "Debug" and "x64". Then, navigate to Project -> [project name] properties.</li>
    <li>There are three things we need to add to the project properties. In here, double check that the configuration is Debug and the Platform is x64. Navigate to Configuration Properties -> VC++ Directories. Edit Include Directories and add OpenCV's include path; it should be something like <tt>C:\OpenCV-4.5.3\opencv\build\include</tt>. Do the same to add <tt>C:\OpenCV-4.5.3\opencv\build\x64\vc15\lib</tt> to the Library Directories.</li>
    <li>Finally, navigate to Linker -> Input and edit Additional Dependencies to include
  </ol>
  </p>
