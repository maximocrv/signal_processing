#set title 'Autocorrelation Plot Metropolis Algorithm"
#set xlabel "Lags (number of samples skipped)"
#set ylabel "Autocorrelation"
#set output 'noise_removed_signal.png'
#plot 'noise_removed_signal.dat' u 1:2 w lines

#filename = "noise_removed_signal.dat"
#plotfile = "noise_removed_signal.jpg"
#print filename." ".plotfile

#set output plotfile
#plot filename u 1:2 w lines
#set output
set terminal png size 500, 500
set output 'xyz.png'
plot "noise_removed_signal.dat" u 1:2 w lines

#gnuplot -e "set terminal png size 400,300; set output 'xyz.png'; plot [-4:4] exp(-x**2 / 2)"
