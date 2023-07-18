# Prism Render

Prism Render is a ray tracing program that generates realistic images by simulating the behavior of light rays in a virtual scene. 

## Table of Contents
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [License](#license)

## Installation
To run Prism Render, follow these steps:

1. Clone the repository to your local machine.
2. Download the [premake binaries](https://github.com/premake/premake-core) (e.g. premake5.exe) and place them in the root folder.
3. Generate the project files corresponding to your preferred IDE.
4. Run Prism Render

## Usage
The main functionality of the program is implemented in the `main()` function in the `main.cpp` file. Here's a general overview of the steps performed:

1. Initialize the output image with the desired width and height.
2. Load the world image (environment map) for sky color calculations.
3. Create a camera object, specifying its position, orientation, and projection properties.
4. Define materials for different objects in the scene.
5. Define renderable objects in the scene.
6. Set the number of samples per pixel and the maximum bounce limit for the ray tracing algorithm.
7. Render the image by iterating over each pixel
8. Save the output image to a file.

To customize the scene, you can modify the camera position, orientation, and projection properties. You can also add or remove objects by creating instances of the appropriate classes (`Sphere`, `Plane`, `Disc`, `Triangle`, or `Mesh`), setting their properties, and adding them to the `renderObjects` vector.

## Examples
Here are a few examples of how to customize the ray tracing program:

### Adjusting the Camera
To change the camera position, modify the following line in the `main()` function:
```cpp
Camera cam(Vector3(5, 3, 0), Vector3(0, 1, 1), aspectRatio, 1.5);
```
Update the first Vector3 to set the camera's position. The second argument controls the camera's direction of view, and the fourth argument adjusts the field of view. You can also set a point in space that the camera should focus on by calling the `lookAt()` method.

### Adding Objects
To add new objects to the scene, create an instance of the desired class (e.g., `Sphere`, `Plane`, `Disc`, `Triangle`, or `Mesh`) and add it to the `renderObjects` vector:
```cpp
Sphere sphere(Vector3(1, 1, 1), 0.5);
renderObjects.push_back(&sphere);
```
Adjust the constructor arguments according to the object's position, size, and other properties.

### Modifying Materials
To change the appearance of objects, create instances of different material classes (e.g., `Lambertian`, `Metal`, or `Glass`) or create your own subclass of the `Material` class and assign them to objects:
```cpp
Lambertian diffuseRed(Vector3(1, 0.25, 0.25));
Lambertian diffuseWhite(Vector3(1, 1, 1));

std::vector<Material*> materials;
materials.push_back(&diffuseRed);
materials.push_back(&diffuseWhite);

// ...

Sphere sphere(Vector3(1, 1, 1), 0.5);
sphere.materialIndex = 0; // Assign the desired material index
```
You can create multiple materials and assign different materials to different objects by adjusting their `materialIndex` property.

## Contributing
Contributions to the ray tracing program are welcome! If you have any suggestions, bug reports, or feature requests, please open an issue or submit a pull request.

## License
The ray tracing program is released under the [MIT License](https://opensource.org/licenses/MIT). You are free to modify, distribute, and use the code for both commercial and non-commercial purposes. See the `LICENSE` file for more details.