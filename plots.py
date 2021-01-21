import pandas as pd
from pathlib import Path
import matplotlib.pyplot as plt

df_histo = pd.read_table(Path("output_data") / "intensity_histogram.dat", sep="\s+")
df_noise_removed_signal = pd.read_table(Path("output_data/noise_removed_signal.dat"), sep="\s+")
df_original_signal = pd.read_table(Path("output_data/original_signal.dat"), sep="\s+")
#df_fourier_signal = pd.read_table("filtered_fourier_file.dat", sep="\s+")

Path('plots').mkdir(parents=True, exist_ok=True)

fig1 = plt.figure()
plt.plot(df_noise_removed_signal["index"], df_noise_removed_signal["signal_value"])
plt.savefig(Path("plots/noise_removed_signal.png"))

fig2 = plt.figure()
plt.plot(df_original_signal["index"], df_original_signal["signal_value"])
plt.title("")
plt.savefig(Path("plots/original_signal.png"))
