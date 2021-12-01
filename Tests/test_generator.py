# Python code which was used to generate big test files.
import random

# Generating test sizes.
sizes = [0, 10, 10050]
for _ in range(3):
    sizes.append(random.randint(10, 10000))
# Generating filenames.
filenames = ["In/in_{}.txt".format(s) for s in sizes]

test_params = [(filenames[i], sizes[i]) for i in range(len(sizes))]


# Generating test strings.
def generate_tests(filename, size):
    tests = []
    for _ in range(size):
        # Generating integer key.
        key = random.randint(1, 3);
        # Possible since all numbers have 2 parameters.
        if key == 2 and random.randint(1, int(size ** 0.3)) != 6:
            param_1 = random.randint(-100, 100)
            param_2 = random.randint(-100, 100)
        else:
            param_1 = random.randint(-1000, 1000) / 10
            param_2 = random.randint(-1000, 1000) / 10
        # Creating a string with results.
        line = "{} {} {}".format(key, param_1, param_2);
        tests.append(line)

    # Writing test strings to a file.
    with open(filename, 'w') as file:
        file.write('\n'.join(tests))


# Writing all generated tests to files.
for (f, s) in test_params:
    generate_tests(f, s)
