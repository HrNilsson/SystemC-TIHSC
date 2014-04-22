---------------------------------------
--  SystemCrafter VHDL Gate Library  --
--  (c) SystemCrafter Ltd 2004-2006  --
--  All rights reserved		     --
---------------------------------------

library IEEE;
use IEEE.std_logic_1164.all;  -- defines std_logic types
use IEEE.numeric_std.all;  -- defines add, etc

library UNISIM;
use UNISIM.all; -- defines some Xilinx components, including ROC reset component

package craft_gatelibrary is

  function to_unsigned (
    x : std_logic)
    return unsigned;

  function to_unsigned (
    x : std_logic_vector)
    return unsigned;

  function to_signed (
    x : std_logic)
    return signed;

  function to_signed (
    x : std_logic_vector)
    return signed;

  function "+" (
    L, R : unsigned)
    return std_logic;

  function "+" (
    L, R : unsigned)
    return std_logic_vector;

  function "+" (
    L, R : signed)
    return std_logic;

  function "+" (
    L, R : signed)
    return std_logic_vector;

  function "-" (
    L, R : unsigned)
    return std_logic;

  function "-" (
    L, R : unsigned)
    return std_logic_vector;

  function "-" (
    L, R : signed)
    return std_logic;

  function "-" (
    L, R : signed)
    return std_logic_vector;

  function "*" (
    L, R : unsigned)
    return std_logic;
  
  function "*" (
    L, R : unsigned)
    return std_logic_vector;

  function "*" (
    L, R : signed)
    return std_logic;

  function "*" (
    L, R : signed)
    return std_logic_vector;

  function "/" (
    L, R : unsigned)
    return std_logic;

  function "/" (
    L, R : unsigned)
    return std_logic_vector;

  function "/" (
    L, R : signed)
    return std_logic;

  function "/" (
    L, R : signed)
    return std_logic_vector;

  function "mod" (
    L, R : unsigned)
    return std_logic;

  function "mod" (
    L, R : unsigned)
    return std_logic_vector;

  function "mod" (
    L, R : signed)
    return std_logic;

  function "mod" (
    L, R : signed)
    return std_logic_vector;
    
  function "-" ( x : signed)
    return std_logic_vector; 

  function "-" ( x : signed)
    return std_logic;

  function equal (
    L, R : std_logic_vector)
    return std_logic;

  function equal (
    L, R : std_logic)
    return std_logic;

  function notequal (
    L, R : std_logic_vector)
    return std_logic;

  function notequal (
    L, R : std_logic)
    return std_logic;

  function less_signed (
    L, R : std_logic_vector)
    return std_logic;

  function less_signed (
    L, R : std_logic)
    return std_logic;

  function less_unsigned (
    L, R : std_logic_vector)
    return std_logic;

  function less_unsigned (
    L, R : std_logic)
    return std_logic;

  function lessequal_signed (
    L, R : std_logic_vector)
    return std_logic;

  function lessequal_signed (
    L, R : std_logic)
    return std_logic;

  function lessequal_unsigned (
    L, R : std_logic_vector)
    return std_logic;

  function lessequal_unsigned (
    L, R : std_logic)
    return std_logic;

  function greater_signed (
    L, R : std_logic_vector)
    return std_logic;

  function greater_signed (
    L, R : std_logic)
    return std_logic;

  function greater_unsigned (
    L, R : std_logic_vector)
    return std_logic;

  function greater_unsigned (
    L, R : std_logic)
    return std_logic;

  function greaterequal_signed (
    L, R : std_logic_vector)
    return std_logic;

  function greaterequal_signed (
    L, R : std_logic)
    return std_logic;

  function greaterequal_unsigned (
    L, R : std_logic_vector)
    return std_logic;

  function greaterequal_unsigned (
    L, R : std_logic)
    return std_logic;

  function bitselectassigner
-- bitassigner does the following:
-- result(x) = assignee(x) | x != bitindex
-- result(x) = assignor | x == bitindex
    (assignor : in std_logic;
    assignee : in std_logic_vector; 
    bitindex : in std_logic_vector) 
    return std_logic_vector;

  function bitselectassigner
--single bit index version for assignments to eg sc_uint<2>
-- the index is an std_logic, but the assignee is still a vector
    (assignor : in std_logic;
    assignee : in std_logic_vector; 
    bitindex : in std_logic) 
    return std_logic_vector;

  function bitselectassigner
--single bit version for assignments to eg sc_uint<1>
    (assignor : in std_logic;
    assignee : in std_logic; 
    bitindex : in std_logic) 
    return std_logic;

end craft_gatelibrary;

package body craft_gatelibrary is


  procedure divu_craft 
    (quotient_out : out std_logic_vector;
     remainder_out : out std_logic_vector;
     div_by_zero : out boolean;
     L, R : in std_logic_vector ) is
    
    constant len : natural := L'length;
    constant zero_divisor : std_logic_vector(L'range) := (others => '0');
    alias dividend : std_logic_vector(L'range) is L;
    variable divisor : std_logic_vector(len downto 0) := '0' & R;
    variable quotient : std_logic_vector(L'range);
    variable remainder : std_logic_vector(len downto 0) := (others => '0');
    
  begin
    -- assertions
    if L'length /= R'length 
      or L'length /= quotient_out'length
      or L'length /= remainder_out'length
    then
      report "divu_craft: operands have different lengths"
        severity failure;
    end if;
    --  check for zero divisor
    if R = zero_divisor then
      div_by_zero := true;
    else
      --  perform division
      for iter in len-1 downto 0 loop
        if remainder(len) = '0' then
          remainder := std_logic_vector(unsigned(remainder) sll 1);
          remainder(0) := dividend(iter);
          remainder := unsigned(remainder) - unsigned(divisor);
        else
          remainder := std_logic_vector(unsigned(remainder) sll 1);
          remainder(0) := dividend(iter);
          remainder := unsigned(remainder) + unsigned(divisor);
        end if;
        quotient(iter) := not remainder(len);
      end loop;
      if remainder(len) = '1' then
        remainder := unsigned(remainder) + unsigned(divisor);
      end if;
      quotient_out := quotient;
      remainder_out := remainder(len-1 downto 0);
      div_by_zero := false;
    end if;
  end procedure divu_craft;

  function to_unsigned (
    x : std_logic)
    return unsigned is
    variable xv : std_logic_vector(0 downto 0);
  begin
    xv(0) := x;
    return unsigned(xv);
  end to_unsigned;

  function to_unsigned (
    x : std_logic_vector)
    return unsigned is
  begin
    return unsigned(x);
  end to_unsigned;

  function to_signed (
    x : std_logic)
    return signed is
    variable xv : std_logic_vector(0 downto 0);
  begin
    xv(0) := x;
    return signed(xv);
  end to_signed;

  function to_signed (
    x : std_logic_vector)
    return signed is
  begin
    return signed(x);
  end to_signed;

  function "+" (
    L, R : unsigned)
    return std_logic is
  begin
    if L'length /= R'length then
      report "+ (std_logic,unsigned): operands have different lengths"
        severity failure;
    end if;
    return L(0) xor R(0);
  end "+";

  function "+" (
    L, R : unsigned)
    return std_logic_vector is 
    variable ru : unsigned(L'range);
  begin
    if L'length /= R'length then
      report "+ (std_logic_vector,unsigned): operands have different lengths"
        severity failure;
    end if;
    ru := L + R;
    return std_logic_vector(ru);
  end "+";

  function "+" (
    L, R : signed)
    return std_logic is
  begin
    if L'length /= R'length then
      report "+ (std_logic,signed): operands have different lengths"
        severity failure;
    end if;
    return L(0) xor R(0);
  end "+";

  function "+" (
    L, R : signed)
    return std_logic_vector is 
    variable rs : signed(L'range);
  begin
    if L'length /= R'length then
      report "+ (std_logic_vector,signed): operands have different lengths"
        severity failure;
    end if;
    rs := L + R;
    return std_logic_vector(rs);
  end "+";

  function "-" (
    L, R : unsigned)
    return std_logic is
  begin
    if L'length /= R'length then
      report "- (std_logic,unsigned): operands have different lengths"
        severity failure;
    end if;
    return L(0) xor R(0);
  end "-";

  function "-" (
    L, R : unsigned)
    return std_logic_vector is 
    variable ru : unsigned(L'range);
  begin
    if L'length /= R'length then
      report "- (std_logic_vector,unsigned): operands have different lengths"
        severity failure;
    end if;
    ru := L - R;
    return std_logic_vector(ru);
  end "-";

  function "-" (
    L, R : signed)
    return std_logic is
  begin
    if L'length /= R'length then
      report "- (std_logic,signed): operands have different lengths"
        severity failure;
    end if;
    return L(0) xor R(0);
  end "-";

  function "-" (
    L, R : signed)
    return std_logic_vector is 
    variable rs : signed(L'range);
  begin
    if L'length /= R'length then
      report "- (std_logic_vector,signed): operands have different lengths"
        severity failure;
    end if;
    rs := L - R;
    return std_logic_vector(rs);
  end "-";

  function "*" (
    L, R : unsigned)
    return std_logic is
  begin
    if L'length /= R'length then
      report "* (std_logic,unsigned): operands have different lengths"
        severity failure;
    end if;
    return L(0) and R(0);
  end "*";

  function "*" (
    L, R : unsigned)
    return std_logic_vector is 
    variable result : unsigned(L'range);
    variable result_big : unsigned((L'length+R'length-1) downto 0);
  begin
    if L'length /= R'length then
      report "* (std_logic_vector,unsigned): operands have different lengths"
        severity failure;
    end if;
    result_big := L * R;
    result := result_big(L'range);  
    return std_logic_vector(result);
  end "*";

  function "*" (
    L, R : signed)
    return std_logic is
  begin
    if L'length /= R'length then
      report "* (std_logic,signed): operands have different lengths"
        severity failure;
    end if;
    return '0';
  end "*";

  function "*" (
    L, R : signed)
    return std_logic_vector is 
    variable result : signed(L'range);
    variable result_big : signed((L'length+R'length-1) downto 0);
  begin
    if L'length /= R'length then
      report "* (std_logic_vector,signed): operands have different lengths"
        severity failure;
    end if;
    result_big := L * R;
    result := result_big(L'range);  
    return std_logic_vector(result);
  end "*";

  function "/" (
    L, R : unsigned)
    return std_logic is
  begin
    if L'length /= R'length then
      report "/ (std_logic,unsigned): operands have different lengths"
        severity failure;
    end if;
    return L(0);
  end "/";

  function "/" (
    L, R : unsigned)
    return std_logic_vector is 
    variable result : std_logic_vector(L'length-1 downto 0);
    variable ignore_remainder : std_logic_vector(L'length-1 downto 0);
    variable ignore_div_by_zero : boolean;
  begin
    if L'length /= R'length then
      report "/ (std_logic_vector,unsigned): operands have different lengths"
        severity failure;
    end if;
    divu_craft(result,ignore_remainder, ignore_div_by_zero, std_logic_vector(L), std_logic_vector(R));
    return result;
  end "/";

  function "/" (
    L, R : signed)
    return std_logic is
  begin
    if L'length /= R'length then
      report "/ (std_logic,signed): operands have different lengths"
        severity failure;
    end if;
    return L(0);
  end "/";

  --helper functions for signed / and mod
  function is_negative (
    x : signed)
    return boolean is
  begin  -- is_negative
    return (x(x'left) = '1');
  end is_negative;

  -- purpose: return absolute value (unsigned) of signed
  function posval (
    x : signed) 
     return unsigned is
     variable minusx : signed(x'range);
   begin  -- posval
     if (is_negative(x)) then
       minusx := -x;
       return unsigned(minusx);
     else
       return unsigned(x);
     end if;
   end posval;
  
  function "/" (
    L, R : signed)
    return std_logic_vector is 
    variable result : std_logic_vector(L'length-1 downto 0);
    variable ignore_remainder : std_logic_vector(L'length-1 downto 0);
    variable ignore_div_by_zero : boolean;
    variable Lu, Ru : unsigned(L'range);
    variable negative_result : boolean;
  begin
    if L'length /= R'length then
      report "/ (std_logic_vector,unsigned): operands have different lengths"
        severity failure;
    end if;
    Lu := posval(L);
    Ru := posval(R);
    divu_craft(result,ignore_remainder, ignore_div_by_zero, std_logic_vector(Lu), std_logic_vector(Ru));
    negative_result := is_negative(L) xor is_negative(R);
    if (negative_result) then
      result := -signed(result);  
    end if;
    return result;
  end "/";

  function "mod" (
    L, R : unsigned)
    return std_logic is
  begin
    if L'length /= R'length then
      report "mod (std_logic,unsigned): operands have different lengths"
        severity failure;
    end if;
    return '0';
  end "mod";

  function "mod" (
    L, R : unsigned)
    return std_logic_vector is 
    variable ignore_quotient : std_logic_vector(L'length-1 downto 0);
    variable result : std_logic_vector(L'length-1 downto 0);
    variable ignore_div_by_zero : boolean;
  begin
    if L'length /= R'length then
      report "mod (std_logic_vector,unsigned): operands have different lengths"
        severity failure;
    end if;
    divu_craft(ignore_quotient,result, ignore_div_by_zero, std_logic_vector(L), std_logic_vector(R));
    return result;
  end "mod";

  function "mod" (
    L, R : signed)
    return std_logic is
  begin
    if L'length /= R'length then
      report "mod (std_logic,signed): operands have different lengths"
        severity failure;
    end if;
    return '0';
  end "mod";

  function "mod" (
    L, R : signed)
    return std_logic_vector is 
    variable ignore_quotient : std_logic_vector(L'length-1 downto 0);
    variable result : std_logic_vector(L'length-1 downto 0);
    variable ignore_div_by_zero : boolean;
    variable Lu, Ru : unsigned(L'range);
    variable negative_result : boolean;
  begin
    if L'length /= R'length then
      report "mod (std_logic_vector,signed): operands have different lengths"
        severity failure;
    end if;
    Lu := posval(L);
    Ru := posval(R);
    divu_craft(ignore_quotient,result, ignore_div_by_zero, std_logic_vector(Lu), std_logic_vector(Ru));
    negative_result := is_negative(L) xor is_negative(R);
    if (negative_result) then
      result := -signed(result);  
    end if;
    return result;
  end "mod";

  function "-" ( x : signed)
    return std_logic_vector is
    variable minusx : signed(x'range);
  begin
    minusx := -x; 
    return std_logic_vector(minusx); --fixme check this works
  end "-";

  function "-" ( x : signed)
    return std_logic is
    variable minusx_vector : std_logic_vector(x'range);
  begin    
    if x'length /= 1 then
      report "- (signed, std_logic): operand length isn't 1"
      severity failure;
    end if;
    minusx_vector := -x; 
    return minusx_vector(0); 
  end "-";


  function equal (
    -- xst fails to correctly synthesize L=R (at Nov 2004)
    -- so we have to implement equal ourselves.
  L, R : std_logic_vector)
    return std_logic is
    variable diff : boolean;
  begin
    if L'length /= R'length then
      report "notequal: operands have different lengths"
        severity failure;
    end if;
    diff := false;
    for iter in L'length -1 downto 0 loop 
      if L(iter) /= R(iter)  then
        diff := true;
      end if;
    end loop;  -- iter
    if diff then
      return '0';
    else
      return '1';
    end if;
  end equal;

  function equal (
  L, R : std_logic)
    return std_logic is
  begin
    if L = R then
      return '1';
    else
      return '0';
    end if;
  end equal;

  function notequal (
  L, R : std_logic_vector)
    return std_logic is
  begin
    if L'length /= R'length then
      report "notequal: operands have different lengths"
        severity failure;
    end if;
    return not equal(L,R);
  end notequal;

  function notequal (
  L, R : std_logic)
    return std_logic is
  begin
    if L /= R then
      return '1';
    else
      return '0';
    end if;
  end notequal;

  function sign_extend ( x : signed)
    return signed is
    begin
      if (is_negative(x)) then
        return '1'&x;
      else
        return '0'&x;
      end if;
    end sign_extend;
  


  function less_signed (
    --xst has a bug which means that signed comparisons are not handled
    --properly. This does a signed compare by hand, which is probably
    -- slightly less efficient, but it's more reliable than the current
    -- version of xst
    L, R : std_logic_vector)
    return std_logic is
    variable Ls, Rs : signed(L'length -1 downto 0);
    variable Lse, Rse : signed(L'length downto 0); --extra bit for carry
    variable difference : signed(L'length downto 0);  --extra bit for carry
  begin
    if L'length /= R'length then
      report "less_signed: operands have different lengths"
        severity failure;
    end if;
    Ls := signed(L);
    Rs := signed(R);
  -- to get a sub with carry in VHDL I seem to have to sign extend the inputs
    Lse := sign_extend(Ls);
    Rse := sign_extend(Rs);
    difference := Lse - Rse;
    if is_negative(difference) then
      return '1';
    else
      return '0';
    end if;
  end less_signed;

  function less_signed (
    L, R : std_logic)
    return std_logic is
  begin
    if (L= '1') and (R = '0') then  -- for one bit (L < R) iff L is -1 and R is 0
      return '1';
    else
      return '0';
    end if;
  end less_signed;

  function less_unsigned (
    L, R : std_logic_vector)
    return std_logic is
  begin
    if unsigned(L) < unsigned(R) then -- for one bit (L < R) iff L is 0 and R is 1
      return '1';
    else
      return '0';
    end if;
  end less_unsigned;

  function less_unsigned (
    L, R : std_logic)
    return std_logic is
  begin
    if (L='0') and (R='1') then -- for one bit (L < R) iff L is 0 and R is 1
      return '1';
    else
      return '0';
    end if;
  end less_unsigned;

  function lessequal_signed (
    L, R : std_logic_vector)
    return std_logic is
  begin
    return not greater_signed(L,R);
  end lessequal_signed;

  function lessequal_signed (
    L, R : std_logic)
    return std_logic is
  begin
    return not greater_signed(L,R);
  end lessequal_signed;

  function lessequal_unsigned (
    L, R : std_logic_vector)
    return std_logic is
  begin
    return not greater_unsigned(L,R);
  end lessequal_unsigned;


  function lessequal_unsigned (
    L, R : std_logic)
    return std_logic is
  begin
    return not greater_unsigned(L,R);
  end lessequal_unsigned;


  function greater_signed (
    L, R : std_logic_vector)
    return std_logic is
  begin
    return less_signed(R,L);
  end greater_signed;


  function greater_signed (
    L, R : std_logic)
    return std_logic is
  begin
    return less_signed(R,L);
  end greater_signed;


  function greater_unsigned (
    L, R : std_logic_vector)
    return std_logic is
  begin
    return less_unsigned(R,L);
  end greater_unsigned;


  function greater_unsigned (
    L, R : std_logic)
    return std_logic is
  begin
    return less_unsigned(R,L);
  end greater_unsigned;


  function greaterequal_signed (
    L, R : std_logic_vector)
    return std_logic is
  begin
    return not less_signed(L,R);
  end greaterequal_signed;


  function greaterequal_signed (
    L, R : std_logic)
    return std_logic is
  begin
    return not less_signed(L,R);
  end greaterequal_signed;


  function greaterequal_unsigned (
    L, R : std_logic_vector)
    return std_logic is
  begin
    return not less_unsigned(L,R);
  end greaterequal_unsigned;


  function greaterequal_unsigned (
    L, R : std_logic)
    return std_logic is
  begin
    return not less_unsigned(L,R);
  end greaterequal_unsigned;

  function bitselectassigner
-- bitassigner does the following:
-- result(x) = assignee(x) | x != bitindex
-- result(x) = assignor | x == bitindex
    (assignor : in std_logic;
    assignee : in std_logic_vector;
    bitindex : in std_logic_vector)
    return std_logic_vector is
        variable result : std_logic_vector(assignee'range);
    begin
      for iter in assignee'length -1 downto 0 loop
        if iter /= unsigned(bitindex) then
          -- note bitindex can be interpreted as an unsigned as negative
          -- values could never give a meaningful result
          result(iter) := assignee(iter);
        else
          result(iter) := assignor;
        end if;
      end loop; -- iter
      return result;
    end bitselectassigner; 
	 

  function bitselectassigner
--single bit index version for assignments to eg sc_uint<2>
-- the index is an std_logic, but the assignee is still a vector
    (assignor : in std_logic;
     assignee : in std_logic_vector; 
     bitindex : in std_logic) 
    return std_logic_vector is
        variable result : std_logic_vector(assignee'range);
    begin
      if assignee'length /= 2 then
        report "bitselectassign: bitindex is an std_logic, but assignee isn't of length 2"
          severity failure;
      end if;
      if bitindex = '1' then
        result(1) := assignor;
        result(0) := assignee(0);
      else
        result(1) := assignee(1);
        result(0) := assignor;
      end if;
      return result;
    end bitselectassigner;



  function bitselectassigner
--      single bit version for assignments to eg sc_uint<1>
    (assignor : in std_logic;
    assignee : in std_logic; 
    bitindex : in std_logic) 
    return std_logic is
    variable result : std_logic;
  begin
  if bitindex = '0'  then
    result := assignor;
  else
    result := assignee;--no change for out of in range index loop
  end if;
  return result;
  end bitselectassigner;
  
end craft_gatelibrary;
 
