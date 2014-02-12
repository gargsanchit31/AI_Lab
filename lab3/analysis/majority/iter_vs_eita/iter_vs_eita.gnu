# This file is called   s1.gnu
      set   autoscale                        # scale axes automatically
#      unset log                              # remove any log-scaling
#      unset label                            # remove any previous labels
      set xtic auto                          # set xtics automatically
      set ytic auto                          # set ytics automatically
      set title "#Iterations vs Eita"
      set xlabel "Eita"
      set ylabel "#Iterations"
#      set key 0.01,100
#      set label "Yield Point" at 0.003,260
#      set arrow from 0.0028,250 to 0.003,280
#      set xr [0:7]
#      set yr [0.0:8.0]
# to output to png file named output.png
      set terminal png size 700,600 enhanced font "Helvetica,15"
      set output 'output.png'

#      plot    "i.txt" using 1:2 title 'Column' with lines #OR linespoints
      plot  "i.txt"  using 1:2 title 'Column' with lines #plotting log scale on x axis :P
