set terminal png
set output 'plot.png'
plot 'output.dat' using 2:3 with lines title 'Percentage'
