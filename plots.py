import pandas as pd
import matplotlib.pyplot as plt

df_histo = pd.read_table("intensity_histogram.dat", sep="\s+")
df_noise_removed_signal = pd.read_table("noise_removed_signal.dat", sep="\s+")
#df_original_signal = pd.read_table("original_signal.dat", sep="\s+")
#df_fourier_signal = pd.read_table("filtered_fourier_file.dat", sep="\s+")

fig1 = plt.figure()
plt.plot(df_noise_removed_signal["index"], df_noise_removed_signal["signal_value"])
plt.savefig("noise_removed_signal.png")
