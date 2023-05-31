# miniRT

## Ray Tracing Algorithm

#### 1. Ray Generation

* For each pixel in the image, we need to generate a ray that starts from the camera position and passes through the pixel.
* To generate the ray, we need the camera position, the normalized direction vector of the ray, and the field of view (FOV) of the camera.
* The FOV determines the width and height of the viewing plane at a specific distance from the camera.
* By dividing the viewing plane into a grid of pixels, we can calculate the ray direction for each pixel.

#### 2. Ray-Object Intersection

* Once we have the ray, we need to check for intersection with each object in the scene (planes, spheres, and cylinders).
* For each object, we'll implement a specific intersection algorithm that calculates the intersection point, if any, between the ray and the object.
* The intersection algorithms will differ depending on the object type. For example, the intersection algorithm for a sphere involves solving a quadratic equation, while for a plane, it requires calculating the intersection of a ray and a plane equation.
* We'll keep track of the closest intersection point (if any) and the object that was intersected.

#### 3. Shading and Lighting

* Once we find the closest intersection point, we can calculate the shading and lighting for that point.
* We'll use the Phong reflection model, which consists of three components: ambient, diffuse, and specular.
* The ambient component represents the overall ambient light in the scene and is constant for all points.
The diffuse component depends on the incoming light direction and the surface normal at the intersection point.
* The specular component is responsible for simulating the reflection of light off shiny surfaces.
* We'll calculate the color at the intersection point based on the object's material properties and the light sources in the scene.

#### 4. Shadow Rays

* To determine if a point is in shadow, we need to cast shadow rays from the intersection point towards all light sources in the scene.
* If any object is intersected along the way, the point is in shadow.
* We'll calculate the shadow rays and check for intersections with other objects to determine the presence or absence of shadows.

#### 5. Recursive Reflection and Refraction

* To handle reflections and refractions, we'll use recursive ray tracing.
* If an object has reflective or transparent properties, we'll generate additional rays to simulate reflection or refraction.
* For reflection, we'll calculate the reflected ray direction based on the surface normal and recursively trace the reflected ray until it reaches a non-reflective object or a maximum recursion depth.
* For refraction, we'll calculate the refracted ray direction based on the surface normal and the refractive index of the material, and recursively trace the refracted ray.
* We'll compute the final color by blending the reflected and refracted colors with the original shading and lighting calculation.

#### 6. Color Accumulation

* As the rays propagate through the scene, we'll accumulate the color values at each intersection point.
* This can be achieved by initializing a color value at each ray-object intersection and updating it based on the object's material properties, lighting, and any recursive reflections or refractions.

#### 7. Antialiasing

* To reduce the appearance of jagged edges, we can apply antialiasing techniques.
* One common approach is to use a technique called supersampling, where we shoot multiple rays per pixel and average the resulting colors.
* By randomly offsetting the ray origins within each pixel, we can obtain smoother edges and improved image quality
