"""
Distance Matrix Computation using Dynamic Programming
Written in October 2018 by Erin Molloy
Updated in December 2021
Warning: Not thoroughly checked...
"""
import argparse
import numpy
import sys
import treeswift


def tree2matrix(tree, taxa):
    # Resolve polytomies with zero length edges
    tree.resolve_polytomies()

    # Map taxon names to matrix row index
    nmap = {}
    for i, x in enumerate(taxa):
        nmap[x] = i

    # Initiate matrix D and vector v
    n = len(taxa)
    D = numpy.zeros((n, n))
    v = numpy.zeros(n)

    # Perform a post-order traversal
    for node in tree.traverse_postorder():
        if not node.is_leaf():
            children = node.child_nodes()
            left = children[0]
            right = children[1]

            # Update v for left child
            if left.is_leaf():
                l = nmap[left.label]
                v[l] = v[l] + left.get_edge_length()  # + 0.5
                left.children_indices = [l]
            else:
                for l in left.children_indices:
                    v[l] = v[l] + left.get_edge_length()  # + 1.0

            # Update v for right child
            if right.is_leaf():
                r = nmap[right.label]
                v[r] = v[r] + right.get_edge_length()  # + 0.5
                right.children_indices = [r]
            else:
                for r in right.children_indices:
                    v[r] = v[r] + right.get_edge_length()  # + 1.0

            # Update D
            for l in left.children_indices:
                for r in right.children_indices:
                    D[l, r] = v[l] + v[r]
                    D[r, l] = D[l, r]

            # Record children indices below current node
            node.children_indices = left.children_indices + right.children_indices

            # Delete indicies for children nodes
            del left.children_indices
            del right.children_indices
    return D


def write_phylip(dmat, taxa, f):
    ntax = len(taxa)
    f.write("%d\n" % ntax)
    for i, x in enumerate(taxa):
        f.write("%s" % x)
        for j in range(ntax):
            f.write(" %1.4f" % dmat[i, j])
        f.write("\n")


def main(args):
    with open(args.input, 'r') as f:
        newick = f.readline()

    tree = treeswift.read_tree(newick, "newick")
    taxa = [leaf.label for leaf in tree.traverse_leaves()]
    dmat = tree2matrix(tree, taxa)

    with open(args.output, 'w') as f:
        write_phylip(dmat, taxa, f)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()

    parser.add_argument("-i", "--input", type=str,
                        help="Input file containing newick string",
                        required=True)
    parser.add_argument("-o", "--output", type=str,
                        help="Output file containing matrix (phylip format)",
                        required=True)

    main(parser.parse_args())
