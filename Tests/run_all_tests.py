import os, random

# Change this in case executable file changes.
executable_path = "../Source/bin/CSA_Homework_4"

# Clearing current tests in folder.
for filename in os.listdir("Out"):
    os.remove(os.path.join("Out", filename))

# Run tests from folder.
for filename in os.listdir("In"):
    out_name = "Out/out_"  + filename[3:]
    out_sorted_name = "Out/out_SORTED_" + filename[3:]
    print("EXECUTING TEST WITH FILE {}...".format(filename))
    os.system("{} -f {} {} {}".format(executable_path, "In/" + filename, out_name, out_sorted_name))

# Run a few random tests.
# values = [0, 10050, -10, 100]
# values.append(random.randint(1, 10000))
# for val in values:
#     out_name = "Out/out_RANDOM_{}.txt".format(val)
#     out_sorted_name = "Out/out_RANDOM_{}.txt".format(val)
#     print("EXECUTING RANDOM TEST...".format(filename))
#     os.system("{} -r {} {} {}".format(executable_path, val, out_name, out_sorted_name))