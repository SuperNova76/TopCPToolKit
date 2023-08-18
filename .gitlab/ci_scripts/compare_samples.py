from ROOT import TFile, TTree, gROOT
gROOT.SetBatch(True)
import sys

orange_code = "\033[38;5;202m"
blue_code   = "\033[38;5;39m"
red_code    = "\033[38;5;196m"
reset_code  = "\033[0m"

def getTrees(inputfile):
    # Return the list of trees within the input file
    trees = []
    # Get the list of keys in the file
    keys = inputfile.GetListOfKeys()
    # Loop over the keys and extract TTree objects
    for key in keys:
        obj = key.ReadObj()
        if isinstance(obj, TTree):
            trees.append(key.GetName())

    return trees

def compareLists(ref_list, new_list):
    # Compare the two lists of strings, and return the common subset
    # as well as any discrepancies
    _ref = set(ref_list)
    _new = set(new_list)
    missing_in_ref = list(_new - _ref)
    missing_in_new = list(_ref - _new)
    common = list(_new.intersection(_ref))
    
    return common, missing_in_ref, missing_in_new

def compareTrees(ref_file, new_file):
    # Compare the lists of trees from the two files, and return the common subset
    ref_trees = getTrees(ref_file)
    new_trees = getTrees(new_file)
    common, miss_ref, miss_new = compareLists(ref_trees, new_trees)
    if miss_ref or miss_new:
        print(f"{orange_code}Warning: the number of TTrees differs between the new file and the reference file.{reset_code}")
        if miss_ref:
            print(f"{orange_code}  --> the following are missing from the reference file:{reset_code} {miss_ref}")
        if miss_new:
            print(f"{orange_code}  --> the following are missing from the new file:{reset_code} {miss_new}")
    if common:
        print(f"{blue_code}The following TTrees are common to both the reference and new files:{reset_code} {common}")
    failure = bool(miss_ref or miss_new)

    return common, failure

def compareBranches(key, ref_file, new_file):
    # Compare the list of branches from the two files, for a given TTree
    ref_tree = ref_file.Get(key)
    new_tree = new_file.Get(key)
    ref_branches = [branch.GetName() for branch in ref_tree.GetListOfBranches()]
    new_branches = [branch.GetName() for branch in new_tree.GetListOfBranches()]
    common, miss_ref, miss_new = compareLists(ref_branches, new_branches)
    if miss_ref or miss_new:
        print(f"{orange_code}Warning: the number of TBranches differs between the new file and the reference file.{reset_code}")
        if miss_ref:
            print(f"{orange_code}  --> the following are missing from the reference file:{reset_code} {miss_ref}")
        if miss_new:
            print(f"{orange_code}  --> the following are missing from the new file:{reset_code} {miss_new}")
    if common:
        print(f"{blue_code}There are {len(common)} TBranches common to both the reference and new files for TTree {key}.{reset_code}")
    failure = bool(miss_ref or miss_new)

    return common, failure

def compareEvents(key, branches, ref_file, new_file):
    # Compare the events between the two files for the selected tree and branches
    ref_tree = ref_file.Get(key)
    new_tree = new_file.Get(key)
    failure = False
    ref_events = ref_tree.GetEntries()
    new_events = new_tree.GetEntries()
    if ref_events != new_events:
        print(f"{orange_code}Warning: the number of events differs between the new file and the reference file for TTree {key}.{reset_code}")
        print(f"{orange_code}  --> reference:{reset_code} {ref_events}")
        print(f"{orange_code}  --> new file:{reset_code}  {new_events}")
        failure = True
    ref_tree.BuildIndex("eventNumber")
    new_tree.BuildIndex("eventNumber")
    ref_tree.AddFriend(new_tree)
    for event_idx in range(ref_events):
        ref_tree.GetEntry(event_idx)
        for branch in branches:
            ref_value = getattr(ref_tree, branch)
            new_value = getattr(new_tree, branch)
            if ref_value != new_value:
                print(f"{orange_code}Warning: Branch {branch} differs for event {getattr(ref_tree,'eventNumber')}:{reset_code}")
                print(f"{orange_code}  --> reference:{reset_code} {ref_value}")
                print(f"{orange_code}  --> new file: {reset_code} {new_value}")
                failure = True
    
    return failure

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print(f"{red_code}The script compare_samples.py requires 2 arguments!{reset_code}")
        print("Please run it as : python compare_samples.py <reference.root> <new.root>")
        exit(1)
    
    ref_f = TFile.Open(sys.argv[1],"READ")
    new_f = TFile.Open(sys.argv[2],"READ")

    common_trees, failure_trees = compareTrees(ref_f, new_f)

    global_failure = failure_trees

    for tree in common_trees:
        common_branches, failure_branches = compareBranches(tree, ref_f, new_f)
        failure_events = compareEvents(tree, common_branches, ref_f, new_f)
        global_failure |= failure_branches or failure_events
    
    ref_f.Close()
    new_f.Close()
    
    if global_failure:
        print(f"{red_code}At least one of the tests failed! Please check the logs carefully.{reset_code}")
        exit(1)
    else:
        print(f"{blue_code}All tests successful!{reset_code}")
        exit(0)
