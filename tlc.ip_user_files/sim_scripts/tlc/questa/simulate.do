onbreak {quit -f}
onerror {quit -f}

vsim -t 1ps -lib xil_defaultlib tlc_opt

do {wave.do}

view wave
view structure
view signals

do {tlc.udo}

run -all

quit -force
