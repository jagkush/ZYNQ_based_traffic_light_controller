#clock
#set_property IOSTANDARD LVCMOS33 [get_ports clk];
#set_property PACKAGE_PIN K17 [get_ports clk];
#create_clock -period 20.000 -name clk -waveform {0.000 10.000} [get_ports clk];

#rst
#set_property IOSTANDARD LVCMOS33 [get_ports rst];
#set_property PACKAGE_PIN E17 [get_ports rst];

#segment
set_property IOSTANDARD LVCMOS33 [get_ports {gpio_rtl_seg_tri_io[6]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio_rtl_seg_tri_io[5]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio_rtl_seg_tri_io[4]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio_rtl_seg_tri_io[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio_rtl_seg_tri_io[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio_rtl_seg_tri_io[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio_rtl_seg_tri_io[0]}]
set_property PACKAGE_PIN Y19 [get_ports {gpio_rtl_seg_tri_io[6]}]
set_property PACKAGE_PIN W20 [get_ports {gpio_rtl_seg_tri_io[5]}]
set_property PACKAGE_PIN Y17 [get_ports {gpio_rtl_seg_tri_io[4]}]
set_property PACKAGE_PIN Y14 [get_ports {gpio_rtl_seg_tri_io[3]}]
set_property PACKAGE_PIN U19 [get_ports {gpio_rtl_seg_tri_io[2]}]
set_property PACKAGE_PIN U15 [get_ports {gpio_rtl_seg_tri_io[1]}]
set_property PACKAGE_PIN W15 [get_ports {gpio_rtl_seg_tri_io[0]}]

#sel
set_property IOSTANDARD LVCMOS33 [get_ports {gpio_rtl_seg_tri_io[9]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio_rtl_seg_tri_io[8]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio_rtl_seg_tri_io[7]}]
set_property PACKAGE_PIN T16 [get_ports {gpio_rtl_seg_tri_io[9]}]
set_property PACKAGE_PIN Y18 [get_ports {gpio_rtl_seg_tri_io[8]}]
set_property PACKAGE_PIN V20 [get_ports {gpio_rtl_seg_tri_io[7]}]



#led
set_property IOSTANDARD LVCMOS33 [get_ports {gpio_rtl_led_tri_io[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio_rtl_led_tri_io[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio_rtl_led_tri_io[0]}]
set_property PACKAGE_PIN N16 [get_ports {gpio_rtl_led_tri_io[2]}]
set_property PACKAGE_PIN P18 [get_ports {gpio_rtl_led_tri_io[1]}]
set_property PACKAGE_PIN R18 [get_ports {gpio_rtl_led_tri_io[0]}]