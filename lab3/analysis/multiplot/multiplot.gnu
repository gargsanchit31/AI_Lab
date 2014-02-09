      set output 'output.png'
      set terminal png size 700,600 enhanced font "Helvetica,15"
# This file is called   s1.gnu
    set multiplot
   # plot sin(x)
   # plot cos(x)
      set   autoscale                        # scale axes automatically
#      unset log                              # remove any log-scaling
#      unset label                            # remove any previous labels
      set xtic auto                          # set xtics automatically
      set ytic auto                          # set ytics automatically
      set title "Error vs #Iter"
      set xlabel "Error"
      set ylabel "#Iterations"
#      set key 0.01,100
#      set label "Yield Point" at 0.003,260
#      set arrow from 0.0028,250 to 0.003,280
#      set xr [0:7]
#      set yr [0.0:8.0]
# to output to png file named output.png
    
    set style line 1 lt 1 lw 1 pt 3 lc rgb "red"
    set style line 2 lt 3 lw 1 pt 3 lc rgb "blue"
    set style line 3 lt 1 lw 3 pt 3 lc rgb "blue"
    set style line 4 lt 3 lw 3 pt 3 lc rgb "blue"
      plot  "m1.txt"  using 1:2 title 'Column' with lines ls 1  #plotting log scale on x axis :P
      plot  "m2.txt"  using 1:2 title 'Column' with lines ls 2  #plotting log scale on x axis :P
    unset multiplot

#      plot    "in1.txt" using 1:2 title 'Column' with lines #OR linespoints
