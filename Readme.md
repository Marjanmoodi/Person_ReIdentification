# Part-based persopn re-identification
In video surveillance, person re-identification is the task of recognizing whether an individual has already been observed over a network of cameras. Typically, this is achieved by exploiting the clothing appearance. Clothing appearance is represented by means of low-level local and/or global features of the image, usually extracted according to some part-based body model to treat different body parts (e.g. torso and legs) independently. This project provides a system of current approaches to build appearance descriptors for person re-identification.

In this project, we use an appearance-based method for person re-identification. At the first step, we decompose the body parts and secondly extract information like weighted color histogram and texture from this parts. In this way, robustness against the very low resolution, occlusions, different viewpoint and illumination changes is achieved.
You can find the base paper [here](https://ieeexplore.ieee.org/abstract/document/5539926/)
## Sample output
In this figure you can see the query image and preprocossing on it (first row) and best matched result which algorithm has been found (Second row)
![first sample](https://github.com/Marjanmoodi/Person_ReIdentification/blob/master/Result/output1.png)
![Second sample](https://github.com/Marjanmoodi/Person_ReIdentification/blob/master/Result/output2.png)


