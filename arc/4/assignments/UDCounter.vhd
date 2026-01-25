----------
-- File Name : UDCounter.vhd
-- Function : Up/Down Counter
-- Author : Manabu Inoue
-- Rev and Date : 1.0 , 2025/01/20 , original source
----------


library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_signed.all;


entity UDCounter is

	port (
		CLK : in std_logic;
		RST : in std_logic;
		UDS : in std_logic;
		CNT : out integer range 0 to 15
	);
	
end UDCounter;


architecture RTL of UDCounter is





end RTL;