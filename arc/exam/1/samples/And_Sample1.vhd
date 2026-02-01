----------
-- File Name : And_Sample1.vhd
-- Function : Operate the Logical AND for Two Input
-- Author : Manabu Inoue
-- Rev and Date : 1.0 , 2008/10/19 , original source
----------


library IEEE;						--library部
use IEEE.std_logic_1164.all;    --基本関数
use IEEE.std_logic_arith.all;	--算術演算
use IEEE.std_logic_signed.all;	--符号付き演算


entity And_Sample1 is  				--エンティティ部

	port (
		A : in std_logic;		
		B : in std_logic;
		Y : out std_logic
	);
	
end And_Sample1;

-----------
--entity エンティティ名　is
--	port ( 
--		ポート名 : in/out データ型;
--	);
--end エンティティ名;
-----------


architecture RTL of And_Sample1 is   --アーキテクチャ部

begin

	Y <= A and B;

end RTL;

-----------
--architecture アーキテクチャ名 of エンティティ名 is
--begin
--	<信号割当等の処理>
--end アーキテクチャ名;
-----------	
