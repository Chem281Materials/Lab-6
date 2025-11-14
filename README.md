# 💻 CHEM 281 - Python Bindings for C++ Code

## 🧪 Goal

The goal of this lab is to:

1. Familiarize yourself with **wrapping C++ code with Pybind11 and Cython**.
2. Learn how to **write bindings in Pybind11 and Cython**. 
3. Practice using **cheminformatics code**.
4. Complete the missing functions and **wrap them to call in python**.

---

## 🗂️ Provided

- A `docker` file to set up the dev environment.
- Cheminformatics code in `include/` and `src/`.
- Python scripts `test_bindings.py` and `test_cython.py` to test if your wrapped code runs correctly.

---
## 💻 Setup
```bash
./docker_build.sh # You may need to chmod +x
./docker_run.sh # You may need to chmod +x
```
To make and run the C++ executable and pybind11 wrapped code:
```
# Build
mkdir build
cd build
cmake -Dpybind11_DIR=/usr/local/lib/python3.9/site-packages/pybind11/share/cmake/pybind11 ..
make

# Run executable
./clashes_exe

# Run pybind11 bindings test
cd ..
python3 test_bindings.py
```

To make and run the Cython wrapped code:
```
# Make sure you are in the main directory
python setup.py build_ext --inplace
python3 test_cython.py
```

## ✅ Tasks
### Determine if poses have clashes
In the repo you should see the main file `src/clashes.cpp`. We are trying to write some code which will determine if a ligand pose has any clashes inside of an active site. Since we have no gaurentee that the poses are within the active site, we need to place the pose within it. To do this we will get the geometric center of the active site atoms, and then translate the molecules to it. Once we have the molecule inside the active site we can check if we have any clashes! A clash occurs when the pose atom is within some cutoff distance to an active site atom. 

You need to complete the following functions:

1. getGeometricCenter

$$ {C} = ( \frac{1}{N} \sum_{i=1}^{N} x_i,\ \frac{1}{N} \sum_{i=1}^{N} y_i,\ \frac{1}{N} \sum_{i=1}^{N} z_i ) $$

2. translateMoleculeToCenter

$$ \vec{T} = \vec{C} - \vec{P} = (x_c - x,\ y_c - y,\ z_c - z) $$

3. hasClash

$$ cutoff > d = \sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2 + (z_2 - z_1)^2} $$

The active site is defined as `std::vector<Atom>`, and the `Atom` class is also defined in `include/clashes.h`. We are using OpenBabel to hold the molecules and their data, most of the work involving this class has been done for you so you can reuse how to iterate over atoms and such but here is some [documentation](https://openbabel.org/api/3.0/classOpenBabel_1_1OBMol.shtml).

Once you have completed all the functions above, you can compile the code using the commands above and try to run `./clash_exe` if you see SUCCESS!!! then you have completed the coding section.

### Wrap the code using Pybind11
To work on creating the python bindings for Pybind11, look at `python/bindings.cpp`. A few classes and functions have been completed for you. Use [pybind11](https://pybind11.readthedocs.io/en/stable/index.html) to complete the rest of the functions and classes so that `test_bindings.py` can run completely.

When you are ready to build, uncomment the following lines from `CMakeLists.txt`.

```
# Add the Python bindings
pybind11_add_module(clashes python/bindings.cpp)
target_link_libraries(clashes PRIVATE clashes_cpp)
```

Then follow the build directions above to build. Once built, you can run `python3 test_bindings.py` and if you have done everything correctly, you should see the following output:

```
50
153
107.28315686274507
15.332535947712431
96.92914379084966
Number of clashes: 18
```

You should also see a `translated_mols.sdf` file which you can visualize using PyMOL to confirm that all the molecules are now in the active site.

### Wrap the code using Cython
To work on creating the python bindings for Cython, look at `src/cython`. You should see `clash.pxd` and `clash.pyx`. The `clash.pxd` file has been completed for you and contains the delcarations of the functions we want to expose via Cython. Use [cython](https://cython.readthedocs.io/en/latest/src/userguide/wrapping_CPlusPlus.html) to complete the wrapper function get_geometric_center in `clash.pyx`. 

Cython cannot cast types as easily as Pybind11 so you will need to more work to transfer C++ objects to python objects. To expose get_geometric_center you will need to convert the input atoms to a vector[Atom] and then call the C++ function getGeometricCenter. The returning value of this function will also need to be converted to python because Cython won't know how to convert Point3D to a python object!

See how read_pdb_atoms was done for some pointers.

Also take a look at setup.py in the main directory to get an idea of how cython is setup.

To build:
```
# Make sure you are in the main directory
python setup.py build_ext --inplace
python3 test_cython.py
```

### Create a new function in Cython without wrapping ###
Now create a new function `get_geometric_center_cython` and in this case do not call the C++ function getGeometricCenter. Instead, write the logic for getting the centering in the `clash.pyx` file using the correct cdef typing. Once completed you can build again using the process above and test the function by updating the function call in `test_cython.py` or by creating a new one.

### Extra time
The poses you were working on in this lab were created using `utility/make_random_poses`. Can you modify the code to create random poses in place? This way we wouldn't need the translateMoleculeToCenter or getGeometricCenter functions.
