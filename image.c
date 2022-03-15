/*
 * This file is part of libembroidery.
 *
 * Copyright 2018-2022 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
 * This file contains all the read and write functions for the
 * library.
 *
 *******************************************************************
 *
 * PPM Images
 * ----------
 *
 * Basic read/write support for images, so we can convert
 * to any other format we need using imagemagick.
 *
 * We only support P3 ASCII ppm, that is the original, 8 bits per channel.
 *
 * This also allows support for making animations using ffmpeg/avconv
 * of the stitching process.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "embroidery.h"

/* for the PES embedded */
void writeImage(FILE* file, unsigned char image[][48]) {
    int i, j;

    if (!file) {
        printf("ERROR: format-pec.c writeImage(), file argument is null\n");
        return;
    }
    for (i = 0; i < 38; i++) {
        for (j = 0; j < 6; j++) {
            int offset = j * 8;
            unsigned char output = 0;
            output |= (unsigned char)(image[i][offset] != 0);
            output |= (unsigned char)(image[i][offset + 1] != (unsigned char)0) << 1;
            output |= (unsigned char)(image[i][offset + 2] != (unsigned char)0) << 2;
            output |= (unsigned char)(image[i][offset + 3] != (unsigned char)0) << 3;
            output |= (unsigned char)(image[i][offset + 4] != (unsigned char)0) << 4;
            output |= (unsigned char)(image[i][offset + 5] != (unsigned char)0) << 5;
            output |= (unsigned char)(image[i][offset + 6] != (unsigned char)0) << 6;
            output |= (unsigned char)(image[i][offset + 7] != (unsigned char)0) << 7;
            fwrite(&output, 1, 1, file);
        }
    }
}

EmbImage * embImage_create(int width, int height)
{
    int i;
    EmbImage *image;
    image = (EmbImage*)malloc(sizeof(EmbImage));
    image->pixel_width = width;
    image->pixel_height = height;
    image->offset.x = 0.0;
    image->offset.y = 0.0;
    image->color = (EmbColor*)malloc(sizeof(EmbColor)*width*height);
    for (i=0; i<width*height; i++) {
        image->color[i].r = 255;
        image->color[i].g = 255;
        image->color[i].b = 255;
    }
    return image;
}

void embImage_free(EmbImage *image)
{
    free(image->color);
    free(image);
}

/*
 */
int read_ppm_image(char *fname, EmbImage *a)
{
    int i, state;
    FILE *f;
    char header[2];
    f = fopen(fname, "r");
    if (!f) {
        return 0;
    }
    a->pixel_width = 100;
    a->pixel_height = 75;
    state = 0;
    while (fread(header, 1, 1, f) == 1) {
        /* state machine for dealing with the header */
        if (header[0] == '\n') {
            state++;
        }
        if (state == 4) {
            break;
        }
    }
    for (i=0; i<a->pixel_width * a->pixel_height; i++) {
        embColor_read(f, &(a->color[i]), 3);
    }
    fclose(f);
    return 1;
}


/*
 * This function should work, combine with:
 *    $ convert example.ppm example.png
 */
void write_ppm_image(char *fname, EmbImage *a)
{
    int i, j;
    FILE *f;
    char header[100];
    f = fopen(fname, "w");
    if (!f) {
        printf("Failed to open file: %s\n", fname);
        return;
    }
    sprintf(header, "P3\n# Generated by libembroidery 0.1\n%d %d\n%d\n", a->pixel_width, a->pixel_height, 255);
    fputs(header, f);
    for (i=0; i<a->pixel_height; i++) {
        for (j=0; j<a->pixel_width; j++) {
            fprintf(f, "%d %d %d ",
                a->color[j+i*a->pixel_width].r,
                a->color[j+i*a->pixel_width].g,
                a->color[j+i*a->pixel_width].b);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}


/*
 *
 */
float image_diff(EmbImage *a, EmbImage* b)
{
    int i, j;
    float total;
    total = 0.0;
    for (i=0; i<a->pixel_width; i++) {
        for (j=0; j<a->pixel_height; j++) {
            total += embColor_distance(
                a->color[i+j*a->pixel_width],
                b->color[i+j*b->pixel_width]
            );
        }
    }
    return total;
}

/* Render Line
 * -----------
 * 
 */

int render_line(EmbLine line, EmbImage *image, EmbColor color) {
    EmbVector diff, pos, offset;
    int i;
    float pix_w, pix_h;
    offset.x = -10.0;
    offset.y = -10.0;
    embVector_subtract(line.end, line.start, &diff);
    pix_w = image->width / image->pixel_width;
    pix_h = image->height / image->pixel_height;
    for (i = 0; i < 1000; i++) {
        int x, y;
        pos.x = line.start.x + 0.001*i*diff.x + offset.x;
        pos.y = line.start.y + 0.001*i*diff.y + offset.y;
        x = (int)round(pos.x / pix_w);
        y = (int)round(pos.y / pix_h);
        if (x >= 0 && x < image->pixel_width)
        if (y >= 0 && y < image->pixel_height) {
            image->color[x+y*image->pixel_width] = color;
        }
    }
    return 1;
}

/* Basic Render
 * ------------
 * This is a simple algorithm that steps through the stitches and
 * then for each line calls render_line.
 *
 * The caller is responsible for the memory in p.
 */

int embImage_render(EmbPattern *p, float width, float height, char *fname) {
    int i;
    EmbImage *image;
    EmbColor black = {0, 0, 0};
    image = embImage_create(100, 100);
    image->width = width;
    image->height = height;
    for (i=1; i < p->stitchList->count; i++)  {
        EmbLine line;
        line.start.x = p->stitchList->stitch[i-1].x;
        line.start.y = p->stitchList->stitch[i-1].y;
        line.end.x = p->stitchList->stitch[i].x;
        line.end.y = p->stitchList->stitch[i].y;
        render_line(line, image, black); /* HACK: st.color); */
    }
    write_ppm_image(fname, image);
    embImage_free(image);
    return 0;
}

/* EPS style render
 *
 *
 */

int render_postscript(EmbPattern *pattern, EmbImage *image) {
    puts("Postscript rendering not supported, defaulting to ppm.");
    embImage_render(pattern, image->width, image->height, "default.ppm");
    return 1;
}

/* Simulate the stitching of a pattern, using the image for rendering
 * hints about how to represent the pattern.
 */
int embImage_simulate(EmbPattern *pattern, float width, float height, char *fname) {
    embImage_render(pattern, width, height, fname);
    return 0;
}

