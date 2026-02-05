----------
-- File Name : Counter_2bit.vhd
-- Function : Count the Clock (2 bit)
-- Author : Manabu Inoue
-- Rev and Date : 1.0 , 2008/11/19 , original source
----------


library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_signed.all;


entity Counter_2bit is

	port (
		CLK : in std_logic;
		RST : in std_logic;
		CNT : out integer range 0 to 3
	);
	
end Counter_2bit;


architecture RTL of Counter_2bit is

	signal cnt_reg : integer range 0 to 3;

begin

	COUNT2 : process(CLK, RST)
	begin

		if (RST = '1') then -- reset

			cnt_reg <= 0;

		elsif (CLK'event and CLK = '1') then

			if (cnt_reg = 3) then
				cnt_reg <= 0; -- rotation
			else
				cnt_reg <= cnt_reg + 1; -- CNTを直接使うと，outポートのため値の読み出しができない」
			end if;

		end if;

	end process;

	CNT <= cnt_reg;--outポートは直接読み出しができないため

end RTL;