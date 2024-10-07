
import numpy as np
import matplotlib 
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

print("uessir")

df = pd.read_csv("simulation_runs/tundra.csv")

df_alive = df[df['alive'] == 1]
df_alive['melanin'].hist(bins=50)

plt.show()
# df_met = df.iloc[:, 10:]
# print(df.head())
# corr = df_met.corr()

# Create the heatmap
# sns.heatmap(corr, annot=True, cmap='coolwarm_r', vmin = -1, vmax = 1)
# df2 = df.sort_values("height", ascending=False)
# plt.show()
# df3 = (df2["age"] > 17)
# print(df2[["first_name","age", "intel","alive", "height", "speed", "willpower"]].head(10))
# df_counts = df["family_name"].value_counts()
# plot = df_counts.plot.pie()
# plt.show()