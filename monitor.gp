set terminal x11 window ARG1

set title "Acelerometro ADXL355Z"
set ylabel "LSB/g"
set xlabel "Time"
set grid

logname = "logfile"
tmplen = 10
tmpname = "tmp"

bind "x" "end=1"

end = 0
while( end == 0 ) {
    system sprintf( "tail -%d %s > %s", tmplen, logname, tmpname)
    stats [*:*][*:*] "tmp" u 1:5 nooutput
    set xrange [STATS_max_x - 10:STATS_max_x]
    plot "tmp" u 1:2 smooth mcsplines title "Eje X", "tmp" u 1:3 smooth mcsplines title "Eje Y", "tmp" u 1:4 smooth mcsplines title "Eje Z"
    end = STATS_max_y
    pause .02
}
system sprintf( "rm  %s %s", logname, tmpname)
