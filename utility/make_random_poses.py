import numpy as np
from rdkit import Chem
from rdkit.Chem import SDWriter


def random_rotation_matrix():
    theta = np.random.uniform(0, 2*np.pi)
    phi = np.random.uniform(0, 2*np.pi)
    z = np.random.uniform(0, 2*np.pi)

    Rx = np.array([[1, 0, 0],
                   [0, np.cos(theta), -np.sin(theta)],
                   [0, np.sin(theta), np.cos(theta)]])

    Ry = np.array([[np.cos(phi), 0, np.sin(phi)],
                   [0, 1, 0],
                   [-np.sin(phi), 0, np.cos(phi)]])

    Rz = np.array([[np.cos(z), -np.sin(z), 0],
                   [np.sin(z), np.cos(z), 0],
                   [0, 0, 1]])

    return Rz @ Ry @ Rx


def apply_transformation(mol, rotation_matrix, translation_vec):
    mol = Chem.Mol(mol)  # Copy
    conf = mol.GetConformer()

    for i in range(conf.GetNumAtoms()):
        pos = np.array(conf.GetAtomPosition(i))
        new_pos = rotation_matrix @ pos + translation_vec
        conf.SetAtomPosition(i, new_pos)

    return mol


num_poses = 50
writer = SDWriter("poses.sdf")
mol = Chem.SDMolSupplier("datafiles/estradiol.sdf", removeHs=False)[0]
for i in range(num_poses):
    rot = random_rotation_matrix()
    trans = np.random.normal(scale=2.0, size=3)  # Small random translation
    new_mol = apply_transformation(mol, rot, trans)
    new_mol.SetProp("_Name", f"Pose_{i+1}")
    writer.write(new_mol)

writer.close()
