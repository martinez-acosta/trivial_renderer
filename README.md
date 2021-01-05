# Trivial Rendeder
![Last Commit](https://img.shields.io/github/last-commit/martinez-acosta/trivial_renderer)

## Project Goals


Develop an application that implements computer graphics lighting algorithms and rasterization of files in Waveform format

## Libraries/Languages

- C++
- QMake
- Gengetopt (parsing input-user command line)
- Boost  (string manipulation like split)
- FFmpeg (merge the frames into a video)

## Explanation (Spanish)
- https://tinyurl.com/y59kshsp

# Videos
- Z-buffer: https://youtu.be/acT-4PxC0HY
- Bézier: https://youtu.be/KjO8wf7cfM8
- Wireframe: https://youtu.be/aHUB8vPaUEM
- Phong: https://youtu.be/S2gSLifHl_A
- Gourand: https://youtu.be/Ld6avcBQARA
- Flat Shading: https://youtu.be/B_mSwNqAs5g


## Status

- [x] Rasterization
- [x] Z-buffer
- [x] Flat Shading
- [x] Phong Shading
- [x] Gouraud Shading
- [x] Bézier curves

## Build Setup

```bash
# make the project platform-specific
$ qmake trivial_renderer.pro

# compile and generate the executable
$ make

# print help
$ ./trivial_renderer --help

# run examples (generate frames for 3 minutes at 23.976 fps)
# Wireframe:
$ ./trivial_renderer -i Charizard.obj  --resolution 1920,1080 --angleOfView 90 --bezier-curve 0,0,960,750,100,1,1920,1080 --near 0.5 --far 20  --camera 0,0,-50 --wireframe --time 3
# face hiding:
$ ./trivial_renderer -i Charizard.obj  --resolution 1920,1080 --angleOfView 90 --bezier-curve 0,0,960,750,100,1,1920,1080 --near 0.5 --far 20  --camera 0,0,-50 --faceHiding --time 3
# flat shading:
$ ./trivial_renderer -i Charizard.obj  --resolution 1920,1080 --angleOfView 90 --bezier-curve 0,0,960,750,100,1,1920,1080 --near 0.5 --far 20  --camera 0,0,-50 --flatShading 40,40,40 --time 3
# zbuffer + barycentric coordinates:
$ ./trivial_renderer -i Charizard.obj  --resolution 1920,1080 --angleOfView 90 --bezier-curve 0,0,960,750,100,1,1920,1080 --near 0.5 --far 20  --camera 0,0,-50 --zBuffer --time 3
# gourand:
$ ./trivial_renderer -i Charizard.obj  --resolution 1920,1080 --angleOfView 90 --bezier-curve 0,0,960,750,100,1,1920,1080 --near 0.5 --far 20  --camera 0,0,-50 --gourand 40,40,40 --time 3
# phong:
$ ./trivial_renderer -i Charizard.obj  --resolution 1920,1080 --angleOfView 90 --bezier-curve 0,0,960,750,100,1,1920,1080 --near 0.4 --far 20  --camera 0,0,-50 --phong 40,40,40,0.1,0.5,0.4,2 --time 3
# Generate video from frames
$ ffmpeg -framerate 24000/1001 -i %06d.png -c:v libx264 -pix_fmt yuv420p out.mp4
```