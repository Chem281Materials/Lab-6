import clash

active_site = clash.read_pdb_atoms("datafiles/1a52_active_site.pdb")

print(len(active_site))

center = clash.get_geometric_center(active_site)

print(center)
