CREATE OR REPLACE FUNCTION isprime(num IN NUMBER)
RETURN VARCHAR2 IS
BEGIN
  FOR i IN 2..FLOOR(SQRT(num)) LOOP
    IF MOD(num, i) = 0 THEN
      RETURN 'not prime';
    END IF;
  END LOOP;
  RETURN 'prime';
END;
/
 
DECLARE
  num NUMBER := 14;
BEGIN
  DBMS_OUTPUT.PUT_LINE(num || ' is ' || isprime(num));
END;
/
