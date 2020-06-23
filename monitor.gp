set terminal x11 window ARG1

set ylabel "Cluster size"
set xlabel "Run time [sec]"
set grid

logname = "logfile"
tmplen = 10
tmpname = "tmp"

bind "x" "end=1"
end = 0
while( end==0 ) {
    system sprintf( "tail -%d %s > %s", tmplen, logname, tmpname )
    stats [*:*][*:*] "tmp" u 1:5 nooutput
    set xrange [STATS_max_x - 10:STATS_max_x]
    set yrange [-40000:40000]
    plot "tmp" u 1:2 smooth mcsplines title "Eje X", "tmp" u 1:3 smooth mcsplines title "Eje Y", "tmp" u 1:4 smooth mcsplines title "Eje Z"
    end = STATS_max_y
    pause .02
}