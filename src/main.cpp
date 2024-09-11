#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

#include "scene_parser.h"
#include "image.h"
#include "ray.h"
#include "camera.h"
#include "group.h"

char* input_file = NULL; 
int   width = 100;
int   height = 100;
char* output_file = NULL;
float depth_min = 0;
float depth_max = 1;
char* depth_file = NULL;


/**
 * Interpreta los argumentos del programa
 *
 *  sample command lines:
 *  raycast -input input.txt -size 100 100 -output output.tga
 *  raycast -input input.txt -size 100 100 -depth 5.5 8.8 output.tga
 *
 */
void parseArguments(int argc, char* argv[]) {

    //printf("Input %d\n", strcmp(argv[1],"-input"));
    for (int i = 1; i < argc; i++) {
        if (0 == strcmp(argv[i],"-input")) {
            i++;
            assert (i < argc);
            input_file = argv[i];
        } else if (!strcmp(argv[i],"-size")) {
            i++;
            assert (i < argc);
            width = atoi(argv[i]);
            i++;
            assert (i < argc);
            height = atoi(argv[i]);
        } else if (!strcmp(argv[i],"-output")) {
            i++;
            assert (i < argc);
            output_file = argv[i];
        } else if (!strcmp(argv[i],"-depth")) {
            i++;
            assert (i < argc);
            depth_min = atof(argv[i]);
            i++;
            assert (i < argc);
            depth_max = atof(argv[i]);
            i++;
            assert (i < argc);
            depth_file = argv[i];
        } else {
            printf ("whoops error with command line argument %d: '%s'\n",i,argv[i]);
            assert(0);
        }
    }
    //printf("First!!! %s", argv[1]);

}

const int MIN_T = 0;
const int MAX_T = 10000;

void generateImageFromScene(Image& img, Image& dimg, SceneParser& scene){
    int w = img.Width();
    int h = img.Height();

    //generate image / depth image
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            //Collision Check
            Vec2f point = Vec2f((float)i / (float)(w - 1), (float)j / (float)(h - 1));
            Ray ray = scene.getCamera()->generateRay(point);
            Hit hit = Hit(MAX_T, scene.getBackgroundColor());
            bool collision = scene.getGroup()->intersect(ray, hit, MIN_T);

            //Generate color image
            img.SetPixel(i, j, hit.getColor());

            //Generate Depth Image
            const float minV = 0.0, maxV = 1.0;
            float v = (depth_max - hit.getT()) / (depth_max - depth_min);
            float grayColor = min(max(v, minV), maxV);
            dimg.SetPixel(i, j, Vec3f(grayColor, grayColor, grayColor));
        }
    }
}

bool isPPM(char* output_file) {
    int length = strlen(output_file);
    return output_file[length - 3] == 'p' && output_file[length - 2] == 'p' && output_file[length - 1] == 'm';
}

int main(int argc, char* argv[]) {

    // Interpreta los argumentos del programa
    parseArguments(argc, argv);
    
    SceneParser scene = SceneParser(input_file);
    Image image = Image(width, height);
    Image depthImage = Image(width, height);

    generateImageFromScene(image, depthImage, scene);
    
    if (output_file != NULL) {
        if (isPPM(output_file)) image.SavePPM(output_file);
        else image.SaveTGA(output_file);
    }

    if (depth_file != NULL) {
        if (isPPM(depth_file)) depthImage.SavePPM(depth_file);
        else depthImage.SaveTGA(depth_file);
    }

    return 0;
}


