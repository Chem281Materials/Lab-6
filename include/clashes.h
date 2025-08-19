#pragma once

#include <string>
#include <vector>
#include <openbabel3/openbabel/mol.h>

const double CLASH_THRESHOLD = 2.0; // Angstroms

struct Atom {
    std::string element;
    double x, y, z;

    Atom() : element(""), x(0.0), y(0.0), z(0.0) {}

    Atom(const std::string& element, double x, double y, double z)
        : element(element), x(x), y(y), z(z) {}
};

class Molecule {
    public:
        std::vector<Atom> atoms;
};

struct Point3D {
    double x, y, z;
};

std::vector<Atom> readPDBAtoms(const std::string& pdbFile);

std::vector<OpenBabel::OBMol> readSDF(const std::string& filename);

void writeMoleculesToSDF(std::vector<OpenBabel::OBMol>& molecules, const std::string& filename);

bool hasClash(OpenBabel::OBMol& mol, const std::vector<Atom>& activeSiteAtoms, double clashThreshold = 2.0);

Point3D getGeometricCenter(const std::vector<Atom>& atoms);

void translateMoleculeToCenter(OpenBabel::OBMol& mol, const Point3D& newCenter);
