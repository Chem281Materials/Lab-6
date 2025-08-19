// bindings.cpp
#include <openbabel3/openbabel/mol.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "clashes.h"

namespace py = pybind11;

PYBIND11_MODULE(clashes, m) {
    py::class_<Atom>(m, "Atom")
        .def(py::init<std::string, double, double, double>())
        .def_readwrite("element", &Atom::element)
        .def_readwrite("x", &Atom::x)
        .def_readwrite("y", &Atom::y)
        .def_readwrite("z", &Atom::z);

    // Create Point3D class

    py::class_<OpenBabel::OBMol>(m, "OBMol");

    m.def("readPDBAtoms", &readPDBAtoms, "Read atoms from a PDB file");
    // Create the rest of the functions!
}
