----------
-- File Name : Pattern_10_slv.vhd
-- Function : Display the Input Pattern on the 7 Segment LED
-- Author : Manabu Inoue
-- Rev and Date : 1.0 , 2025/01/04 , original source
----------


library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_signed.all;


entity Pattern_10_slv is

	port (
		SW : in std_logic_vector(3 downto 0);
		SEG7 : out std_logic_vector(6 downto 0)
	);

end Pattern_10_slv;


architecture RTL of Pattern_10_slv is

begin

	SEG_CONTROL : process(SW)
	begin

		case SW is
			when "0000" =>   SEG7 <= "0000001"; -- display 0
			when "0001" =>   SEG7 <= "1001111"; -- display 1
			when "0010" =>   SEG7 <= "0010010"; -- display 2
			when "0011" =>   SEG7 <= "0000110"; -- display 3
			when "0100" =>   SEG7 <= "1001100"; -- display 4
			when "0101" =>   SEG7 <= "0100100"; -- display 5
			when "0110" =>   SEG7 <= "0100000"; -- display 6
			when "0111" =>   SEG7 <= "0001101"; -- display 7
			when "1000" =>   SEG7 <= "0000000"; -- display 8
			when "1001" =>   SEG7 <= "0000100"; -- display 9
			when others =>  SEG7 <= "1111110"; -- display -
		end case;

	end process;

end RTL;