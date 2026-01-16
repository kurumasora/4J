----------
-- File Name : Logical_01_strct.vhd
-- Function : Display the Input Logic on the 7 Segment LED
-- Author : Manabu Inoue
-- Rev and Date : 1.0 , 2008/10/19 , original source
--                2.0 , 2008/10/19 , structure description
----------


library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_signed.all;


entity Logical_01_strct is

	port (
		SW : in std_logic;
		SEG7 : out std_logic_vector(6 downto 0)
	);
	
end Logical_01_strct;


architecture STRUCTURE of Logical_01_strct is

	component Logic_to_Int
	port (
		SW : in std_logic;
		DATA : out integer range 0 to 1
	);
	end component;

	component Int_to_Seg7
	port (
		INTD : in integer range 0 to 1;
		SEG7 : out std_logic_vector(6 downto 0)
	);
	end component;

	signal data_intd : integer range 0 to 1;

begin

	LTI : Logic_to_Int port map (
		SW => SW,
		DATA => data_intd
	);

	ITS : Int_to_Seg7 port map (
		INTD => data_intd,
		SEG7 => SEG7
	);

end STRUCTURE;