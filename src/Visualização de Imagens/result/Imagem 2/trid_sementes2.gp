set terminal wxt persist
set pm3d
set hidden3d
splot 'image.txt' matrix with pm3d
