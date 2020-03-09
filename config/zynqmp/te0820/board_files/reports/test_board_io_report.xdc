set_property PACKAGE_PIN K9 [get_ports {SI5338_CLK0_D_clk_p[0]}]
set_property PACKAGE_PIN J9 [get_ports {SI5338_CLK0_D_clk_n[0]}]
set_property PACKAGE_PIN H1 [get_ports {x0[0]}]
set_property PACKAGE_PIN J1 [get_ports {x1[0]}]
set_property DIRECTION OUT [get_ports {x0[0]}]
set_property IOSTANDARD LVCMOS18 [get_ports {x0[0]}]
set_property DRIVE 12 [get_ports {x0[0]}]
set_property SLEW SLOW [get_ports {x0[0]}]
set_property DIRECTION OUT [get_ports {x1[0]}]
set_property IOSTANDARD LVCMOS18 [get_ports {x1[0]}]
set_property DRIVE 12 [get_ports {x1[0]}]
set_property SLEW SLOW [get_ports {x1[0]}]
set_property DIRECTION IN [get_ports {SI5338_CLK0_D_clk_p[0]}]
set_property IOSTANDARD LVDS [get_ports {SI5338_CLK0_D_clk_p[0]}]
set_property DIFF_TERM TRUE [get_ports {SI5338_CLK0_D_clk_p[0]}]
set_property EQUALIZATION EQ_NONE [get_ports {SI5338_CLK0_D_clk_p[0]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {SI5338_CLK0_D_clk_p[0]}]
set_property LVDS_PRE_EMPHASIS FALSE [get_ports {SI5338_CLK0_D_clk_p[0]}]
set_property DIRECTION IN [get_ports {SI5338_CLK0_D_clk_n[0]}]
set_property IOSTANDARD LVDS [get_ports {SI5338_CLK0_D_clk_n[0]}]
set_property DIFF_TERM TRUE [get_ports {SI5338_CLK0_D_clk_n[0]}]
set_property EQUALIZATION EQ_NONE [get_ports {SI5338_CLK0_D_clk_n[0]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {SI5338_CLK0_D_clk_n[0]}]
set_property LVDS_PRE_EMPHASIS FALSE [get_ports {SI5338_CLK0_D_clk_n[0]}]
#revert back to original instance
current_instance -quiet
