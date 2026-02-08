library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_signed.all;


entity Or_Sample is

	port (
		A : in std_logic;
		B : in std_logic;
		Y : out std_logic
	);
	
end Or_Sample;


architecture RTL of Or_Sample is

begin

	
	LOGICAL_AND : process(A, B)
	begin

		if (A = '1') or (B = '1') then
			Y <= '1';
		else
			Y <= '0';
		end if ;

	end process; 
	


end RTL;