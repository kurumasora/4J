----------
-- File Name : Logic_to_Int.vhd
-- Function : Convert Data from Std_Logic to Integer
-- Author : Manabu Inoue
-- Rev and Date : 1.0 , 2008/10/19 , original source
----------


library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_signed.all;


entity Logic_to_Int is

	port (
		SW : in std_logic;
		DATA : out integer range 0 to 1
	);
	
end Logic_to_Int;


architecture RTL of Logic_to_Int is

begin

	LOGIC_to_INT : process(SW)
	begin

		case SW is
			when '0' =>     DATA <= 0; -- integer 0
			when others =>  DATA <= 1; -- integer 1
		end case;

	end process;

end RTL;