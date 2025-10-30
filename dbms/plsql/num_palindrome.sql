CREATE OR REPLACE FUNCTION reverse(num IN NUMBER)
RETURN NUMBER IS
  rev NUMBER := 0;
  og number := num;
BEGIN
  WHILE og >= 10 LOOP
    rev := (rev * 10) + MOD(og, 10);
    og := TRUNC(og / 10);
  END LOOP;

  rev := (rev * 10) + og;
  RETURN rev;
END;
/

 
DECLARE
  num NUMBER := 5;
BEGIN
  IF reverse(num) = num THEN
    DBMS_OUTPUT.PUT_LINE(num || ' is a palindrome.');
  ELSE
    DBMS_OUTPUT.PUT_LINE(num || ' is not a palindrome.');
  END IF;
END;
/
