# ZYNQ_based_traffic_light_controller
###### A final project for FPGA_SOC course

The project shows a simple demonstration of the Traffic Light Controller using ~Zynq-7000 xc7z010clg400-1~ field programmable gate array (FPGA) board.
The hardware architecture was designed with ~Vivaldo 2019.1~ Software design kit, and 
~Xilinx SDK~ was used for software logic.


### Project Objective
The objective of this project is to design a traffic control system with appropriate delay which can be implemented to show the working principle of a traffic light controllers. The simple traffic light controller design is based on Xilinx ZYNQ (Embedded ARM processor) and it’s simply a switching implementation of 3 lights with a countdown clock. The state depicts the change of state of the traffic signal. The signal light values which are available as registers are triggered based on the state, whereas the state value is changed in accordance with a countdown clock with system clock frequency of 50MHz.
