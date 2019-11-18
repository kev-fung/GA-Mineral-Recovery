# Optimal Mineral Recovery with Genetic Algorithms

Mineral processing operations often use a series of separation units (known as circuits) to recover the target material into a concentrate stream and simultaneously filter out waste material to a tailings stream. Individual separation units have their own inefficiencies - hence such circuits are used to eliminate this problem. An economical optimisation problem arises out from the least amount of units required to separate the input material the quickest. Therefore, we (Team Gold) developed a C++ program parallelised with MPI and OpenMP to fast determine optimal circuit arrangements. 

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![GitHub contributors](https://img.shields.io/github/contributors/kev-fung/GA-Mineral-Recovery)](https://github.com/kev-fung/GA-Mineral-Recovery/graphs/contributors)

![minsep](https://github.com/kev-fung/GA-Mineral-Recovery/front_img.PNG)


1. GA Program
	1. Make a new Visual studio project, and link the src folder and Includes folder to the project.
	2. The src folder contains the .cpp files.
	3. The Includes folder contains the .h files.

2. Parallelised GA Program
	1. Move into the MPI folders and compile with:   mpic++ -std=c++11 *.h  *.cpp -o run
	2. Run the executable generated.
	3. OMP parallel folder contains the omp code

3. Extension
	1. extra_AdditionalComponents contains the code that allows for additional flow components. Runs as n

4. Applications and Tools
	1. Animation and plotting graphs
	2. Testings

