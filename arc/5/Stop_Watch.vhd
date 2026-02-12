----------
-- File Name : Stop_Watch.vhd
-- Function : Count and Display the Time (second)
-- Author : Manabu Inoue
-- Rev and Date : 1.0 , 2008/11/19 , original source
--                1.1 , 2008/12/24 , add Mode_Disp module for seminar
----------


library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_signed.all;


entity Stop_Watch is

	port (
		CLK : in std_logic;
		RST : in std_logic;
		SSS : in std_logic; -- SSS means Start and Stop Select
		IND : out std_logic_vector(1 downto 0);
		LSEG : out std_logic_vector(6 downto 0);
		RSEG : out std_logic_vector(6 downto 0)
	);
	
end Stop_Watch;


architecture STRUCTURE of Stop_Watch is

	component Time_Manager
	port (
		CLK : in std_logic;
		RST : in std_logic;
		SSS : in std_logic; -- SSS means Start and Stop Select
		IND : out std_logic_vector(1 downto 0); -- mode indicator
		DIG_O : out integer range 0 to 15; -- digit 1
		DIG_T : out integer range 0 to 15 -- digit 10
	);
	end component;

	component Pattern_10
	port (
		DATA : in integer range 0 to 15;
		SEG7 : out std_logic_vector(6 downto 0)
	);
	end component;

	signal do_data, dt_data : integer range 0 to 15;

begin

	TM : Time_Manager port map (
		CLK => CLK,
		RST => RST,
		SSS => SSS,
		IND => IND,
		DIG_O => do_data,
		DIG_T => dt_data
	);

	-- right-side segment
	RPT : Pattern_10 port map (
		DATA => do_data,
		SEG7 => RSEG
	);

	-- left-side segment
	LPT : Pattern_10 port map (
		DATA => dt_data,
		SEG7 => LSEG
	);

end STRUCTURE;