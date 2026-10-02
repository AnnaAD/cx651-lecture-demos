import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("timings.csv")
for p, g in df.groupby("program"):
    g = g.sort_values("threads")
    plt.plot(g.threads, g.seconds.iloc[0] / g.seconds, "o-", label=p)
n = df.threads.max()
plt.plot([1, n], [1, n], "k--", label="ideal")
plt.xlabel("Cores")
plt.ylabel("Speedup")
plt.legend()
plt.savefig("speedup.png")
