set terminal x11 window ARG1

set ylabel "Cluster size"
set xlabel "Run time [sec]"
set grid

logname = "logfile"
tmplen = 50
it = 0.0
tmpname = "tmp"
bind "x" "end=1"
end = 0
while( end==0 ) {
    system sprintf( "tail -%d %s > %s", tmplen, logname, tmpname )
    stats [*:*][*:*] "tmp" u 1:2 nooutput
    set xrange [STATS_max_x - 50:STATS_max_x+5]
    set yrange [-40000:40000]
    plot "tmp" u 1:2 title "Eje X" w l, "tmp" u 1:3 title "Eje Y" w l, "tmp" u 1:4 title "Eje Z" w l
    #splot [] [] [] "tmp" u 1:2:3 w l
    pause .02
}