# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mrzs/Proj/part_darknet

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mrzs/Proj/part_darknet/build

# Include any dependencies generated for this target.
include CMakeFiles/demo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/demo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/demo.dir/flags.make

CMakeFiles/demo.dir/test/main.c.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/test/main.c.o: ../test/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mrzs/Proj/part_darknet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/demo.dir/test/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/demo.dir/test/main.c.o   -c /home/mrzs/Proj/part_darknet/test/main.c

CMakeFiles/demo.dir/test/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/demo.dir/test/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mrzs/Proj/part_darknet/test/main.c > CMakeFiles/demo.dir/test/main.c.i

CMakeFiles/demo.dir/test/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/demo.dir/test/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mrzs/Proj/part_darknet/test/main.c -o CMakeFiles/demo.dir/test/main.c.s

CMakeFiles/demo.dir/test/main.c.o.requires:

.PHONY : CMakeFiles/demo.dir/test/main.c.o.requires

CMakeFiles/demo.dir/test/main.c.o.provides: CMakeFiles/demo.dir/test/main.c.o.requires
	$(MAKE) -f CMakeFiles/demo.dir/build.make CMakeFiles/demo.dir/test/main.c.o.provides.build
.PHONY : CMakeFiles/demo.dir/test/main.c.o.provides

CMakeFiles/demo.dir/test/main.c.o.provides.build: CMakeFiles/demo.dir/test/main.c.o


# Object files for target demo
demo_OBJECTS = \
"CMakeFiles/demo.dir/test/main.c.o"

# External object files for target demo
demo_EXTERNAL_OBJECTS =

demo: CMakeFiles/demo.dir/test/main.c.o
demo: CMakeFiles/demo.dir/build.make
demo: liblib_core.so
demo: /usr/local/lib/libopencv_stitching.so.3.4.3
demo: /usr/local/lib/libopencv_superres.so.3.4.3
demo: /usr/local/lib/libopencv_videostab.so.3.4.3
demo: /usr/local/lib/libopencv_img_hash.so.3.4.3
demo: /usr/local/lib/libopencv_line_descriptor.so.3.4.3
demo: /usr/local/lib/libopencv_tracking.so.3.4.3
demo: /usr/local/lib/libopencv_aruco.so.3.4.3
demo: /usr/local/lib/libopencv_xfeatures2d.so.3.4.3
demo: /usr/local/lib/libopencv_bioinspired.so.3.4.3
demo: /usr/local/lib/libopencv_surface_matching.so.3.4.3
demo: /usr/local/lib/libopencv_reg.so.3.4.3
demo: /usr/local/lib/libopencv_hfs.so.3.4.3
demo: /usr/local/lib/libopencv_structured_light.so.3.4.3
demo: /usr/local/lib/libopencv_saliency.so.3.4.3
demo: /usr/local/lib/libopencv_rgbd.so.3.4.3
demo: /usr/local/lib/libopencv_datasets.so.3.4.3
demo: /usr/local/lib/libopencv_dnn_objdetect.so.3.4.3
demo: /usr/local/lib/libopencv_freetype.so.3.4.3
demo: /usr/local/lib/libopencv_face.so.3.4.3
demo: /usr/local/lib/libopencv_ccalib.so.3.4.3
demo: /usr/local/lib/libopencv_optflow.so.3.4.3
demo: /usr/local/lib/libopencv_plot.so.3.4.3
demo: /usr/local/lib/libopencv_stereo.so.3.4.3
demo: /usr/local/lib/libopencv_fuzzy.so.3.4.3
demo: /usr/local/lib/libopencv_xobjdetect.so.3.4.3
demo: /usr/local/lib/libopencv_dpm.so.3.4.3
demo: /usr/local/lib/libopencv_hdf.so.3.4.3
demo: /usr/local/lib/libopencv_xphoto.so.3.4.3
demo: /usr/local/lib/libopencv_bgsegm.so.3.4.3
demo: /usr/local/lib/libopencv_shape.so.3.4.3
demo: /usr/local/lib/libopencv_text.so.3.4.3
demo: /usr/local/lib/libopencv_ml.so.3.4.3
demo: /usr/local/lib/libopencv_phase_unwrapping.so.3.4.3
demo: /usr/local/lib/libopencv_dnn.so.3.4.3
demo: /usr/local/lib/libopencv_photo.so.3.4.3
demo: /usr/local/lib/libopencv_ximgproc.so.3.4.3
demo: /usr/local/lib/libopencv_objdetect.so.3.4.3
demo: /usr/local/lib/libopencv_calib3d.so.3.4.3
demo: /usr/local/lib/libopencv_features2d.so.3.4.3
demo: /usr/local/lib/libopencv_flann.so.3.4.3
demo: /usr/local/lib/libopencv_highgui.so.3.4.3
demo: /usr/local/lib/libopencv_videoio.so.3.4.3
demo: /usr/local/lib/libopencv_imgcodecs.so.3.4.3
demo: /usr/local/lib/libopencv_video.so.3.4.3
demo: /usr/local/lib/libopencv_imgproc.so.3.4.3
demo: /usr/local/lib/libopencv_core.so.3.4.3
demo: CMakeFiles/demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mrzs/Proj/part_darknet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable demo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/demo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/demo.dir/build: demo

.PHONY : CMakeFiles/demo.dir/build

CMakeFiles/demo.dir/requires: CMakeFiles/demo.dir/test/main.c.o.requires

.PHONY : CMakeFiles/demo.dir/requires

CMakeFiles/demo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/demo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/demo.dir/clean

CMakeFiles/demo.dir/depend:
	cd /home/mrzs/Proj/part_darknet/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mrzs/Proj/part_darknet /home/mrzs/Proj/part_darknet /home/mrzs/Proj/part_darknet/build /home/mrzs/Proj/part_darknet/build /home/mrzs/Proj/part_darknet/build/CMakeFiles/demo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/demo.dir/depend
