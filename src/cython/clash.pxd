# distutils: language = c++

from libcpp.vector cimport vector
from libcpp.string cimport string
from libcpp cimport bool


cdef extern from "clashes.h" namespace "":
    cdef cppclass Atom:
        string element
        double x, y, z

    cdef cppclass Point3D:
        double x, y, z

    vector[Atom] readPDBAtoms(string filename)
    Point3D getGeometricCenter(const vector[Atom]& atoms)

