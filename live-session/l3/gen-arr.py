import random
N = 1000 * 1000
with open("array.c", "w") as f:
    f.write("int array[1000000] = {\n")
    for i in range(N):
        f.write(str(random.randint(-100, 100)))
        f.write("," if i < N - 1 else "")

    f.write("\n};\n")
