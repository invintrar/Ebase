#set terminal x11 title name
#set terminal x11 window ARG1

#set terminal wxt 1

logname = "tmp"
tmpname = "tmp1"
tmplen = 1

unset key; unset border; unset tics;

value = 0

cont = 1

print(hola)

bind "x" "end=1" 
end = 0; t=0

while (cont < 100){
	t = t + 0.1
	splot [] [] [-1:1] exp(-0.2*sqrt(x**2+y**2))*cos(sqrt(x**2+y**2) - t)
	cont = cont + 1
	pause 0.001
}