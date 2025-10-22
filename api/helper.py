#helpers file to take care of extra functionality inside the views.py

import os
import subprocess
import pathlib
from PIL import Image

current_path = pathlib.Path().resolve()

image_processor = os.path.join(current_path, "api/image_process", "filter") #program written in C to apply filters
allowed_filters = ["blur", "grayscale", "sepia", "revert"]
out_path = "/Users/uglyprincess/Documents/Code/Python/Filtero/backend/api/image_process/old.bmp"
new_path = "/Users/uglyprincess/Documents/Code/Python/Filtero/backend/api/image_process/new.bmp"

def cleanup():
    #uploads folder
    for file in os.listdir("uploads"):
        file_path = os.path.join("uploads", file)
        os.remove(file_path)

    #image_processor

def apply_filter(in_path, filter_name):
    if filter_name.lower() not in allowed_filters:
        raise ValueError(f"Filter '{filter_name}' is not allowed")

    try:
        with Image.open(in_path) as img:
            img.convert("RGB").save(out_path)
            print(f"converted image at {out_path}")
    except Exception as e:
        print(f"Failed to convert image {in_path} to RGB: {e}")
        raise

    try:
        subprocess.run(
            [image_processor, "-"+filter_name[0], out_path, new_path],
            check=True,
            capture_output=True,
            text=True
        )
        cleanup()
    except subprocess.CalledProcessError as e:
        print(f"Couldn't execute {image_processor} with filter {filter_name}")

    print(new_path)
    return new_path