----------
-- File Name : Pattern_10.vhd
-- Function : Display the Input Data on the 7 Segment LED
-- Author : Manabu Inoue
-- Rev and Date : 1.0 , 2008/11/19 , original source
----------


library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_signed.all;


entity Pattern_10 is

	port (
		DATA : in integer range 0 to 15;
		SEG7 : out std_logic_vector(6 downto 0)
	);

end Pattern_10;


architecture RTL of Pattern_10 is

begin

	SEG_CONTROL : process(DATA)
	begin

		case DATA is
			when 0 =>       SEG7 <= "0000001"; -- display 0
			when 1 =>       SEG7 <= "1001111"; -- display 1
			when 2 =>       SEG7 <= "0010010"; -- display 2
			when 3 =>       SEG7 <= "0000110"; -- display 3
			when 4 =>       SEG7 <= "1001100"; -- display 4
			when 5 =>       SEG7 <= "0100100"; -- display 5
			when 6 =>       SEG7 <= "0100000"; -- display 6
			when 7 =>       SEG7 <= "0001101"; -- display 7
			when 8 =>       SEG7 <= "0000000"; -- display 8
			when 9 =>       SEG7 <= "0000100"; -- display 9
			when others =>  SEG7 <= "1111110"; -- display -
		end case;

	end process;

end RTL;