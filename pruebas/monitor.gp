#set terminal x11 window ARG1

set ylabel "Cluster size"
set xlabel "Run time [sec]"

logname = "logfile"
tmplen = 40
tmplen1 = 1
tmpname = "tmp"
tmpname1 = "tmp1"
bind "x" "end=1"
end = 0
while( end==0 ) {
    #system sprintf( "tail -%d %s > %s", tmplen, logname, tmpname )
    #stats [*:*][*:*] "tmp" u 1:2 nooutput
    #set xrange [STATS_max_x-11.0:STATS_max_x+1]
    #plot "tmp" u 1:2 title "Eje X" w l, "" u 1:3 title "Eje Y" w l, "" u 1:4 title "EjeZ" w l, "" u 1:5 title "Currente" w l
    #splot [] [] [] "tmp" u 1:2:3 w l
    #system sprintf( "tail -%d %s > %s", tmplen1, logname, tmpname1 )
    stats "logfile" u 1:5 nooutput
    print STATS_max_x
    print STATS_max_y
    pause 2
    end = 1
}