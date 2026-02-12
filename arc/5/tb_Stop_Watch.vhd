----------
-- File Name : tb_Stop_Watch.vhd
-- Function : Test Bench for Stop_Watch.vhd
-- Author : Manabu Inoue
-- Rev and Date : 1.0 , 2008/11/19 , original source
--                1.1 , 2008/12/24 , add Mode_Disp module for seminar
----------


library IEEE;
use IEEE.std_logic_1164.all;

entity tb_Stop_Watch is
end tb_Stop_Watch;

architecture IO of tb_Stop_Watch is

	component Stop_Watch
	port (
		CLK : in std_logic;
		RST : in std_logic;
		SSS : in std_logic; -- SSS means Start and Stop Select
		IND : out std_logic_vector(1 downto 0);
		LSEG : out std_logic_vector(6 downto 0);
		RSEG : out std_logic_vector(6 downto 0)
	);
	end component;

	signal done : boolean := false;
	signal clk : std_logic := '0';
	signal rst : std_logic := '0';
	signal sss : std_logic := '0';
	signal ind : std_logic_vector(1 downto 0);
	signal lseg, rseg : std_logic_vector(6 downto 0);

begin

	SIM : Stop_Watch port map (
		CLK => clk,
		RST => rst,
		SSS => sss,
		IND => ind,
		LSEG => lseg,
		RSEG => rseg
	);

	SIM_TIME : process
	begin
		wait for 50000 ns;
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
			rst <= '1';
			wait for 30 ns;
			rst <= '0';
			wait for 30000 ns;
			rst <= '1';
			wait for 30 ns;
		else
			wait;
		end if;
	end process;

	INPUT_SSS : process
	begin
		if done = false then
			sss <= '0';
			wait for 100 ns;
			sss <= '1';
			wait for 5000 ns;
		else
			wait;
		end if;
	end process;

end IO;