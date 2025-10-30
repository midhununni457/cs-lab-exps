CREATE OR REPLACE FUNCTION sumofdigits(num IN NUMBER)
RETURN NUMBER IS
  total NUMBER := 0;
  og number := num;
BEGIN
  WHILE og >= 10 LOOP
    total := total + MOD(og, 10);
    og := TRUNC(og / 10);
  END LOOP;

  total := total + og;
  RETURN total;
END;
/

 
DECLARE
  num NUMBER := 1234;
BEGIN
  DBMS_OUTPUT.PUT_LINE('Sum of digits of ' || num || ' is: ' || sumofdigits(num));
END;
/
