library IEEE;
use IEEE.std_logic_1164.all;  -- defines std_logic types
use IEEE.numeric_std.all;  -- defines add, etc

library UNISIM;
use UNISIM.all; -- defines some Xilinx components, including ROC reset component

use work.craft_gatelibrary.all;
entity SynFir is 
   port (
      clock :  in  std_logic;
      reset :  in  std_logic;
      sample_clock :  in  std_logic;
      in_data :  in  std_logic_vector(17 downto 0);
      out_data :  out  std_logic_vector(17 downto 0);
      in_coef0 :  in  std_logic_vector(31 downto 0);
      in_coef1 :  in  std_logic_vector(31 downto 0);
      in_coef2 :  in  std_logic_vector(31 downto 0);
      in_coef3 :  in  std_logic_vector(31 downto 0);
      in_coef4 :  in  std_logic_vector(31 downto 0);
      in_coef5 :  in  std_logic_vector(31 downto 0);
      in_coef6 :  in  std_logic_vector(31 downto 0);
      in_coef7 :  in  std_logic_vector(31 downto 0);
      in_coef8 :  in  std_logic_vector(31 downto 0);
      in_coef9 :  in  std_logic_vector(31 downto 0);
      in_coef10 :  in  std_logic_vector(31 downto 0);
      in_coef11 :  in  std_logic_vector(31 downto 0);
      in_coef12 :  in  std_logic_vector(31 downto 0);
      in_coef13 :  in  std_logic_vector(31 downto 0);
      in_coef14 :  in  std_logic_vector(31 downto 0);
      in_coef15 :  in  std_logic_vector(31 downto 0);
      in_coef16 :  in  std_logic_vector(31 downto 0);
      in_coef17 :  in  std_logic_vector(31 downto 0);
      in_coef18 :  in  std_logic_vector(31 downto 0);
      in_coef19 :  in  std_logic_vector(31 downto 0);
      in_coef20 :  in  std_logic_vector(31 downto 0);
      in_coef21 :  in  std_logic_vector(31 downto 0);
      in_coef22 :  in  std_logic_vector(31 downto 0)
   );
end SynFir;

architecture SynFir_syn of SynFir is

   --signal declarations
   signal s258 : std_logic;
   signal s259 : std_logic;
   signal s260 : std_logic;
   signal s261 : std_logic;
   signal s262 : std_logic;
   signal s263 : std_logic_vector(17 downto 0);
   signal s264 : std_logic_vector(17 downto 0);
   signal s265 : std_logic_vector(17 downto 0);
   signal s267 : std_logic_vector(31 downto 0);
   signal s268 : std_logic_vector(31 downto 0);
   signal s269 : std_logic_vector(31 downto 0);
   signal s270 : std_logic_vector(31 downto 0);
   signal s271 : std_logic_vector(31 downto 0);
   signal s272 : std_logic_vector(31 downto 0);
   signal s273 : std_logic_vector(31 downto 0);
   signal s274 : std_logic_vector(31 downto 0);
   signal s275 : std_logic_vector(31 downto 0);
   signal s276 : std_logic_vector(31 downto 0);
   signal s277 : std_logic_vector(31 downto 0);
   signal s278 : std_logic_vector(31 downto 0);
   signal s279 : std_logic_vector(31 downto 0);
   signal s280 : std_logic_vector(31 downto 0);
   signal s281 : std_logic_vector(31 downto 0);
   signal s282 : std_logic_vector(31 downto 0);
   signal s283 : std_logic_vector(31 downto 0);
   signal s284 : std_logic_vector(31 downto 0);
   signal s285 : std_logic_vector(31 downto 0);
   signal s286 : std_logic_vector(31 downto 0);
   signal s287 : std_logic_vector(31 downto 0);
   signal s288 : std_logic_vector(31 downto 0);
   signal s289 : std_logic_vector(31 downto 0);
   signal s290_0, s290_1, s290_2, s290_3, s290_4, s290_5, s290_6, s290_7, s290_8, s290_9, s290_10, s290_11, s290_12, s290_13, s290_14, s290_15, s290_16, s290_17, s290_18, s290_19, s290_20, s290_21, s290_22 : std_logic_vector(17 downto 0);
   signal s291_0, s291_1, s291_2, s291_3, s291_4, s291_5, s291_6, s291_7, s291_8, s291_9, s291_10, s291_11, s291_12, s291_13, s291_14, s291_15, s291_16, s291_17, s291_18, s291_19, s291_20, s291_21, s291_22 : std_logic_vector(17 downto 0);
   signal s293_0, s293_1, s293_2, s293_3, s293_4, s293_5, s293_6, s293_7, s293_8, s293_9, s293_10, s293_11, s293_12, s293_13, s293_14, s293_15, s293_16, s293_17, s293_18, s293_19, s293_20, s293_21, s293_22 : std_logic_vector(31 downto 0);
   signal s294_0, s294_1, s294_2, s294_3, s294_4, s294_5, s294_6, s294_7, s294_8, s294_9, s294_10, s294_11, s294_12, s294_13, s294_14, s294_15, s294_16, s294_17, s294_18, s294_19, s294_20, s294_21, s294_22 : std_logic_vector(31 downto 0);
   signal s296 : std_logic;
   signal s297 : std_logic;
   signal s298 : std_logic;
   signal s299 : std_logic;
   signal s300 : std_logic;


   --component declarations
   component ROC -- the Xilinx reset component
     port (O : out std_logic);
   end component; --ROC

   component SynFir_DoCalculate
   port (
      clockin_craft :  in  std_logic;
      syncreset_craft :  in  std_logic;
      asyncreset_craft :  in  std_logic;
      start_craft :  in  std_logic;
      finish_craft :  out  std_logic;
      clock :  in  std_logic;
      reset :  in  std_logic;
      sample_clock :  in  std_logic;
      in_data :  in  std_logic_vector(17 downto 0);
      out_data_out :  out  std_logic_vector(17 downto 0);
      out_data_prev :  in  std_logic_vector(17 downto 0);
      out_data_new :  in  std_logic_vector(17 downto 0);
      in_coef0 :  in  std_logic_vector(31 downto 0);
      in_coef1 :  in  std_logic_vector(31 downto 0);
      in_coef2 :  in  std_logic_vector(31 downto 0);
      in_coef3 :  in  std_logic_vector(31 downto 0);
      in_coef4 :  in  std_logic_vector(31 downto 0);
      in_coef5 :  in  std_logic_vector(31 downto 0);
      in_coef6 :  in  std_logic_vector(31 downto 0);
      in_coef7 :  in  std_logic_vector(31 downto 0);
      in_coef8 :  in  std_logic_vector(31 downto 0);
      in_coef9 :  in  std_logic_vector(31 downto 0);
      in_coef10 :  in  std_logic_vector(31 downto 0);
      in_coef11 :  in  std_logic_vector(31 downto 0);
      in_coef12 :  in  std_logic_vector(31 downto 0);
      in_coef13 :  in  std_logic_vector(31 downto 0);
      in_coef14 :  in  std_logic_vector(31 downto 0);
      in_coef15 :  in  std_logic_vector(31 downto 0);
      in_coef16 :  in  std_logic_vector(31 downto 0);
      in_coef17 :  in  std_logic_vector(31 downto 0);
      in_coef18 :  in  std_logic_vector(31 downto 0);
      in_coef19 :  in  std_logic_vector(31 downto 0);
      in_coef20 :  in  std_logic_vector(31 downto 0);
      in_coef21 :  in  std_logic_vector(31 downto 0);
      in_coef22 :  in  std_logic_vector(31 downto 0);
      m_delay_line_out_0, m_delay_line_out_1, m_delay_line_out_2, m_delay_line_out_3, m_delay_line_out_4, m_delay_line_out_5, m_delay_line_out_6, m_delay_line_out_7, m_delay_line_out_8, m_delay_line_out_9, m_delay_line_out_10, m_delay_line_out_11, m_delay_line_out_12, m_delay_line_out_13, m_delay_line_out_14, m_delay_line_out_15, m_delay_line_out_16, m_delay_line_out_17, m_delay_line_out_18, m_delay_line_out_19, m_delay_line_out_20, m_delay_line_out_21, m_delay_line_out_22 :  out  std_logic_vector(17 downto 0);
      m_delay_line_prev_0, m_delay_line_prev_1, m_delay_line_prev_2, m_delay_line_prev_3, m_delay_line_prev_4, m_delay_line_prev_5, m_delay_line_prev_6, m_delay_line_prev_7, m_delay_line_prev_8, m_delay_line_prev_9, m_delay_line_prev_10, m_delay_line_prev_11, m_delay_line_prev_12, m_delay_line_prev_13, m_delay_line_prev_14, m_delay_line_prev_15, m_delay_line_prev_16, m_delay_line_prev_17, m_delay_line_prev_18, m_delay_line_prev_19, m_delay_line_prev_20, m_delay_line_prev_21, m_delay_line_prev_22 :  in  std_logic_vector(17 downto 0);
      m_delay_line_new_0, m_delay_line_new_1, m_delay_line_new_2, m_delay_line_new_3, m_delay_line_new_4, m_delay_line_new_5, m_delay_line_new_6, m_delay_line_new_7, m_delay_line_new_8, m_delay_line_new_9, m_delay_line_new_10, m_delay_line_new_11, m_delay_line_new_12, m_delay_line_new_13, m_delay_line_new_14, m_delay_line_new_15, m_delay_line_new_16, m_delay_line_new_17, m_delay_line_new_18, m_delay_line_new_19, m_delay_line_new_20, m_delay_line_new_21, m_delay_line_new_22 :  in  std_logic_vector(17 downto 0);
      m_coeffs_out_0, m_coeffs_out_1, m_coeffs_out_2, m_coeffs_out_3, m_coeffs_out_4, m_coeffs_out_5, m_coeffs_out_6, m_coeffs_out_7, m_coeffs_out_8, m_coeffs_out_9, m_coeffs_out_10, m_coeffs_out_11, m_coeffs_out_12, m_coeffs_out_13, m_coeffs_out_14, m_coeffs_out_15, m_coeffs_out_16, m_coeffs_out_17, m_coeffs_out_18, m_coeffs_out_19, m_coeffs_out_20, m_coeffs_out_21, m_coeffs_out_22 :  out  std_logic_vector(31 downto 0);
      m_coeffs_prev_0, m_coeffs_prev_1, m_coeffs_prev_2, m_coeffs_prev_3, m_coeffs_prev_4, m_coeffs_prev_5, m_coeffs_prev_6, m_coeffs_prev_7, m_coeffs_prev_8, m_coeffs_prev_9, m_coeffs_prev_10, m_coeffs_prev_11, m_coeffs_prev_12, m_coeffs_prev_13, m_coeffs_prev_14, m_coeffs_prev_15, m_coeffs_prev_16, m_coeffs_prev_17, m_coeffs_prev_18, m_coeffs_prev_19, m_coeffs_prev_20, m_coeffs_prev_21, m_coeffs_prev_22 :  in  std_logic_vector(31 downto 0);
      m_coeffs_new_0, m_coeffs_new_1, m_coeffs_new_2, m_coeffs_new_3, m_coeffs_new_4, m_coeffs_new_5, m_coeffs_new_6, m_coeffs_new_7, m_coeffs_new_8, m_coeffs_new_9, m_coeffs_new_10, m_coeffs_new_11, m_coeffs_new_12, m_coeffs_new_13, m_coeffs_new_14, m_coeffs_new_15, m_coeffs_new_16, m_coeffs_new_17, m_coeffs_new_18, m_coeffs_new_19, m_coeffs_new_20, m_coeffs_new_21, m_coeffs_new_22 :  in  std_logic_vector(31 downto 0)
   );
   end component; -- SynFir_DoCalculate


begin -- body of SynFir_syn

   -- port connections
   s258 <= clock;
   s261 <= reset;
   s262 <= sample_clock;
   s263 <= in_data;
   out_data <= s265;
   s267 <= in_coef0;
   s268 <= in_coef1;
   s269 <= in_coef2;
   s270 <= in_coef3;
   s271 <= in_coef4;
   s272 <= in_coef5;
   s273 <= in_coef6;
   s274 <= in_coef7;
   s275 <= in_coef8;
   s276 <= in_coef9;
   s277 <= in_coef10;
   s278 <= in_coef11;
   s279 <= in_coef12;
   s280 <= in_coef13;
   s281 <= in_coef14;
   s282 <= in_coef15;
   s283 <= in_coef16;
   s284 <= in_coef17;
   s285 <= in_coef18;
   s286 <= in_coef19;
   s287 <= in_coef20;
   s288 <= in_coef21;
   s289 <= in_coef22;


   -- hierarchical container SynFir_DoCalculate_0
   SynFir_DoCalculate_0 : 
    SynFir_DoCalculate
     port map (
      asyncreset_craft => s259, 
      clock => s258, 
      clockin_craft => s258, 
      finish_craft => s300, 
      in_coef0 => s267, 
      in_coef1 => s268, 
      in_coef10 => s277, 
      in_coef11 => s278, 
      in_coef12 => s279, 
      in_coef13 => s280, 
      in_coef14 => s281, 
      in_coef15 => s282, 
      in_coef16 => s283, 
      in_coef17 => s284, 
      in_coef18 => s285, 
      in_coef19 => s286, 
      in_coef2 => s269, 
      in_coef20 => s287, 
      in_coef21 => s288, 
      in_coef22 => s289, 
      in_coef3 => s270, 
      in_coef4 => s271, 
      in_coef5 => s272, 
      in_coef6 => s273, 
      in_coef7 => s274, 
      in_coef8 => s275, 
      in_coef9 => s276, 
      in_data => s263, 
      m_coeffs_new_0 => s294_0, 
      m_coeffs_new_1 => s294_1, 
      m_coeffs_new_2 => s294_2, 
      m_coeffs_new_3 => s294_3, 
      m_coeffs_new_4 => s294_4, 
      m_coeffs_new_5 => s294_5, 
      m_coeffs_new_6 => s294_6, 
      m_coeffs_new_7 => s294_7, 
      m_coeffs_new_8 => s294_8, 
      m_coeffs_new_9 => s294_9, 
      m_coeffs_new_10 => s294_10, 
      m_coeffs_new_11 => s294_11, 
      m_coeffs_new_12 => s294_12, 
      m_coeffs_new_13 => s294_13, 
      m_coeffs_new_14 => s294_14, 
      m_coeffs_new_15 => s294_15, 
      m_coeffs_new_16 => s294_16, 
      m_coeffs_new_17 => s294_17, 
      m_coeffs_new_18 => s294_18, 
      m_coeffs_new_19 => s294_19, 
      m_coeffs_new_20 => s294_20, 
      m_coeffs_new_21 => s294_21, 
      m_coeffs_new_22 => s294_22, 
      m_coeffs_out_0 => s293_0, 
      m_coeffs_out_1 => s293_1, 
      m_coeffs_out_2 => s293_2, 
      m_coeffs_out_3 => s293_3, 
      m_coeffs_out_4 => s293_4, 
      m_coeffs_out_5 => s293_5, 
      m_coeffs_out_6 => s293_6, 
      m_coeffs_out_7 => s293_7, 
      m_coeffs_out_8 => s293_8, 
      m_coeffs_out_9 => s293_9, 
      m_coeffs_out_10 => s293_10, 
      m_coeffs_out_11 => s293_11, 
      m_coeffs_out_12 => s293_12, 
      m_coeffs_out_13 => s293_13, 
      m_coeffs_out_14 => s293_14, 
      m_coeffs_out_15 => s293_15, 
      m_coeffs_out_16 => s293_16, 
      m_coeffs_out_17 => s293_17, 
      m_coeffs_out_18 => s293_18, 
      m_coeffs_out_19 => s293_19, 
      m_coeffs_out_20 => s293_20, 
      m_coeffs_out_21 => s293_21, 
      m_coeffs_out_22 => s293_22, 
      m_coeffs_prev_0 => s294_0, 
      m_coeffs_prev_1 => s294_1, 
      m_coeffs_prev_2 => s294_2, 
      m_coeffs_prev_3 => s294_3, 
      m_coeffs_prev_4 => s294_4, 
      m_coeffs_prev_5 => s294_5, 
      m_coeffs_prev_6 => s294_6, 
      m_coeffs_prev_7 => s294_7, 
      m_coeffs_prev_8 => s294_8, 
      m_coeffs_prev_9 => s294_9, 
      m_coeffs_prev_10 => s294_10, 
      m_coeffs_prev_11 => s294_11, 
      m_coeffs_prev_12 => s294_12, 
      m_coeffs_prev_13 => s294_13, 
      m_coeffs_prev_14 => s294_14, 
      m_coeffs_prev_15 => s294_15, 
      m_coeffs_prev_16 => s294_16, 
      m_coeffs_prev_17 => s294_17, 
      m_coeffs_prev_18 => s294_18, 
      m_coeffs_prev_19 => s294_19, 
      m_coeffs_prev_20 => s294_20, 
      m_coeffs_prev_21 => s294_21, 
      m_coeffs_prev_22 => s294_22, 
      m_delay_line_new_0 => s291_0, 
      m_delay_line_new_1 => s291_1, 
      m_delay_line_new_2 => s291_2, 
      m_delay_line_new_3 => s291_3, 
      m_delay_line_new_4 => s291_4, 
      m_delay_line_new_5 => s291_5, 
      m_delay_line_new_6 => s291_6, 
      m_delay_line_new_7 => s291_7, 
      m_delay_line_new_8 => s291_8, 
      m_delay_line_new_9 => s291_9, 
      m_delay_line_new_10 => s291_10, 
      m_delay_line_new_11 => s291_11, 
      m_delay_line_new_12 => s291_12, 
      m_delay_line_new_13 => s291_13, 
      m_delay_line_new_14 => s291_14, 
      m_delay_line_new_15 => s291_15, 
      m_delay_line_new_16 => s291_16, 
      m_delay_line_new_17 => s291_17, 
      m_delay_line_new_18 => s291_18, 
      m_delay_line_new_19 => s291_19, 
      m_delay_line_new_20 => s291_20, 
      m_delay_line_new_21 => s291_21, 
      m_delay_line_new_22 => s291_22, 
      m_delay_line_out_0 => s290_0, 
      m_delay_line_out_1 => s290_1, 
      m_delay_line_out_2 => s290_2, 
      m_delay_line_out_3 => s290_3, 
      m_delay_line_out_4 => s290_4, 
      m_delay_line_out_5 => s290_5, 
      m_delay_line_out_6 => s290_6, 
      m_delay_line_out_7 => s290_7, 
      m_delay_line_out_8 => s290_8, 
      m_delay_line_out_9 => s290_9, 
      m_delay_line_out_10 => s290_10, 
      m_delay_line_out_11 => s290_11, 
      m_delay_line_out_12 => s290_12, 
      m_delay_line_out_13 => s290_13, 
      m_delay_line_out_14 => s290_14, 
      m_delay_line_out_15 => s290_15, 
      m_delay_line_out_16 => s290_16, 
      m_delay_line_out_17 => s290_17, 
      m_delay_line_out_18 => s290_18, 
      m_delay_line_out_19 => s290_19, 
      m_delay_line_out_20 => s290_20, 
      m_delay_line_out_21 => s290_21, 
      m_delay_line_out_22 => s290_22, 
      m_delay_line_prev_0 => s291_0, 
      m_delay_line_prev_1 => s291_1, 
      m_delay_line_prev_2 => s291_2, 
      m_delay_line_prev_3 => s291_3, 
      m_delay_line_prev_4 => s291_4, 
      m_delay_line_prev_5 => s291_5, 
      m_delay_line_prev_6 => s291_6, 
      m_delay_line_prev_7 => s291_7, 
      m_delay_line_prev_8 => s291_8, 
      m_delay_line_prev_9 => s291_9, 
      m_delay_line_prev_10 => s291_10, 
      m_delay_line_prev_11 => s291_11, 
      m_delay_line_prev_12 => s291_12, 
      m_delay_line_prev_13 => s291_13, 
      m_delay_line_prev_14 => s291_14, 
      m_delay_line_prev_15 => s291_15, 
      m_delay_line_prev_16 => s291_16, 
      m_delay_line_prev_17 => s291_17, 
      m_delay_line_prev_18 => s291_18, 
      m_delay_line_prev_19 => s291_19, 
      m_delay_line_prev_20 => s291_20, 
      m_delay_line_prev_21 => s291_21, 
      m_delay_line_prev_22 => s291_22, 
      out_data_new => s265, 
      out_data_out => s264, 
      out_data_prev => s265, 
      reset => s261, 
      sample_clock => s262, 
      start_craft => s299, 
      syncreset_craft => s260
     );

   rocblock_214 : ROC port map (O => s259);  -- rocblock module rocblock_214

   s260 <= '0';  -- constint module constint_0_215

   -- register reg_out_data_216
   process (s258)
   begin
   if s258'event and s258='1' then  
     s265 <= s264;
   end if;
   end process;

   -- register reg_m_delay_line_217
   process (s258)
   begin
   if s258'event and s258='1' then  
     s291_0 <= s290_0;
     s291_1 <= s290_1;
     s291_2 <= s290_2;
     s291_3 <= s290_3;
     s291_4 <= s290_4;
     s291_5 <= s290_5;
     s291_6 <= s290_6;
     s291_7 <= s290_7;
     s291_8 <= s290_8;
     s291_9 <= s290_9;
     s291_10 <= s290_10;
     s291_11 <= s290_11;
     s291_12 <= s290_12;
     s291_13 <= s290_13;
     s291_14 <= s290_14;
     s291_15 <= s290_15;
     s291_16 <= s290_16;
     s291_17 <= s290_17;
     s291_18 <= s290_18;
     s291_19 <= s290_19;
     s291_20 <= s290_20;
     s291_21 <= s290_21;
     s291_22 <= s290_22;
   end if;
   end process;

   -- register reg_m_coeffs_218
   process (s258)
   begin
   if s258'event and s258='1' then  
     s294_0 <= s293_0;
     s294_1 <= s293_1;
     s294_2 <= s293_2;
     s294_3 <= s293_3;
     s294_4 <= s293_4;
     s294_5 <= s293_5;
     s294_6 <= s293_6;
     s294_7 <= s293_7;
     s294_8 <= s293_8;
     s294_9 <= s293_9;
     s294_10 <= s293_10;
     s294_11 <= s293_11;
     s294_12 <= s293_12;
     s294_13 <= s293_13;
     s294_14 <= s293_14;
     s294_15 <= s293_15;
     s294_16 <= s293_16;
     s294_17 <= s293_17;
     s294_18 <= s293_18;
     s294_19 <= s293_19;
     s294_20 <= s293_20;
     s294_21 <= s293_21;
     s294_22 <= s293_22;
   end if;
   end process;

   s296 <= '1';  -- constint module constint_1_219

   -- register state_reg_220
   process (s258, s260, s259)
   begin
   if s259 = '1' then
     s297 <= '0';
   elsif s258'event and s258='1' then  
     if s260 = '1' then
        s297 <= '0';
     else
        s297 <= s296;
     end if;
   end if;
   end process;

   s298 <= not s297;  -- not module inv_221

   -- register state_reg_222
   process (s258, s260, s259)
   begin
   if s259 = '1' then
     s299 <= '0';
   elsif s258'event and s258='1' then  
     if s260 = '1' then
        s299 <= '0';
     else
        s299 <= s298;
     end if;
   end if;
   end process;
end SynFir_syn;

