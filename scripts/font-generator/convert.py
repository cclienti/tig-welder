#!/usr/bin/env python3

import os
import sys
import glob
import argparse
import numpy
from PIL import Image


def read_images(filenames, transpose, hflip, vlip, invert):
    sprites = {}
    for filename in filenames:
        char_code = int(os.path.basename(filename).split("|")[1])
        im_frame = Image.open(filename)

        if transpose:
            im_frame = im_frame.transpose(Image.TRANSPOSE)
        if hflip:
            im_frame = im_frame.transpose(Image.FLIP_LEFT_RIGHT)
        if vlip:
            im_frame = im_frame.transpose(Image.FLIP_TOP_BOTTOM)

        width = im_frame.width
        height = im_frame.height

        sprite = numpy.array(im_frame.getdata()).reshape(height, width)

        if invert:
            sprite = sprite ^ 255

        sprite = sprite // 255

        sprites[char_code] = sprite
    return sprites


def convert_image(image):
    codes = []
    for line in image:
        code = sum(2**numpy.array(range(len(line))) * line)
        codes += [f"0x{code:02x}"]
    return "{" + ", ".join(codes) + "}"


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Convert font images to a C array")
    parser.add_argument("images", type=str, nargs="+",
                        help="All images that must be converted to a C array")
    parser.add_argument("--transpose", "-t", action="store_true", help="Transpose image like a matrix")
    parser.add_argument("--hflip", "-hf", action="store_true", help="Flip left and right (after transpose)")
    parser.add_argument("--vflip", "-vf", action="store_true", help="Flip top and bottom (after transpose)")
    parser.add_argument("--invert", "-i", action="store_true", help="Invert 0 and 255")
    parser.add_argument("--min-code", "-min", type=int, default=32, help="min ascii code to consider")
    parser.add_argument("--max-code", "-max", type=int, default=126, help="max ascii code to consider")

    args = parser.parse_args()
    sprites = read_images(args.images, args.transpose, args.hflip, args.vflip, args.invert)
    for key in sorted(sprites.keys()):
        if key < args.min_code or key > args.max_code:
            continue
        print(sprites[key], file=sys.stderr)
        chr_key = chr(key)
        chr_key = "backslash" if chr_key == "\\" else chr_key
        print(convert_image(sprites[key]) + f", // {key} - {chr(key)}")
