import glob, re
import matplotlib.pyplot as plt

data = {}

for f in glob.glob("data/matmul-*.txt"):
    text = open(f).read()
    print(text)
    m = re.search(r"D1\s+miss\s+rate:\s+([\d.]+)%", text)
    print(m)
    if m:
        data[f.split("/")[-1][7:-4]] = float(m.group(1))

plt.bar(data.keys(), data.values())
plt.xticks(fontsize=24)
plt.yticks(fontsize=24)
plt.ylabel("D1 Cache Miss Rate (%)", fontsize=24)
plt.title("Matrix Multiplication Cache Miss Rate",fontsize=24)
plt.tight_layout()
plt.savefig("data/miss-rate.png")
plt.show()
