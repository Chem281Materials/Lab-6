import sys
import os
# Add the build directory to the Python path
sys.path.append(os.path.join(os.path.dirname(__file__), 'build'))


import clashes


def main():
    mols = clashes.readSDF("datafiles/estradiol_poses.sdf")
    print(len(mols))

    active_site = clashes.readPDBAtoms("datafiles/1a52_active_site.pdb")
    print(len(active_site))

    site_center = clashes.getGeometricCenter(active_site)
    print(site_center.x)
    print(site_center.y)
    print(site_center.z)

    for mol in mols:
        clashes.translateMoleculeToCenter(mol, site_center)

    clashes.writeMoleculesToSDF(mols, "translated_mols.sdf")

    clash_count = sum(1 for mol in mols if clashes.hasClash(mol, active_site, 1.0))
    print(f"Number of clashes: {clash_count}")


if __name__ == "__main__":
    main()
