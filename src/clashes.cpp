#include "clashes.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

#include <openbabel3/openbabel/obconversion.h>
#include <openbabel3/openbabel/atom.h>


std::vector<Atom> readPDBAtoms(const std::string& pdbFile) {
    std::vector<Atom> atoms;
    std::ifstream infile(pdbFile);
    std::string line;
    while (std::getline(infile, line)) {
        if (line.substr(0, 4) == "ATOM" || line.substr(0, 6) == "HETATM") {
            atoms.emplace_back(line.substr(76, 2), 
                               std::stod(line.substr(30, 8)),
                               std::stod(line.substr(38, 8)),
                               std::stod(line.substr(46, 8)));
        }
    }
    return atoms;
}

std::vector<OpenBabel::OBMol> readSDF(const std::string& filename) {
    std::vector<OpenBabel::OBMol> molecules;

    OpenBabel::OBConversion conv;
    conv.SetInFormat("sdf");

    std::ifstream infile(filename);
    if (!infile) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    OpenBabel::OBMol mol;
    while (conv.Read(&mol, &infile)) {
        molecules.push_back(mol);  // copy the molecule
        mol.Clear();               // reset for next read
    }

    return molecules;
}

void writeMoleculesToSDF(std::vector<OpenBabel::OBMol>& molecules, const std::string& filename) {
    OpenBabel::OBConversion conv;
    conv.SetOutFormat("sdf");

    std::ofstream ofs(filename);
    if (!ofs.is_open()) {
        std::cerr << "Error: could not open file " << filename << " for writing." << std::endl;
        return;
    }

    conv.SetOutStream(&ofs);

    for (auto& mol : molecules) {
        if (!conv.Write(&mol)) {
            std::cerr << "Warning: failed to write a molecule to " << filename << std::endl;
        }
    }

    conv.CloseOutFile();  // ensure flushing of the last molecule
}

bool hasClash(OpenBabel::OBMol& mol, const std::vector<Atom>& activeSiteAtoms, double clashThreshold) {
    // Complete this function!!!
}

Point3D getGeometricCenter(const std::vector<Atom>& atoms) {
    // Complete this function!!!
}

void translateMoleculeToCenter(OpenBabel::OBMol& mol, const Point3D& newCenter) {
    std::vector<Atom> molecule_atoms;
    for (OpenBabel::OBAtomIterator atom_it = mol.BeginAtoms(); atom_it != mol.EndAtoms(); ++atom_it) {
        OpenBabel::OBAtom* atom = *atom_it;
        molecule_atoms.emplace_back(std::string(atom->GetType()), atom->GetX(), atom->GetY(), atom->GetZ());
    }
    // Step 1: Calculate current geometric center
    Point3D currentCenter = getGeometricCenter(molecule_atoms);

    // Step 2: Calculate translation vector
    /// COMPLETE THIS FUNCTION!!!

    // Step 3: Translate each atom
    for (OpenBabel::OBAtomIterator atom_it = mol.BeginAtoms(); atom_it != mol.EndAtoms(); ++atom_it) {
        OpenBabel::OBAtom* atom = *atom_it;
        atom->SetVector(atom->GetX() + dx, atom->GetY() + dy, atom->GetZ() + dz);
    }
}
