#set terminal x11 window ARG1

set ylabel "Cluster size"
set xlabel "Run time [sec]"
set grid

plot "logfile" using 2 title "Eje X" with lines , "logfile" using 3 title "Eje Y" with lines, "logfile" using 4 title "Eje Z" with lines
#save "grap.gp"
#plot ARG1, ARG2, ARG3
pause 1

#splot [] [] [-1:1] ARG1

