----------
-- File Name : Int_to_Seg7.vhd
-- Function : Convert Data from Integer to 7 Segment LED
-- Author : Manabu Inoue
-- Rev and Date : 1.0 , 2008/10/19 , original source
----------


library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_signed.all;


entity Pattern_8 is

	port (
		DATA : in integer range 0 to 7;
		SEG7 : out std_logic_vector(6 downto 0)
	);
	
end Pattern_8;


architecture RTL of Pattern_8 is

begin

	INT_to_SEG7 : process(DATA)
	begin

		case DATA is
			when 0 =>       SEG7 <= "0000001"; -- display 0
			when 1 =>       SEG7 <= "1001111"; -- display 1
			when 2 =>		SEG7 <= "0010010";
			when 3 => 		SEG7 <= "0000110";
			when 4 => 		SEG7 <= "1001100";
			when 5 =>		SEG7 <= "0100100";
			when 6 =>		SEG7 <= "0100000";
			when 7 => 		SEG7 <= "0001101";	
			when others =>  SEG7 <= "1111110"; -- display -
		end case;

	end process;

end RTL;