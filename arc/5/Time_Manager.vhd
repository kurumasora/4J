----------
-- File Name : Time_Manager.vhd
-- Function : Manage the Time Count
-- Author : Manabu Inoue
-- Rev and Date : 1.0 , 2008/11/19 , original source
----------


library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_signed.all;


entity Time_Manager is

	port (
		CLK : in std_logic;
		RST : in std_logic;
		SSS : in std_logic; -- SSS means Start and Stop Select
		IND : out std_logic_vector(1 downto 0); -- mode indicator
		DIG_O : out integer range 0 to 15; -- digit 1
		DIG_T : out integer range 0 to 15 -- digit 10
	);
	
end Time_Manager;


architecture RTL of Time_Manager is

	--constant CLK_FREQ : integer := 10000000; -- on board oscillator (-1)
	constant CLK_FREQ : integer := 5; -- for simulation

	signal clk_cnt : integer range 0 to 16777216; -- 2^24
	signal digo_reg, digt_reg : integer range 0 to 15;

begin

	COUNT2 : process(CLK, RST)
	begin

		if (RST = '1') then -- reset

			digt_reg <= 0;
			digo_reg <= 0;
			clk_cnt <= 0;

			IND <= "00";

		elsif (CLK'event and CLK = '1') then

			if (SSS = '0') then -- stop mode

				digt_reg <= digt_reg;
				digo_reg <= digo_reg;
				clk_cnt <= clk_cnt;

				IND <= "00";

			else -- start mode

				-- digit 10 control
				if ((digo_reg = 9) and (digt_reg = 9)) then
					digt_reg <= digt_reg;--99でストップ
				elsif ((digo_reg = 9) and (clk_cnt = CLK_FREQ)) then
					digt_reg <= digt_reg + 1;
				else
					digt_reg <= digt_reg;
				end if;

				-- digit 1 control
				if ((digo_reg = 9) and (digt_reg = 9)) then
					digo_reg <= digo_reg;
				elsif ((digo_reg = 9) and (clk_cnt = CLK_FREQ)) then
					digo_reg <= 0;
				elsif (clk_cnt = CLK_FREQ) then
					digo_reg <= digo_reg + 1;
				else
					digo_reg <= digo_reg;
				end if;

				-- make 1 second
				if ((digo_reg = 9) and (digt_reg = 9)) then
					clk_cnt <= clk_cnt;
				elsif (clk_cnt = CLK_FREQ) then
					clk_cnt <= 0;
				else
					clk_cnt <= clk_cnt + 1;
				end if;

				IND <= "11";

			end if;

		end if;

	end process;

	DIG_T <= digt_reg;
	DIG_O <= digo_reg;

end RTL;