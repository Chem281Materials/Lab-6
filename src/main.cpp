#include "clashes.h"

#include <algorithm>
#include <iostream>

int main() {
    // Load the molecules
    std::vector<OpenBabel::OBMol> mols = readSDF("../datafiles/estradiol_poses.sdf");
    std::cout << mols.size() << std::endl;
    auto mol = mols[0];
    std::cout << mol.NumAtoms() << std::endl;

    // Load receptor active site
    std::vector<Atom> active_site = readPDBAtoms("../datafiles/1a52_active_site.pdb");
    std::cout << active_site.size() << std::endl;

    // Calculate the geometric center and translate molcules
    Point3D site_center = getGeometricCenter(active_site);
    std::cout << "Site coords: " << site_center.x << " " << site_center.y << " " << site_center.z << std::endl;
    for (auto& mol: mols) {
        translateMoleculeToCenter(mol, site_center);
    }
    // Write out SDF.
    writeMoleculesToSDF(mols, "translated_mols.sdf");

    // Check clashes
    int clashes = std::count_if(mols.begin(), mols.end(), [&active_site](OpenBabel::OBMol& mol) {
        return hasClash(mol, active_site, 1.0);
    });
    if (clashes != 18) {
        std::cout << "Code is not correct you have: " << clashes << " clashes, should be 18." << std::endl;
    } else {
        std::cout << "SUCCESS!!!" << std::endl;
    }
}
