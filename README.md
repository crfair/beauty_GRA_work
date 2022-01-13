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
    <li>The method of setting up each project in VS will vary depending on if it is an openFrameworks or OpenCV project. BackgroundSubtraction, CannyCountourDetection, and CannyEdgeDetection are openFrameworks projects, while swarming, swarming_meshes, and swarming3D are OpenCV projects.
  </ol>
  </p>
