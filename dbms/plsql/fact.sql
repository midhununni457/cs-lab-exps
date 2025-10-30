CREATE OR REPLACE FUNCTION factorial(num IN NUMBER) RETURN NUMBER IS
  fact NUMBER := 1;
BEGIN
  FOR i IN 1..num LOOP
    fact := fact * i;
  END LOOP;
  RETURN fact;
END;
/

DECLARE
  num NUMBER := 5;
BEGIN
  DBMS_OUTPUT.PUT_LINE('Factorial of ' || num || ' is: ' || factorial(num));
END;
/