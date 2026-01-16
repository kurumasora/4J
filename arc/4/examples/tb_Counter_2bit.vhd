----------
-- File Name : tb_Counter_2bit.vhd
-- Function : Test Bench for Counter_2bit.vhd
-- Author : Manabu Inoue
-- Rev and Date : 1.0 , 2008/11/19 , original source
----------


library IEEE;
use IEEE.std_logic_1164.all;

entity tb_Counter_2bit is
end tb_Counter_2bit;

architecture IO of tb_Counter_2bit is

	component Counter_2bit
	port (
		CLK : in std_logic;
		RST : in std_logic;
		CNT : out integer range 0 to 3
	);
	end component;

	signal done : boolean := false;
	signal clk : std_logic := '0';
	signal rst : std_logic := '0';
	signal cnt : integer range 0 to 3;

begin

	SIM : Counter_2bit port map (
		CLK => clk,
		RST => rst,
		CNT => cnt
	);

	SIM_TIME : process
	begin
		wait for 1000 ns;
		done <= true;
		wait;
	end process;

	INPUT_CLK : process
	begin
		if done = false then
			clk <= '0';
			wait for 10 ns;
			clk <= '1';
			wait for 10 ns;
		else
			wait;
		end if;
	end process;

	INPUT_RST : process
	begin
		if done = false then
			rst <= '0';
			wait for 200 ns;
			rst <= '1';
			wait for 30 ns;
		else
			wait;
		end if;
	end process;

end IO;