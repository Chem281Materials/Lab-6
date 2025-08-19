# distutils: language = c++

from libcpp.string cimport string
from libcpp.vector cimport vector
from clash cimport readPDBAtoms, Atom, getGeometricCenter, Point3D


def read_pdb_atoms(str filename):
    cdef vector[Atom] cpp_atoms = readPDBAtoms(filename.encode("utf-8"))
    result = []

    for i in range(cpp_atoms.size()):
        result.append((cpp_atoms[i].element, cpp_atoms[i].x, cpp_atoms[i].y, cpp_atoms[i].z))

    return result

def get_geometric_center(atoms):
    # COMPLETE THIS FUNCTION!
    return