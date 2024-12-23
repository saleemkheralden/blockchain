import os
import glob
import sys

# Compiler command
compiler = "cl"

# Compiler flags
flags = "/EHsc"

# Target executable
def compile_cpp_files():
    cpp_files = glob.glob("*.cpp")
    for cpp_file in cpp_files:
        obj_file = cpp_file.replace(".cpp", ".obj")
        os.system(f"{compiler} {flags} /c {cpp_file} /Fo{obj_file}")

def link_objects(target):
    obj_files = glob.glob("*.obj")
    obj_string = " ".join(obj_files)
    os.system(f"{compiler} {flags} {obj_string} /Fe{target}")

def clean():
    obj_files = glob.glob("*.obj")
    for obj_file in obj_files:
        os.remove(obj_file)
        
    exe_files = glob.glob("*.exe")
    for exe_file in exe_files:
        os.remove(exe_file)

if __name__ == "__main__":
    if len(sys.argv) > 1 and sys.argv[1] == "clean":
        clean()
    elif len(sys.argv) > 1:
        target = sys.argv[1]
        compile_cpp_files()
        link_objects(target)
    else:
        compile_cpp_files()
        link_objects("zaher")
