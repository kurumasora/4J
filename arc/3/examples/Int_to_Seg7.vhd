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


entity Int_to_Seg7 is

	port (
		INTD : in integer range 0 to 1;
		SEG7 : out std_logic_vector(6 downto 0)
	);
	
end Int_to_Seg7;


architecture RTL of Int_to_Seg7 is

begin

	INT_to_SEG7 : process(INTD)
	begin

		case INTD is
			when 0 =>       SEG7 <= "0000001"; -- display 0
			when 1 =>       SEG7 <= "1001111"; -- display 1
			when others =>  SEG7 <= "1111110"; -- display -
		end case;

	end process;

end RTL;